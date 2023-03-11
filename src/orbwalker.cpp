namespace OrbWalker {
    ObjList *turrets{};
    ObjList *inhibitors{};
    uintptr_t HUDInput{};
    XMFLOAT3 *MousePos{};
    Object *me{};
    ObjList *heroes{};
    ObjList *minions{};
    ObjList *attackables{};
    uint64_t lastAttackTime{};
    uint64_t lastMoveTime{};
    bool *pAttackChampionsOnly;

    void Initialize() {
        me = *(Object **) (Offsets::oLocalPlayer);
        heroes = *(ObjList **) (Offsets::oHeroList);
//        attackables = *reinterpret_cast<ObjList**>(Offsets::oAttackableList);
        turrets = *(ObjList **) (Offsets::oTurretList);
        //inhibitors = *(ObjList**)Offsets::oInhibitorList;
        minions = *(ObjList **) (Offsets::oMinionList);
        HUDInput = *(uintptr_t *) (*(uintptr_t *) Offsets::oHudInstance + 0x24);
        MousePos = (XMFLOAT3 *) (*(uintptr_t *) (*(uintptr_t *) Offsets::oHudInstance + 0x14) + 0x1C);
        pAttackChampionsOnly = (bool *) (*(::uintptr_t *) (*(::uintptr_t *) Offsets::oHudInstance + 0x30) + 0x20);
        Functions::GetGameTime();
    }

    Object *GetTarget(Type type) {
        switch (type) {
            case Type::AutoKite:
                return heroes->GetLowestHealth(me);
            case Type::CleanLane:
                if (auto target = minions->GetLowestHealth(me);target) {
                    return target;
                } else {
                    return turrets->GetLowestHealth(me);
                }
            case Type::LastHit:
                return minions->GetLastHit(me);
            default:
                return nullptr;
        }
    }

    void Execute(Type type) {
//            Functions::PrintChat(Offsets::oChatClient, (std::to_string(me->GetAD())+'\t'+std::to_string(me->GetACD())).data(), 0xFFFFFE);
        //    Functions::PrintChat(Offsets::oChatClient, std::to_string(Functions::GetPing(Offsets::oNetClient)).data(), 0xFFFFFE);
        if (auto target = GetTarget(type); target && Functions::GetGameTime() >= lastAttackTime + me->GetAD()) {
            lastAttackTime = Functions::GetGameTime();
            /*if (type == Type::CleanLane) {
                const auto pos = Renderer::WorldToScreen(me->position);
                Functions::IssueOrder(HUDInput, 0, 1, 1, pos.x, pos.y, 0);
            } else */{
                const auto pos = Renderer::WorldToScreen(target->position);
                Functions::IssueOrder(HUDInput, 0, 1, 0, pos.x, pos.y, 1);
            }
        } else if (Functions::GetGameTime() >= lastAttackTime + me->GetACD() &&
                   Functions::GetGameTime() >= lastMoveTime + 50) {
            lastMoveTime = Functions::GetGameTime();
            const auto pos = Renderer::WorldToScreen(*MousePos);
            Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
        }
    }
}