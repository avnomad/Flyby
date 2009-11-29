#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>
#include <cmath>

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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotated(90,0,1,0);
	glRotated(-90,1,0,0);
	glRotated(fi,0,1,0);
	glRotated(-theta,0,0,1);
	glTranslated(-px,-py,-pz);


	//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_shininess[] = { 50.0 };
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidSphere(10,100,100);
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(320,320);
	glutInitWindowPosition(800,160);
	glutCreateWindow("Creating Geometry");
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	// glew initialization
	glewInit();

	// OpenGL initialization
	glClearDepth(farClip);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightPosition[4] = {0,0,20,1};
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);


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
