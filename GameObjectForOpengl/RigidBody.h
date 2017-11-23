#pragma once
class RigidBody :MonoBehavour {
public:
	Vector3 velocity;
	//����Ĵ�С�������ʼ��ʱ��Ӧ�ø���ֵ
	int colliderNum = 0;
	//���Կ�����awake��ʱ���ʼ��,��Start��ֵ
	SphereCollider** colliders = NULL;
private:
	//�����������
	int startAddColliderPointer = 0;
public:

	void StartAddCollider(SphereCollider *pointer) {
		colliders[startAddColliderPointer] = pointer;
		startAddColliderPointer++;
	}

	RigidBody() {
		mainScene.physicEngine.rigidBodyNum++;
	}
	~RigidBody() {
		if (colliders != NULL) {
			delete colliders;
		}
	}
	void Init() override {
		gameObject->rigidBody = this;
	}

	void Awake() override {
		mainScene.physicEngine.AwakeAddRigidBody(this);
	}
};