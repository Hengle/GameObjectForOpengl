//========================================================
/**
*  @file      SkyBox.h
*
*  ��Ŀ������ OPENGL������Ϸ
*  �ļ�����:  ��պ���
*  ����ƽ̨�� Windows
*
*  ���ߣ�     405
*  �����ʼ�:  459762891@qq.com
*  �������ڣ� 2016-6-14
*  �޸����ڣ� 2016-6-14
*
*/
//========================================================
#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#define GL_CLAMP_TO_EDGE	0x812F

/** ��պ��� */
class CSkyBox
{
public:
	/** ���캯�� */
	CSkyBox();
	~CSkyBox();

	/** ��ʼ�� */
	bool init();

	/** ��Ⱦ */
	void render();

private:

	CBMPLoader  m_texture[6];   /**< ��պ�����   */
	float       length;         /**< ���� */
	float       width;          /**< ��� */
	float       height;         /**< �߶� */
	float       yRot;           /**< ��Y����ת */

};


#endif ///__SKYBOX_H__