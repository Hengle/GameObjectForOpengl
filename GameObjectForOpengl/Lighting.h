#pragma once
#define LIGHT_MAX_NUM 8
//��Դ���ݸ�ʽ
class LightData {
public:
	static int num;								//��Դ����
	static float positions[3 * LIGHT_MAX_NUM];	//��Դλ��
	static float colors[4 * LIGHT_MAX_NUM];		//��Դ��ɫ
	static float itensities[LIGHT_MAX_NUM];		//��Դǿ��
	static float distanceSqrs[LIGHT_MAX_NUM];	//���Դ������þ����ƽ��
	static void FlushPositions();
	static Vector3 pos[LIGHT_MAX_NUM];
};

//TODO:�½�һ��cpp�ļ����г�ʼ������SetLight���������ƽ�й�ĳ�ʼ��