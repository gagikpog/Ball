#include "Ball.h"
#include <vector>
#include <ctime>

int listH = 800;
int listW = 800;

using namespace std;

vector<Ball> ball;

//Ball one;

void test(Ball& b1, Ball& b2)
{
	if (sqrt((b1.X - b2.X)*(b1.X - b2.X) + (b1.Y - b2.Y)*(b1.Y - b2.Y)) < (b1.R + b2.R))
	{
		b1.rebound(b2.X, b2.Y, b2.VX, b2.VY);
		b2.rebound(b1.X, b1.Y, b1.VX, b1.VY);
	}
}

void Display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glVertex2f(0, 0);
//	glVertex2f(0, listH / 2.0f);
//	glVertex2f(listW / 2.0f,0);
//	glEnd();

	for (int i = 0; i < ball.size() - 1; i++)
	{
		for (int j = i + 1; j < ball.size(); j++)
		{
			test(ball[i], ball[j]);
		}
	}

	for (int i = 0; i < ball.size(); i++)
	{
		ball[i].Init();
//		if (ball[i].R < 0.1)
//			ball.erase(ball.begin());
	}

	glutSwapBuffers();
}

void Reshop(int aw, int ah)
{
	listH = ah;
	listW = aw;

	glViewport(0, 0, aw, ah);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, listW, 0, listH);

	glMatrixMode(GL_MODELVIEW);

}

void timer(int)
{

	glutPostRedisplay();//ej@ obnavit

	for (int i = 0; i < ball.size(); i++)
	{
		ball[i].graviry();
	}

	glutTimerFunc(25, timer, 0);
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':{
//		glTranslatef(-10, 0, 0);//texapoxum

		break; }

	default:
		break;
	}
}

void keys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
//		glRotatef(1, 0, 0, 1);//frcnel
		break;
	default:

		break;
	}

}


void mouse(int ax, int ay)
{
	for (int i = 0; i < ball.size(); i++)
	{
		ball[i].Mouse(ax, listH - ay);
	}
}
void mouse(int state, int ax, int ay)
{
}

void mouse(int button, int state, int ax, int ay)
{

	for (int i = 0; i < ball.size(); i++)
	{
		ball[i].Mouse(button, state, ax, listH - ay);
	}

	if (button == 2 && state == 1)
		ball.push_back(Ball());

//	if (button == 1 && state == 1)
//		ball[0].rebound(1,1,1,1);

}


int main(int argc, char**argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB |GLUT_DOUBLE );
	glutInitWindowPosition(200,200);
	glutInitWindowSize(listW,listH);
	glutCreateWindow("Gagik");

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, listW, 0, listH );

	glMatrixMode(GL_MODELVIEW);

//	glTranslatef(0, 0, 0);//texapoxum
//	glScalef(0.8, 0.8, 0.8);//sexmel
//	glRotatef(0, 0, 0, 0);//frcnel


	for (int i = 0; i < 3; i++)
	{
		ball.push_back(Ball(rand()% listW, rand() % listH));
	}

	glutReshapeFunc(Reshop);//eji razmer

	glutKeyboardFunc(keys);//char/klaviatura
	glutSpecialFunc(keys);//int/klaviatura

	glutMotionFunc(mouse);//////////////MUK
	glutMultiPassiveFunc(mouse);
	glutMouseFunc(mouse);///////////////

//	glutSetWindowTitle("ert");//zagalovki poxel

	glutTimerFunc(50, timer, 0);
	glutDisplayFunc(Display);
	glutMainLoop();


	return 0;
}