#pragma once

#include <vector>
struct ShaderFile
{
	GLenum shaderType;
	const char* filePath;
	ShaderFile(GLenum type, const char* path)
		:shaderType(type), filePath(path) {}
};

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragPath);
	Shader(const char* vertexPath, const char* fragPath, const char* geometryPath);
	void use() const;
	void LoadMatrix() const;
	static void useNone();
	~Shader();
public:
	GLuint programId;
private:
	/*
	* ���ļ����ض����ƬԪ��ɫ��
	* ���ݲ���Ϊ [(��ɫ���ļ����ͣ���ɫ���ļ�·��)+]
	*/
	void loadFromFile(std::vector<ShaderFile>& shaderFileVec);
	/*
	* ��ȡ��ɫ������Դ��
	*/
	bool loadShaderSource(const char* filePath, std::string& source);
};
