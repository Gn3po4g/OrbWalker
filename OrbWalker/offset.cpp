#include "stdafx.hpp"

namespace offset {
	using namespace std;

	uintptr_t
		oGameTime,
		oLocalPlayer,
		oHeroList,
		oTurretList,
		oMinionList,
		oChatClient,
		oHudInstance,
		oViewPort,

		oPrintChat,
		oWorldToScreen,
		oIssueOrder,
		oIssueMove,
		oAttackDelay,
		oAttackWindup,
		oIsAlive,
		oBonusRadius;

	struct {
		uintptr_t& reference;
		string pattern;
		uintptr_t addition;
	} sig2scan[] = {
		{oGameTime, "F3 0F 5C 35 ? ? ? ? 0F 28 F8", 4},
		{oLocalPlayer, "48 8B 05 ? ? ? ? 4C 8B D2 4C 8B C1", 3},
		{oHeroList, "48 8B 05 ? ? ? ? 4C 8B 78 08", 3},
		{oTurretList, "48 8B 1D ? ? ? ? 48 8B 5B 28 48 85 DB", 3},
		{oMinionList, "48 8B 0D ? ? ? ? E8 ? ? ? ? EB 07", 3},
		{oChatClient, "41 FF D1 48 8B 0D ? ? ? ?", 6},
		{oHudInstance, "48 8B 0D ? ? ? ? 8B 57 10", 3},
		{oViewPort, "48 8B 3D ? ? ? ? FF 90 ? ? ? ?", 3},

		{oPrintChat, "E8 ? ? ? ? 4C 8B C3 B2 01", 1},
		{oWorldToScreen, "E8 ? ? ? ? F3 0F 10 44 24 ? 49 8B CE", 1},
		{oIssueOrder, "45 33 C0 E8 ? ? ? ? 48 83 C4 48", 4},
		{oIssueMove, "44 88 7C 24 ? E8 ? ? ? ? EB 1D", 6},
		{oAttackDelay, "E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?", 1},
		{oAttackWindup, "89 83 ? ? ? ? E8 ? ? ? ? 48 8B CE", 7},
		{oIsAlive, "48 8B D8 E8 ? ? ? ? 84 C0 74 35", 4},
		{oBonusRadius, "E8 ? ? ? ? 0F 28 F8 48 8B D3 48 8B CE", 1}
	};

	vector<pair<uint8_t, bool>> pattern2bytes(const string& input) {
		vector<pair<uint8_t, bool>> result;
		stringstream ss(input);
		string token;
		while (getline(ss, token, ' ')) {
			if (token == "?") {
				result.emplace_back(0, false);
			}
			else {
				int value = stoi(token, nullptr, 16);
				result.emplace_back(value, true);
			}
		}
		return result;
	}

	uintptr_t FindAddress(const string& pattern) {
		auto byteArr = pattern2bytes(pattern);
		MODULEINFO moduleInfo{};
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &moduleInfo, sizeof(MODULEINFO));
		const auto begin = (uint8_t*)moduleInfo.lpBaseOfDll;
		const auto size = moduleInfo.SizeOfImage;
		MEMORY_BASIC_INFORMATION mbi{};
		for (auto* cur = begin; cur < begin + size; cur += mbi.RegionSize) {
			if (!VirtualQuery(cur, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;
			auto startAddr = (uint8_t*)mbi.BaseAddress, endAddr = startAddr + mbi.RegionSize;
			auto result = search(startAddr, endAddr, byteArr.begin(), byteArr.end(),
				[](uint8_t a, pair<uint8_t, bool> b) {
					return !b.second || a == b.first;
				});
			if (result != endAddr) return (uintptr_t)result;
		}
		return 0;
	}

	void Init() {
		for (auto& [what, pattern, addition] : sig2scan) {
			auto address = FindAddress(pattern);
			while (!address) {
				//MessageBox(nullptr, (string("Unable to find ") + pattern).data(), "", MB_OK);
				this_thread::sleep_for(100ms);
				address = FindAddress(pattern);
			}
			address += addition;
			what = address + 4 + *(int32_t*)address;
		}
	}
}