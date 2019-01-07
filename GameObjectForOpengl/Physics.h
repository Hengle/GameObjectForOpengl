#pragma once
#include<vector>
//��������
class Physics
{
private:
	//�������
	//����߶�
	double floorHeight;
	//���浯��
	double floorBoundness;

	//�����
	std::vector<RigidBody*> rigidBodyList;
	//��ײ���
	std::vector<SphereCollider*> sphereColliderList;
public:
	Physics();
	Physics(double height, double boundness);

	//���õ������
	void SetFloorParameters(double height, double boundness);
	//��Ӹ���
	void AddRigidBody(RigidBody *pointer);
	//�����ײ��
	void AddSphereCollider(SphereCollider *pointer);

	//Contract�������ڽ�����ײ�������ݽ����дrigidBody���ٶ�
	void Contract();
private:
	void Contract(RigidBody* rigidBody);
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider);
	void Contract(RigidBody* lhs, RigidBody* rhs);
};

