#pragma once
#include "SolidSphere.h"

class eraseThis {
public:
	eraseThis();
	bool operator()(const SolidSphere& sph);
};