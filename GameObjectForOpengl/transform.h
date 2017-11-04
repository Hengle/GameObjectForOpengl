#pragma once


//�任���
class Transform {
public:
	//��������
	Vector3 localPosition;
	//��ת��Ԫ��
	Quaternion rotation;
	//ŷ����
	const Vector3 eulerAngle()const;
	//���ӵ���Ϸ����
	GameObject* gameObject;
	//���ر任����
	Matrix localMatrix;
	//���ر任�����Ƿ���Ҫˢ��
	bool localNeedFlush;
	//����任����
	Matrix worldMatrix;
	//����任�����Ƿ���Ҫˢ��
	bool worldNeedFlush;
	
	Transform(GameObject* g);
	Transform(Vector3 pos, Quaternion rot);
	~Transform();
	//ƽ��
	void Translate(const Vector3& transition);
	//ƽ��
	void Translate(double x, double y, double z);
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
	//ˢ�¾���
	void Flush();
	//���¸����������
	void FlushDown();
	const Vector3 forward();
	const Vector3 right();
	const Vector3 up();
};