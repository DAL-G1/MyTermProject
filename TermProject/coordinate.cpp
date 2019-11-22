#include "coordinate.h"
#include <vector>

Coordinate::Coordinate() {
	coordinate = new Vector3 * [10];
	full = new bool* [10];
	coorSphere = new SolidSphere * [10];
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) {
			coordinate[i] = new Vector3[10];
			full[i] = new bool[10];
			coorSphere[i] = new SolidSphere[10];
			for (int j = 0; j < 10; j++) {
				coordinate[i][j] = Vector3(-180 + 2 * j * COORX, 180 - i * COORY, 0);
				full[i][j] = false;

			}
		}
		else {
			coordinate[i] = new Vector3[9];
			full[i] = new bool[9];
			coorSphere[i] = new SolidSphere[9];
			for (int j = 0; j < 9; j++) {
				coordinate[i][j] = Vector3(-160 + 2 * j * COORX, 180 - i * COORY, 0);
				full[i][j] = false;
			}
		}
	}

	
}

Coordinate::~Coordinate() {
	for (int i = 0; i < 10; i++) {
		delete[]coordinate[i];
		delete[]full[i];
		delete[]coorSphere[i];
	}
	delete[]coordinate;
	delete[]full;
	delete[]coorSphere;

}

Vector3 Coordinate::XYtoMatrix(const Vector3& v) {
	int row = (180.0 - v.getXYZ()[1]) / COORY+0.5;
	int column;
	if (row % 2 == 0)
		column = (180.0 + v.getXYZ()[0]) / (2.0 * COORX)+0.5;
	else
		column = (160.0 + v.getXYZ()[0]) / (2.0 * COORX)+0.5;
	return Vector3(row, column, 0);
}

bool Coordinate::isfull(const Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	return full[x][y];
}

Vector3 Coordinate::search(const Vector3& ball,const Vector3& collisionBall) {
	Vector3 position;
	Vector3 near[6]; //충돌한 공 주변의 6개 공
	near[0].setXYZ(collisionBall[0] - COORX, collisionBall[1] + COORY, 0);
	near[1].setXYZ(collisionBall[0] + COORX, collisionBall[1] + COORY, 0);
	near[2].setXYZ(collisionBall[0] + 2 * COORX, collisionBall[1], 0);
	near[3].setXYZ(collisionBall[0] + COORX, collisionBall[1] - COORY, 0);
	near[4].setXYZ(collisionBall[0] - COORX, collisionBall[1] - COORY, 0);
	near[5].setXYZ(collisionBall[0] - 2 * COORX, collisionBall[1], 0);
	float min = 4*COORX*COORX;  //공지름^2(=최대거리^2)
	for (int i = 0; i < 6; i++) {
		float distance = dotProduct(near[i]-ball,near[i]-ball);  //주변6개 공과 쏘아진 공의 중심 사이 거리 계산
		if (distance < min ) {  //최소거리 탐색
			position = near[i];  //좌표 대입
			min = distance; //거리 대입
		}
	}
	//가장 가까운 거리에 있는 공의 중심 좌표 return
	int row = XYtoMatrix(position)[0];
	int column = XYtoMatrix(position)[1];
	return coordinate[row][column];
}

void Coordinate::setfull(const Vector3& v) {
	int x,y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	full[x][y] = true;
}

void Coordinate::setempty(const Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	full[x][y] = false;
}

void Coordinate::setSphere(const SolidSphere& sph) {
	int row = XYtoMatrix(sph.getCenter())[0];
	int column = XYtoMatrix(sph.getCenter())[1];
	coorSphere[row][column] = SolidSphere(sph);
}

Vector3 Coordinate::upper(Vector3& ball) {
	float min = 2 * COORX;
	int ballX=0;
	for (int x = -180; x <= 180; x += 40) {
		float distance = x - ball.getXYZ()[0];
		
		if (distance * distance < min * min) {
			min = distance;
			ballX = x;
		}
		
		
	}
	return Vector3(ballX, 180, 0);
}

void Coordinate::detectColor(SolidSphere& sph, std::vector<Vector3> &ers_vec, int color) {
	int c = color;
	std::vector<Vector3> near;
	Vector3 ball = sph.getCenter();
	if (-180 <= ball[0] - COORX && ball[0] - COORX <= 180 && -180 <= ball[1] + COORY && ball[1] + COORY <= 180)
	{
		Vector3 near1;
		near1.setXYZ(ball[0] - COORX, ball[1] + COORY, 0);
		near.push_back(near1);
	}
	if (-180 <= ball[0] + COORX && ball[0] + COORX <= 180 && -180 <= ball[1] + COORY && ball[1] + COORY <= 180)
	{
		Vector3 near2;
		near2.setXYZ(ball[0] + COORX, ball[1] + COORY, 0);
		near.push_back(near2);
	}
	if (-180 <= ball[0] + 2 * COORX && ball[0] + 2 * COORX <= 180 && -180 <= ball[1] && ball[1] <= 180)
	{
		Vector3 near3;
		near3.setXYZ(ball[0] + 2 * COORX, ball[1], 0);
		near.push_back(near3);
	}
	if (-180 <= ball[0] + COORX && ball[0] + COORX <= 180 && -180 <= ball[1] - COORY && ball[1] - COORY <= 180)
	{
		Vector3 near4;
		near4.setXYZ(ball[0] + COORX, ball[1] - COORY, 0);
		near.push_back(near4);
	}
	if (-180 <= ball[0] - COORX && ball[0] - COORX <= 180 && -180 <= ball[1] - COORY && ball[1] - COORY <= 180)
	{
		Vector3 near5;
		near5.setXYZ(ball[0] - COORX, ball[1] - COORY, 0);
		near.push_back(near5);
	}
	if (-180 <= ball[0] - 2 * COORX && ball[0] - 2 * COORX <= 180 && -180 <= ball[1] && ball[1] <= 180)
	{
		Vector3 near6;
		near6.setXYZ(ball[0] - 2 * COORX, ball[1], 0);
		near.push_back(near6);
	}
	for (int i = 0; i < near.size(); i++) {
		int row = XYtoMatrix(near[i])[0];
		int column = XYtoMatrix(near[i])[1];
		if (full[row][column]) {
			if (coorSphere[row][column].getColor() == color && coorSphere[row][column].getErs() == false)
			{
				Vector3 cErs;
				cErs.setXYZ(coorSphere[row][column].getCenter()[0], coorSphere[row][column].getCenter()[1], 0);
				ers_vec.push_back(cErs);
				coorSphere[row][column].setErs(true);
				detectColor((coorSphere[row][column]), ers_vec, c);
			}
		}
	}

}