#include <time.h>
#include "OpenglIndex.h"

Scene mainScene;
double deltaTime;//Toʵ��
int lastTime;

void Initial()
{
	deltaTime = 1000.0f / 60;
	lastTime = GetTickCount();

	glEnable(GL_DEPTH_TEST | GL_FOG);	// ������Ȳ���
	glFrontFace(GL_CCW);		// ָ����ʱ���Ʒ���ʾ���������
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);	//����

	//��������
	//glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	
	if (!mainScene.skyBox.init())
	{
		MessageBox(NULL, "��ʼ�����ʧ��!", "����", MB_OK);
		exit(0);
	}
	SetScene();
	SetLight();

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
	gluPerspective(45.0, fAspect, 1.0, 1500.0);

	/*
	GLfloat nRange = 100.0f;
	if (w <= h)
	glOrtho(-nRange, nRange, nRange*h / w, -nRange*h / w, -nRange*2.0f + 300, nRange*2.0f + 300);
	else
	glOrtho(-nRange*w / h, nRange*w / h, nRange, -nRange, -nRange*2.0f + 300, nRange*2.0f + 300);
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	//��������ʾ������
	ShowCursor(false);
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 //����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int time = GetTickCount();
	int delta = time - lastTime;
	deltaTime = delta / 1000.0;
	lastTime = time;


	mainScene.Update();
	mainScene.Render();
	glutSwapBuffers();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, TimerFunc, 1);
}
