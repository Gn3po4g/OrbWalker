using namespace std;

Object *ObjList::GetLowestHealth(Object *me) const {
    static Object *previous = nullptr;
    span<Object *> obj_list(list, size);
    auto filtered = obj_list | views::filter([&me](Object *obj) {
        return Functions::IsAlive(obj) && obj->team != me->team && obj->visible && obj->targetable
               && obj->DistanceTo(me) <= me->attack_range + obj->GetBR() + me->GetBR() &&
               obj != previous;
    }) | ranges::to<vector>();
    ranges::sort(filtered, ranges::less{}, &Object::health);
    previous = filtered.empty() ? nullptr : *filtered.begin();
    return previous;
}

Object *ObjList::GetLastHit(Object *me) const {
    span<Object *> obj_list(list, size);
    auto filtered = obj_list | views::filter([&me](Object *obj) {
        return Functions::IsAlive(obj) && obj->health <= me->base_attack + me->bonus_attack && obj->team != me->team
               && obj->visible && obj->targetable &&
               obj->DistanceTo(me) <= me->attack_range + obj->GetBR() + me->GetBR();
    }) | ranges::to<vector>();
    ranges::sort(filtered, ranges::less{}, &Object::health);
    return filtered.empty() ? nullptr : *filtered.begin();
}