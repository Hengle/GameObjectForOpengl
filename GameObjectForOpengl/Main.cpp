////////////////////////////////////////////////////////////////////////////
//ʵ��Ҫ��(1)���OpenGL�еı任���̡�                                   //
//          (2)���͸��ͶӰ��ƽ��ͶӰ�Ĳ�ͬ��                             // 
//          (3)��Ӵ���ʵ��̫����������������˶�ģ�͡�                   //
//          (4)�˽���Ȳ��ԡ�                                             //
//          (5)ͨ���任�����۲��λ���뷽���                             //
//          (6)�������ģ��                                               //
////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include"GameObject.h"

GLfloat distance = 300;
GLfloat yRot = 0;
GLfloat xRot = 30;
Scene mainScene;

class Earth :public GameObject {
public:
	Earth() {

	}
	void Render() override {
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.2f, 0.2f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glutSolidSphere(5, 15, 15);
	}
};

void SetScene() {
	mainScene.SetCamera(new Vector3(0, 0, -200), new Vector3(0, 0, 0));
	mainScene.AddGameObject(new Earth());
}

void Initial()
{
	glEnable(GL_DEPTH_TEST | GL_FOG);	// ������Ȳ���
										//glEnable(GL_LIGHTING);
	glFrontFace(GL_CCW);		// ָ����ʱ���Ʒ���ʾ���������

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//����

	SetScene();
	mainScene.Awake();


	GLfloat sun_light_position[] = { 0.0f, 0, -distance, 1.0f };
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	mainScene.Start();
}



void ChangeSize(int w, int h)
{
	if (h == 0)	h = 1;

	// ���������ߴ�
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �����޼��ռ�
	GLfloat fAspect;
	fAspect = (float)w / (float)h;
	gluPerspective(45.0, fAspect, 1.0, 500.0);

	/*
	GLfloat nRange = 100.0f;
	if (w <= h)
	glOrtho(-nRange, nRange, nRange*h / w, -nRange*h / w, -nRange*2.0f + 300, nRange*2.0f + 300);
	else
	glOrtho(-nRange*w / h, nRange*w / h, nRange, -nRange, -nRange*2.0f + 300, nRange*2.0f + 300);
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

float Angle(float in) {
	while (in >= 360) {
		in -= 360;
	}
	return in;
}


GLfloat step = 1.0f;

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	mainScene.Render();
	glutSwapBuffers();

}
void RenderScene2(void)
{
	// ��ԭ�Ӻ���ת�ĽǶ�
	static float fElect1 = 0.0f;
	//���õ�����ת�ٶ�
	GLfloat earthRotateSpeed = 1.0f / 12;
	//���õ�����ת�ٶ�
	GLfloat earthSelfRotateSpeed = 30;
	//���������Ƶ����ٶ�
	GLfloat moonRotateSpeed = 1;
	//����������ת�ٶ�
	GLfloat moonSelfRotateSpeed = -moonRotateSpeed;

	GLfloat rSun = 20;
	GLfloat rEarth = 5;
	GLfloat rMoon = 2;

	GLfloat disSE = 100;
	GLfloat disEM = 20;





	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	//��ͼ����z�Ḻ���ƶ�
	glTranslatef(0.0f, 0.0f, -distance);
	//glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);


	// ���ƻ�ɫ��̫��

	GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.3f, 1.0f };
	GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.0f, 1.0f };
	GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_mat_emission[] = { 0.8f, 0.8f, 0.0f, 1.0f };
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

	GLUquadric *obj = gluNewQuadric();
	//gluSphere(obj, rSun, 30, 30);

	glPushMatrix();
	glRotatef(1,20, 40, 60);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, 0, 0);
	glutSolidCube(50);
	glPopMatrix();


	//���浱ǰ��ģ����ͼ����
	glPushMatrix();
	glRotatef(Angle(fElect1*earthRotateSpeed), 0.0f, 1.0f, 0.0f);//��y����תһ���ĽǶ�
	glTranslatef(disSE, 0.0f, 0.0f);//ƽ��һ�ξ���
	glRotatef(Angle(fElect1*earthRotateSpeed), 0.0f, -1.0f, 0.0f);//��y������һ���ĽǶ�
	glRotatef(30, 0.0f, 0.0f, 1.0f);


	glPushMatrix();
	glRotatef(Angle(fElect1*earthSelfRotateSpeed), 0.0f, 1.0f, 0.0f);//��ת
	GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat earth_mat_diffuse[] = { 0.2f, 0.2f, 0.5f, 1.0f };
	GLfloat earth_mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat earth_mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	glutSolidSphere(rEarth, 15, 15);//��������
	glPopMatrix();

	glPushMatrix();
	glRotatef(Angle(fElect1*moonRotateSpeed), 0.0f, 1.0f, 0.0f);
	glTranslatef(disEM, 0, 0);
	glRotatef(Angle(fElect1*moonSelfRotateSpeed), 0, 1, 0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidSphere(rMoon, 8, 8);//��������
	glPopMatrix();

	glPopMatrix();

	// ������ת����
	fElect1 += step;

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		step = 1.0f / 10;
		break;
	case '2':
		step = 1.0f;
		break;
	case '3':
		step = 10.0f;
		break;
	case '4':
		step = 30.0f;
		break;
	case 'w':
	case 'W':
		distance--;
		break;
	case 's':
	case 'S':
		distance++;
		break;
	case 'a':
	case 'A':
		yRot += 10;
		break;
	case 'd':
	case 'D':
		yRot -= 10;
		break;
	case 'q':
	case 'Q':
		xRot += 3;
		break;
	case 'e':
	case 'E':
		xRot -= 3;
		break;
	}
	//glutPostRedisplay();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("�յ���ģ��");

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(Keyboard);//������Ӧ�ص�����
	glutTimerFunc(100, TimerFunc, 1);

	Initial();
	glutMainLoop();

	return 0;
}
