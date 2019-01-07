#pragma once
//������ײ��
class SphereCollider : public MonoBehaviour {
public:
	const Vector3 offset;
	double radius;
	double boundness;	//����ϵ��
	SphereCollider(double r);
	SphereCollider(double r, const Vector3& offset);
	SphereCollider(double r, const Vector3& offset, double boundness);
	//��ȡ��ײ������������
	Vector3 GetPosition();
	Vector3 GetNextPosition();
private:
	Vector3 position;	//��������
	void Awake() override;
};