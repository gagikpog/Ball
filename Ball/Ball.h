#pragma once

#include <GL\freeglut.h>
#include <cmath>

#define Pi 3.141592653589793238462643


struct Vector2f
{
	Vector2f() {}
	Vector2f(float x, float y)
	{
		X = x;
		Y = y;
	}
	Vector2f(const Vector2f& value)
	{
		X = value.X;
		Y = value.Y;
	}
	Vector2f operator+(const Vector2f& value) const
	{
		return Vector2f(X + value.X, Y + value.Y);
	}
	Vector2f operator-(const Vector2f& value) const
	{
		return Vector2f(X - value.X, Y - value.Y);
	}
	Vector2f& operator=(const Vector2f& value)
	{
		X = value.X;
		Y = value.Y;
		return *this;
	}
	Vector2f& operator+=(const Vector2f& value)
	{
		X += value.X;
		Y += value.Y;
		return *this;
	}
	Vector2f& operator-=(const Vector2f& value)
	{
		X -= value.X;
		Y -= value.Y;
		return *this;
	}
	Vector2f operator*(const float value)
	{
		return Vector2f(X*value, Y*value);
	}
	Vector2f operator/(const float value)
	{
		return Vector2f(X / value, Y / value);
	}
	Vector2f& operator*=(const float value)
	{
		X = X*value;
		Y = Y*value;
		return *this;
	}
	Vector2f& operator/=(const float value)
	{
		X = X / value;
		Y = Y / value;
		return *this;
	}
	bool operator==(const Vector2f& operator2)
	{
		return (X == operator2.X && Y == operator2.Y);
	}
	float ScalarProduct(const Vector2f& value)
	{
		return X*value.X + Y*value.Y;
	}
	float GetLength()
	{
		return sqrtf(X*X + Y*Y);
	}
	Vector2f GetBase()
	{
		float l = GetLength();
		return Vector2f(X / l, Y / l);
	}
	Vector2f GetPerpendicular()
	{
		float n = sqrtf(X*X + Y*Y) / ((X*X) / (Y*Y) + 1);
		float m = (-Y*n) / X;
		return Vector2f(m, n);
	}
	float X = 0;
	float Y = 0;
};


class Ball
{
public:
	Ball();
	Ball(float x,float y);
	~Ball();

	float R = 50;
	bool Gravity;

	Vector2f Position;
	Vector2f Velocity;
	///////function
	void Init();
	void graviry();
	void rebound(Ball& b);

	int Mouse(int button, int state, int ax, int ay);
	int Mouse(int ax, int ay); 

private:
	bool is_click;
	float x1,y1;
	BYTE color[3];

};

