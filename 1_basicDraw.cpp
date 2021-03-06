#include <GL\glut.h> //glut头文件（已包含<GL\gl.h>和<GL\glu.h>文件）

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//清除操作。在此为清除颜色缓冲，还可以清除GL_DEPTH_BUFFER_BIT等。
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//清除颜色设置为黑色
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//绘制矩形，四个参数分别代表横纵坐标 
	glFlush();//强制刷新，保证前面的OpenGL命令能够执行，而不是存储在缓冲区中等待其他OpenGL命令。
}

//argc命令个数
//argc[0]文件路径名称，其他的值为输入的命令
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);//对glut初始化，在所有其他方法前调用一次
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//设置单缓冲，RGB颜色索引
	glutInitWindowSize(1000,500);//初始化窗口大小
	glutInitWindowPosition(500,500);//初始化窗口位置
	glutCreateWindow(argv[0]);//创建显示窗口
	glutDisplayFunc(display);//调用绘图函数
	glutMainLoop();//窗口被创建时，并不立即显示在屏幕上，而是进行消息循环将窗口显示在屏幕上，当窗口关闭时函数返回。
	return 0;
}