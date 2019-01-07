#include <time.h>
#include "OpenglIndex.h"
#include "Lighting.h"

GameObject* currentGameObjectPointer = NULL;

Scene mainScene;
double deltaTime;
int lastTime;

GLuint depthTex;
Matrix shadowVPM;
float shadowVP[16];
float viewReverseMat[16];
bool shadowOnly = false;
GLuint shadowFBO;
GLuint shadowMapShader;

int screenWidth;
int screenHeight;

void Initial() {
	BasicInitial();
	SceneInitial();
	SetUpShadowMap();
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

	srand((unsigned int)time(0));

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	Input::Init();
	glutTimerFunc(100, TimerFunc, 1);

	glEnable(GL_DEPTH_TEST);// ������Ȳ���
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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
void SetUpShadowMap() {
	glActiveTexture(GL_TEXTURE0 + SHADOW_TEX_CNT);
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float border[4] = { 1,1,1,1 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	//ע��FBO����Ⱦ��ȵ�����
	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTex, 0);

	glDrawBuffer(GL_NONE);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result == GL_FRAMEBUFFER_COMPLETE) {
		printf_s("Framebuffer is complete.\n");
	}
	else {
		ShowWarnMessage("Framebuffer is not complete!");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glActiveTexture(GL_TEXTURE0);
	//����MVP����
	//projection
	glOrtho(-128, 128, -128, 128, -64, 64);
	Matrix p = Matrix();
	glGetDoublev(GL_PROJECTION_MATRIX, p.m);

	//view
	Vector3 eye = LightData::pos[0];
	gluLookAt(eye.x, eye.y, eye.z, 0, 0, 0, 0, 1, 0);
	Matrix v = Matrix();
	glGetDoublev(GL_MODELVIEW_MATRIX, v.m);

	shadowVPM = v*p;

	for (int i = 0;i < 16;i++) {
		shadowVP[i] = (float)shadowVPM.m[i];
	}
}
void ChangeSize(int w, int h)
{
	if (h == 0)	h = 1;

	screenWidth = w;
	screenHeight = h;
	// ���������ߴ�
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �����޼��ռ�
	GLfloat fAspect;
	fAspect = (float)w / (float)h;
	gluPerspective(45.0, fAspect, 1.0, 2500);

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

	LightData::FlushPositions();

	mainScene.Update();

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

