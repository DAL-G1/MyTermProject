#include <vector>
#include<iostream>
#include "SolidSphere.h"
#include "Light.h"
#include"arrow.h"
#include"Line.h"
#include <Windows.h>
#include<math.h>


using namespace std;

#define WIDTH 400
#define HEIGHT 400

#define ALLWIDTH 400
#define ALLHEIGHT 600

#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2

#define RAD 0.01745329

vector<SolidSphere> spheres;
Light* light;
Line* line;
Arrow shooter;


int option = 0;
enum {STOP,LEFT,RIGHT,SHOOT};

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

	SolidSphere sphere1(15, 100, 100);
	sphere1.setCenter(0, -250, 0);
	sphere1.setVelocity(0, 0, 0);
	spheres.push_back(sphere1);

	shooter.setAngle(0, 0, 0);
	shooter.setMTL();
	shooter.setPosition(0, 0, 0);
}

void idle() {
	// collision handling
	for (int i = 0; i < spheres.size(); i++)
		for (int j = i + 1; j < spheres.size(); j++)
			spheres[i].collisionHandling(spheres[j]);
	
	/* Implementation: boundary check */
	
	for (int i = 0; i < spheres.size(); i++) {
		if (spheres[i].getCenter()[0] + spheres[i].getProperties()[0] > WIDTH / 2) {
			Vector3 v = spheres[i].getVelocity();
			v.setXYZ(-v[0], v[1], v[2]);
			spheres[i].setVelocity(v);
		}
		if (spheres[i].getCenter()[0] - spheres[i].getProperties()[0] < -WIDTH / 2) {
			Vector3 v = spheres[i].getVelocity();
			v.setXYZ(-v[0], v[1], v[2]);
			spheres[i].setVelocity(v);
		}
		//upper
		if (spheres[i].getCenter()[1] + spheres[i].getProperties()[0] > HEIGHT / 2) {
			/*Vector3 v = spheres[i].getVelocity();
			v.setXYZ(v[0], -v[1], v[2]);
			spheres[i].setVelocity(v);*/
			spheres[i].setVelocity(0,0,0);
		}

		//spheres[i].move();
	}

	glutPostRedisplay();
}

void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (option) {
	case RIGHT:
		if (shooter.getRotateAngle() <= 60)
			shooter.Rotate(20);
		option=STOP;
		break;
	case LEFT:
		if (shooter.getRotateAngle() >= -60)
			shooter.Rotate(-20);
		option=STOP;		
		break;
	case SHOOT:
		spheres.back().setVelocity(sin(shooter.getRotateAngle() * RAD), cos(shooter.getRotateAngle() * RAD), 0);
		//spheres.back().setVelocity(5, 10, 0);
		cout << spheres.back().getVelocity()[0] <<" "<< spheres.back().getVelocity()[1] <<" "<< spheres.back().getVelocity()[2]<< endl;
		cout << spheres.back().getCenter()[0] << " " << spheres.back().getCenter()[1]<<" "<< spheres.back().getCenter()[2] << endl;
		option = STOP;
		break;
	default:
		break;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ALLWIDTH / 2, ALLWIDTH / 2, -ALLHEIGHT / 2, ALLHEIGHT / 2, -100.0, 100.0);

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
	case GLUT_KEY_UP:
		cout << "shoot" << endl;
		option = SHOOT;
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
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	//keyboard callback
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
