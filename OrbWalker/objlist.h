#pragma once

class ObjList {
	PAD(0x4);
	Object** list;
	int size;

	Object* GetBestTargetFor(const Object*) const;
};
