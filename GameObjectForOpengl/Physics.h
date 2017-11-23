#pragma once
//
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
	void AwakeInit() {
		if (solidColliderNum != 0) {
			solidColliders = new SphereCollider*[solidColliderNum];
		}
		if (rigidBodyNum != 0) {
			rigidBodys = new RigidBody*[rigidBodyNum];
		}
	}
	void StartInit() {
		for (int i = 0;i < rigidBodyNum;i++) {
			if (rigidBodys[i]->colliderNum != 0) {
				rigidBodys[i]->colliders = new SphereCollider*[rigidBodys[i]->colliderNum];
			}
		}
	}
	~Physics() {
		if (solidColliders != NULL) {
			delete solidColliders;
		}
		if (rigidBodys != NULL) {
			delete rigidBodys;
		}
	}
	void AwakeAddSolidCollider(SphereCollider *pointer) {
		solidColliders[awakeSolidColliderNumPointer] = pointer;
		awakeSolidColliderNumPointer++;
	}
	void AwakeAddRigidBody(RigidBody *pointer) {
		rigidBodys[awakeRigidBodyNumPointer] = pointer;
		awakeRigidBodyNumPointer++;
	}

	//Contract�������ڽ�����ײ�������ݽ����дrigidBody���ٶ�
	void Contract() {
		//��ÿһ��rigidBody
		for (int r = 0; r < rigidBodyNum;r++) {
			//�뾲̬��ײ����
			for (int i = 0;i < solidColliderNum;i++) {
				Contract(rigidBodys[r], solidColliders[i]);
			}
			//������rigidBody���
			for (int i = r + 1;i < rigidBodyNum;i++) {
				Contract(rigidBodys[r], rigidBodys[i]);
			}
		}
	}
private:
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider) {

	}
	void Contract(RigidBody* lhs, RigidBody* rhs) {

	}
};

