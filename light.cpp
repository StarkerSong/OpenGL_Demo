#include <GL\glut.h>

//Óë¹âÕÕÏà¹ØµÄÉèÖÃ GL_POSITION
// 1.·½ÏòÐÔ¹âÔ´£º¹âÔ´Î»ÓÚÎÞÏÞÔ¶´¦£¬µ±¹âÏßµ½´ïÎïÌå±íÃæÊ±£¬¿ÉÒÔÈÏÎªËùÓÐµÄ¹âÏß¶¼ÊÇÆ½ÐÐµÄ  Èç£ºÌ«Ñô
// 2.Î»ÖÃÐÔ¹âÔ´£ºÔÚ³¡¾°ÖÐµÄ×¼È·Î»ÖÃ¾ö¶¨ÁËËû¶Ô³¡¾°Ëù²úÉúµÄÐ§¹û¡£¾ßÌåËµÊÇ¾ö¶¨ÁË¹âÏßµÄ·½Ïò¡£ Èç£ºÌ¨µÆ

void init()
{
	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[] = {50.0};
	

	//£¨1£©GL_POSITION(x,y,z,w) 
	//·½ÏòÐÔ¹âÔ´£¬wÎª0£¬ Ä¬ÈÏÇé¿öÏÂGL_POSITIONÎª(0,0,1,0)¶¨ÒåÖ¸ÏòzÖá¸º·½ÏòµÄ·½ÏòÐÔ¹âÔ´¡£ 	
	GLfloat light_position[] = {1.0,1.0,1.0,1.0};
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0};//¹âµÄÉ¢ÉäÇ¿¶È£¨light0µÄÄ¬ÈÏÖµÎª°×É«£¬ÆäËûÎªºÚÉ«£© ×î½Ó½üÎÒÃÇÏëÏóµÄ¹â 
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0};//¹âµÄ¾µÃæÇ¿¶È£¨light0µÄÄ¬ÈÏÖµÎª°×É«£¬ÆäËûÎªºÚÉ«£© Ïë´´½¨±ÆÕæµÄÐ§¹û£¬Í¨³£½«GL_SPECULARºÍGL_DIFFUSE²ÎÊýÖµÉèÖÃÏàÍ¬

	GLfloat white_light[] = {1.0,1.0,1.0,1.0};
	GLfloat lmodel_ambient[] = {0.1,0.1,0.1,1.0};

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	glLightfv(GL_LIGHT0,GL_POSITION,light_position);//¹âÔ´Î»ÖÃ×ø±ê(x,y,z,w)
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);//»·¾³¹â
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);//É¢Éä¹â 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//¾µÃæ·´Éä¹â 

	//£¨2£©GL_POSITION(x,y,z,w) 
	//Î»ÖÃÐÔ¹âÔ´£¬wÎª·Ç0Öµ£¬Ä¬ÈÏÇé¿öÏÂÎ»ÖÃÐÔ¹âÔ´ÏòËùÓÐ·½Ïò·¢Éä¹âÏß£¬µ«¿ÉÒÔÍ¨¹ý°Ñ¹âÔ´¶¨ÒåÎª¾Û¹âµÆ£¬°ÑÕÕÃ÷·¶Î§ÏÞÖÆÔÚ×µÌåÀï¡£

	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0};
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = {-0.2,2.0,1.0,1.0};
	GLfloat spot_direction[] = {-1.0,-1.0,0.0};//¾Û¹âµÆÎ»ÖÃ

	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	 
	//»·¾³¹â¡¢É¢Éä¹âºÍ¾µÃæ¹âµÄÇ¿¶È½øÐÐË¥¼õ£¬Ö»ÓÐ·¢Éä¹âºÍÈ«¾Ö»·¾³¹âµÄÇ¿¶ÈÃ»ÓÐË¥¼õ
	//¼ÆËãË¥¼õÒò×Ó
	glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);//½«¹â×¶ÇÐ½Ç²ÎÊýÉèÖÃÎª45¶È 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);//Ö¸¶¨¾Û¹âµÆµÄ·½Ïò£¬È·¶¨¹â×¶µÄÖá Ä¬ÈÏÎª£¨0£¬0£¬-1.0£©¹âÏßÖ¸ÏòzÖáµÄ¸º·½Ïò
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);//Ä¬ÈÏÎª0£¬¿ØÖÆ¹âµÄ¼¯ÖÐ¶È£¬¹âµÄÇ¿¶ÈÔÚÖÐÐÄ×î¸ß£¬±ßÔµÔ½Èõ£¬Ë¥¼õ·ù¶ÈÊÇ¹âÏß·½ÏòÓë¹âÏßºÍËüËùÕÕÉä¶¥µãµÄ·½ÏòÖ®¼ä¼Ð½ÇµÄÓàÏÒÖµµÄ¾Û¹âÖ¸Êý´Î·½¡£

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

//»æÖÆÎïÌå
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
 	glutSolidTeapot(0.9);//¶¨Òå²èºø 
	glFlush();
}

//´°¿Ú±ä»¯
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