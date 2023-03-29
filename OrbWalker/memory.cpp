#include "pch.h"

using namespace std;

namespace Offsets {
    uintptr_t oGameTime{};
    uintptr_t oChatClient{};
    uintptr_t oNetClient{};
    uintptr_t oLocalPlayer{};
    uintptr_t oHudInstance{};
    uintptr_t oViewProjMatrices{};
    uintptr_t oHeroList{};
    uintptr_t oTurretList;
    uintptr_t oInhibitorList;
    uintptr_t oMinionList{};
    uintptr_t oAttackableList;

    uintptr_t oGetPing{};
    uintptr_t oPrintChat{};
    uintptr_t oIssueOrder{};
    uintptr_t oGetAttackDelay{};
    uintptr_t oGetAttackCastDelay{};
    uintptr_t oIsAlive{};
    uintptr_t oGetRadius{};
}

namespace Memory {
    tuple<uintptr_t *, string, bool> sig_to_scan[] = {
            {&Offsets::oGameTime,           "F3 0F 11 05 ? ? ? ? 8B 49 08",                           true},
            {&Offsets::oChatClient,         "8B 0D ? ? ? ? 8A D8 85 C9",                              true},
            {&Offsets::oLocalPlayer,        "8B 3D ? ? ? ? 3B F7 75 09",                              true},
            {&Offsets::oHudInstance,        "8B 0D ? ? ? ? FF 77 08 8B 49 14",                        true},
            {&Offsets::oViewProjMatrices,   "B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ?", true},
            {&Offsets::oHeroList,           "A1 ? ? ? ? 53 55 33 DB",                                 true},
            {&Offsets::oTurretList,         "8B 35 ? ? ? ? 8B 76 18",                                 true},
            //{ &Offsets::oInhibitorList, "A1 ? ? ? ? 53 55 56 8B 70 04 8B 40 08", true },
            {&Offsets::oMinionList,         "8B 0D ? ? ? ? E8 ? ? ? ? EB 09",                         true},
//            {&Offsets::oAttackableList,     "8B 15 ? ? ? ? 56 57 8B 7A 04",                           true},

            {&Offsets::oPrintChat,          "E8 ? ? ? ? 8B 4C 24 20 C6 47 0D 01",                     false},
            {&Offsets::oIssueOrder,         "E8 ? ? ? ? 84 C0 74 0B F3 0F 10 44 24 ?",                false},
            {&Offsets::oGetAttackDelay,     "E8 ? ? ? ? D8 44 24 14 83 C4 04",                        false},
            {&Offsets::oGetAttackCastDelay, "E8 ? ? ? ? D9 9E ? ? ? ? 57",                            false},
            {&Offsets::oIsAlive,            "E8 ? ? ? ? 84 C0 74 2A 8D 8F ? ? ? ?",                   false},
            {&Offsets::oGetRadius,          "E8 ? ? ? ? D8 44 24 0C 8B 7C 24 18",                     false}
    };

    lm_module_t GameModule{};
    int *GameState{};

    uintptr_t FindAddress(string &pattern) {
        lm_page_t page;
        page.end = GameModule.base;
        while (page.end < GameModule.end && LM_GetPage(page.end, &page)) {
            if (page.prot & LM_PROT_R) {
                auto scansize = page.size - ranges::distance(pattern | views::split(' '));
                if (auto address = LM_SigScan(pattern.data(), page.base, scansize);
                        address != LM_ADDRESS_BAD) {
                    return address;
                }
            }
        }
        return LM_ADDRESS_BAD;
    }

    void Initialize() {
        LM_FindModule(string("League of Legends.exe").data(), &GameModule);
        while (true) {
            if (!GameState) {
                this_thread::sleep_for(1s);
                Scan(true);
            } else if (*GameState != 2) {
                this_thread::sleep_for(500ms);
            } else {
                this_thread::sleep_for(500ms);
                Scan(false);
                break;
            }
        }
    }

    void Scan(const bool init) {
        if (init) {
            string pattern = "A1 ? ? ? ? 68 ? ? ? ? 8B 70 08 E8 ? ? ? ?";
            if (auto address = FindAddress(pattern); address == LM_ADDRESS_BAD) {
                MessageBox(nullptr, "Failed to find GameState", "WARN", MB_OK | MB_ICONWARNING);
            } else {
                auto oGameState = *(uintptr_t *) (address + pattern.find_first_of('?') / 3);
                GameState = (int *) (*(uintptr_t *) oGameState + 0x8);
            }
        } else {
            for (auto &[offset, pattern, read]: sig_to_scan) {
                if (auto address = FindAddress(pattern); address == LM_ADDRESS_BAD) {
                    MessageBox(nullptr, ("Failed to find pattern: " + pattern).c_str(), "WARN", MB_OK | MB_ICONWARNING);
                } else {
                    *offset = read ? *(uintptr_t *) (address + pattern.find_first_of('?') / 3)
                                   : address + *(uintptr_t *) (address + 1) + 5;
                }
            }
        }
    }
}