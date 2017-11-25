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

		double distance = delta.sqrtMagnitude();
		if (distance < r*r) {
			distance = sqrt(distance);
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
	for (int j = 0;j < rhs->colliderNum;j++) {
		SphereCollider *rCollider = rhs->colliders[j];
		for (int i = 0;i < lhs->colliderNum;i++) {
			SphereCollider *lCollider = lhs->colliders[i];

			Vector3 delta = rCollider->GetPosition() - lCollider->GetPosition();
			double r = lCollider->radius + rCollider->radius;
			double distance = delta.magnitude();

			if (distance < r) {
				double squeeze = (r - distance) / (2 * distance);
				Vector3 squeezeVec = delta * squeeze;

				//���߼���
				lhs->transform->Translate(-squeezeVec, Space::World);
				rhs->transform->Translate(squeezeVec, Space::World);

				//����
				delta /= distance;

				double lv = Vector3::Dot(lhs->velocity, delta);
				double rv = Vector3::Dot(rhs->velocity, delta);

				double mSum = lhs->Mass + rhs->Mass;
				double lm = lhs->Mass / mSum;
				double rm = rhs->Mass / mSum;

				double lvResult = lv * (lm - rm - 1) + 2 * rm * rv;
				double rvResult = rv * (rm - lm - 1) + 2 * lm * lv;

				lhs->velocity += delta * lvResult;
				rhs->velocity += delta * rvResult;
			}
		}
	}
}
