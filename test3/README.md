# ComputerGraphicsExperiment
Computer graphics experiment 计算机图形学实验

## 实验3——三维图形绘制

  - 1).实验目的

    - 理解OpenGL三维观察流水线

    - 理解3D模式数据结构及绘制方法

  - 2).实验内容

    - 编程实现图1、图2

    - 编程实现3D彩色立方体

    - 完成实验报告

      - 图1

        ![testQ3.1](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/Q/testQ3.1.png)

      - 图2

        ![testQ3.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/Q/testQ3.2.png)

## 实验代码

 - 1.test3.1

```c++

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


```

 - 效果截图

    ![testA3.1](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA3.1.png)

 - 2.test3.2

 ```c++

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


```

 - 效果截图

    ![testA3.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA3.2.png)
