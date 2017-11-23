#pragma once
#include"SkyBox.h"
//����
class Scene {
public:
	GameObject *root;
	GameObject camera;
	CSkyBox skyBox;
	Scene();
	~Scene();
	void Render();
	void SetCamera(const Vector3& pos, const Quaternion& rot);
	GameObject* AddGameObject(GameObject* g);
	//�ݻ����弰��������
	void Destroy(GameObject* g);
	//�ݻ����弰��ͬ������
	void DestroyLayer(GameObject* g);
	void Awake();
	void Start();
	void Update();
	void FixedUpdate();
private:
	void Awake(GameObject* g);
	void Start(GameObject* g);
	void Update(GameObject* g);
	void FixedUpdate(GameObject* g);
	void RenderGameObjects(GameObject* g);
};
