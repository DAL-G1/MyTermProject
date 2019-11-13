#include "Line.h"

using namespace std;

Line::Line() {};
void Line::setPosition1(float x, float y, float z) {
	position1.setXYZ(x, y, z);
}
void Line::setPosition2(float x, float y, float z) {
	position2.setXYZ(x, y, z);
}
Vector3 Line::getPosition1()const {
	return position1;
};
Vector3 Line::getPosition2()const {
	return position2;
};
void Line::setTime() {
	itime = time(0);
}
void Line::timeRun() {
	pass_time = time(0) - itime;
	glColor3f(1, 0, 0);
	glLineWidth(10.0f);
	glEnable(GL_LINE);
	glBegin(GL_LINES);
		glVertex2f(position1.getXYZ()[0], position1.getXYZ()[1]);
		glVertex2f(position2.getXYZ()[0] - 4 * pass_time, position2.getXYZ()[1]);
	glEnd();
}
