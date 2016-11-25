#include <gl\glut.h>

#include <FTGL\FTGLPixmapFont.h>
#include <FTGL\ftgl.h> 

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4
#define MAXCHAR 300
static float solidZ = MAXZ;
static float transparentZ = MINZ;
static float spin = 0;
static GLuint sphereList, cubeList;
static GLfloat transparent = 1.0;

int width = 100;
int height = 100;
  
FTGLPixmapFont *font = NULL;

static void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
	GLfloat mat_shininess[] = { 100, 0 };
	GLfloat position[] = { 0.5, 0.5, 1.0, 0.0 }; 

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);	 

	sphereList = glGenLists(1);
	glNewList(sphereList, GL_COMPILE);
	glutSolidSphere(0.4, 50, 50);
	glEndList();
	cubeList = glGenLists(1);
	glNewList(cubeList, GL_COMPILE);
	glutSolidCube(0.6); 
	glEndList();  

	font = new FTGLPixmapFont("C:\\WINDOWS\\Fonts\\simhei.ttf");
	if (font->Error())
		return;
	font->FaceSize(20);
}


void display(void)
{
	GLfloat mat_solid[] = { 1, 0, 0.0, 1.0 };
	GLfloat mat_zero[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_transparent[] = { 0.0, 0, 1, transparent };
	GLfloat mat_emission[] = { 0.0, 0.3, 0, 0.6 };
	GLfloat mat_font[] = { 0.0, 0.0, 1.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//�Ȼ��Ʋ�͸�������壬�ٻ���͸����������
	glPushMatrix();
	glTranslatef(-0.15, -0.15, solidZ); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid); 
	glCallList(sphereList);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0.15, 0.15, transparentZ); 
	glRotatef(15.0, 1.0, 1.0, 0.0);
	glRotatef(spin, 0.0, 1.0, 0.0); 

		//FTGL �������
		glPushMatrix();
		glDisable(GL_LIGHTING); //��������������ʱ����Ҫ�رչ���
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glRasterPos3f(0.3, 0.3, 0.3);//�������������꣬ȷ����ǰ��դλ�ã��൱��glVertex�����꣬������ʾ�ַ�����ʼλ��  glWindowPosֱ���Դ�������ָ����դλ��
		wchar_t font_str[] = L"FTGL �����������";
		font->Render(font_str);
		glEnable(GL_LIGHTING);//�������գ���Ⱦ������
		glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_transparent);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glCallList(cubeList);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -15.0, 15.0);
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void animate()
{
	if (solidZ <= MINZ || transparentZ >= MAXZ)
		glutIdleFunc(NULL);
	else{
		solidZ -= ZINC;
		transparentZ += ZINC;
		glutPostRedisplay();
	}
}

void rotate()
{
	if (spin < 360)
		spin += 0.5;
	else
		spin = 0.0;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (tolower(key)){
	case 'a': 
		solidZ = MAXZ;
		transparentZ = MINZ;
		glutIdleFunc(animate);
		break;
	case 'r': 
		solidZ = MAXZ;
		transparentZ = MINZ;
		glutPostRedisplay();
		break;
	case 'z'://��ת������
		glutIdleFunc(rotate);
		break;
	case 27:
		exit(0);
		break;
	}
}

void mouse(int button,int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			transparent += 0.1;
			cout <<"������͸���ȣ�" <<transparent << endl;
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			transparent -= 0.1;
			cout <<"������͸���ȣ�"<< transparent << endl;
			glutPostRedisplay();
		}
		break;
	}
}

void printOpenGLInformation()
{
	cout << "OpenGLʵ�ֳ��̵����֣�" << glGetString(GL_VENDOR) << endl;
	cout << "��Ⱦ����ʶ����" << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL���߿�汾��" << gluGetString(GLU_VERSION) << endl;
	cout << "OOpenGLʵ�ֵİ汾�ţ�" << glGetString(GL_VERSION) << endl;
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	printOpenGLInformation();
	glutMainLoop();
	return 0;
}