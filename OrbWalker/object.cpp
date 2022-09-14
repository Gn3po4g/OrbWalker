#include "pch.h"

float Object::DisTo(const Object *other) const {
	return position.DisTo(other->position);
}

bool Object::IsAlive() {
	return functions->IsAlive(this);
}

float Object::GetAttackDelay() {
	return functions->GetAttackDelay(this) * 1000.f;
}

float Object::GetAttackCastDelay() {
	return functions->GetAttackCastDelay(this) * 1000.f;
}