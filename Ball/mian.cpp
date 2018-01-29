#include "Ball.h"
#include <vector>
#include <ctime>

using namespace std;

int WndH = 800;
int WndW = 800;

vector<Ball> balls;

void test(Ball& b1, Ball& b2)
{
	if((b1.Position-b2.Position).GetLength() < b1.R+b2.R)
		b1.rebound(b2);
}

void Display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < (int (balls.size())) - 1; i++)
		for (int j = i + 1; j < balls.size(); j++)
			test(balls[i], balls[j]);

	for (int i = 0; i < balls.size(); i++)
		balls[i].Init();

	glutSwapBuffers();
}

void Reshop(int aw, int ah)
{
	WndH = ah;
	WndW = aw;
	glViewport(0, 0, aw, ah);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WndW, 0, WndH);

	glMatrixMode(GL_MODELVIEW);

}

void timer(int)
{
	glutPostRedisplay();
	for (int i = 0; i < balls.size(); i++)
		balls[i].graviry();
	glutTimerFunc(25, timer, 0);
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c': balls.clear();
		break;
	default:
		break;
	}
}

void keys(int key, int x, int y)
{
}

void mouse(int ax, int ay)
{
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i].Mouse(ax, WndH - ay);
	}
}

void mouse(int state, int ax, int ay)
{
}

void mouse(int button, int state, int ax, int ay)
{
	if(button == 0)
		for (int i = 0; i < balls.size(); i++)
			balls[i].Mouse(button, state, ax, WndH - ay);

	if (button == 2 && state == 1)
		balls.push_back(Ball(ax,WndH - ay));
}

int main(int argc, char**argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB |GLUT_DOUBLE );
	glutInitWindowPosition(10,10);
	glutInitWindowSize(WndW,WndH);
	glutCreateWindow("Ball");

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WndW, 0, WndH );

	glMatrixMode(GL_MODELVIEW);

	for (int i = 0; i < 3; i++)
		balls.push_back(Ball(rand()% (WndW -100)+50, rand() % (WndH-100)+50));

	glutReshapeFunc(Reshop);

	glutKeyboardFunc(keys);
	glutSpecialFunc(keys);

	glutMotionFunc(mouse);
	glutMultiPassiveFunc(mouse);
	glutMouseFunc(mouse);
	
	glutTimerFunc(50, timer, 0);
	glutDisplayFunc(Display);
	glutMainLoop();

	return 0;
}