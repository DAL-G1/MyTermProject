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
	if (dotProduct(getCenter() - sph.getCenter(), getCenter() - sph.getCenter())
		< pow((getProperties()[0] + sph.getProperties()[0]),2)) {
		return true;
	}
	else
	return false;
}

void SolidSphere::collisionHandling(const SolidSphere& sph) {
	if (collisionDetection(sph)) {
		/*float v_c1 = dotProduct(getVelocity() - sph.getVelocity(), getCenter() - sph.getCenter());
		float v_c2 = dotProduct(sph.getVelocity() - getVelocity(), sph.getCenter() - getCenter());
		float c_c_sqaure = dotProduct(getCenter() - sph.getCenter(), getCenter() - sph.getCenter());
		setVelocity(
			getVelocity()[0] - (getCenter()[0] - sph.getCenter()[0]) * (v_c1 / c_c_sqaure),
			getVelocity()[1] - (getCenter()[1] - sph.getCenter()[1]) * (v_c1 / c_c_sqaure),
			getVelocity()[2] - (getCenter()[2] - sph.getCenter()[2]) * (v_c1 / c_c_sqaure)
		);
		sph.setVelocity(
			sph.getVelocity()[0] - (sph.getCenter()[0] - getCenter()[0]) * (v_c2 / c_c_sqaure),
			sph.getVelocity()[1] - (sph.getCenter()[1] - getCenter()[1]) * (v_c2 / c_c_sqaure),
			sph.getVelocity()[2] - (sph.getCenter()[2] - getCenter()[2]) * (v_c2 / c_c_sqaure)
		);*/
		setVelocity(0, 0, 0);
		

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
void SolidSphere::shootReady(float x, float y, float z) {
	setCenter(x, y, z);
}

void SolidSphere::stop(float x, float y, float z) {
	setCenter(x, y, z);
}

void SolidSphere::detectColor(std::vector<SolidSphere>& spheres, std::vector<int>& v, int c) {
	std::vector<int>::iterator iter;
	for (int i = 0; i < spheres.size() - 1; i++) {
		if (1600 >= dotProduct(spheres[i].getCenter() - getCenter(), spheres[i].getCenter() - getCenter())&&velocity[1]==0)
		{
			iter = find(v.begin(), v.end(), i);
			if (c==spheres[i].getColor()&&iter == v.end()) {//i가 v에 없다면
				std::cout << c << std::endl;
				std::cout << spheres[i].getColor() << std::endl;//왜 color에 쓰레기값이 들어가지?
				std::cout << "푸시백" << std::endl;
				v.push_back(i);
				spheres[i].detectColor(spheres,v,c);
			}
			else {}
		}
	}
}
