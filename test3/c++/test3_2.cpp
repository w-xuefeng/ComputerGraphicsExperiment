#include <gl/glut.h>

GLfloat vertices[][3] = {
    {-1.0,-1.0,-1.0},
    {1.0,-1.0,-1.0},
    {1.0,1.0,-1.0},
    {-1.0,1.0,-1.0},
    {-1.0,-1.0,1.0}, 
    {1.0,-1.0,1.0},
    {1.0,1.0,1.0},
    {-1.0,1.0,1.0}
};

GLfloat colors[8][3] = {
    {0.0,0.0,0.0},
    {1.0,0.0,0.0},
    {1.0,1.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0}, 
    {1.0,0.0,1.0},
    {1.0,1.0,1.0},
    {0.0,1.0,1.0}
};

void init(void){
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void myReshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
    glMatrixMode(GL_MODELVIEW);
}

void polygon(int a, int b, int c , int d){
    glBegin(GL_POLYGON);
        glColor3fv(colors[a]);
        glVertex3fv(vertices[a]);
        glColor3fv(colors[b]);
        glVertex3fv(vertices[b]);
        glColor3fv(colors[c]);
        glVertex3fv(vertices[c]);
        glColor3fv(colors[d]);
        glVertex3fv(vertices[d]);
    glEnd();
}

void colorcube(void){
    polygon(0,3,2,1);
    polygon(0,1,5,4);
    polygon(0,4,7,3);
    polygon(2,3,7,6);    
    polygon(1,2,6,5);
    polygon(4,5,6,7);
}

void drawTeapot(void){    
    glLoadIdentity();
    gluLookAt(5.0,5.0,8.0,-2.5,-2.5,0.0,0.0,1.0,0.0);
    glColor3f(1.0,0.0,0.7);   
    glutWireTeapot(2);    
}


void drawCube(void){    
    glLoadIdentity();
    gluLookAt(5.0,3.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);    
    colorcube();
    glScalef(2.0,2.0,2.0);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT); 
    drawTeapot();   
    drawCube();   
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
