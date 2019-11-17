#include "coordinate.h"

Coordinate::Coordinate() {
	coordinate = new Vector3 * [10];
	full = new bool* [10];
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) {
			coordinate[i] = new Vector3[10];
			full[i] = new bool[10];
			for (int j = 0; j < 10; j++) {
				coordinate[i][j] = Vector3(-180 + 2 * j * COORX, 180 - i * COORY, 0);
				full[i][j] = false;
			}
		}
		else {
			coordinate[i] = new Vector3[9];
			full[i] = new bool[9];
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
	}
	delete[]coordinate;
	delete[]full;

}

Vector3 Coordinate::XYtoMatrix(Vector3& v) {
	int row = (180.0 - v.getXYZ()[1]) / COORY;
	int column;
	if (row % 2 == 0)
		column = (180.0 + v.getXYZ()[0]) / (2 * COORX);
	else
		column = (160.0 + v.getXYZ()[0]) / (2 * COORX);
	return Vector3(row, column, 0);
}

bool Coordinate::isfull(Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	return full[x][y];
}

Vector3 Coordinate::search(const Vector3& ball,const Vector3& collisionBall) {
	Vector3 position;
	Vector3 near[6];
	near[0].setXYZ(collisionBall[0] - COORX, collisionBall[1] + COORY, 0);
	near[1].setXYZ(collisionBall[0] + COORX, collisionBall[1] + COORY, 0);
	near[2].setXYZ(collisionBall[0] + 2 * COORX, collisionBall[1], 0);
	near[3].setXYZ(collisionBall[0] + COORX, collisionBall[1] - COORY, 0);
	near[4].setXYZ(collisionBall[0] - COORX, collisionBall[1] - COORY, 0);
	near[5].setXYZ(collisionBall[0] - 2 * COORX, collisionBall[1], 0);
	float min = 2*COORX;
	for (int i = 0; i < 6; i++) {
		float distance = dotProduct(near[i], ball);
		if (distance < min && !isfull(near[i]))
			position = near[i];
	}
	return position;
}

void Coordinate::setfull(Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	full[x][y] = true;
}

void Coordinate::setempty(Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	full[x][y] = false;
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
		//ball.setXYZ(ballX, 180, 0);
		
	}
	return Vector3(ballX, 180, 0);
}