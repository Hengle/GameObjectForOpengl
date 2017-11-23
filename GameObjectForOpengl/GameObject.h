#pragma once

//��Ϸ����
class GameObject {
public:
	GameObject* parent;
	GameObject* child;
	GameObject* next;

	const char* Name;

	Transform transform;
	RigidBody *rigidBody;

	MonoBehavour* componentsPointer;

	//���캯��
	GameObject(const char* name, const Vector3& position,const Quaternion& rotation);
	GameObject(const char* name);
	~GameObject();
	//��Ⱦ
	virtual void Render();
	void SetParent(GameObject *parent);
	GameObject* AddChild(GameObject *child);

	//������
	void AddComponent(MonoBehavour* component);
private:
	//���ø��ӹ�ϵ
	static void SetParent(GameObject* parent, GameObject* child);
	//ɾ����һ�����
	void PopComponent();
};

