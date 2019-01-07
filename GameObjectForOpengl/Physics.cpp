#include"UnityIndex.h"

Physics::Physics() :floorHeight(0), floorBoundness(0.1)
{
}

Physics::Physics(double height, double boundness) : floorHeight(height), floorBoundness(boundness)
{
}

void Physics::SetFloorParameters(double height, double boundness)
{
	floorHeight = height;
	floorBoundness = boundness;
}

void Physics::AddRigidBody(RigidBody * pointer)
{
	rigidBodyList.push_back(pointer);
}

void Physics::AddSphereCollider(SphereCollider * pointer)
{
	sphereColliderList.push_back(pointer);
}

//Contract�������ڽ�����ײ�������ݽ����дrigidBody���ٶ�
void Physics::Contract() {
	//��ÿһ��rigidBody
	for (unsigned int r = 0;r < rigidBodyList.size();r++) {
		//�������
		Contract(rigidBodyList[r]);
		//�뾲̬��ײ����
		for each(SphereCollider* s in sphereColliderList) {
			Contract(rigidBodyList[r], s);
		}
		//������rigidBody���
		for (unsigned i = r + 1;i < rigidBodyList.size();i++) {
			Contract(rigidBodyList[r], rigidBodyList[i]);
		}
	}
}

//����������ײ���
void Physics::Contract(RigidBody * rigidBody)
{
	//TODO
	for each (SphereCollider* sp in rigidBody->sphereColliderList)
	{
		double distance = floorHeight - sp->GetPosition().y + sp->radius;
		if (distance > 0) {
			//����
			rigidBody->transform->Translate(Vector3::up*distance, Space::World);

			//����
			rigidBody->velocity +=
				Vector3::up * Vector3::Dot(rigidBody->velocity, Vector3::down) * (floorBoundness * sp->boundness + 1);
		}
	}
}

//�뾲̬��ײ�������ײ���
void Physics::Contract(RigidBody* rigidBody, SphereCollider *solidCollider) {
	Vector3 pos = solidCollider->GetPosition();
	for each (SphereCollider* sp in rigidBody->sphereColliderList)
	{
		Vector3 delta = sp->GetPosition() - pos;
		double r = sp->radius + solidCollider->radius;

		double distance = delta.sqrMagnitude();
		if (distance < r*r) {
			distance = sqrt(distance);
			//����
			rigidBody->transform->Translate(delta*((r - distance) / distance), Space::World);

			//printf_s("Contract!");

			//����
			delta /= distance;
			rigidBody->velocity -= delta * Vector3::Dot(rigidBody->velocity, delta) * (solidCollider->boundness * sp->boundness + 1);
		}
	}
}

//������rigidBody������ײ���
void Physics::Contract(RigidBody* lhs, RigidBody* rhs) {
	for each (SphereCollider* rCollider in rhs->sphereColliderList)
	{
		for each (SphereCollider* lCollider in lhs->sphereColliderList)
		{
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
