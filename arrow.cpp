#include"arrow.h"

Arrow::Arrow() {
	cone[0] = 10; cone[1] = 20;
	cylinder[0] = 5; cylinder[1] = 30;

	RotateAngle = 0;
}

void Arrow::setMTL() {
	mtl.setEmission(0.1, 0.1, 0.1, 1);
	mtl.setAmbient(0.19225, 0.19225, 0.19225, 1);
	mtl.setDiffuse(0.50754, 0.50754, 0.50754, 1);
	mtl.setSpecular(0.508273, 0.508273, 0.508273, 1);
	mtl.setShininess(51.2);
}

void Arrow::setAngle(float x, float y, float z) {
	angle.setXYZ(x, y, z);
}

void Arrow::setPosition(float x, float y, float z) {
	position.setXYZ(x, y, z);
}

void Arrow::Rotate(int angle) {
	RotateAngle += angle;
}

void Arrow::draw() const {
	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT,GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());


	/*glRotatef(-90, 1, 0, 0);
	glRotatef(RotateAngle, 0, 1, 0);
	glTranslatef(0, 0, 50);
	glTranslatef(0, 0, -120);
	glutSolidCone(15, 25, 100, 100);*/

	glTranslatef(0, -250, 0);
	
	glRotatef(-90, 1, 0, 0);
	glRotatef(RotateAngle, 0, 1, 0);
	glTranslatef(0, 0, 40);
	glutSolidCone(14, 23, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());
	/*glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(RotateAngle, 0, 1, 0);
	glTranslatef(0, 0, -120);
	gluCylinder(obj, 7,7, 50, 100, 100);*/

	glTranslatef(0, -250, 0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(RotateAngle, 0, 1, 0);
	glTranslatef(0, 0, -40);
	gluCylinder(obj, 6, 6, 80, 100, 100);
	glPopMatrix();

	
}