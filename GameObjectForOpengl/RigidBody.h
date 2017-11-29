#pragma once
/*���壬������ڹ�������ײ��ǰ��*/
class RigidBody :public MonoBehavour {
public:
	Vector3 velocity = Vector3::zero;

	//��ײ���
	std::vector<SphereCollider*> sphereColliderList;
	//����
	double Mass;
private:
	//���ٶȴ�С
	double g;
public:

	//�����ײ��
	void AddSphereCollider(SphereCollider *pointer);
	//Ԥ�������ü��ٶ�ģ�������ٶ�
	void SetVelocity(const Vector3& v);

	//���壬������ڹ�������ײ��ǰ��
	RigidBody(double g = 10.0, double mass = 1);
	void Init() override;
	void Update() override;
	void FixedUpdate() override;
};