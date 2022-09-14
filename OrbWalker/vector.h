#pragma once

class Vector3 {
public:
	float x, y, z;

	[[nodiscard]] float DisTo(Vector3) const;
};
