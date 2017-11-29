#pragma once
//������ײ��
class SphereCollider : public MonoBehavour {
public:
	const Vector3 offset;
	double radius;
	Vector3 position;	//��������
	double boundness;	//����ϵ��
	SphereCollider(double r);
	SphereCollider(double r, const Vector3& offset);
	SphereCollider(double r, const Vector3& offset, double boundness);
	//��ȡ��ײ������������
	Vector3 GetPosition();
	Vector3 GetNextPosition();
private:
	void Awake() override;
};