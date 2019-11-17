#pragma once
#include"Vector3.h"

#define COORX 20
#define COORY 34.641016151

class Coordinate {
public:
	Coordinate();
	~Coordinate();
	Vector3 XYtoMatrix(Vector3& v);
	bool isfull(Vector3& v);
	void setfull(Vector3& v);
	void setempty(Vector3& v);
	Vector3 search(const Vector3& ball,const Vector3& collsionBall);
	Vector3 upper(Vector3& ball);

private:
	Vector3** coordinate;
	bool** full;
};