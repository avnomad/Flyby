#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(40,60,0,0,0,0,0,0,1);


	//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_shininess[] = { 50.0 };
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidSphere(10,100,100);
	glPushMatrix();
		glTranslated(15,0,0);
		glRotated(90,0,1,0);
		glutSolidTorus(5,15,100,100);
	glPopMatrix();
	glPushMatrix();
		glTranslated(-15,0,0);
		glRotated(90,0,1,0);
		glutSolidTorus(5,15,100,100);
	glPopMatrix();

	glutSwapBuffers();
} // end function display


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	} // end switch
} // end function keyboard


void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,w/(GLdouble)h,5,100);
	glMatrixMode(GL_MODELVIEW);
} // end function reshape


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(320,320);
	glutInitWindowPosition(800,160);
	glutCreateWindow("Creating Geometry");

	// glew initialization
	glewInit();

	// OpenGL initialization
	glClearDepth(100);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightPosition[4] = {0,0,20,1};
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);


	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
