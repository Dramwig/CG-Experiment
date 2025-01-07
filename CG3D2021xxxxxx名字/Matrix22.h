#pragma once
#include "Vector2.h"
template <typename T> class Matrix22
{
public:
	typedef T BaseType;
	// 默认构造，单位矩阵（方阵，从左上角到右下角的对角线（称为主对角线）上的元素均为1以外全都为0）
	Matrix22()
	{
		setIdentity();
	}
	~Matrix22() = default;
	// 从其他类型的Matrix22矩阵构造
	template<typename S>
	explicit Matrix22(const Matrix22<S>& m)
	{
		e(0, 0) = (T)m.e(0, 0); e(1, 0) = (T)m.e(1, 0);
		e(0, 1) = (T)m.e(0, 1); e(1, 1) = (T)m.e(1, 1);
	}
	// 拷贝构造
	Matrix22(const Matrix22& other)
	{
		operator=(other);
	}
	/// 构造，主对角线元素都初始化为指定值，其他元素为0
	explicit Matrix22(T n)
	{
		setIdentity();
		e(0, 0) = e(1, 1) = n;
	}
	//构造，按行给出所有元素
	explicit Matrix22(T e00, T e01, T e10, T e11)
	{
		e(0, 0) = e00; e(0, 1) = e01;
		e(1, 0) = e10; e(1, 1) = e11;
	}
	/// 构造，从2x2数组构造
	/// a[0][0] a[0][1]
	/// a[1][0] a[1][1]
	explicit Matrix22(T a[2][2])
	{
		e(0, 0) = a[0][0]; e(0, 1) = a[0][1];
		e(1, 0) = a[1][0]; e(1, 1) = a[1][1];
	}
	/// 所有元素设为指定值
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
	//按元素所在行列访问元素
	const T& e(int i, int j) const { return eVec[j][i]; }
	T& e(int i, int j) { return eVec[j][i]; }
protected:
	Vector2<T> eVec[2]; //列向量
};
typedef Matrix22<int> Mat2i;
typedef Matrix22<float> Mat2f;
typedef Matrix22<double> Mat2d;
typedef Mat2d Mat2;
