#pragma once
#include <assimp\material.h>
#include "Vector3.h"

struct vec2 {
	vec2() :vec2(0, 0)
	{
	}
	vec2(float x, float y) :x(x), y(y) {
	}
	float x;
	float y;
};
struct vec3 {
	vec3() :vec3(0, 0, 0)
	{
	}
	vec3(float x, float y, float z) :x(x), y(y), z(z) {
	}
	float x;
	float y;
	float z;
};

// ��ʾһ����������
struct Vertex
{
	vec3 position;
	vec2 texCoords;
	vec3 normal;
	vec3 tangent;
};

// ��ʾһ��Texture
struct Texture
{
	int id;
	aiTextureType type;
	std::string path;
};
// ��ʾһ��������Ⱦ����Сʵ��
class Mesh
{
public:
	void draw(const Shader& shader) const;// ����Mesh
	Mesh();
	Mesh(const std::vector<Vertex>& vertData,
		const std::vector<Texture> & textures,
		const std::vector<GLuint>& indices); // ����һ��Mesh
	void setData(const std::vector<Vertex>& vertData,
		const std::vector<Texture> & textures,
		const std::vector<GLuint>& indices);
	void final() const;
	~Mesh();
private:
	std::vector<Vertex> vertData;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	GLuint VAOId, VBOId, EBOId;

	void setupMesh();  // ����VAO,VBO�Ȼ�����
};
