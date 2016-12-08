#include <GL/glut.h>   
#include <cmath>
#include <iostream>
using namespace std;

#define M_PI 3.14159265358979323846

static float c = M_PI / 180.0f; //弧度和角度转换参数  
static int du = 90, oldmy = -1, oldmx = -1; //du是视点绕y轴的角度,opengl里默认y轴是上方向  
static float r = 1.5f, h = 0.0f; //r是视点绕y轴的半径,h是视点高度即在y轴上的坐标  
static float alpha_disk1 = 1.0;
static float alpha_disk2 = 1.0;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };//环境光
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//散射光
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//镜面光
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//光源位置

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0, 0, 0, 1 };
	GLfloat mat_shininess[] = { 50.0 };//光泽度 范围在[0.0,128.0]，值越大亮点越小、更亮。

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHT0);	
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 
	glLoadIdentity(); 
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0); 
	//cout << r*cos(c*du) << " " << r*sin(c*du) << endl; 

	GLfloat mat_teapot[] = {1,0,0,0 };//散射颜色
	GLfloat mat_disk1[] = {0,1,0,alpha_disk1};
	GLfloat mat_disk2[] = { 0, 0, 1,alpha_disk2 }; 

	//球体
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_teapot); //所有顶点的alpha值都是材料的散射颜色的alpha值 
	glPushMatrix(); 
	glutSolidSphere(0.5, 60, 60);
	glPopMatrix(); 

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	//圆盘1 绿色
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_disk1);
	glPushMatrix();  
	GLUquadricObj *quadricObj1 = gluNewQuadric();
	gluDisk(quadricObj1, 0, 0.7, 50, 50); 
	glPopMatrix();

	//圆盘2 蓝色
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_disk2);
	glPushMatrix();  
	glRotatef(100, 0, 1, 0);
	GLUquadricObj *quadricObj2 = gluNewQuadric();
	gluDisk(quadricObj2, 0, 0.7, 50, 50); 
	glPopMatrix();
	 
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);   

	glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
	switch (tolower(key))
	{
	case 'a':
		alpha_disk1 -= 0.2;
		if (alpha_disk1 <= 0.0)
			alpha_disk1 = 0.0;
		glutPostRedisplay();
		break;
	case 'd':
		alpha_disk1 += 0.2;
		if (alpha_disk1 >= 1.0)
			alpha_disk1 = 1.0;
		glutPostRedisplay();
		break;
	case 's':
		alpha_disk2 -= 0.2;
		if (alpha_disk2 <= 0.0)
			alpha_disk2 = 0.0;
		glutPostRedisplay();
		break;
	case 'w':
		alpha_disk2 += 0.2;
		if (alpha_disk2 >= 1.0)
			alpha_disk2 = 1.0;
		glutPostRedisplay();
		break; 
	}
}

void Mouse(int button, int state, int x, int y) //处理鼠标点击  
{
	if (state == GLUT_DOWN) //记录鼠标在窗口中的初始坐标  
	{
		oldmx = x;
		oldmy = y;
	}		
}
void onMouseMove(int x, int y) //处理鼠标拖动  
{
	du += x - oldmx; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上 左右转   
	h += 0.03f*(y - oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上 上下转   
	if (h>1.0f) 
		h = 1.0f; //视点y坐标作一些限制，不会使视点太奇怪  
	else if (h<-1.0f) 
		h = -1.0f;
	oldmx = x, oldmy = y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备  
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)w / h, 0.01f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
}

void printOpenGLMessage()
{
	cout << "OpenGL实现厂商的名字：" << glGetString(GL_VENDOR) << endl;
	cout << "渲染器标识符：" << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL工具库版本：" << gluGetString(GLU_VERSION) << endl;
	cout << "OOpenGL实现的版本号：" << glGetString(GL_VERSION) << endl;
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH|GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGL");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);   
	glutKeyboardFunc(keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	printOpenGLMessage();
	glutMainLoop();
	return 0;
}

