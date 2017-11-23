#pragma once
//������ײ��
class SphereCollider : public MonoBehavour {
public:
	const Vector3 offset;
	double radius;
	Vector3 position;	//��������
	SphereCollider(double r) :offset(Vector3::zero), radius(r) {

	}
	SphereCollider(double r, const Vector3& offset) :offset(offset), radius(r) {

	}
	//��ȡ��ײ������������
	Vector3 GetPosition() {
		if (transform->worldNeedFlush) {
			position = transform->GetWorldMatrix()*offset;
		}
		return position;
	}
private:
	void Awake() override {
		position = transform->GetWorldMatrix()*offset;
	}
};