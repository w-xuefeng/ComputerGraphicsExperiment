#include <gl/glut.h>

void display(void) {	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	int polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glVertex3f( 0.0, 0.5, 0.0);
	glVertex3f( -0.4, -0.3, 0.0);
	glVertex3f( 0.4, -0.3, 0.0);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glVertex3f( -0.4, 0.3, 0.0);
	glVertex3f(0.4, 0.3, 0.0);
	glVertex3f( 0, -0.5, 0.0);
	glEnd();

	glPolygonMode(GL_FRONT, polygonMode[0]);
	glPolygonMode(GL_BACK, polygonMode[1]);

	glFlush();
}

void main(int argc, char* *argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("sample");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutMainLoop();
}