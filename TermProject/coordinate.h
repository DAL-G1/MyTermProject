#pragma once
#include"Vector3.h"

#define COORX 20
#define COORY 34.641016151

class Coordinate {
public:
	Coordinate();
	~Coordinate();
	Vector3 XYtoMatrix(const Vector3& v);
	bool isfull(const Vector3& v);
	void setfull(const Vector3& v);
	void setempty(const Vector3& v);
	Vector3 search(const Vector3& ball,const Vector3& collsionBall);
	Vector3 upper(Vector3& ball);

private:
	Vector3** coordinate;
	bool** full;
};