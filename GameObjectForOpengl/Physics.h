#pragma once
//��������
class Physics
{
private:
	//�����
	std::vector<RigidBody*> rigidBodyList;
	//��ײ���
	std::vector<SphereCollider*> sphereColliderList;
public:
	//��Ӹ���
	void AddRigidBody(RigidBody *pointer);
	//�����ײ��
	void AddSphereCollider(SphereCollider *pointer);

	//Contract�������ڽ�����ײ�������ݽ����дrigidBody���ٶ�
	void Contract();
private:
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider);
	void Contract(RigidBody* lhs, RigidBody* rhs);
};

