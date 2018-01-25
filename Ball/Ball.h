#pragma once

#include <GL\freeglut.h>
#include <cmath>

#define Pi 3.14159265358979323846

class Ball
{
public:
	Ball();
	~Ball();

	float X, Y, R,VY,VX;
	bool Gravity;


	///////function
	void Init();
	void graviry();
	float rebound(float x,float y,float vx,float vy);

	int Mouse(int button, int state, int ax, int ay);
	int Mouse(int ax, int ay); 

private:
	bool is_klick;
	float x1,y1;

};

