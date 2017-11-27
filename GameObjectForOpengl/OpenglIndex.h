#pragma once
#include <windows.h>
#include <iostream>
#include <gl\gl.h>
#include <gl\glu.h>
#include <GL\glew.h>
#include <GL\glut.h>
#include "UnityIndex.h"
#include "Input.h"
#include "CBMPLoader.h"
#include "SkyBox.h"
////////////////////////////////////////////////////////////////////////////
//ʵ��Ҫ��(1)���OpenGL�еı任���̡�                                   //
//          (2)���͸��ͶӰ��ƽ��ͶӰ�Ĳ�ͬ��                             // 
//          (3)��Ӵ���ʵ��̫����������������˶�ģ�͡�                   //
//          (4)�˽���Ȳ��ԡ�                                             //
//          (5)ͨ���任�����۲��λ���뷽���                             //
//          (6)�������ģ��                                               //
////////////////////////////////////////////////////////////////////////////



void Initial();//��ʼ��
void BasicInitial();//������ʼ��
void SceneInitial();//������ʼ��
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);
void SetScene();//�༭����
void SetLight();//���ù�Դ
void SetCursorVisible(bool visible);//���ù���Ƿ�ɼ�
void SetGameMode(bool b);//����ȫ����Ϸģʽ��ȡ��ʱ���˳���Ϸ
void ShowWarnMessage(const char* message, const char* title = "����");//��ʾ������Ϣ

//�����Ǽ����ó������� ���ӵķ���
GameObject* currentGameObjectPointer = NULL;
extern GameObject* AddGameObject(GameObject* g);
extern GameObject* AddChild(GameObject *child);
extern MonoBehavour* AddComponent(MonoBehavour* component);
