# ComputerGraphicsExperiment
Computer graphics experiment 计算机图形学实验

## 实验5——曲线绘制

 - 调试程序例1；
 - 调试程序例2；
 - 完成实验报告

## 实验代码

 - 1.test5.1

```c++
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

```

 - 效果截图

    ![testA4.1](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA5.1.png)

 - 2.test5.2

 ```c++

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



```

 - 效果截图

    ![testA4.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA5.2.png)
