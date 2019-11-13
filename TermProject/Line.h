#pragma once
#include "Light.h"
#include "Vector3.h"
#include <ctime>

class Line
{
public:
	Line();
	void setPosition1(float x, float y, float z);
	void setPosition2(float x, float y, float z);
	Vector3 getPosition1()const;
	Vector3 getPosition2()const;
	void timeRun();
	void setTime();

private:
	Vector3 position1;
	Vector3 position2;
	int itime;
	int pass_time;
};