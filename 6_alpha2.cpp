#include <GL/glut.h>   
#include <cmath>
#include <iostream>
using namespace std;

#define M_PI 3.14159265358979323846

static float c = M_PI / 180.0f; //���ȺͽǶ�ת������  
static int du = 90, oldmy = -1, oldmx = -1; //du���ӵ���y��ĽǶ�,opengl��Ĭ��y�����Ϸ���  
static float r = 1.5f, h = 0.0f; //r���ӵ���y��İ뾶,h���ӵ�߶ȼ���y���ϵ�����  
static float alpha_disk1 = 1.0;
static float alpha_disk2 = 1.0;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };//������
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//ɢ���
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//�����
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//��Դλ��

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0, 0, 0, 1 };
	GLfloat mat_shininess[] = { 50.0 };//����� ��Χ��[0.0,128.0]��ֵԽ������ԽС��������

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

	GLfloat mat_teapot[] = {1,0,0,0 };//ɢ����ɫ
	GLfloat mat_disk1[] = {0,1,0,alpha_disk1};
	GLfloat mat_disk2[] = { 0, 0, 1,alpha_disk2 }; 

	//����
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_teapot); //���ж����alphaֵ���ǲ��ϵ�ɢ����ɫ��alphaֵ 
	glPushMatrix(); 
	glutSolidSphere(0.5, 60, 60);
	glPopMatrix(); 

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	//Բ��1 ��ɫ
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_disk1);
	glPushMatrix();  
	GLUquadricObj *quadricObj1 = gluNewQuadric();
	gluDisk(quadricObj1, 0, 0.7, 50, 50); 
	glPopMatrix();

	//Բ��2 ��ɫ
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

void Mouse(int button, int state, int x, int y) //���������  
{
	if (state == GLUT_DOWN) //��¼����ڴ����еĳ�ʼ����  
	{
		oldmx = x;
		oldmy = y;
	}		
}
void onMouseMove(int x, int y) //��������϶�  
{
	du += x - oldmx; //����ڴ���x�᷽���ϵ������ӵ��ӵ���y��ĽǶ��� ����ת   
	h += 0.03f*(y - oldmy); //����ڴ���y�᷽���ϵĸı�ӵ��ӵ��y������ ����ת   
	if (h>1.0f) 
		h = 1.0f; //�ӵ�y������һЩ���ƣ�����ʹ�ӵ�̫���  
	else if (h<-1.0f) 
		h = -1.0f;
	oldmx = x, oldmy = y; //�Ѵ�ʱ�����������Ϊ��ֵ��Ϊ��һ�μ���������׼��  
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
	cout << "OpenGLʵ�ֳ��̵����֣�" << glGetString(GL_VENDOR) << endl;
	cout << "��Ⱦ����ʶ����" << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL���߿�汾��" << gluGetString(GLU_VERSION) << endl;
	cout << "OOpenGLʵ�ֵİ汾�ţ�" << glGetString(GL_VERSION) << endl;
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

