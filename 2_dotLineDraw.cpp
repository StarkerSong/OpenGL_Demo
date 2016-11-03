#include <GL\glut.h>

int Width = 500;//����Ĭ�ϴ��ڴ�С��ֵ
int Height = 500;

//��ʼ������
void init()
{
	glClearColor(0,0,0,1);//�����ɫ����Ϊ��ɫ
	glShadeModel(GL_SMOOTH);//������ɫģʽ������һ��ΪGL_SMOOTH��GL_FLAT
	glEnable(GL_DEPTH_TEST);//�������
}

//����ͼ��
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -2);
	
	//���ƺ���������
	glViewport(0, 0, Width, Height);
	glPushMatrix();//���־���״̬
	glColor3f(1.0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(-Width/2.0,0,0);
	glVertex3f(Width / 2.0, 0, 0);
	glVertex3f(0,-Height/2.0,0);
	glVertex3f(0, Height / 2.0, 0);
	glEnd();
	glPopMatrix();//�ָ�����״̬

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

	glutSwapBuffers(); // ˢ�»�ͼ�����ʱ����δִ�е�OpenGL���ִ��
}

//�����ڴ�С�ı�ʱ��glutReshapeFunc���������á����⣬�ú����ڴ��ڳ��α�����ʱ����
void reshape(int w,int h)
{
	h = h ? h : 1;//��ֹhΪ0
	glViewport(0,0,w,h);//���ӿ�����Ϊ��������
	Width = w;
	Height = h;
	glMatrixMode(GL_PROJECTION);//���õ�ǰ����ΪͶӰ����ʵ�����ǽ���ǰ״̬���뵽��ջ��
	glLoadIdentity();
	gluPerspective(90, (GLfloat)w / (GLfloat)h, 0.001, 10);//����ü�����
	glMatrixMode(GL_MODELVIEW);//ѡ��ģ����ͼ����
	glLoadIdentity();//��������ϵͳ
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,500);
	init();//��glutDisplayFunc���Ե���˳�򣬲��һ�����ʡ�ԣ�ʡ�Ժ����Ĭ�����ã�����Ϊ��ɫ
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}