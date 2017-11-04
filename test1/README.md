# ComputerGraphicsExperiment
Computer graphics experiment 计算机图形学实验

## 实验1——OpenGL基础

 - 1).实验目的

   - 理解OpenGL的程序结构

   - 理解OpenGL基本图元

 - 2).下载OpenGL实用工具库文件  glut32.dll,glut.h,glut32.lib

 - 3).配置运行环境

 - 4).实验内容

   - 编译运行教材P23程序实例

   - 编程实现下图

   - 实验报告（程序源码、运行结果）

	![testQ1.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/Q/testQ1.2.png)

## 实验代码

 - 1.test1.1

```c++

#include <gl/glut.h>

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2i(100, 100);
		glVertex2i(200, 100);
		glVertex2i(200, 200);
		glVertex2i(100, 200);
	glEnd();
	glFlush();
}

void main(int argc, char* *argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("sample");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
	glutDisplayFunc(display);
	glutMainLoop();
}

```

 - 效果截图

	![testA1.1](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA1.1.png)
 
 - [webGL版预览](https://w-xuefeng.github.io/ComputerGraphicsExperiment/test1/webGL/test1.1.webgl.html)

 - [canvas版预览](https://w-xuefeng.github.io/ComputerGraphicsExperiment/test1/webGL/test1.1.canvas.html)

 - 2.test1.2

 ```c++

 #include <gl/glut.h>

void display(void) {	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f,  300.0f, 0.0f);
		glVertex3f(50.0f,  250.0f, 0.0f);
		glVertex3f(100.0f,  200.0f, 0.0f);
		glVertex3f(50.0f,  200.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2i(0, 0);
		glVertex2i(50, 0);
		glVertex2i(50, 50);
		glVertex2i(0, 50);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f( 50.0f, 50.0f, 0.0f);
		glVertex3f( 180.0f, 50.0f, 0.0f);
		glVertex3f( 100.0f,  180.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f( 300.0f,  280.0f, 0.0f);
		glVertex3f( 350.0f,  260.0f, 0.0f);
		glVertex3f( 340.0f,  230.0f, 0.0f);
		glVertex3f( 305.0f,  220.0f, 0.0f);
	glEnd();


	glFlush();
}

void main(int argc, char* *argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("sample");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
	glutDisplayFunc(display);
	glutMainLoop();
}

```

 - 效果截图

	![testA1.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA1.2.png)
