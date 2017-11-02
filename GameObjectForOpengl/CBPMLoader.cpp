//========================================================
/**
*  @file  CBMPLoader.cpp
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
#include "OpenglPrefab.h"

/** ���캯�� */
CBMPLoader::CBMPLoader()
{
	/** ��ʼ����ԱֵΪ0 */
	image = 0;
	imageWidth = 0;
	imageHeight = 0;
}

/** �������� */
CBMPLoader::~CBMPLoader()
{
	FreeImage(); /**< �ͷ�ͼ������ռ�ݵ��ڴ� */
}

/** װ��һ��λͼ�ļ� */
bool CBMPLoader::LoadBitmap(const char *file)
{
	FILE *pFile = 0; /**< �ļ�ָ�� */

					 /** ����λͼ�ļ���Ϣ��λͼ�ļ�ͷ�ṹ */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;

	unsigned char textureColors = 0;/**< ���ڽ�ͼ����ɫ��BGR�任��RGB */

									/** ���ļ�,�������� */
	fopen_s(&pFile, file, "rb");
	if (pFile == 0) return false;

	/** ����λͼ�ļ�ͷ��Ϣ */
	fread_s(&header, sizeof(BITMAPFILEHEADER), sizeof(BITMAPFILEHEADER), 1, pFile);

	/** �����ļ��Ƿ�Ϊλͼ�ļ� */
	if (header.bfType != BITMAP_ID)
	{
		fclose(pFile);             /**< ������λͼ�ļ�,��ر��ļ������� */
		return false;
	}

	/** ����λͼ�ļ���Ϣ */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** ����ͼ��Ŀ�Ⱥ͸߶� */
	imageWidth = bitmapInfoHeader.biWidth;
	imageHeight = bitmapInfoHeader.biHeight;

	/** ȷ����ȡ���ݵĴ�С */
	if (bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
		bitmapInfoHeader.biHeight * 3;

	/** ��ָ���Ƶ����ݿ�ʼλ�� */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** �����ڴ� */
	image = new unsigned char[bitmapInfoHeader.biSizeImage];

	/** ����ڴ�����Ƿ�ɹ� */
	if (!image)                        /**< �������ڴ�ʧ���򷵻� */
	{
		delete[] image;
		fclose(pFile);
		return false;
	}

	/** ��ȡͼ������ */
	fread(image, 1, bitmapInfoHeader.biSizeImage, pFile);

	/** ��ͼ����ɫ���ݸ�ʽ���н���,��BGRת��ΪRGB */
	for (int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index += 3)
	{
		textureColors = image[index];
		image[index] = image[index + 2];
		image[index + 2] = textureColors;
	}

	fclose(pFile);       /**< �ر��ļ� */
	return true;         /**< �ɹ����� */
}

/** װ��һ��λͼ�ļ� */
bool CBMPLoader::LoadBitmap(const char *file, bool flag)
{
	FILE *pFile = 0; /**< �ļ�ָ�� */

					 /** ����λͼ�ļ���Ϣ��λͼ�ļ�ͷ�ṹ */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;

	unsigned char textureColors = 0;/**< ���ڽ�ͼ����ɫ��BGR�任��RGB */

									/** ���ļ�,�������� */
	fopen_s(&pFile, file, "rb");
	if (pFile == 0) return false;

	/** ����λͼ�ļ�ͷ��Ϣ */
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);

	/** �����ļ��Ƿ�Ϊλͼ�ļ� */
	if (header.bfType != BITMAP_ID)
	{
		fclose(pFile);             /**< ������λͼ�ļ�,��ر��ļ������� */
		return false;
	}

	/** ����λͼ�ļ���Ϣ */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** ����ͼ��Ŀ�Ⱥ͸߶� */
	imageWidth = bitmapInfoHeader.biWidth;
	imageHeight = bitmapInfoHeader.biHeight;

	/** ȷ����ȡ���ݵĴ�С */
	if (bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
		bitmapInfoHeader.biHeight * 4;

	/** ��ָ���Ƶ����ݿ�ʼλ�� */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** �����ڴ� */
	image = new unsigned char[bitmapInfoHeader.biSizeImage * 2];

	/** ����ڴ�����Ƿ�ɹ� */
	if (!image)                        /**< �������ڴ�ʧ���򷵻� */
	{
		delete[] image;
		fclose(pFile);
		return false;
	}

	/** ��ȡͼ������ */
	fread(image, 1, bitmapInfoHeader.biSizeImage, pFile);

	/** ��ͼ����ɫ���ݸ�ʽ���н���,��BGRת��ΪRGB */
	for (int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index += 4)
	{
		textureColors = image[index];
		image[index] = image[index + 2];
		image[index + 2] = textureColors;
		if (image[index] >= 200 && image[index + 1] >= 200 && image[index + 2] >= 200)
		{
			image[index + 3] = 1;
		}
		else
			image[index + 3] = 0;
	}

	fclose(pFile);       /**< �ر��ļ� */
	return true;         /**< �ɹ����� */
}
/** �ͷ��ڴ� */
void CBMPLoader::FreeImage()
{
	/** �ͷŷ�����ڴ� */
	if (image)
	{
		delete[] image;
		image = 0;
	}
}
bool CBMPLoader::loadTexture(char* path, int wrap_s, int wrap_T) {
	char* fileName = path;
	if (!LoadBitmap(fileName))                    /**< ����λͼ�ļ� */
	{
		MessageBox(NULL, "װ��λͼ�ļ�ʧ�ܣ�", "����", MB_OK);       /**< �������ʧ���򵯳��Ի��� */
		exit(0);
	}
	glGenTextures(1, &ID);                            /**< ����һ������������� */


	glBindTexture(GL_TEXTURE_2D, ID);                 /**< ����������� */

													  /** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageWidth,
		imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		image);


	return true;

}
