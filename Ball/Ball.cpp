#include "Ball.h"

extern int WndH , WndW;

Ball::Ball()
{
	Position.X = Position.Y = 500.0f;
	R = 50.0f;
	is_click = false;
	Gravity = false;
	color[0] = rand() % 255;
	color[1] = rand() % 255;
	color[2] = rand() % 255;
}

Ball::Ball(float x, float y)
{
	Position.X = x;
	Position.Y = y;
	R = 50.0f;
	is_click = false;
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
		glVertex2f(Position.X  + cos(i)*R, Position.Y  + sin(i)*R);
	}
	glEnd();
}

void Ball::graviry()
{
	if (!is_click)
	{
		if (Position.Y + Velocity.Y < R || Position.Y + Velocity.Y > WndH - R)
		{
			Velocity.Y *= -1;
		}
		if (Position.X + Velocity.X < R || Position.X + Velocity.X > WndW - R)
		{
			Velocity.X *= -1;
		}
		
//		if (Velocity.Y > -30 && Position.Y >= R+1)
//			Velocity.Y -= 1.2;
		Velocity.X *= 0.99;
		Velocity.Y *= 0.99;
		Position.X += Velocity.X;
		Position.Y += Velocity.Y;
	}
}

inline float len(float x1,float y1,float x2,float y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void Ball::rebound(Ball& ball)
{

	Vector2f oo1 = ball.Position - Position;
	Vector2f oo2 = oo1.GetPerpendicular();

	Vector2f vn1 = oo1.GetBase()*Velocity.ScalarProduct(oo1) / oo1.GetLength();
	Vector2f vt1 = oo2.GetBase()*Velocity.ScalarProduct(oo2) / oo2.GetLength();

	Vector2f vn2 = oo1.GetBase()*ball.Velocity.ScalarProduct(oo1) / oo1.GetLength();
	Vector2f vt2 = oo2.GetBase()*ball.Velocity.ScalarProduct(oo2) / oo2.GetLength();

	Velocity = vt1 - (vn1 + vn2*0.4f);
	ball.Velocity = vt2 - (vn2 - vn1*0.4f);

}

int Ball::Mouse(int button, int state, int ax, int ay)
{
	x1 = ax - Position.X;
	y1 = ay - Position.Y;
	float in(0);
	if (button == 0)
		is_click = true;
	else is_click = false;
	if (state == 1)
		is_click = 0;

	in = sqrt((Position.X - ax)*(Position.X - ax) + (Position.Y - ay)*(Position.Y - ay));

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
		is_click = false;
	}
	return 0;

}

int Ball::Mouse(int ax, int ay)
{

	float in(0);
	static float x, y;

	if (is_click){

		Velocity.Y = ay - Position.Y;
		Velocity.X = ax - x;

		Position.X = ax - x1;
		Position.Y = ay - y1;
		x = ax;
		y = ay;
		return 1;
	}
	return 0;
}