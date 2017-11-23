#pragma once
//������ײ��
class SphereCollider : public MonoBehavour {
public:
	const Vector3 offset;
	double radius;
	Vector3 position;	//��������
	SphereCollider(double r);
	SphereCollider(double r, const Vector3& offset);
	//��ȡ��ײ������������
	Vector3 GetPosition();
private:
	void Awake() override;
	void Start() override;
};