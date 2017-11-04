#include <gl/glut.h>

void display(void) {	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f,  300.0f, 0.0f);
		glVertex3f(50.0f,  250.0f, 0.0f);
		glVertex3f(100.0f,  200.0f, 0.0f);
		glVertex3f(50.0f,  200.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2i(0, 0);
		glVertex2i(50, 0);
		glVertex2i(50, 50);
		glVertex2i(0, 50);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f( 50.0f, 50.0f, 0.0f);
		glVertex3f( 180.0f, 50.0f, 0.0f);
		glVertex3f( 100.0f,  180.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f( 300.0f,  280.0f, 0.0f);
		glVertex3f( 350.0f,  260.0f, 0.0f);
		glVertex3f( 340.0f,  230.0f, 0.0f);
		glVertex3f( 305.0f,  220.0f, 0.0f);
	glEnd();


	glFlush();
}

void main(int argc, char* *argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("sample");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
	glutDisplayFunc(display);
	glutMainLoop();
}