module;
#include <cstdint>
#include <string>
#include "../Libmem/libmem.h"
#include <ranges>
#include <thread>
module Offset;

using namespace std;

struct {
	uintptr_t* what;
	string pattern;
	uintptr_t addition;
} sig_to_scan[] = {
		{&offset.oGameTime,					"F3 0F 5C 35 ? ? ? ? 0F 28 F8", 4}, //ok
		{&offset.oLocalPlayer,			"48 8B 05 ? ? ? ? 4C 8B D2 4C 8B C1", 3}, //ok
		{&offset.oViewProjMatrices, "48 83 EC 28 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 28", 7}, //ok
		{&offset.oHeroList,					"48 8B 0D ? ? ? ? 48 8D 54 24 ? 33 C0 89 44 24 24", 3}, //ok
		{&offset.oTurretList,				"48 8B 1D ? ? ? ? 48 8B 5B 28 48 85 DB 74 2D", 3}, //ok
		//{ &offsets.oInhibitorList, "A1 ? ? ? ? 53 55 56 8B 70 04 8B 40 08", true },
		{&offset.oMinionList,				"48 8B 0D ? ? ? ? E8 ? ? ? ? EB 07", 3}, //ok
		{&offset.oChatClient,				"41 FF D1 48 8B 0D ? ? ? ?", 6},
		{&offset.oHudInstance,			"48 8B 0D ? ? ? ? 8B 57 10", 3}, //ok

		{&offset.oPrintChat,				"E8 ? ? ? ? 4C 8B C3 B2 01", 1},
		{&offset.oIssueOrder,				"45 33 C0 E8 ? ? ? ? 48 83 C4 48", 4}, //ok
		{&offset.oAttackDelay,			"E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?", 1}, //ok
		{&offset.oAttackCastDelay,	"89 83 ? ? ? ? E8 ? ? ? ? 48 8B CE", 7}, //ok
		{&offset.oIsAlive,					"48 8B D8 E8 ? ? ? ? 84 C0 74 35", 4}, //ok
		{&offset.oBonusRadius,			"E8 ? ? ? ? 0F 28 F8 48 8B D3 48 8B CE", 1} //ok
};

lm_module_t GameModule{};

uintptr_t FindAddress(string& pattern) {
	lm_page_t page{};
	page.end = GameModule.base;
	while (page.end < GameModule.end && LM_GetPage(page.end, &page)) {
		if (page.prot & LM_PROT_R) {
			const auto scan_size = page.size - ranges::distance(pattern | views::split(' '));
			if (const auto address = LM_SigScan(pattern.data(), page.base, scan_size);
				address != LM_ADDRESS_BAD) {
				return address;
			}
		}
	}
	return LM_ADDRESS_BAD;
}

void InitOffest() {
	LM_FindModule(string("League of Legends.exe").data(), &GameModule);
	for (auto& [what, pattern, addition] : sig_to_scan) {
		uintptr_t address = FindAddress(pattern);
		while (address == LM_ADDRESS_BAD) {
			//MessageBox(nullptr, (string("Unable to find ") + pattern).data(), "", MB_OK);
			this_thread::sleep_for(100ms);
			address = FindAddress(pattern);
		}
		*what = address + addition + 4 + *(int32_t*)(address + addition);
	}
}