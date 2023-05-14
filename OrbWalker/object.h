#pragma once

class Object {
public:
    XMFLOAT3 position() const;
    float health() const;
    duration<float> acd() const;
    duration<float> ad() const;
    bool AttackableFor(Object* const) const;
    bool InRangeOf(Object* const) const;
};