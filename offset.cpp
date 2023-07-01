module;

#include <Windows.h>

module Offset;

import std.core;

using namespace std;

struct {
		uintptr_t *what;
		string pattern;
		uintptr_t addition;
} sig_to_scan[] = {
		{&offset.oGameTime,         "F3 0F 5C 35 ? ? ? ? 0F 28 F8",          4}, //ok
		{&offset.oLocalPlayer,      "48 8B 05 ? ? ? ? 4C 8B D2 4C 8B C1",    3}, //ok
		{&offset.oViewProjMatrices, "48 8D 0D ? ? ? ? 0F 10 00",             3}, //ok
		{&offset.oHeroList,         "48 8B 05 ? ? ? ? 4C 8B 78 08",          3}, //ok
		{&offset.oTurretList,       "48 8B 1D ? ? ? ? 48 8B 5B 28 48 85 DB", 3}, //ok
		//{ &offsets.oInhibitorList, "A1 ? ? ? ? 53 55 56 8B 70 04 8B 40 08", true },
		{&offset.oMinionList,       "48 8B 0D ? ? ? ? E8 ? ? ? ? EB 07",     3}, //ok
		{&offset.oChatClient,       "41 FF D1 48 8B 0D ? ? ? ?",             6},
		{&offset.oHudInstance,      "48 8B 0D ? ? ? ? 8B 57 10",             3}, //ok

		{&offset.oPrintChat,        "E8 ? ? ? ? 4C 8B C3 B2 01",             1},
		{&offset.oIssueOrder,       "45 33 C0 E8 ? ? ? ? 48 83 C4 48",       4}, //ok
		{&offset.oAttackDelay,      "E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?",  1}, //ok
		{&offset.oAttackCastDelay,  "89 83 ? ? ? ? E8 ? ? ? ? 48 8B CE",     7}, //ok
		{&offset.oIsAlive,          "48 8B D8 E8 ? ? ? ? 84 C0 74 35",       4}, //ok
		{&offset.oBonusRadius,      "E8 ? ? ? ? 0F 28 F8 48 8B D3 48 8B CE", 1} //ok
};

vector <pair<uint8_t, bool>> convertStringToVector(const string &input) {
	vector <pair<uint8_t, bool>> result;
	stringstream ss(input);
	string token;
	while (getline(ss, token, ' ')) {
		if (token == "?") {
			result.emplace_back(0, false);
		} else {
			int value = stoi(token, nullptr, 16);
			result.emplace_back(value, true);
		}
	}
	return result;
}

uintptr_t FindAddress(string &pattern) {
	auto moduleAddr = GetModuleHandle(nullptr);
	MEMORY_BASIC_INFORMATION memInfo;
	auto *baseAddress = (uint8_t *) moduleAddr;
	auto patternArr = convertStringToVector(pattern);
	while (VirtualQuery(baseAddress, &memInfo, sizeof(memInfo)) != 0) {
		if (memInfo.Protect != PAGE_NOACCESS) {
			auto startAddr = (uint8_t *) memInfo.BaseAddress, endAddr = startAddr + memInfo.RegionSize;
			auto result = search(startAddr, endAddr, patternArr.begin(), patternArr.end(),
			                     [](uint8_t a, pair<uint8_t, bool> b) {
					                     return !b.second || a == b.first;
			                     });
			if (result != endAddr) {
				return (uintptr_t) result;
			}
		}
		baseAddress = baseAddress + memInfo.RegionSize;
	}
	return 0;
}

void InitOffset() {
	for (auto &[what, pattern, addition]: sig_to_scan) {
		uintptr_t address = FindAddress(pattern);
		while (!address) {
			//MessageBox(nullptr, (string("Unable to find ") + pattern).data(), "", MB_OK);
			this_thread::sleep_for(100ms);
			address = FindAddress(pattern);
		}
		*what = address + addition + 4 + *(int32_t * )(address + addition);
	}
}