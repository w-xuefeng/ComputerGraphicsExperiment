# ComputerGraphicsExperiment
Computer graphics experiment 计算机图形学实验

## 实验4——几何变换

 - 1).理解图形变换及矩阵栈的概念

 - 2).调试教材P102-103程序，输出下图(左)结果并完成实验报告

 - 3).调试实验程序例2，完成下列工作

       - 将前视图代码（左下）补充完整，输出结果如下图

       - 逐条注释Bool init()代码段的各个函数

 - 4).完成实验报告


      - 图1

        ![testQ4.1](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/Q/testQ4.1.png)

      - 图2

        ![testQ4.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/Q/testQ4.2.png)

## 实验代码

 - 1.test4.1

```c++
#include <gl/glut.h>

GLfloat shield[5][3] = {
    {5,0,0},
    {8,20,0},
    {0,25,0},
    {-8,20,0},
    {-5,0,0}
};

GLfloat colors[4][3] = {
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {1,1,0}
};

void draw_shield(void) {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 5; ++i) glVertex3fv(shield[i]);
    glEnd();
}

void draw_ring(void) {
    for (int r = 0; r < 360; r+=15){
        glPushMatrix();
        glRotated(r, 0, 0, 1);
        glTranslated(0, 50, 0);
        draw_shield();
        glPopMatrix();
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < 4; ++i) {
        glColor3fv(colors[i]);
        glPushMatrix();
        glTranslated((i-3)*50, (i-3)*50, -i*5);
        glScaled(i+1, i+1, i+1);
        draw_ring();
        glPopMatrix();
    }
    glFlush();
}

void main(int argc, char **argv){
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(200,100);
    glutCreateWindow("CTM stack");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300, 300, -300, 300, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(display);
    glutMainLoop();
}



```

 - 效果截图

    ![testA4.1](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA4.1.png)

 - 2.test3.2

 ```c++

#include <gl/glut.h>

int win_height=320, win_width=320;
GLint object = 0;
GLfloat Angle = 25;
bool init() {
    glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

    object = glGenLists(1);
    glNewList(object, GL_COMPILE);
    glutSolidTeapot(1.8);
    glEndList();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    return true;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 左上：顶视图
    glViewport(0, win_height/2, win_width/2, win_height/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
    gluLookAt (0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glCallList(object);

    // 右上：右视图
    glViewport(win_width/2, win_height/2, win_width/2, win_height/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
    gluLookAt (5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glCallList(object);

    // 左下：前视图
    glViewport(0, 0, win_width/2, win_height/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glCallList(object);
    
    //学生补充完整


    // 右下：旋转的透视视区
    glViewport(win_width/2, 0, win_width/2, win_height/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1, 50);
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef (30.0, 1.0, 0.0, 0.0);
    glRotatef (Angle, 0.0, 1.0, 0.0);
    glCallList(object);
    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    win_height=h;
    win_width=w;
}

int main (int argc,  char *argv[]) {
    glutInit(&argc, argv);                                      
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);// 显示模式RGBA+双缓存
    int windowHandle = glutCreateWindow("MultiView"); 
    glutReshapeWindow(win_width, win_height);    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);// 窗口大小变化时
    init();
    glutMainLoop();                               
    glDeleteLists(object, 1);
    return 0;
}


```

 - 效果截图

    ![testA4.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA4.2.png)
