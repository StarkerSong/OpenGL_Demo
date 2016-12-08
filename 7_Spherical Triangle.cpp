#define   _CRT_SECURE_NO_WARNINGS 
#include <GL/glut.h>   
#include <cmath>
#include <iostream>
#include <iomanip>
#include "stdlib.h" 
#include "stdio.h" 
#include "math.h" 
using namespace std;
 
#define M_PI 3.14159265358979323846

static float c = M_PI / 180.0f; //弧度和角度转换参数  
static int du = 90, oldmy = -1, oldmx = -1; //du是视点绕y轴的角度,opengl里默认y轴是上方向  
static float r = 1.5f, h = 0.0f; //r是视点绕y轴的半径,h是视点高度即在y轴上的坐标  
static float alpha_disk1 = 1.0;
static float alpha_disk2 = 1.0;

typedef struct {
	double x, y, z;
} XYZ;
typedef struct {
	XYZ p1, p2, p3;
} FACET3; 

XYZ MidPoint(XYZ, XYZ);
void Normalise(XYZ *);

/*
Return the midpoint between two vectors
*/
XYZ MidPoint(XYZ p1, XYZ p2)
{
	XYZ p;

	p.x = (p1.x + p2.x) / 2;
	p.y = (p1.y + p2.y) / 2;
	p.z = (p1.z + p2.z) / 2;

	return(p);
}

/*
Normalise a vector
*/
void Normalise(XYZ *p)
{
	double length;

	length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
	if (length != 0) {
		p->x /= length;
		p->y /= length;
		p->z /= length;
	}
	else {
		p->x = 0;
		p->y = 0;
		p->z = 0;
	}
}

void drawSpherical()
{
	glNewList(1, GL_COMPILE);
	int i, j;
	int n = 0, nstart;
	int iterations = 7; //迭代次数
	double theta[3] = { 0, 0, 90 }, phi[3] = { 90, 0, 0 }; // 直角坐标系下的角度
	XYZ p1, p2, p3;
	// 初始化三角顶点  
	FACET3 *f = (FACET3 *)malloc(sizeof(FACET3));

	f[0].p1.x = cos(phi[0]) * cos(theta[0]);
	f[0].p1.y = cos(phi[0]) * sin(theta[0]);
	f[0].p1.z = sin(phi[0]);
	f[0].p2.x = cos(phi[1]) * cos(theta[1]);
	f[0].p2.y = cos(phi[1]) * sin(theta[1]);
	f[0].p2.z = sin(phi[1]);
	f[0].p3.x = cos(phi[2]) * cos(theta[2]);
	f[0].p3.y = cos(phi[2]) * sin(theta[2]);
	f[0].p3.z = sin(phi[2]);

	n = 1;

	for (i = 1; i<iterations; i++) {
		nstart = n;

		for (j = 0; j<nstart; j++) {
			f = (FACET3 *)realloc(f, (n + 3)*sizeof(FACET3));

			// 新的侧面复制副本
			f[n] = f[j];
			f[n + 1] = f[j];
			f[n + 2] = f[j];

			// 计算中点并且规范化
			p1 = MidPoint(f[j].p1, f[j].p2);
			Normalise(&p1);
			p2 = MidPoint(f[j].p2, f[j].p3);
			Normalise(&p2);
			p3 = MidPoint(f[j].p3, f[j].p1);
			Normalise(&p3);

			// 替换为当前三角面
			f[j].p2 = p1;
			f[j].p3 = p3;

			// 在三角面中改变顶点  
			f[n].p1 = p1;
			f[n].p3 = p2;
			f[n + 1].p1 = p3;
			f[n + 1].p2 = p2;
			f[n + 2].p1 = p1;
			f[n + 2].p2 = p2;
			f[n + 2].p3 = p3;
			n += 3;
		}
	}

	fprintf(stderr, "%d facets generated\\n", n);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(f[0].p1.x, f[0].p1.y, f[0].p1.z);
	glVertex3f(0, 0, 0);
	glVertex3f(f[0].p2.x, f[0].p2.y, f[0].p2.z);
	glVertex3f(0, 0, 0);
	glVertex3f(f[0].p3.x, f[0].p3.y, f[0].p3.z);
	glEnd();

	for (int i = 0; i < n; ++i)
	{
		glBegin(GL_TRIANGLES);
		glNormal3f(f[i].p1.x, f[i].p1.y, f[i].p1.z);
		glVertex3f(f[i].p1.x, f[i].p1.y, f[i].p1.z);
		glNormal3f(f[i].p2.x, f[i].p2.y, f[i].p2.z);
		glVertex3f(f[i].p2.x, f[i].p2.y, f[i].p2.z);
		glNormal3f(f[i].p3.x, f[i].p3.y, f[i].p3.z);
		glVertex3f(f[i].p3.x, f[i].p3.y, f[i].p3.z);
		glEnd();
	}
	glEndList();
}

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

	drawSpherical();
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

	////球体
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_teapot); //所有顶点的alpha值都是材料的散射颜色的alpha值 
	//glPushMatrix(); 
	//glutSolidSphere(0.5, 60, 60);
	//glPopMatrix(); 

	//glEnable(GL_BLEND);
	//glDepthMask(GL_FALSE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	////圆盘1 绿色
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_disk1);
	//glPushMatrix();  
	//GLUquadricObj *quadricObj1 = gluNewQuadric();
	//gluDisk(quadricObj1, 0, 0.7, 50, 50); 
	//glPopMatrix();

	////圆盘2 蓝色
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_disk2);
	//glPushMatrix();  
	//glRotatef(100, 0, 1, 0);
	//GLUquadricObj *quadricObj2 = gluNewQuadric();
	//gluDisk(quadricObj2, 0, 0.7, 50, 50); 
	//glPopMatrix();
	// 
	//glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);   

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_teapot);

	glCallList(1);
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
		//if (w <= h)
		//	glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -15.0, 15.0);
		//else
		//	glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -15.0, 15.0);
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

