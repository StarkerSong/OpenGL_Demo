#include <GL\glut.h>

int Width = 500;
int Height = 500;

void init()
{
	glClearColor(0,0,0,1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -2);
	
	//���ƺ���������
	glViewport(0, 0, Width, Height);
	glPushMatrix();
	glColor3f(1.0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(-Width/2.0,0,0);
	glVertex3f(Width / 2.0, 0, 0);
	glVertex3f(0,-Height/2.0,0);
	glVertex3f(0, Height / 2.0, 0);
	glEnd();
	glPopMatrix();

	//��������
	glViewport(0,Height/2,Width/2,Height/2);
	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(45, 1, 1, 0);
	glutWireCube(1.5);
	glPopMatrix();

	//���Ʋ��
	glViewport(Width/2,Height/2,Width/2,Height/2);
	glPushMatrix();
	glColor3f(1,1,0);
	glutWireTeapot(1.0);
	glPopMatrix();

	//����Բ׶
	glViewport(0, 0, Width / 2, Height / 2);
	glPushMatrix();
	glColor3f(0, 1, 1);
	glRotatef(45, 1, 1, 0);//��x��y����ת45��
	glutWireCone(1.0, 1.0, 10, 10);//base:Բ׶�뾶 height��Բ׶�ĸ߶�
	glPopMatrix();

	//��������
	glViewport(Width / 2, 0, Width / 2, Height / 2);
	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(45, 1, 1, 0);//��x��y����ת45��
	glutWireSphere(1.0, 10, 10);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	Width = w;
	Height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLfloat)w / (GLfloat)h, 0.001, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,500);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}