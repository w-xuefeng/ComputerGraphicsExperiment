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

