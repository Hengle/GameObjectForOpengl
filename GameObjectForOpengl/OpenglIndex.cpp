#include <time.h>
#include "OpenglIndex.h"

GameObject* currentGameObjectPointer = NULL;

Scene mainScene;
double deltaTime;//Toʵ��
int lastTime;

void Initial() {
	BasicInitial();
	SceneInitial();
}
/*ȫ���봰��ģʽ���õĳ�ʼ������
*/
void BasicInitial() {
	// ��ʼ��GLEW ��ȡOpenGL����
	glewExperimental = GL_TRUE; // ��glew��ȡ������չ����
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Error::GLEW glew version:" << glewGetString(GLEW_VERSION)
			<< " error string:" << glewGetErrorString(status) << std::endl;
		//glfwTerminate();
		std::system("pause");
		//return -1;
	}


	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	Input::Init();
	glutTimerFunc(100, TimerFunc, 1);

	glEnable(GL_DEPTH_TEST);// ������Ȳ���
	glEnable(GL_CULL_FACE);
	//glEnable(GL_FOG);	
	//glFrontFace(GL_CCW);		// ָ����ʱ���Ʒ���ʾ���������
	//glShadeModel(GL_SMOOTH);
	if (!mainScene.skyBox.init())
	{
		MessageBox(NULL, "��ʼ�����ʧ��!", "����", MB_OK);
		exit(0);
	}
	SetLight();
}
void SceneInitial() {
	glClearColor(0.2f, 1.0f, 0.1f, 1.0f);	//����
	lastTime = -1;
	//��������
	//glDepthFunc(GL_LEQUAL);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	currentGameObjectPointer = &mainScene.camera;

	SetScene();

	mainScene.Awake();
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
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mainScene.Render();
	glutSwapBuffers();


	if (lastTime < 0) {
		lastTime = clock();
	}
	int time = clock();
	int delta = time - lastTime;
	deltaTime = delta / 1000.0;
	lastTime = time;

	Input::Update();

	mainScene.Update();
	mainScene.FixedUpdate();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, TimerFunc, 1);
}

void SetCursorVisible(bool visible) {
	while (visible != (ShowCursor(visible) >= 0));
}

void SetGameMode(bool b) {
	if (b) {
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
			//����DPI����
			SetProcessDPIAware();
		}
		else {
			ShowWarnMessage("�޷�����ȫ��ģʽ��");
		}
	}
	else {
		glutLeaveGameMode();
	}
}

void ShowWarnMessage(const char* message, const char* title) {
	MessageBox(NULL, message, title, MB_ICONEXCLAMATION);
}