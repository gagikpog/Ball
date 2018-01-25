#pragma once

#include <GL\freeglut.h>
#include <cmath>

#define Pi 3.141592653589793238462643

class Ball
{
public:
	Ball();
	Ball(float x,float y);
	~Ball();

	float X = 0, Y = 0, R = 50,VY = 0,VX = 0;
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
	BYTE color[3];

};

