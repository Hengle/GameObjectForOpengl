#pragma once
#include <soil.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
/*
���������
*/
class TextureHelper
{
public:
	/* �ɹ�����2D�����򷵻��������Id ���򷵻�0
	*/
	static  GLuint load2DTexture(const char* filename, GLint internalFormat = GL_RGBA,
		GLenum picFormat = GL_RGBA, int loadChannels = SOIL_LOAD_RGBA);

	/* ʹ��2D����������Ϊ0��ȡ��ʹ������
	*/
	static void use2DTexture(GLuint textureId);

	/* ����DDS����
	*/
	static GLuint loadDDS(const char * filename);
};
