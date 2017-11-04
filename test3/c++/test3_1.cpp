#include <gl/glut.h>

void init(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
}

void myReshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 //   gluPerspective(45.0, float(w) / h, 0.1, 100.0);
	glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glScalef(2.0,1.0,1.0);
	glutWireCube(1);
	glFlush();
}

void main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("3D Cube");
    init();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
}
