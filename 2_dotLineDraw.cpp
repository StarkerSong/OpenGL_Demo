#include <GL\glut.h>

int Width = 500;//设置默认窗口大小的值
int Height = 500;

//初始化设置
void init()
{
	glClearColor(0,0,0,1);//清除颜色设置为黑色
	glShadeModel(GL_SMOOTH);//设置着色模式，参数一般为GL_SMOOTH或GL_FLAT
	glEnable(GL_DEPTH_TEST);//启用深度
}

//绘制图形
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -2);
	
	//绘制横纵坐标轴
	glViewport(0, 0, Width, Height);
	glPushMatrix();//保持矩阵状态
	glColor3f(1.0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(-Width/2.0,0,0);
	glVertex3f(Width / 2.0, 0, 0);
	glVertex3f(0,-Height/2.0,0);
	glVertex3f(0, Height / 2.0, 0);
	glEnd();
	glPopMatrix();//恢复矩阵状态

	//虚立方体
	glViewport(0,Height/2,Width/2,Height/2);
	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(45, 1, 1, 0);
	glutWireCube(1.5);
	glPopMatrix();

	//绘制茶壶
	glViewport(Width/2,Height/2,Width/2,Height/2);
	glPushMatrix();
	glColor3f(1,1,0);
	glutWireTeapot(1.0);
	glPopMatrix();

	//绘制圆锥
	glViewport(0, 0, Width / 2, Height / 2);
	glPushMatrix();
	glColor3f(0, 1, 1);
	glRotatef(45, 1, 1, 0);//绕x、y轴旋转45度
	glutWireCone(1.0, 1.0, 10, 10);//base:圆锥半径 height：圆锥的高度
	glPopMatrix();

	//绘制球体
	glViewport(Width / 2, 0, Width / 2, Height / 2);
	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(45, 1, 1, 0);//绕x、y轴旋转45度
	glutWireSphere(1.0, 10, 10);
	glPopMatrix();

	glutSwapBuffers(); // 刷新绘图命令，此时所有未执行的OpenGL命令被执行
}

//当窗口大小改变时，glutReshapeFunc函数被调用。此外，该函数在窗口初次被创建时调用
void reshape(int w,int h)
{
	h = h ? h : 1;//防止h为0
	glViewport(0,0,w,h);//将视口设置为整个窗口
	Width = w;
	Height = h;
	glMatrixMode(GL_PROJECTION);//设置当前矩阵为投影矩阵，实际上是将当前状态放入到堆栈中
	glLoadIdentity();
	gluPerspective(90, (GLfloat)w / (GLfloat)h, 0.001, 10);//定义裁剪区域
	glMatrixMode(GL_MODELVIEW);//选择模型视图矩阵
	glLoadIdentity();//重置坐标系统
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,500);
	init();//和glutDisplayFunc可以调换顺序，并且还可以省略，省略后采用默认设置，背景为黑色
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}