#pragma once

#include <map>
#include <assimp/scene.h>


/*
* ����һ��ģ�� ģ�Ϳ��԰���һ������Mesh
*/
class Model
{
public:
	void draw(const Shader& shader) const;
	bool loadModel(const std::string& filePath);
	Model(const std::string& filePath);
	~Model();
private:
	/*
	* �ݹ鴦��ģ�͵Ľ��
	*/
	bool processNode(const aiNode* node, const aiScene* sceneObjPtr);
	bool processMesh(const aiMesh* meshPtr, const aiScene* sceneObjPtr, Mesh& meshObj);
	/*
	* ��ȡһ�������е�����
	*/
	bool processMaterial(const aiMaterial* matPtr, const aiScene* sceneObjPtr,
		const aiTextureType textureType, std::vector<Texture>& textures);
private:
	std::vector<Mesh> meshes; // ����Mesh
	std::string modelFileDir; // ����ģ���ļ����ļ���·��
	typedef std::map<std::string, Texture> LoadedTextMapType; // key = texture file path
	LoadedTextMapType loadedTextureMap; // �����Ѿ����ص�����
};
