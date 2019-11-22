#pragma once
#include"Vector3.h"
#include<math.h>
#include"SolidSphere.h"

#define COORX 20
#define COORY 34.7
//#define DD 
//
//double COORX = 20.0;
//double COORY = 20 * sqrt(3);

class Coordinate {
public:
	Coordinate();
	~Coordinate();
	Vector3 XYtoMatrix(const Vector3& v);
	bool isfull(const Vector3& v);
	void setfull(const Vector3& v);
	void setempty(const Vector3& v);
	void setSphere(const SolidSphere& sph);
	Vector3 search(const Vector3& ball,const Vector3& collsionBall);
	Vector3 upper(Vector3& ball);
	void detectColor(SolidSphere& sph, std::vector<Vector3>& ers_vec, int color);


private:
	enum { RED, GREEN, CYAN, YELLOW };
	Vector3** coordinate;
	bool** full;
	SolidSphere** coorSphere;

};