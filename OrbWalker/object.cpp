#include "pch.h"

float Object::DisTo(const Object *other) const {
	return position.DisTo(other->position);
}

bool Object::IsAlive() {
	return functions->IsAlive(this);
}

int Object::GetAttackDelayTicks() {
	return static_cast<int>(functions->GetAttackDelay(this) * 1000.f);
}

int Object::GetAttackCastDelayTicks() {
	return static_cast<int>(functions->GetAttackCastDelay(this) * 1000.f);
}