#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>
#include <cmath>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;



#define PI 3.1415926535897932385

// globals
double px = 0;
double py = 65;
double pz = 0;
double fi = 0;
double theta = -90;

int oldx = 0;
int oldy = 0;

const double farClip = 300;
const double plane0[4] = {cos(PI/3),0,sin(PI/3),0};
const double plane1[4] = {0,0,1,0};
const double plane2[4] = {cos(PI/3),0,-sin(PI/3),0};
const double plane3[4] = {0,0,-1,0};
GLUquadric *const options = gluNewQuadric();

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotated(90,0,1,0);
	glRotated(-90,1,0,0);
	glRotated(fi,0,1,0);
	glRotated(-theta,0,0,1);
	glTranslated(-px,-py,-pz);


	GLfloat wire_material[4] = {0.0,0.75,0.0,1.0};
	glMaterialfv(GL_BACK,GL_AMBIENT_AND_DIFFUSE,wire_material);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glClipPlane(GL_CLIP_DISTANCE0,plane0);
	glClipPlane(GL_CLIP_DISTANCE1,plane1);
	glutSolidSphere(10,100,100);
	glClipPlane(GL_CLIP_DISTANCE0,plane2);
	glClipPlane(GL_CLIP_DISTANCE1,plane3);
	glutSolidSphere(10,100,100);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glPushMatrix();
		glRotated(-150,0,1,0);
		gluPartialDisk(options,0,10,50,100,0,180);
	glPopMatrix();
	glPushMatrix();
		glRotated(-30,0,1,0);
		gluPartialDisk(options,0,10,50,100,180,180);
	glPopMatrix();
	glPushMatrix();
		glTranslated(15,0,0);
		glPushMatrix();
			glTranslated(0,0,15);
			glutSolidSphere(7,100,100);
		glPopMatrix();
		glPushMatrix();
			glTranslated(0,15,0);
			glutSolidSphere(7,100,100);
		glPopMatrix();
		glRotated(90,0,1,0);
		glutSolidTorus(5,15,100,100);
	glPopMatrix();
	glPushMatrix();
		glTranslated(-15,0,0);
		glPushMatrix();
			glTranslated(0,0,15);
			glutSolidSphere(7,100,100);
		glPopMatrix();
		glRotated(90,0,1,0);
		glutSolidTorus(5,15,100,100);
	glPopMatrix();

	glutSwapBuffers();
} // end function display


void mouse(int key, int state, int x, int y)
{
	if(key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		oldx = x;
		oldy = y;
	} // end if
} // end function mouse


void mouseMove(int x, int y)
{
	theta -= x-oldx;
	if(theta > 180)
		theta -= 360;
	if(theta < -180)
		theta += 360;
	fi -= y-oldy;
	if(fi>90)
		fi = 90;
	if(fi< -90)
		fi = -90;
	oldx = x;
	oldy = y;
	glutPostRedisplay();
} // end function mouseMove


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'a':	// left
		px += cos(PI*theta/180.0+PI/2);
		py += sin(PI*theta/180.0+PI/2);
		break;
	case 'd':	// right
		px -= cos(PI*theta/180.0+PI/2);
		py -= sin(PI*theta/180.0+PI/2);
		break;
	case 'w':	// forward
		px += cos(PI*fi/180.0)*cos(PI*theta/180.0);
		py += cos(PI*fi/180.0)*sin(PI*theta/180.0);
		pz += sin(PI*fi/180.0);
		break;
	case 's':	// backwards
		px -= cos(PI*fi/180.0)*cos(PI*theta/180.0);
		py -= cos(PI*fi/180.0)*sin(PI*theta/180.0);
		pz -= sin(PI*fi/180.0);
		break;
	case ' ':	// up
		pz += 1;
		break;
	case 'c':	// down
		pz -= 1;
		break;
	case 27:	// escape key
		exit(0);
	} // end switch
	glutPostRedisplay();
} // end function keyboard


void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,w/(GLdouble)h,1,farClip);
	glMatrixMode(GL_MODELVIEW);
} // end function reshape


void always()
{
	glutPostRedisplay();
} // end function always


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(320,320);
	glutInitWindowPosition(800,160);
	glutCreateWindow("Creating Geometry");
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutFullScreen();

	// glew initialization
	glewInit();

	// OpenGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glPolygonMode(GL_BACK,GL_LINE);

	GLfloat black[4] = {0.0,0.0,0.0,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

	GLfloat lightPosition[4] = {0,0,20,1};
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLineWidth(0.5);

	gluQuadricDrawStyle(options,GL_FILL);
	gluQuadricNormals(options,GL_SMOOTH);

	// implementation dependant constants query
	int temp;
	glGetIntegerv(GL_MAX_CLIP_DISTANCES,&temp);
	cout << "max clip distances:\t" << temp << endl;

	// event handling initialization
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(always);
	glutMainLoop();
	return 0;
} // end function main
