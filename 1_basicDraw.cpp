#include <GL\glut.h> //glutͷ�ļ����Ѱ���<GL\gl.h>��<GL\glu.h>�ļ���

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//����������ڴ�Ϊ�����ɫ���壬���������GL_DEPTH_BUFFER_BIT�ȡ�
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//�����ɫ����Ϊ��ɫ
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//���ƾ��Σ��ĸ������ֱ������������ 
	glFlush();//ǿ��ˢ�£���֤ǰ���OpenGL�����ܹ�ִ�У������Ǵ洢�ڻ������еȴ�����OpenGL���
}

//argc�������
//argc[0]�ļ�·�����ƣ�������ֵΪ���������
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);//��glut��ʼ������������������ǰ����һ��
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//���õ����壬RGB��ɫ����
	glutCreateWindow(argv[0]);//��������
	glutInitWindowSize(500,500);//��ʼ�����ڴ�С
	glutInitWindowPosition(500,500);//��ʼ������λ��
	glutDisplayFunc(display);//���û�ͼ����
	glutMainLoop();//���ڱ�����ʱ������������ʾ����Ļ�ϣ����ǽ�����Ϣѭ����������ʾ����Ļ�ϣ������ڹر�ʱ�������ء�
	return 0;
}