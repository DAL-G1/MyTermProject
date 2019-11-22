#include "eraseThis.h"


eraseThis::eraseThis() {}
bool eraseThis::operator()(SolidSphere& sph) {
	if (sph.getErs() == true)
		return true;
	else
		return false;
}

