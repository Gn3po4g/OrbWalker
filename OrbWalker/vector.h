#pragma once

class Vector2 {
public:
	float x, y;
};

class Vector3 {
public:
	float x, y, z;

	[[nodiscard]] float DistanceTo(Vector3 other) const
	{
		const auto dx = this->x - other.x;
		const auto dy = this->y - other.y;
		const auto dz = this->z - other.z;
		return sqrtf(dx * dx + dy * dy + dz * dz);
	}
};
