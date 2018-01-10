#pragma once
#include <windows.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\glut.h>
#include "UnityIndex.h"
#include "Input.h"
#include "Texture.h"
#include "Shader.h"
#include "SkyBox.h"
#define SHADOW_TEX_CNT 8	//shadowmap�Ĵ洢λ��


void Initial();//��ʼ��
void BasicInitial();//������ʼ��
void SceneInitial();
void SetUpShadowMap();
//������ʼ��
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);
void SetScene();//�༭����
void SetLight();//���ù�Դ
void SetCursorVisible(bool visible);//���ù���Ƿ�ɼ�
void SetGameMode(bool b);//����ȫ����Ϸģʽ��ȡ��ʱ���˳���Ϸ
void ShowWarnMessage(const char* message, const char* title = "����");//��ʾ������Ϣ

extern GLuint depthTex;
extern float shadowVP[16];
extern float viewReverseMat[16];
extern bool shadowOnly;
extern GLuint shadowFBO;
extern GLuint shadowMapShader;
extern int screenWidth;
extern int screenHeight;
#define SHADOWMAP_WIDTH 8192
#define SHADOWMAP_HEIGHT 8192

