#pragma once

//�任���
class Transform {
private:
	//������ת��Ԫ��
	Quaternion worldRotation;
	bool worldRotationNeedFlush;
	//���ر任����
	Matrix localMatrix;
	//���ر任�����Ƿ���Ҫˢ��
	bool localNeedFlush;
	//����任����
	Matrix worldMatrix;
	//ˢ�¾���
	void Flush(bool ifRotate = false);
	//���¸����������
	void FlushDown(bool asRoot, bool ifRotate);

public:
	//��������
	Vector3 localPosition;
	//��ת��Ԫ��
	Quaternion rotation;
	//������������
	Vector3 localScale;

	//ŷ����
	const Vector3 eulerAngle()const;
	//���ӵ���Ϸ����
	GameObject* gameObject;

	Transform(GameObject* g);
	Transform(GameObject* g, const Vector3& pos, const Quaternion& rot);
	Transform(GameObject* g, const Vector3& pos, const Quaternion& rot, const Vector3& scale);
	~Transform();
	//ƽ��
	void Translate(double x, double y, double z, Space space = Space::Self);
	//ƽ��
	void Translate(const Vector3& transition, Space space = Space::Self);
	//��ת
	void Rotate(Quaternion& rot, Space space = Space::Self);
	//ŷ����ת
	void Rotate(double x, double y, double z, Space space = Space::Self);
	//����λ��
	void SetLocalPosition(const Vector3& pos);
	//����λ��
	void SetLocalPosition(double x, double y, double z);
	//������ת
	void SetRotation(Quaternion& rot);
	//��ȡ��ˢ�±��ر任����
	Matrix& GetLocalMatrix();
	//��ȡ��ˢ������任����
	Matrix& GetWorldMatrix();
	//����任�����Ƿ���Ҫˢ��
	bool worldNeedFlush;
	//��ȡ������任����
	Matrix GetParentWorldMatrix();

	Quaternion GetWorldRotation();
	Quaternion GetParentWorldRotation();
	//��ȡ��������
	Vector3 GetPosition();
	const Vector3 forward();
	const Vector3 right();
	const Vector3 up();
};