#pragma once

class Vector2 {
public:
	float x, y;
};

class Vector3 {
public:
	float x, y, z;

	float DisTo(Vector3) const;
};
