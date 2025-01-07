#pragma once
#include "Vector2.h"
template <typename T> class Matrix22
{
public:
	typedef T BaseType;
	// Ĭ�Ϲ��죬��λ���󣨷��󣬴����Ͻǵ����½ǵĶԽ��ߣ���Ϊ���Խ��ߣ��ϵ�Ԫ�ؾ�Ϊ1����ȫ��Ϊ0��
	Matrix22()
	{
		setIdentity();
	}
	~Matrix22() = default;
	// ���������͵�Matrix22������
	template<typename S>
	explicit Matrix22(const Matrix22<S>& m)
	{
		e(0, 0) = (T)m.e(0, 0); e(1, 0) = (T)m.e(1, 0);
		e(0, 1) = (T)m.e(0, 1); e(1, 1) = (T)m.e(1, 1);
	}
	// ��������
	Matrix22(const Matrix22& other)
	{
		operator=(other);
	}
	/// ���죬���Խ���Ԫ�ض���ʼ��Ϊָ��ֵ������Ԫ��Ϊ0
	explicit Matrix22(T n)
	{
		setIdentity();
		e(0, 0) = e(1, 1) = n;
	}
	//���죬���и�������Ԫ��
	explicit Matrix22(T e00, T e01, T e10, T e11)
	{
		e(0, 0) = e00; e(0, 1) = e01;
		e(1, 0) = e10; e(1, 1) = e11;
	}
	/// ���죬��2x2���鹹��
	/// a[0][0] a[0][1]
	/// a[1][0] a[1][1]
	explicit Matrix22(T a[2][2])
	{
		e(0, 0) = a[0][0]; e(0, 1) = a[0][1];
		e(1, 0) = a[1][0]; e(1, 1) = a[1][1];
	}
	/// ����Ԫ����Ϊָ��ֵ
	Matrix22& fill(T val)
	{
		e(0, 0) = e(1, 0) = e(0, 1) = e(1, 1) = val;
		return *this;
	}
	Matrix22& setIdentity()
	{
		//static const T I2d[] =
		//{
		// (T)1, (T)0,
		// (T)0, (T)1
		//};
		//memcpy(eVec, I2d, sizeof(T) * 4);
		e(0, 0) = (T)1;
		e(0, 1) = (T)0;
		e(1, 0) = (T)0;
		e(1, 1) = (T)1;
		return *this;
	}
	//��Ԫ���������з���Ԫ��
	const T& e(int i, int j) const { return eVec[j][i]; }
	T& e(int i, int j) { return eVec[j][i]; }
protected:
	Vector2<T> eVec[2]; //������
};
typedef Matrix22<int> Mat2i;
typedef Matrix22<float> Mat2f;
typedef Matrix22<double> Mat2d;
typedef Mat2d Mat2;
