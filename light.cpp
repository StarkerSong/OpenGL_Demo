#include <GL\glut.h> 
 
//与光照相关的设置 GL_POSITION
// 1.方向性光源：光源位于无限远处，当光线到达物体表面时，可以认为所有的光线都是平行的  如：太阳
// 2.位置性光源：在场景中的准确位置决定了他对场景所产生的效果。具体说是决定了光线的方向。 如：台灯

void init()
{
	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[] = {50.0};
	

	//（1）GL_POSITION(x,y,z,w) 
	//方向性光源，w为0， 默认情况下GL_POSITION为(0,0,1,0)定义指向z轴负方向的方向性光源。 	
	GLfloat light_position[] = {1.0,1.0,1.0,1.0};
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0};//光的散射强度（light0的默认值为白色，其他为黑色） 最接近我们想象的光 
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0};//光的镜面强度（light0的默认值为白色，其他为黑色） 想创建逼真的效果，通常将GL_SPECULAR和GL_DIFFUSE参数值设置相同

	GLfloat white_light[] = {1.0,1.0,1.0,1.0};
	GLfloat lmodel_ambient[] = {0.1,0.1,0.1,1.0};

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	glLightfv(GL_LIGHT0,GL_POSITION,light_position);//光源位置坐标(x,y,z,w)
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);//环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);//散射光 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//镜面反射光 

	//（2）GL_POSITION(x,y,z,w) 
	//位置性光源，w为非0值，默认情况下位置性光源向所有方向发射光线，但可以通过把光源定义为聚光灯，把照明范围限制在椎体里。

	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0};
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = {-0.2,2.0,1.0,1.0};
	GLfloat spot_direction[] = {-1.0,-1.0,0.0};//聚光灯位置

	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	 
	//环境光、散射光和镜面光的强度进行衰减，只有发射光和全局环境光的强度没有衰减
	//计算衰减因子
	glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);//将光锥切角参数设置为45度 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);//指定聚光灯的方向，确定光锥的轴 默认为（0，0，-1.0）光线指向z轴的负方向
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);//默认为0，控制光的集中度，光的强度在中心最高，边缘越弱，衰减幅度是光线方向与光线和它所照射顶点的方向之间夹角的余弦值的聚光指数次方。

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

//绘制物体
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
 	glutSolidTeapot(0.9);//定义茶壶 
	glFlush();
}

//窗口变化
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