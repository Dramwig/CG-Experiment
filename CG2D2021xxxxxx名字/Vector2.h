#ifndef _Vector2_H_INCLUDED
#define _Vector2_H_INCLUDED
#include <limits>
#include <vector> //用到std中的vector，定义数组用
#include <iostream> //输出测试用到
#include "CGBase.h"
//避免与标准库中有冲突
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef dot
#undef dot
#endif
#ifdef cross
#undef cross
#endif
// 二维矢量类模板
template <typename T> class Vector2
{
public:
	typedef T BaseType;
	typedef T* T_ptr;
	static const int element_count = 2;
	Vector2() { elements[0] = 0; elements[1] = 0; }
	~Vector2() = default;
	Vector2(const Vector2& other) { elements[0] = other.x(); elements[1] = other.y(); }
	Vector2(CPoint point) { elements[0] = (T)point.x; elements[1] = (T)point.y; }
	// 从其他基本类型的Vector2构造
	template<typename S> explicit Vector2(const Vector2<S>& other)
	{
		elements[0] = T(other.x());
		elements[1] = T(other.y());
	}
	// 构造成(a, a)形式。显式构造，避免自动类型转换
	explicit Vector2(T val) { elements[0] = val; elements[1] = val; }
	// 构造成(a, b)形式
	Vector2(T val1, T val2) { elements[0] = val1; elements[1] = val2; }
	// 从数组构造（要求至少2个元素）。显式构造，避免自动类型转换
	explicit Vector2(const T_ptr& pval) { elements[0] = pval[0]; elements[1] = pval[1]; }
	// 返回元素，作为一个二维点坐标(x,y)
	const T x() const { return elements[0]; }
	const T y() const { return elements[1]; }
	T& x() { return elements[0]; }
	T& y() { return elements[1]; }
	// 返回元素数组指针
	const T* ptr() const { return elements; }
	T* ptr() { return elements; }
	//运算符重载
	Vector2 operator+(const Vector2& other) const {
		return Vector2(x() + other.x(), y() +
			other.y());
	}
	Vector2 operator-(const Vector2& other) const {
		return Vector2(x() - other.x(), y() -
			other.y());
	}
	Vector2 operator*(const Vector2& other) const {
		return Vector2(x() * other.x(), y() *
			other.y());
	}
	Vector2 operator/(const Vector2& other) const {
		return Vector2(x() / other.x(), y() /
			other.y());
	}
	Vector2 operator+(T val) const { return Vector2(x() + val, y() + val); }
	Vector2 operator-(T val) const { return Vector2(x() - val, y() - val); }
	Vector2 operator*(T val) const { return Vector2(x() * val, y() * val); }
	Vector2 operator/(T val) const { return Vector2(x() / val, y() / val); }
	Vector2 operator-() const { return Vector2(-x(), -y()); }
	//自行补充实现部分：
	/* 自行补充以下几个成员函数，实现相关的矢量运算*/
	Vector2& negate() {
		return *this = -(*this);
	}

	Vector2& operator+=(const Vector2& other) {
		x(x() + other.x());
		y(y() + other.y());
		return *this;
	}

	Vector2& operator-=(const Vector2& other) {
		x(x() - other.x());
		y(y() - other.y());
		return *this;
	}

	Vector2& operator*=(const Vector2& other) {
		x(x() * other.x());
		y(y() * other.y());
		return *this;
	}

	Vector2& operator/=(const Vector2& other) {
		// 检查是否是除以零
		if (other.x() != 0 && other.y() != 0) {
			x(x() / other.x());
			y(y() / other.y());
		}
		else {
			throw std::runtime_error("Division by zero in Vector2::operator/=(const Vector2&)");
		}
		return *this;
	}

	Vector2& operator+=(T val) {
		x(x() + val);
		y(y() + val);
		return *this;
	}

	Vector2& operator-=(T val) {
		x(x() - val);
		y(y() - val);
		return *this;
	}

	Vector2& operator*=(T val) {
		x(x() * val);
		y(y() * val);
		return *this;
	}

	Vector2& operator/=(T val) {
		// 检查是否是除以零
		if (val != 0) {
			x(x() / val);
			y(y() / val);
		}
		else {
			throw std::runtime_error("Division by zero in Vector2::operator/=(const T)");
		}
		return *this;
	}
	/*以上是自定义的*/
	
	Vector2& operator=(const Vector2& other)
	{
		if (this != &other)
		{
			x() = other.x();
			y() = other.y();
		}
		return *this;
	}
	Vector2& operator=(T val)
	{
		x() = y() = val;
		return *this;
	}
	template<typename S> bool operator==(const Vector2<S>& other) const
	{
		return x() == other.x() && y() == other.y();
	}
	template<typename S> bool operator!=(const Vector2<S>& other) const
	{
		return !operator==(other);
	}
	template<typename S> bool operator<(const Vector2<S>& other) const
	{
		if (x() != other.x())
			return x() < other.x();
		else
			return y() < other.y();
	}
	// 按给定误差精度判断是否相等
	bool equalWithTolerance(const Vector2& other, T e) const
	{
		for (int i = 0; i < 2; i++)
			if ((((*this)[i] > other[i]) ? (*this)[i] - other[i] : other[i] - (*this)[i]) > e)
				return false;
		return true;
	}
	// 点积
	T dot(const Vector2& other) const { return x() * other.x() + y() * other.y(); }
	// 叉积
	T cross(const Vector2& other) const { return x() * other.y() - y() * other.x(); }
	// 长度
	T length() const { return ::sqrt(x() * x() + y() * y()); }
	// 常量的平方
	T lengthSquared() const { return x() * x() + y() * y(); }
	bool isNull() const { return !x() && !y(); }
	// 规范化，如果长度为0，则success(如果有）为false
	Vector2& normalize(T* len = nullptr, bool* success = nullptr)
	{
		T leng = length();
		if (len)
			*len = leng;
		if (leng)
		{
			x() /= leng;
			y() /= leng;
			if (success)
				*success = true;
		}
		else {
			if (success)
				*success = false;
		}
		return *this;
	}
	// 返回规范化的向量
	Vector2 normalized(T* len = nullptr, bool* success = nullptr) const
	{
		T leng = length();
		if (len)
			*len = leng;
		if (leng)
		{
			if (success)
				*success = true;
			return Vector2(x() / leng, y() / leng);
		}
		else {
			if (success)
				*success = false;
			return Vector2(T(0));
		}
	}
	// 下标运算访问元素（要求下标不越界）
	T& operator[] (unsigned i) { return elements[i]; }
	constexpr const T& operator[] (unsigned i) const { return elements[i]; }
	// 按类型设置元素值
	template <typename S> void setValue(S a, S b)
	{
		x() = (T)a;
		y() = (T)b;
	}
	template <typename S> void setValue(const Vector2<S>& v)
	{
		x() = (T)v.x();
		y() = (T)v.y();
	}
	// 按需取出元素的值
	template <typename S> void getValue(S& a, S& b) const
	{
		a = S(x());
		b = S(y());
	}
	template <typename S> void getValue(Vector2<S>& v) const
	{
		v.x() = S(x());
		v.x() = S(y());
	}
	constexpr static unsigned int dimensions() { return element_count; }
	// 类型最小值（通常是负值）
	constexpr static T baseTypeLowest() { return std::numeric_limits<T>::lowest(); }
	// 类型最大值（通常是正值）
	constexpr static T baseTypeMax() { return std::numeric_limits<T>::max(); }
	// 类型最小值（通常是负值）
	constexpr static T baseTypeSmallest() { return std::numeric_limits<T>::min(); }
	// 类型小值e则 1+e != 1
	constexpr static T baseTypeEpsilon() { return std::numeric_limits<T>::epsilon(); }
protected:
	T elements[element_count];
};
// 数乘
template<typename T>
inline const Vector2<T> operator*(T val, const Vector2<T>& v)
{
	return v * val;
}
//输出测试
template <typename T>
inline std::ostream& operator<< (std::ostream& s, const Vector2<T>& v)
{
	return s << '(' << v.x() << ' ' << v.y() << ')';
}
//预定义的便捷访问模板类：二维矢量类
typedef Vector2<int> Vec2i;
typedef Vector2<unsigned int> Vec2u;
typedef Vector2<float> Vec2f;
typedef Vector2<double> Vec2d;
typedef Vec2d Vec2;
//预定义的便捷访问模板类：二维位置类
typedef Vector2<int> Pos2i;
typedef Vector2<unsigned int> Pos2u;
typedef Vector2<float> Pos2f;
typedef Vector2<double> Pos2d;
typedef Pos2d Pos2;
//预定义的便捷访问模板类：二维矢量数组类
typedef std::vector<Vec2i> Vec2iArray;
typedef std::vector<Vec2u> Vec2uArray;
typedef std::vector<Vec2f> Vec2fArray;
typedef std::vector<Vec2d> Vec2dArray;
//预定义的便捷访问模板类：二维位置数组类
typedef std::vector<Pos2i> Pos2iArray;
typedef std::vector<Pos2u> Pos2uArray;
typedef std::vector<Pos2f> Pos2fArray;
typedef std::vector<Pos2d> Pos2dArray;
#endif //_Vector2_H_INCLUDED
