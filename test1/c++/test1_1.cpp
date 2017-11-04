#include <gl/glut.h>

void display(void) {	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2i(100, 100);
		glVertex2i(200, 100);
		glVertex2i(200, 200);
		glVertex2i(100, 200);
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