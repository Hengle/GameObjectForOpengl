#pragma once

//������
class Matrix
{
public:
	//������
	double m[16];
	//Ĭ��ֵ
	static const Matrix identity;
	Matrix();
	Matrix(
		double m0, double m1, double m2, double m3,
		double m4, double m5, double m6, double m7,
		double m8, double m9, double m10, double m11,
		double m12, double m13, double m14, double m15);
	~Matrix();
	//Ĭ�Ͽվ���
	Matrix& SetIdentity();
	//Ӧ��Vector��Ϊƽ�ƾ���
	Matrix& SetTransition(const Vector3&in);
	//Ӧ����Ԫ����Ϊ��ת����
	Matrix& SetRotation(const Quaternion&in);
	//����ƽ�ƾ�������ת����
	Matrix& Set(const Vector3&v, const Quaternion&q);
	//��ȡ��Ԫ��
	Quaternion GetRotation()const;
	//��ȡ�����
	Matrix operator~()const; 
	//������һ�����ʾ���(ֻ��)
	const double* operator[](int row)const;
	//���ظ�ֵ����
	void operator=(const Matrix&rhs);
	//�˷�
	const Matrix operator*(const Matrix&rhs)const;
	//��VectorӦ�þ���
	const Vector3 operator*(const Vector3&rhs)const;
	//��VectorӦ����ת����
	const Vector3 operator^(const Vector3&rhs)const;

	//������ֵ
	void SetParam(int row, int column, double value);
	//��һ�и�ֵ
	void SetRow(int row, double v0, double v1, double v2, double v3);
	//ȡ����vector��Ϊ������
	static Matrix VectorAsColumn(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	//ȡ����vector��Ϊ������
	static Matrix VectorAsRow(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	void OutPut();
private:
	//������һ�����ʾ���
	double* operator[](int row);
};

//Ӧ�þ���
extern void glApplyMatrix(Matrix& m);

