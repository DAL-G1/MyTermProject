#include "SolidSphere.h"
#include <math.h>

SolidSphere::SolidSphere(float r, int sl, int st) : SolidShape3D() {
	properties.setXYZ(r, sl, st);
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	properties = sph.properties;
}

Vector3 SolidSphere::getProperties() const{
	return properties;
}

bool SolidSphere::collisionDetection(const SolidSphere& sph) {
	
	float dc = dotProduct(center - sph.center, center - sph.center);
	float r = properties.getXYZ()[0] + sph.properties.getXYZ()[0];
	if (dc <= r * r)
		return true;
	else return false;
	
}

void SolidSphere::collisionHandling(SolidSphere& sph) {
	if (collisionDetection(sph)) {
		/* Implementation: collision handling */
		float a = dotProduct(velocity - sph.velocity, center - sph.center);
		float c = dotProduct(center - sph.center, center - sph.center);
		velocity = velocity - (a / c)*(center - sph.center);
		sph.velocity = sph.velocity - (a / c)*(sph.center - center);
	}
}

void SolidSphere::draw() const {
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(properties[0], properties[1], properties[2]);
	glPopMatrix();
}