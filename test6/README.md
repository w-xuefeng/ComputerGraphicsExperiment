# ComputerGraphicsExperiment
Computer graphics experiment 计算机图形学实验

## 实验6——动画

 - 实验内容：
 - 1）.利用双缓冲区技术完成2D正方形绕中心点旋转动画；
 - 2）.编程绘制3D动画，下图左绕Y轴旋转，下图右绕顶点（1，1，1）X方向旋转。

 - ![testQ6.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/Q/testQ6.2.png)


## 实验代码

 - 1.test6.1

```c++
#include<stdio.h>
#include<gl/GLUT.h>


static GLfloat spin = 0.0;


void init(void){
	glClearColor(0.0,0.0,0.0,0.0);	
	//将清空颜色设置为黑
	glShadeModel(GL_FLAT);
	//OpenGL1.0提供的接口。作用：设置着色模式。参数mode可以是GL_SMOOTH（默认值）或GL_FLAT。采用恒定着色时（即GL_FLAT），使用图元中某个顶点的颜色来渲染整个图元
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	//清除颜色缓存
	glPushMatrix();
	//将当前矩阵压栈（保存现场）
	glRotatef(spin,0.0,0.0,1.0);
	//旋转方向，遵循右手原则
	glColor3f(1.0,1.0,1.0);
	glRectf(-25.0,-25.0,25.0,25.0);
	glPopMatrix();
	glutSwapBuffers();
	//双缓存技术的函数，作用为交换两个缓冲区的指针
}


void spinDisplay(void){
	spin = spin + 0.04;
	if ( spin > 360.0){
		spin = spin - 360.0;
	}
	glutPostRedisplay();
	//glutPostRedisplay 标记当前窗口需要重新绘制。通过glutMainLoop下一次循环时，窗口显示将被回调以重新显示窗口的正常面板
}


void reshape(int w,int h){
	glViewport(0,0,(GLsizei) w,(GLsizei) h);
	//函数作用：用一个视景体截取图像
	glMatrixMode(GL_PROJECTION);
	//mode 指定哪一个矩阵堆栈是下一个矩阵操作的目标,参数表示接下来要进行投影相关的操作
	glLoadIdentity();
	//设置当前变化矩阵为单位矩阵；单位矩阵就是对角线上都是1，其余元素皆为0的矩阵。然后复位
	glOrtho(-50.0,50.0,-50.0,50.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	//进行视景相关的操作
	glLoadIdentity();
}


void mouse(int button,int state,int x,int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
			//glutIdleFunc函数如果启用，这个idle function会被不断调用，直到有窗口事件发生
			break;
		case GLUT_RIGHT_BUTTON:
			if(state == GLUT_DOWN)
			glutIdleFunc(NULL);
			break;
		default:break;
	}
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);//每次重绘场景时调用
	glutReshapeFunc(reshape);//每次窗口改变时调用
	glutMouseFunc(mouse);//每次使用鼠标时调用
	glutMainLoop();
	return 0;
}


```

 - 效果截图

    ![testA4.1](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA6.1.gif)

 - 2.test6.2

 ```c++



```

 - 效果截图

    ![testA4.2](https://raw.githubusercontent.com/w-xuefeng/ComputerGraphicsExperiment/master/assets/A/testA6.2.gif)
