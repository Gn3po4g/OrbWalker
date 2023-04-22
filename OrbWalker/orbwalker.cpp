#include "pch.h"

namespace OrbWalker
{
    Object* me{};
    ObjList* heroes{};
    ObjList* minions{};
    ObjList* turrets{};
    ObjList* inhibitors{};
    uintptr_t hud_input{};
    XMFLOAT3* mouse_pos{};
    bool* p_aco;

    void Initialize(){
        me = *(Object**)offsets.oLocalPlayer;
        heroes = *(ObjList**)offsets.oHeroList;
        turrets = *(ObjList**)offsets.oTurretList;
        ////inhibitors = *(ObjList**)offsets.oInhibitorList;
        minions = *(ObjList**)offsets.oMinionList;
        hud_input = *(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x48);
        mouse_pos = (XMFLOAT3*)(*(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x28) + 0x20);
        p_aco = (bool*)(*(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x60) + 0x30);
    }

    Object* get_target(const Type type){
        Object* target = nullptr;
        switch (type)
        {
        case Type::AutoKite:
            target = heroes->get_lowest_health(me);
            break;
        case Type::CleanLane:
            ((target = minions->get_lowest_health(me))) || ((target = turrets->get_lowest_health(me)));
            break;
        case Type::LastHit:
            target = minions->get_last_hit(me);
            break;
        default: break;
        }
        return target;
    }

    struct Timer
    {
        float last_attack_time{};
        float last_act_time{};
        float last_move_time{};
    };

    void execute(const Type type){
        static Timer timer{};
        static bool is_turning_around = false;
        const float now = Functions::GetGameTime();
        if (now < timer.last_act_time + 0.033f) return;
        timer.last_act_time = now;
        if (const auto target = get_target(type); target &&
            (now >= timer.last_attack_time + me->ad() || is_turning_around))
        {
            if (!is_turning_around) timer.last_attack_time = now;
            is_turning_around = true;
            const auto pos = Renderer::WorldToScreen(target->position());
            Functions::IssueOrder(hud_input, 0, 0, 1, pos.x, pos.y, 1);
            if (me->IsFacing(target))
            {
                is_turning_around = false;
                timer.last_move_time = now + me->acd();
            }
        }
        else if (now >= timer.last_move_time)
        {
            const auto pos = Renderer::WorldToScreen(*mouse_pos);
            Functions::IssueOrder(hud_input, 0, 0, 0, pos.x, pos.y, 0);
        }
    }
}
