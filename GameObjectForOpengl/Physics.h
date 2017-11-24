#pragma once
class Physics
{
public:
	//����Ĵ�С�������ʼ��ʱ��Ӧ�ø���ֵ
	int solidColliderNum = 0;
	int rigidBodyNum = 0;
private:
	//���Կ�����awake��ʱ���ʼ������ֵ
	SphereCollider** solidColliders = NULL;
	RigidBody** rigidBodys = NULL;

	//�����������
	int awakeSolidColliderNumPointer = 0;
	int awakeRigidBodyNumPointer = 0;
public:
	void AwakeInit();
	void StartInit();
	~Physics();
	void AwakeAddSolidCollider(SphereCollider *pointer);
	void AwakeAddRigidBody(RigidBody *pointer);

	//Contract�������ڽ�����ײ�������ݽ����дrigidBody���ٶ�
	void Contract();
private:
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider);
	void Contract(RigidBody* lhs, RigidBody* rhs);
};

