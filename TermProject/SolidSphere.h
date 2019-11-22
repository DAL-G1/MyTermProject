#pragma once
#include "coordinate.h"
#include "SolidShape3D.h"
#include <vector>

class SolidSphere : public SolidShape3D
{
public:
	SolidSphere() {}
	SolidSphere(float r, int sl, int st);
	SolidSphere(const SolidSphere& sph);
	Vector3 getProperties() const;
	bool collisionDetection(const SolidSphere& sph);
	void collisionHandling(const SolidSphere& sph);
	void draw() const;
	void shootReady(float x, float y, float z);
	void stop(float x, float y, float z);

private:
	Vector3 properties;
};

