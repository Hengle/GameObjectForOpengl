#pragma once
class Quaternion {
public:
	double x, y, z, w;
	Quaternion();
	Quaternion(double x, double y, double z, double w);

	//ŷ����
	Vector3 EulerAngle() const;
	//ȡģ
	double magnitude();
	//ȡģƽ��
	double sqrtMagnitude();
	//��һ��
	Quaternion& Normalize();
	//��ŷ���Ǵ�����Ԫ��
	static Quaternion Euler(const Vector3 &in);
	//��ŷ���Ǵ�����Ԫ��
	static Quaternion Euler(double x, double y, double z);
	static Quaternion Quaternion::EulerX(double x);
	//��ŷ���Ǵ�����Ԫ��
	static Quaternion Quaternion::EulerY(double y);
	//��ŷ���Ǵ�����Ԫ��
	static Quaternion Quaternion::EulerZ(double z);
	//�ƶ�����ת
	static Quaternion RotationAround(Vector3 u, double angle);
	static Quaternion LookAtRotation(Vector3 forward, Vector3 up);
	static Quaternion FromToRotation(const Vector3& fromTo);
	static Quaternion FromToRotation(const Vector3& from, const Vector3& to);
	//���
	static double Dot(const Quaternion&lhs, const Quaternion&rhs);
	//�Ƕ�
	static double Angle(const Quaternion&lhs, const Quaternion&rhs);
	//���Բ�ֵ
	static Quaternion Lerp(const Quaternion&a, const Quaternion&b, double t);
	//���β�ֵ
	static Quaternion Slerp(const Quaternion &lhs, const Quaternion &rhs, double t);
	//��ֵ
	void operator=(const Quaternion &rhs);
	//����
	const Quaternion operator~() const;
	//���
	const Quaternion operator+(const Quaternion&rhs) const;
	//�˻�
	const Quaternion operator*(const Quaternion&rhs) const;
	//����
	Quaternion operator*(double rhs) const;
	//��������
	const Vector3 operator*(const Vector3&u) const;


	//Ĭ��ֵ
	static const Quaternion identity;
};

