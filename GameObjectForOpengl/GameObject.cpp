#include"UnityIndex.h"

//���캯��
GameObject::GameObject(const char* name, const Vector3& position, const Quaternion& rotation) 
	:Name(name), parent(NULL), child(NULL), next(NULL), componentsPointer(NULL), transform(this) 
{
	transform.localPosition = position;
	transform.rotation = rotation;
}
GameObject::GameObject(const char* name)
	: Name(name), parent(NULL), child(NULL), next(NULL), componentsPointer(NULL), transform(this)
{

}
GameObject::~GameObject() {
	//������
	while (componentsPointer != NULL)
		PopComponent();
}
//��Ⱦ
void GameObject::Render() {

}
void GameObject::SetParent(GameObject *parent) {
	SetParent(parent, this);
}
GameObject* GameObject::AddChild(GameObject *child) {
	SetParent(this, child);
	return child;
}

//������
void GameObject::AddComponent(MonoBehavour* component) {
	component->next = componentsPointer;
	componentsPointer = component;
	component->gameObject = this;
	component->transform = &transform;
	component->Awake();
}
//���ø��ӹ�ϵ
void GameObject::SetParent(GameObject* parent, GameObject* child) {
	child->parent = parent;
	if (parent == NULL) return;
	if (parent->child == NULL) {
		parent->child = child;
		return;
	}
	GameObject* pc = parent->child;
	while (pc->next != NULL) {
		pc = pc->next;
	}
	pc->next = child;
}
//ɾ����һ�����
void GameObject::PopComponent() {
	if (componentsPointer != NULL) {
		MonoBehavour* pointer = componentsPointer->next;
		delete componentsPointer;
		componentsPointer = pointer;
	}
}
