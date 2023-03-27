#pragma once

namespace Offsets {
//    extern uintptr_t oGameTime;
    extern uintptr_t oChatClient;
    extern uintptr_t oLocalPlayer;
    extern uintptr_t oHudInstance;
    extern uintptr_t oViewProjMatrices;
    extern uintptr_t oHeroList;
    extern uintptr_t oTurretList;
    extern uintptr_t oInhibitorList;
    extern uintptr_t oMinionList;
    extern uintptr_t oAttackableList;

    extern uintptr_t oPrintChat;
    extern uintptr_t oIssueOrder;
    extern uintptr_t oGetAttackDelay;
    extern uintptr_t oGetAttackCastDelay;
    extern uintptr_t oIsAlive;
    extern uintptr_t oGetRadius;
}

namespace Memory {
    void Initialize();

    void Scan(bool);
};
