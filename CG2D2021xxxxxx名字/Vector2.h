#ifndef _Vector2_H_INCLUDED
#define _Vector2_H_INCLUDED
#include <limits>
#include <vector> //�õ�std�е�vector������������
#include <iostream> //��������õ�
#include "CGBase.h"
//�������׼�����г�ͻ
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
// ��άʸ����ģ��
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
	// �������������͵�Vector2����
	template<typename S> explicit Vector2(const Vector2<S>& other)
	{
		elements[0] = T(other.x());
		elements[1] = T(other.y());
	}
	// �����(a, a)��ʽ����ʽ���죬�����Զ�����ת��
	explicit Vector2(T val) { elements[0] = val; elements[1] = val; }
	// �����(a, b)��ʽ
	Vector2(T val1, T val2) { elements[0] = val1; elements[1] = val2; }
	// �����鹹�죨Ҫ������2��Ԫ�أ�����ʽ���죬�����Զ�����ת��
	explicit Vector2(const T_ptr& pval) { elements[0] = pval[0]; elements[1] = pval[1]; }
	// ����Ԫ�أ���Ϊһ����ά������(x,y)
	const T x() const { return elements[0]; }
	const T y() const { return elements[1]; }
	T& x() { return elements[0]; }
	T& y() { return elements[1]; }
	// ����Ԫ������ָ��
	const T* ptr() const { return elements; }
	T* ptr() { return elements; }
	//���������
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
	//���в���ʵ�ֲ��֣�
	/* ���в������¼�����Ա������ʵ����ص�ʸ������*/
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
		// ����Ƿ��ǳ�����
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
		// ����Ƿ��ǳ�����
		if (val != 0) {
			x(x() / val);
			y(y() / val);
		}
		else {
			throw std::runtime_error("Division by zero in Vector2::operator/=(const T)");
		}
		return *this;
	}
	/*�������Զ����*/
	
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
	// �����������ж��Ƿ����
	bool equalWithTolerance(const Vector2& other, T e) const
	{
		for (int i = 0; i < 2; i++)
			if ((((*this)[i] > other[i]) ? (*this)[i] - other[i] : other[i] - (*this)[i]) > e)
				return false;
		return true;
	}
	// ���
	T dot(const Vector2& other) const { return x() * other.x() + y() * other.y(); }
	// ���
	T cross(const Vector2& other) const { return x() * other.y() - y() * other.x(); }
	// ����
	T length() const { return ::sqrt(x() * x() + y() * y()); }
	// ������ƽ��
	T lengthSquared() const { return x() * x() + y() * y(); }
	bool isNull() const { return !x() && !y(); }
	// �淶�����������Ϊ0����success(����У�Ϊfalse
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
	// ���ع淶��������
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
	// �±��������Ԫ�أ�Ҫ���±겻Խ�磩
	T& operator[] (unsigned i) { return elements[i]; }
	constexpr const T& operator[] (unsigned i) const { return elements[i]; }
	// ����������Ԫ��ֵ
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
	// ����ȡ��Ԫ�ص�ֵ
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
	// ������Сֵ��ͨ���Ǹ�ֵ��
	constexpr static T baseTypeLowest() { return std::numeric_limits<T>::lowest(); }
	// �������ֵ��ͨ������ֵ��
	constexpr static T baseTypeMax() { return std::numeric_limits<T>::max(); }
	// ������Сֵ��ͨ���Ǹ�ֵ��
	constexpr static T baseTypeSmallest() { return std::numeric_limits<T>::min(); }
	// ����Сֵe�� 1+e != 1
	constexpr static T baseTypeEpsilon() { return std::numeric_limits<T>::epsilon(); }
protected:
	T elements[element_count];
};
// ����
template<typename T>
inline const Vector2<T> operator*(T val, const Vector2<T>& v)
{
	return v * val;
}
//�������
template <typename T>
inline std::ostream& operator<< (std::ostream& s, const Vector2<T>& v)
{
	return s << '(' << v.x() << ' ' << v.y() << ')';
}
//Ԥ����ı�ݷ���ģ���ࣺ��άʸ����
typedef Vector2<int> Vec2i;
typedef Vector2<unsigned int> Vec2u;
typedef Vector2<float> Vec2f;
typedef Vector2<double> Vec2d;
typedef Vec2d Vec2;
//Ԥ����ı�ݷ���ģ���ࣺ��άλ����
typedef Vector2<int> Pos2i;
typedef Vector2<unsigned int> Pos2u;
typedef Vector2<float> Pos2f;
typedef Vector2<double> Pos2d;
typedef Pos2d Pos2;
//Ԥ����ı�ݷ���ģ���ࣺ��άʸ��������
typedef std::vector<Vec2i> Vec2iArray;
typedef std::vector<Vec2u> Vec2uArray;
typedef std::vector<Vec2f> Vec2fArray;
typedef std::vector<Vec2d> Vec2dArray;
//Ԥ����ı�ݷ���ģ���ࣺ��άλ��������
typedef std::vector<Pos2i> Pos2iArray;
typedef std::vector<Pos2u> Pos2uArray;
typedef std::vector<Pos2f> Pos2fArray;
typedef std::vector<Pos2d> Pos2dArray;
#endif //_Vector2_H_INCLUDED
