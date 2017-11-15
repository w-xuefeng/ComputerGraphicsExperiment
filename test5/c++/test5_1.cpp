#include <gl/glut.h>
#include <stdlib.h>

GLsizei winWidth=400,winHeight=300;
GLint ptFlag=0;

class scrPt{
  public:
    GLint x,y;
};

void init(){
  glClearColor(0.0,0.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,200.0,0.0,100.0);
}


void drawline(scrPt endPt1,scrPt endPt2){      
 glBegin(GL_LINES);   
    glVertex2i(endPt1.x,endPt1.y);
    glVertex2i(endPt2.x,endPt2.y);
 glEnd();
}

void mouse(GLint button,GLint action,GLint xMouse,GLint yMouse){
   static scrPt endPt1,endPt2;
    if(ptFlag==0){
       if(button==GLUT_LEFT_BUTTON&&action==GLUT_DOWN)
        { endPt1.x=xMouse;
          endPt1.y=yMouse;
          ptFlag=1;
        }
       else
        if(button==GLUT_RIGHT_BUTTON) exit(0);
    }else
         if(button==GLUT_LEFT_BUTTON&&action==GLUT_DOWN)
        { endPt2.x=xMouse;
          endPt2.y=winHeight-yMouse;
          drawline(endPt1,endPt2);
          endPt1=endPt2;
        }   else
        if(button==GLUT_RIGHT_BUTTON) exit(0);
    glFlush();
}

void keyboard (unsigned char key, int x, int y){
   switch (key) {
      case 'q':
      case 'Q':
         exit(0);
         break;
      
      default:
         break;
   }
}

void reshape(GLint newWidth,GLint newHeight){
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,GLdouble(newWidth),0.0,GLdouble(newHeight));
    winWidth=newWidth;
    winHeight=newHeight;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
}


void main( int argc, char** argv ){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE );
  glutInitWindowSize(winWidth, winHeight);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("plot polyline");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);   
  glutKeyboardFunc(keyboard);
  glutMainLoop();
}

