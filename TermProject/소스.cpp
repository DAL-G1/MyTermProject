#include <vector>
#include <iostream>
#include "SolidSphere.h"
#include "Light.h"
#include "Line.h"
#include <Windows.h>
#include<math.h>
#include"arrow.h"
#include"coordinate.h"
using namespace std;
#define WIDTH 400
#define HEIGHT 400

#define ALLWIDTH 400
#define ALLHEIGHT 600

#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2

#define READYX 0
#define READYY -250
#define READYZ 0

#define WAITINGX -155
#define WAITINGY -260
#define WAITINGZ 0

#define RAD 0.01745329



vector<SolidSphere> spheres;
Light* light;
Line* line;
Arrow shooter;
Coordinate Ballset;



int option = 0;
enum { STOP, LEFT, RIGHT, SHOOT };
vector<SolidSphere>::size_type shooting_num = 0;
/*
//back ground 위한 변수들
GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info);
GLubyte* pBytes;
BITMAPINFO* info;
GLuint textures[2];
void initTextures();
//back ground 위한 변수들

void initTextures()
{
	glGenTextures(2, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//pBytes = LoadBitmap("Hp.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 81, 82, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

void draw_background() {
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glTranslatef(-45, -57, 0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(1, 1);
			glVertex2f(-8, 8);
			glTexCoord2f(1, 1);
			glVertex2f(-8, 8);
			glTexCoord2f(1, 1);
			glVertex2f(-8, 8);
			glTexCoord2f(1, 1);
			glVertex2f(-8, 8);
		}
		glEnd();
	}
	glPopMatrix();
}
*/
void draw_characters(void* font, const char* c, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(c); i++) {
		glutBitmapCharacter(font, c[i]);
	}
}

void init() {
	light = new Light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
	light->setAmbient(0.5, 0.5, 0.5, 1.0);
	light->setDiffuse(0.7, 0.7, 0.7, 1.0);
	light->setSpecular(1.0, 1.0, 1.0, 1.0);
	
	line = new Line();
	line->setPosition1(40.0, 240.0, 0.0);
	line->setPosition2(160.0, 240.0, 0.0);
	line->setTime();
	
	srand((unsigned int)time(NULL));
	SolidSphere sphere1(20, 100, 100); //처음에 READY되어 있는 공
	sphere1.setCenter(READYX, READYY, READYZ);
	spheres.push_back(sphere1);
	
	SolidSphere sphere2(20, 100, 100); //처음에 WAITING하고 있는 공
	sphere2.setCenter(WAITINGX, WAITINGY, WAITINGZ);
	spheres.push_back(sphere2);

	shooter.setAngle(0, 0, 0);
	shooter.setMTL();
	shooter.setPosition(0, 0, 0);

	

}

void idle() {
	// collision handling
	/*for (int i = 0; i < spheres.size(); i++)
		for (int j = i + 1; j < spheres.size(); j++) {
			spheres[i].collisionHandling(spheres[j]);
			if (spheres[i].collisionDetection(spheres[j])) {
				Vector3 position=Ballset.search(spheres[i].getCenter(), spheres[j].getCenter());
				spheres[i].setCenter(position);
			}

		}*/

	/* Implementation: boundary check */

	for (int i = 0; i < spheres.size(); i++) {
		//upper
		if (spheres[i].getProperties()[0] + spheres[i].getCenter()[1] > boundaryY) {
			spheres[i].setVelocity(0,0,0);
			Vector3 center = spheres[i].getCenter();
			spheres[i].setCenter(Ballset.upper(center));
			cout << i << "번째 " << spheres[i].getCenter()[0] << ", " << spheres[i].getCenter()[1] << endl;
		}


		//right
		if (spheres[i].getProperties()[0] + spheres[i].getCenter()[0] > boundaryX) {
			spheres[i].setVelocity(-spheres[i].getVelocity()[0], spheres[i].getVelocity()[1], spheres[i].getVelocity()[2]);
		}

		//left
		if (-spheres[i].getProperties()[0] + spheres[i].getCenter()[0] < -boundaryX) {
			spheres[i].setVelocity(-spheres[i].getVelocity()[0], spheres[i].getVelocity()[1], spheres[i].getVelocity()[2]);
		}
	}
	glutPostRedisplay();
}


void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (option) {
	case RIGHT:
		if (shooter.getRotateAngle() <= 70)
			shooter.Rotate(10);
		option = STOP;
		break;
	case LEFT:
		if (shooter.getRotateAngle() >= -70)
			shooter.Rotate(-10);
		option = STOP;
		break;
	case SHOOT:
		option = STOP;
		break;
	default:
		break;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ALLWIDTH/ 2, ALLWIDTH / 2, -ALLHEIGHT/2, ALLHEIGHT / 2, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	draw_characters(GLUT_BITMAP_HELVETICA_18, "SCORE", -180, 270);
	draw_characters(GLUT_BITMAP_HELVETICA_18, "TIME", 20, 270);
	draw_characters(GLUT_BITMAP_HELVETICA_18, "NEXT", -180, -230);
	glColor3f(1.0, 1.0, 0.0);
	//string 새로 지정하여  String a = score+ "points"; 한 후 draw_characters에 넣어주기
	draw_characters(GLUT_BITMAP_HELVETICA_18, "0 points", -110, 240);
	line->timeRun(); //SolidShpere의 draw+move 합친것
	//키보드 입력 시 실행하는 것에 setTime(); 함수 넣어주면 키보드 입력시 마다 원래대로 돌아옴

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	light->draw();

	/*int a = 1;
	auto& b = a;*/
	for (auto& sph : spheres)
		//위와 같은 이유로, for (auto& sph : spheres)를 사용하면 안됨. 값의 복사가 일어나기떄문
		//따라서, &를 붙여줘서 복사자를 사용해야함.
	{
		sph.draw();
		sph.move();
	}
	shooter.draw();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27://esc
		exit(0);
	
	case 32://space Bar
	{	cout << "shoot" << endl;
		option = SHOOT;
		line->setTime();

		//spheres[shooting_num].setVelocity(sin(shooter.getRotateAngle() * RAD), cos(shooter.getRotateAngle() * RAD), 0);
		spheres.back().setVelocity(sin(shooter.getRotateAngle() * RAD), cos(shooter.getRotateAngle() * RAD), 0);
		shooting_num = shooting_num + 1;
		spheres.back().shootReady(READYX, READYY, READYZ);
		SolidSphere new_sphere(20, 100, 100); //대기하는 곳에 만들어지는 공
		new_sphere.setCenter(WAITINGX, WAITINGY, WAITINGZ);
		spheres.push_back(new_sphere); 
	}
	default:
		break;
	}
}
void processSpecialKeys(int key, int x, int y) {
	cout << "pressed " << key << endl;
	switch (key) {
	case GLUT_KEY_LEFT:
		glutPostRedisplay();
		cout << "left" << endl;

		option = LEFT;
		break;
	case GLUT_KEY_RIGHT:
		glutPostRedisplay();
		cout << "right" << endl;

		option = RIGHT;
		break;
	default:
		break;
	}

}

int main(int argc, char** argv) {
	// init GLUT and create Window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(400, 50);
	glutInitWindowSize(ALLWIDTH, ALLHEIGHT);
	glutCreateWindow("Move spheres and handle collisions");
	init();

	// register callbacks
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
