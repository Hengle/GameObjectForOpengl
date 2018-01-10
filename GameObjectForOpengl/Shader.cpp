#include "OpenglIndex.h"
#include <fstream>
#include "Shader.h"
#include "Lighting.h"

Shader::Shader(const char* vertexPath, const char* fragPath) :programId(0)
{
	std::vector<ShaderFile> fileVec;
	fileVec.push_back(ShaderFile(GL_VERTEX_SHADER, vertexPath));
	fileVec.push_back(ShaderFile(GL_FRAGMENT_SHADER, fragPath));
	loadFromFile(fileVec);
}
Shader::Shader(const char* vertexPath, const char* fragPath, const char* geometryPath) :programId(0)
{
	std::vector<ShaderFile> fileVec;
	fileVec.push_back(ShaderFile(GL_VERTEX_SHADER, vertexPath));
	fileVec.push_back(ShaderFile(GL_FRAGMENT_SHADER, fragPath));
	fileVec.push_back(ShaderFile(GL_GEOMETRY_SHADER, geometryPath));
	loadFromFile(fileVec);
}
void Shader::use(bool ifLoadLight) const
{
	glUseProgram(this->programId);
	if (ifLoadLight) LoadUniform();
}
void Shader::LoadUniform() const
{
	//���ع�������
	glUniform1i(glGetUniformLocation(programId, "lightNum"), LightData::num);
	glUniform3fv(glGetUniformLocation(programId, "lightPositions"), LIGHT_MAX_NUM, LightData::positions);
	glUniform4fv(glGetUniformLocation(programId, "lightColors"), LIGHT_MAX_NUM, LightData::colors);
	glUniform1fv(glGetUniformLocation(programId, "lightItensities"), LIGHT_MAX_NUM, LightData::itensities);
	glUniform1fv(glGetUniformLocation(programId, "lightDS"), LIGHT_MAX_NUM, LightData::distanceSqrs);
}
void Shader::LoadTexture(int texID) const
{
	TextureHelper::use2DTexture(texID);
	glUniform1i(glGetUniformLocation(programId, "texture_diffuse0"), 0);
}
void Shader::useNone()
{
	glUseProgram(0);
}
Shader::~Shader()
{
	if (this->programId)
	{
		glDeleteProgram(this->programId);
	}
}
/*
* ���ļ����ض����ƬԪ��ɫ��
* ���ݲ���Ϊ [(��ɫ���ļ����ͣ���ɫ���ļ�·��)+]
*/
void Shader::loadFromFile(std::vector<ShaderFile>& shaderFileVec)
{
	std::vector<GLuint> shaderObjectIdVec;
	std::string vertexSource, fragSource;
	std::vector<std::string> sourceVec;
	size_t shaderCount = shaderFileVec.size();
	// ��ȡ�ļ�Դ����
	for (size_t i = 0; i < shaderCount; ++i)
	{
		std::string shaderSource;
		if (!loadShaderSource(shaderFileVec[i].filePath, shaderSource))
		{
			std::string out = "Error::Shader could not load file:";
			out += shaderFileVec[i].filePath;
			ShowWarnMessage(out.c_str());
			return;
		}
		sourceVec.push_back(shaderSource);
	}
	bool bSuccess = true;
	// ����shader object
	for (size_t i = 0; i < shaderCount; ++i)
	{
		GLuint shaderId = glCreateShader(shaderFileVec[i].shaderType);
		const char *c_str = sourceVec[i].c_str();
		glShaderSource(shaderId, 1, &c_str, NULL);
		glCompileShader(shaderId);
		GLint compileStatus = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus); // ������״̬
		if (compileStatus == GL_FALSE) // ��ȡ���󱨸�
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> errLog(maxLength);
			glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errLog[0]);
			std::cout << "Error::Shader file [" << shaderFileVec[i].filePath << " ] compiled failed,"
				<< &errLog[0] << std::endl;
			bSuccess = false;
		}
		shaderObjectIdVec.push_back(shaderId);
	}
	// ����shader program
	if (bSuccess)
	{
		this->programId = glCreateProgram();
		for (size_t i = 0; i < shaderCount; ++i)
		{
			glAttachShader(this->programId, shaderObjectIdVec[i]);
		}
		glLinkProgram(this->programId);
		GLint linkStatus;
		glGetProgramiv(this->programId, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> errLog(maxLength);
			glGetProgramInfoLog(this->programId, maxLength, &maxLength, &errLog[0]);
			std::cout << "Error::shader link failed," << &errLog[0] << std::endl;
		}
	}
	// ������ɺ�detach ���ͷ�shader object
	for (size_t i = 0; i < shaderCount; ++i)
	{
		if (this->programId != 0)
		{
			glDetachShader(this->programId, shaderObjectIdVec[i]);
		}
		glDeleteShader(shaderObjectIdVec[i]);
	}
}
/*
* ��ȡ��ɫ������Դ��
*/
bool Shader::loadShaderSource(const char* filePath, std::string& source)
{
	source.clear();
	std::ifstream in_stream(filePath);
	if (!in_stream)
	{
		return false;
	}
	source.assign(std::istreambuf_iterator<char>(in_stream),
		std::istreambuf_iterator<char>()); // �ļ��������������ַ���
	return true;
}
