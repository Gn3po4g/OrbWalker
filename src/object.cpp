float Object::DistanceTo(const Object *other) const {
    float dx = position.x - other->position.x;
    float dy = position.y - other->position.y;
    float dz = position.z - other->position.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

double Object::GetBR() const {
    return Functions::GetRadius(this);
}

uint32_t Object::GetACD() const {
    return static_cast<uint32_t>(Functions::GetAttackCastDelay(this) * 1000) + 100;
}

uint32_t Object::GetAD() const {
    return static_cast<uint32_t>(Functions::GetAttackDelay(this) * 1000) + 20;
}
