#pragma once

class Object {
public:
    int32_t team();
    XMFLOAT3 position();
    bool visible();
    bool targetable();
    float health();
    float base_attack();
    float bonus_attack();
    float attack_range();
    float br() const;
    float acd() const;
    float ad() const;

    float DistanceTo(Object *);
    bool IsFacing(Object*);
};