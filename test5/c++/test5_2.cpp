#include <gl/glut.h>
#include <stdlib.h>

GLsizei winWidth=400,
winHeight=300;
GLint ptFlag=0;
class scrPt{
public:
  GLint x,y;
};

GLfloat red=1.0,green=1.0,blue=1.0;
GLenum fillMode=GL_SMOOTH;

void init(){
  glClearColor(0.0,0.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,200.0,0.0,100.0);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glShadeModel(fillMode);
  glColor3f(red,green,blue);
  glBegin(GL_TRIANGLES);
    glVertex2i(280,20);
    glVertex2i(160,280);
    glColor3f(red,0.0,0.0);
    glVertex2i(20,100);
  glEnd();
  glFlush();
}

void filloption(GLint selectdoption){
  switch(selectdoption){
    case 1:fillMode=GL_FLAT;break;
    case 2:fillMode=GL_SMOOTH;break;
  }
  glutPostRedisplay();
}

void reshape(GLint newWidth,GLint newHeight){
  glViewport(0,0,newWidth,newHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,GLdouble(newWidth),0.0,GLdouble(newHeight));
  winWidth=newWidth;
  winHeight=newHeight;
}


void main( int argc, char** argv ){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE );
  glutInitWindowSize(winWidth, winHeight);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("Menu Example");
  init();
  glutDisplayFunc(display);
  glutCreateMenu(filloption);
  glutAddMenuEntry("Solid_color Fill",1);
  glutAddMenuEntry("Color_Interpolation Fill",2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutReshapeFunc(reshape);
  glutMainLoop();
}
