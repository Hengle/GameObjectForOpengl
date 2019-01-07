//========================================================
/**
*  @file      SkyBox.cpp
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

#include "OpenglHeader.h"
#include "ModelIndex.h"
#include "SkyBox.h"


CSkyBox::CSkyBox() :length(1400.0f), width(1400.0f), height(1400.0f), yRot(0.01f)
{

}

CSkyBox::~CSkyBox()
{
	/** ɾ�����������ռ�õ��ڴ� */

}


/** ��պг�ʼ�� */
bool CSkyBox::init()
{
	char filename[128];                                         /**< ���������ļ��� */
	char *bmpName[] = { "back","front","up","left","right","down" };
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(filename, "data/Sky Box Bmp/%s", bmpName[i]);
		strcat_s(filename, ".bmp");
		m_texture[i] = TextureHelper::load2DTexture(filename);
		if (m_texture[i] == 0)
			return false;
	}
	return true;

}


void CSkyBox::render()
{
	/** ��ó����й���״̬ */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);

	if (lp)  /**< �رչ��� */
		glDisable(GL_LIGHTING);

	glColor3f(1, 1, 1);

	glActiveTexture(GL_TEXTURE0);

	/** ��ʼ���� */
	glPushMatrix();

	/** ���Ʊ��� */
	TextureHelper::use2DTexture(m_texture[0]);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, -length + 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height, -length + 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height, -length + 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, -height, -length + 1);
	glEnd();



	/** ����ǰ�� */
	TextureHelper::use2DTexture(m_texture[1]);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, length - 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, height, length - 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height, length - 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height, length - 1);

	glEnd();



	/** ���ƶ��� */
	TextureHelper::use2DTexture(m_texture[2]);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height - 1, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height - 1, length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, height - 1, length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height - 1, -length);

	glEnd();


	/** �������� */
	TextureHelper::use2DTexture(m_texture[3]);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-width + 1, height, -length);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-width + 1, height, length);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-width + 1, -height, length);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-width + 1, -height, -length);

	glEnd();

	/** �������� */
	TextureHelper::use2DTexture(m_texture[4]);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width - 1, -height, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width - 1, -height, length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width - 1, height, length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width - 1, height, -length);
	glEnd();

	/** ���Ƶ��� */
	TextureHelper::use2DTexture(m_texture[5]);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height + 1, -length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height + 1, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height + 1, length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height + 1, length);

	glEnd();


	glPopMatrix();                 /** ���ƽ��� */

	if (lp)                         /** �ָ�����״̬ */
		glEnable(GL_LIGHTING);
}
