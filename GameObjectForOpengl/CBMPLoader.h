//========================================================
/**
*  @file  CBMPLoader.h
*
*  ��Ŀ������ OPENGL������Ϸ
*  �ļ�����:  λͼ������
*  ����ƽ̨�� Windows
*
*  ���ߣ�     405
*  �����ʼ�:  459762891@qq.com
*  �������ڣ� 2016-6-14
*  �޸����ڣ� 2016-6-14
*
*/
//========================================================
#ifndef __CBMPLOADER_H__
#define __CBMPLOADER_H__

#define BITMAP_ID 0x4D42	/**< λͼ�ļ��ı�־ */

/** λͼ������ */
class CBMPLoader
{
public:
	CBMPLoader();
	~CBMPLoader();
	bool LoadBitmap(const char *file, bool flag);
	bool LoadBitmap(const char *filename); /**< װ��һ��bmp�ļ� */
	void FreeImage();                /**< �ͷ�ͼ������ */
	bool loadTexture(char* path, int wrap_s = GL_REPEAT, int wrap_T = GL_REPEAT);//һ��װ������

	unsigned int ID;                 /**< ���������ID�� */
	int imageWidth;                  /**< ͼ���� */
	int imageHeight;                 /**< ͼ��߶� */
	unsigned char *image;            /**< ָ��ͼ�����ݵ�ָ�� */
};

#endif //__CBMPLOADER_H__

