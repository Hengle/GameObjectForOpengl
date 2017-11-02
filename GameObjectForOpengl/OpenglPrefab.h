#pragma once
#include <windows.h>
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "Input.h"
#include "CBMPLoader.h"
#include "SkyBox.h"
#include "GameObject.h"
#include "GameObject.h"
////////////////////////////////////////////////////////////////////////////
//ʵ��Ҫ��(1)���OpenGL�еı任���̡�                                   //
//          (2)���͸��ͶӰ��ƽ��ͶӰ�Ĳ�ͬ��                             // 
//          (3)��Ӵ���ʵ��̫����������������˶�ģ�͡�                   //
//          (4)�˽���Ȳ��ԡ�                                             //
//          (5)ͨ���任�����۲��λ���뷽���                             //
//          (6)�������ģ��                                               //
////////////////////////////////////////////////////////////////////////////

extern Scene mainScene;
extern int deltaTime;//Toʵ��

void Initial();//��ʼ��
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);
void SetScene();//�༭����
void SetLight();//���ù�Դ
void Keyboard(unsigned char key, int x, int y);