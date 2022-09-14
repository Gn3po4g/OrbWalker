#include "pch.h"

float Vector3::DisTo(const Vector3 other) const {
	const auto dx = this->x - other.x;
	const auto dy = this->y - other.y;
	const auto dz = this->z - other.z;
  return sqrtf(dx * dx + dy * dy + dz * dz);
}
