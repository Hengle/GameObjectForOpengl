#pragma once
class RigidBody :public MonoBehavour {
public:
	Vector3 velocity = Vector3::zero;
	//����Ĵ�С�������ʼ��ʱ��Ӧ�ø���ֵ
	int colliderNum = 0;
	//���Կ�����awake��ʱ���ʼ��,��Start��ֵ
	SphereCollider** colliders = NULL;
private:
	//�����������
	int startAddColliderPointer = 0;
	//���ٶȴ�С
	double g;
public:

	void StartAddCollider(SphereCollider *pointer);
	///<summary>
	///Ԥ�������ü��ٶ�ģ�������ٶ�
	///</summary>
	void SetVelocity(const Vector3& v);

	RigidBody(double g = 10.0);
	~RigidBody();
	void Init() override;
	void Awake() override;
	void Update() override;
	void FixedUpdate() override;
};