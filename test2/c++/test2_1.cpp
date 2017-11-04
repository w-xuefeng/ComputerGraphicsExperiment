#include <gl/glut.h>

void display(void) {	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	
	int i;		
	float pointSize = 0;
	glGetFloatv(GL_POINT_SIZE, &pointSize);
	for (i = 0; i < 5; i++) {
		glPointSize((float)(i + 1));
		glBegin(GL_POINTS);
		glVertex3f(100 + 50 * i, 380, 0.0);
		glEnd();
	}
	glPointSize(pointSize);

	float lineWidth = 0;
	glGetFloatv(GL_LINE_WIDTH, &lineWidth);
	for (i = 0; i < 5; i++) {
		glLineWidth((float)(i + 1));
		glBegin(GL_LINES);
		glVertex3f(80 , 370 - i * 15, 0.0);
		glVertex3f(320 , 370 - i * 15, 0.0);
		glEnd();
	}
	glLineWidth(lineWidth);

	int polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glVertex3f(30, 230, 0.0);
	glVertex3f(60, 280, 0.0);
	glVertex3f(90, 230, 0.0);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	glVertex3f( 170, 230, 0.0);
	glVertex3f( 200, 280, 0.0);
	glVertex3f( 230, 230, 0.0);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glBegin(GL_TRIANGLES);
	glVertex3f( 310, 230, 0.0);
	glVertex3f( 340, 280, 0.0);
	glVertex3f( 370, 230, 0.0);
	glEnd();

	glPolygonMode(GL_FRONT, polygonMode[0]);
	glPolygonMode(GL_BACK, polygonMode[1]);

	int lineStipples[] = {
		//1010 1010 1010 1010 = 10 10 10 10
		0xAAAA,
		//0000 1111 0000 1111 =  0 15  0 15
		0x0F0F,
		//1111 1111 1111 0000 = 15 15 15  0
		0xFFF0,
		//0000 0000 0000 1111 =  0  0  0 15
		0x000F,
		//0001 0001 0001 0001 =  1  1  1  1
		0x1111
	};

	glEnable(GL_LINE_STIPPLE);
	for (i = 0; i < 5; i++)	{
		glLineStipple(1, lineStipples[i]);
		glBegin(GL_LINES);
		glVertex3f(50, 220 - i * 25, 0.0);
		glVertex3f(170, 220 - i * 25, 0.0);
		glEnd();
		glLineStipple(3, lineStipples[i]);
		glBegin(GL_LINES);
		glVertex3f( 220, 220 - i * 25, 0.0);
		glVertex3f( 350, 220 - i * 25, 0.0);
		glEnd();
	}
	glDisable(GL_LINE_STIPPLE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
	glVertex3f( 50,  20, 0.0);
	glVertex3f( 120,  100, 0.0);
	glVertex3f( 200,  60, 0.0);
	glVertex3f( 280,  100, 0.0);
	glVertex3f( 350,  20, 0.0);
	glEnd();



	glFlush();
}

void main(int argc, char* *argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("sample");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
	glutDisplayFunc(display);
	glutMainLoop();
}