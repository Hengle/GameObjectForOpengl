#include"UnityIndex.h"

void Physics::AwakeInit() {
	if (solidColliderNum != 0) {
		solidColliders = new SphereCollider*[solidColliderNum];
	}
	if (rigidBodyNum != 0) {
		rigidBodys = new RigidBody*[rigidBodyNum];
	}
}
void Physics::StartInit() {
	for (int i = 0;i < rigidBodyNum;i++) {
		if (rigidBodys[i]->colliderNum != 0) {
			rigidBodys[i]->colliders = new SphereCollider*[rigidBodys[i]->colliderNum];
		}
	}
}
Physics::~Physics() {
	if (solidColliders != NULL) {
		delete solidColliders;
	}
	if (rigidBodys != NULL) {
		delete rigidBodys;
	}
}
void Physics::AwakeAddSolidCollider(SphereCollider *pointer) {
	solidColliders[awakeSolidColliderNumPointer] = pointer;
	awakeSolidColliderNumPointer++;
}
void Physics::AwakeAddRigidBody(RigidBody *pointer) {
	rigidBodys[awakeRigidBodyNumPointer] = pointer;
	awakeRigidBodyNumPointer++;
}

//Contract�������ڽ�����ײ�������ݽ����дrigidBody���ٶ�
void Physics::Contract() {
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

void Physics::Contract(RigidBody* rigidBody, SphereCollider *solidCollider) {
	Vector3 pos = solidCollider->GetPosition();
	for (int i = 0;i < rigidBody->colliderNum;i++) {
		SphereCollider *sp = rigidBody->colliders[i];
		Vector3 delta = sp->GetPosition() - pos;
		double r = sp->radius + solidCollider->radius;

		double distance = delta.magnitude();
		if (distance < r) {
			//����
			rigidBody->transform->Translate(delta*((r - distance) / distance), Space::World);

			//printf_s("Contract!");

			//����
			delta /= distance;
			rigidBody->velocity -= delta * Vector3::Dot(rigidBody->velocity, delta) * ((solidCollider->boundness + sp->boundness) / 2 + 1);
		}
	}
}

//������rigidBody������ײ���
void Physics::Contract(RigidBody* lhs, RigidBody* rhs) {

}
