#include <iostream>
#include <GL\glew.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "ModelIndex.h"


void Model::draw(const Shader& shader) const
{
	shader.use();
	for (std::vector<Mesh>::const_iterator it = this->meshes.begin(); this->meshes.end() != it; ++it)
	{
		it->draw(shader);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
	glUseProgram(0);
}
bool Model::loadModel(const std::string& filePath)
{
	Assimp::Importer importer;
	if (filePath.empty())
	{
		std::cerr << "Error:Model::loadModel, empty model file path." << std::endl;
		return false;
	}
	const aiScene* sceneObjPtr = importer.ReadFile(filePath,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!sceneObjPtr
		|| sceneObjPtr->mFlags == AI_SCENE_FLAGS_INCOMPLETE
		|| !sceneObjPtr->mRootNode)
	{
		std::cerr << "Error:Model::loadModel, description: "
			<< importer.GetErrorString() << std::endl;
		return false;
	}
	this->modelFileDir = filePath.substr(0, filePath.find_last_of('/'));
	if (!this->processNode(sceneObjPtr->mRootNode, sceneObjPtr))
	{
		std::cerr << "Error:Model::loadModel, process node failed." << std::endl;
		return false;
	}
	return true;
}
Model::Model(const std::string & filePath)
{
	loadModel(filePath);
}
Model::~Model()
{
	for (std::vector<Mesh>::const_iterator it = this->meshes.begin(); this->meshes.end() != it; ++it)
	{
		it->final();
	}
}
/*
* 递归处理模型的结点
*/
bool Model::processNode(const aiNode* node, const aiScene* sceneObjPtr)
{
	if (!node || !sceneObjPtr)
	{
		return false;
	}
	// 先处理自身结点
	for (size_t i = 0; i < node->mNumMeshes; ++i)
	{
		// 注意node中的mesh是对sceneObject中mesh的索引
		const aiMesh* meshPtr = sceneObjPtr->mMeshes[node->mMeshes[i]];
		if (meshPtr)
		{
			Mesh meshObj;
			if (this->processMesh(meshPtr, sceneObjPtr, meshObj))
			{
				this->meshes.push_back(meshObj);
			}
		}
	}
	// 处理孩子结点
	for (size_t i = 0; i < node->mNumChildren; ++i)
	{
		this->processNode(node->mChildren[i], sceneObjPtr);
	}
	return true;
}
bool Model::processMesh(const aiMesh* meshPtr, const aiScene* sceneObjPtr, Mesh& meshObj)
{
	if (!meshPtr || !sceneObjPtr)
	{
		return false;
	}
	std::vector<Vertex> vertData;
	std::vector<Texture> textures;
	std::vector<GLuint> indices;
	// 从Mesh得到顶点数据、法向量、纹理数据
	for (size_t i = 0; i < meshPtr->mNumVertices; ++i)
	{
		Vertex vertex;
		// 获取顶点位置
		if (meshPtr->HasPositions())
		{
			vertex.position.x = meshPtr->mVertices[i].x;
			vertex.position.y = meshPtr->mVertices[i].y;
			vertex.position.z = meshPtr->mVertices[i].z;
		}
		// 获取纹理数据 目前只处理0号纹理
		if (meshPtr->HasTextureCoords(0))
		{
			vertex.texCoords.x = meshPtr->mTextureCoords[0][i].x;
			vertex.texCoords.y = meshPtr->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texCoords = vec2(0.0f, 0.0f);
		}
		// 获取法向量数据
		if (meshPtr->HasNormals())
		{
			vertex.normal.x = meshPtr->mNormals[i].x;
			vertex.normal.y = meshPtr->mNormals[i].y;
			vertex.normal.z = meshPtr->mNormals[i].z;
		}
		// 获取切向量数据
		if (meshPtr->HasTangentsAndBitangents()) {
			vertex.tangent.x = meshPtr->mBitangents[i].x;
			vertex.tangent.y = meshPtr->mBitangents[i].y;
			vertex.tangent.z = meshPtr->mBitangents[i].z;
		}
		vertData.push_back(vertex);
	}
	// 获取索引数据
	for (size_t i = 0; i < meshPtr->mNumFaces; ++i)
	{
		aiFace face = meshPtr->mFaces[i];
		if (face.mNumIndices != 3)
		{
			std::cerr << "Error:Model::processMesh, mesh not transformed to triangle mesh." << std::endl;
			return false;
		}
		for (size_t j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	// 获取纹理数据
	if (meshPtr->mMaterialIndex >= 0)
	{
		const aiMaterial* materialPtr = sceneObjPtr->mMaterials[meshPtr->mMaterialIndex];
		// 获取diffuse类型
		std::vector<Texture> diffuseTexture;
		this->processMaterial(materialPtr, sceneObjPtr, aiTextureType_DIFFUSE, diffuseTexture);
		textures.insert(textures.end(), diffuseTexture.begin(), diffuseTexture.end());
		// 获取specular类型
		std::vector<Texture> specularTexture;
		this->processMaterial(materialPtr, sceneObjPtr, aiTextureType_SPECULAR, specularTexture);
		textures.insert(textures.end(), specularTexture.begin(), specularTexture.end());
		//获取normal类型
		std::vector<Texture> normalTexture;
		this->processMaterial(materialPtr, sceneObjPtr, aiTextureType_HEIGHT, normalTexture);
		textures.insert(textures.end(), normalTexture.begin(), normalTexture.end());
	}
	meshObj.setData(vertData, textures, indices);
	return true;
}
/*
* 获取一个材质中的纹理
*/
bool Model::processMaterial(const aiMaterial* matPtr, const aiScene* sceneObjPtr,
	const aiTextureType textureType, std::vector<Texture>& textures)
{
	textures.clear();

	if (!matPtr
		|| !sceneObjPtr)
	{
		return false;
	}
	if (matPtr->GetTextureCount(textureType) <= 0)
	{
		return true;
	}
	for (size_t i = 0; i < matPtr->GetTextureCount(textureType); ++i)
	{
		Texture text;
		aiString textPath;
		aiReturn retStatus = matPtr->GetTexture(textureType, i, &textPath);
		if (retStatus != aiReturn_SUCCESS
			|| textPath.length == 0)
		{
			std::cerr << "Warning, load texture type=" << textureType
				<< "index= " << i << " failed with return value= "
				<< retStatus << std::endl;
			continue;
		}

		/*这部分用于测试*/
		std::cout << "Load texture type=" << textureType
			<< "index= " << i << " path= "
			<< textPath.C_Str() << std::endl;
		/****测试结束****/

		std::string absolutePath = this->modelFileDir + "/" + textPath.C_Str();
		LoadedTextMapType::const_iterator it = this->loadedTextureMap.find(absolutePath);
		if (it == this->loadedTextureMap.end()) // 检查是否已经加载过了
		{
			GLint textId = TextureHelper::load2DTexture(absolutePath.c_str());
			text.id = textId;
			text.path = absolutePath;
			text.type = textureType;
			textures.push_back(text);
			loadedTextureMap[absolutePath] = text;
		}
		else
		{
			textures.push_back(it->second);
		}
	}
	return true;
}
