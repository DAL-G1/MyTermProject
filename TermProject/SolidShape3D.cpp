#include "SolidShape3D.h"

SolidShape3D::SolidShape3D() {
	center.setXYZ(0, 0, 0);
	velocity.setXYZ(0, 0, 0);
	setErs(false);
	setMTL();
}

SolidShape3D::SolidShape3D(const SolidShape3D& sh3d) {
	setCenter(sh3d.center);
	setVelocity(sh3d.velocity);
	setErs(sh3d.ers);
	mtl.setMTL(sh3d.mtl);
	setColor(sh3d.color);
}

void SolidShape3D::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void SolidShape3D::setCenter(const Vector3& c) {
	center = c;
}

Vector3 SolidShape3D::getCenter() const {
	return center;
}

void SolidShape3D::setVelocity(float x, float y, float z) {
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;
}

void SolidShape3D::setVelocity(const Vector3& v) {
	velocity = v;
}

Vector3 SolidShape3D::getVelocity() const {
	return velocity;
}

void SolidShape3D::move() {
	center = center + (3)*velocity;
}
void SolidShape3D::setCyan(){
	mtl.setAmbient(0.0, 0.05, 0.05, 1);
	mtl.setDiffuse(0.4, 0.5, 0.5, 1);
	mtl.setSpecular(0.04, 0.7, 0.7, 1);
	mtl.setEmission(0.1, 0.1, 0.06, 1);
	mtl.setShininess(10);
}
void SolidShape3D::setGreen() {
	mtl.setAmbient(0.0, 0.05, 0.0, 1);
	mtl.setDiffuse(0.4, 0.5, 0.4, 1);
	mtl.setSpecular(0.04, 0.7, 0.04, 1);
	mtl.setEmission(0.1, 0.1, 0.06, 1);
	mtl.setShininess(10);
}
void SolidShape3D::setRed() {
	mtl.setAmbient(0.05, 0.0, 0.0, 1);
	mtl.setDiffuse(0.5, 0.4, 0.4, 1);
	mtl.setSpecular(0.7, 0.04, 0.04, 1);
	mtl.setEmission(0.1, 0.1, 0.06, 1);
	mtl.setShininess(10);
}
void SolidShape3D::setYellow() {
	mtl.setAmbient(0.05, 0.05, 0.0, 1);
	mtl.setDiffuse(0.5, 0.5, 0.4, 1);
	mtl.setSpecular(0.7, 0.7, 0.04, 1);
	mtl.setEmission(0.1, 0.1, 0.1, 1);
	mtl.setShininess(10);
}
int SolidShape3D::getColor() {
	return color;
}
void SolidShape3D::setColor(int c) {
	color = c;
}
bool SolidShape3D::getErs() {
	return ers;
}
void SolidShape3D::setErs(bool e) {
	ers = e;
}

void SolidShape3D::setMTL() {
	//여기서 랜덤함수 돌리기
	int c = (int)rand() % 4;
	switch (c)
	{
	case RED:
		color = RED;
		setRed();
		break;
	case GREEN:
		color = GREEN;
		setGreen();
		break;
	case CYAN:
		color = CYAN;
		setCyan();
		break;
	case YELLOW:
		color = YELLOW;
		setYellow();
		break;
		}


}