#include "Ball.h"

extern int listH , listW;

Ball::Ball()
{
	X = Y = 500.0f;
	R = 50.0f;
	is_klick = false;
	Gravity = false;
	color[0] = rand() % 255;
	color[1] = rand() % 255;
	color[2] = rand() % 255;
	//VY = 20;
}

Ball::Ball(float x, float y)
{
	X = x;
	Y = y;
	R = 50.0f;
	is_klick = false;
	Gravity = false;
	color[0] = rand() % 255;
	color[1] = rand() % 255;
	color[2] = rand() % 255;
}


Ball::~Ball()
{
}


void Ball::Init()
{

	glBegin(GL_POLYGON);
	glColor3b(color[0], color[1], color[2]);

	for (float i = 0; i < 6; i+=0.1f)
	{
		glVertex2f(X  + cos(i)*R, Y  + sin(i)*R);
	}
	glEnd();
}

void Ball::graviry()
{
	if (!is_klick){
		if (Y -R > -VY)
		{
			Y += VY;
			if (VY > -30)
				VY -= 1;
		}
		else {
			Y = R;
			VY = -VY-4;
		}

		if (VX > 0)
			VX -= 0.1f;
		if (VX < 0)
			VX += 0.1f;
		if (VX > -0.1f && VX<0.1f)
			VX = 0;


		X += VX;
		if (X >= listW-R||X <= R)
			VX = -VX;

	}
	//else H = Y;
}


float Ball::rebound(float x, float y, float vx, float vy)
{
	float proek,xx,yy,L,tx,ty;
	xx = X - x;
	yy = Y - y;

	L = sqrt(xx*xx + yy*yy);
	proek =2*(xx*VX + yy*VY) / L;
	tx = -(xx / L)*proek;
	ty = -(yy / L)*proek;

	VX = VX + tx - vx*0.5f;
	VY = VY + ty - vy*0.5f;
	return 0;
}

int Ball::Mouse(int button, int state, int ax, int ay)
{
	x1 = ax - X;
	y1 = ay - Y;
	float in(0);
	if (button == 0)
		is_klick = true;
	else is_klick = false;
	if (state == 1)
		is_klick = 0;

	in = sqrt((X - ax)*(X - ax) + (Y - ay)*(Y - ay));

	if (in <= R)
	{
		if (state)
			if (button == 0)
			{
				return 1;
			}
			else{
				if (button == 2)
					return 2;
			}

	}
	else{
		is_klick = false;
	}
	return 0;

}

int Ball::Mouse(int ax, int ay)
{

	float in(0);
	static float x, y;

	if (is_klick){

		VY = ay - Y;
		VX = ax - x;

		X = ax - x1;
		Y = ay - y1;


			x = ax;
			y = ay;
			return 1;
	}
	return 0;
}