#pragma once

class Object {
public:
    PAD(0x34);
    int team;             //0x34
    PAD(0x1A4);
    XMFLOAT3 position;    //0x1DC
    PAD(0x8C);
    bool visible;         //0x274
    PAD(0xA8F);
    bool targetable;      //0xD04
    PAD(0x177);
    float health;         //0xE7C
    PAD(0x454);
    float bonus_attack;   //0x12D4
    PAD(0x84);
    float base_attack;    //0x135C
    PAD(0x44);
    float attack_range;   //0x13A4
    PAD(0x864);
    XMFLOAT3 direction;   //0x1C0C

    float DistanceTo(Object *) const;

    bool IsFacing(Object*) const;

    double GetBR() const;

    uint32_t GetACD() const;

    uint32_t GetAD() const;
};