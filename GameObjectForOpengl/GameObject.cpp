#include "DebugModule.h"
#include "UnityIndex.h"

GameObject::GameObject(const char * name, const Vector3 & position, const Quaternion & rotation, const Vector3 & scale)
	:Name(name), parent(NULL), child(NULL), next(NULL), componentsPointer(NULL),
	transform(this, position, rotation, scale), rigidBody(NULL)
{

}
GameObject::GameObject(const char* name, const Vector3& position, const Quaternion& rotation)
	: Name(name), parent(NULL), child(NULL), next(NULL), componentsPointer(NULL),
	transform(this, position, rotation), rigidBody(NULL)
{

}
GameObject::GameObject(const char* name)
	: Name(name), parent(NULL), child(NULL), next(NULL), componentsPointer(NULL),
	transform(this), rigidBody(NULL)
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
	currentGameObjectPointer = child;
	return child;
}

//������
MonoBehavour* GameObject::AddComponent(MonoBehavour* component) {
	component->next = componentsPointer;
	componentsPointer = component;
	component->gameObject = this;
	component->transform = &transform;
	component->Init();
	return component;
}
void GameObject::DestroyComponent(MonoBehavour * component)
{
	if (component == NULL) {
		ShowWarnMessage("������ͼɾ�������ڵ������");
		return;
	}
	if (componentsPointer == component) {
		PopComponent();
		return;
	}
	MonoBehavour *p = componentsPointer;
	while (p != NULL && p->next != component) p = p->next;
	if (p == NULL) {
		ShowWarnMessage("������ͼɾ�������ڵ������");
		return;
	}
	p->next = component->next;
	delete component;
}
//ɾ����һ�����
void GameObject::PopComponent() {
	if (componentsPointer != NULL) {
		MonoBehavour* pointer = componentsPointer->next;
		delete componentsPointer;
		componentsPointer = pointer;
	}
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

