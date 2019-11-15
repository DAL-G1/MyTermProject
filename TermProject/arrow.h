#pragma once

#include <GL/glut.h>
#include "Material.h"
#include "Vector3.h"
#include <math.h>


class Arrow {
public:
	Arrow();
	void draw() const;
	void setAngle(float x, float y, float z);
	void setMTL();
	void setPosition(float x, float y, float z);
	void Rotate(int);
	float getRotateAngle() { return RotateAngle; }
	GLUquadricObj * obj = gluNewQuadric();
	
protected:
	Material mtl;
	Vector3 angle;
	Vector3 position;
	float RotateAngle;
	float cone[2];
	float cylinder[2];


};




