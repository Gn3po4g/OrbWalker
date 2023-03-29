#include "pch.h"

namespace Functions {
    fnPrintChat PrintChat{};
    fnIssueOrder IssueOrder{};
    fnGetAttackCastDelay GetAttackCastDelay{};
    fnGetAttackDelay GetAttackDelay{};
    fnIsAlive IsAlive{};
    fnGetRadius GetRadius{};

    void Initialize() {
        PrintChat = (fnPrintChat) Offsets::oPrintChat;
        IssueOrder = (fnIssueOrder) Offsets::oIssueOrder;
        GetAttackCastDelay = (fnGetAttackCastDelay) Offsets::oGetAttackCastDelay;
        GetAttackDelay = (fnGetAttackDelay) Offsets::oGetAttackDelay;
        IsAlive = (fnIsAlive) Offsets::oIsAlive;
        GetRadius = (fnGetRadius) Offsets::oGetRadius;
    }

    bool IsChatOpen() {
        return *(bool *) (*(uintptr_t *) Offsets::oChatClient + 0x820);
    }

    bool IsLeagueInBackground() {
        return *(bool *) (*(uintptr_t *) Offsets::oHudInstance + 0x69);
    }

    uint64_t GetGameTime() {
        return static_cast<uint64_t>(*(float *) Offsets::oGameTime * 1000);
    }

}