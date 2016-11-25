#include <GL\glut.h> 
 
//�������ص����� GL_POSITION
// 1.�����Թ�Դ����Դλ������Զ���������ߵ����������ʱ��������Ϊ���еĹ��߶���ƽ�е�  �磺̫��
// 2.λ���Թ�Դ���ڳ����е�׼ȷλ�þ��������Գ�����������Ч��������˵�Ǿ����˹��ߵķ��� �磺̨��

void init()
{
	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[] = {50.0};
	

	//��1��GL_POSITION(x,y,z,w) 
	//�����Թ�Դ��wΪ0�� Ĭ�������GL_POSITIONΪ(0,0,1,0)����ָ��z�Ḻ����ķ����Թ�Դ�� 	
	GLfloat light_position[] = {1.0,1.0,1.0,1.0};
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0};//���ɢ��ǿ�ȣ�light0��Ĭ��ֵΪ��ɫ������Ϊ��ɫ�� ��ӽ���������Ĺ� 
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0};//��ľ���ǿ�ȣ�light0��Ĭ��ֵΪ��ɫ������Ϊ��ɫ�� �봴�������Ч����ͨ����GL_SPECULAR��GL_DIFFUSE����ֵ������ͬ

	GLfloat white_light[] = {1.0,1.0,1.0,1.0};
	GLfloat lmodel_ambient[] = {0.1,0.1,0.1,1.0};

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	glLightfv(GL_LIGHT0,GL_POSITION,light_position);//��Դλ������(x,y,z,w)
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);//������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);//ɢ��� 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//���淴��� 

	//��2��GL_POSITION(x,y,z,w) 
	//λ���Թ�Դ��wΪ��0ֵ��Ĭ�������λ���Թ�Դ�����з�������ߣ�������ͨ���ѹ�Դ����Ϊ�۹�ƣ���������Χ������׵���

	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0};
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = {-0.2,2.0,1.0,1.0};
	GLfloat spot_direction[] = {-1.0,-1.0,0.0};//�۹��λ��

	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	 
	//�����⡢ɢ���;�����ǿ�Ƚ���˥����ֻ�з�����ȫ�ֻ������ǿ��û��˥��
	//����˥������
	glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);//����׶�нǲ�������Ϊ45�� 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);//ָ���۹�Ƶķ���ȷ����׶���� Ĭ��Ϊ��0��0��-1.0������ָ��z��ĸ�����
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);//Ĭ��Ϊ0�����ƹ�ļ��жȣ����ǿ����������ߣ���ԵԽ����˥�������ǹ��߷�������ߺ��������䶥��ķ���֮��нǵ�����ֵ�ľ۹�ָ���η���

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

//��������
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
 	glutSolidTeapot(0.9);//������ 
	glFlush();
}

//���ڱ仯
void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}