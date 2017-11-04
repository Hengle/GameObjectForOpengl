#pragma once

class Vector3 {
public:
	double x, y, z;
	Vector3(double x, double y, double z);
	Vector3();
	Vector3& operator=(const Vector3& rhs);
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	const Vector3 operator+(const Vector3& rhs)const;
	const Vector3 operator- (const Vector3& rhs)const;
	const Vector3 operator- ()const;
	const Vector3 operator* (double rhs)const;
	const Vector3 operator/ (double rhs)const;
	Vector3& operator*=(double rhs);
	Vector3& operator/=(double rhs);
	//ģ
	double magnitude() const;
	//ģ��ƽ��
	double sqrtMagnitude()const;
	//��һ��
	Vector3& Normalize();
	//��һ����ֻ��
	const Vector3 normalized() const;
	//���
	static double Dot(const Vector3& lhs, const Vector3& rhs);
	//���
	static const Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
	//���Բ�ֵ
	static const Vector3 Lerp(const Vector3& lhs, const Vector3& rhs, double k);


	//Ĭ��ֵ����
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 one;

};
