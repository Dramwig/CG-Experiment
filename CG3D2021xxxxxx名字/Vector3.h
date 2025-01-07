#ifndef _Vector3_H_INCLUDED
#define _Vector3_H_INCLUDED
#include "Vector2.h"
template <typename T> class Vector3
{
public:
	typedef T BaseType;
	typedef T* T_ptr;
	static const int element_count = 3;
	// Ĭ�Ϲ���
	Vector3() { elements[0] = 0; elements[1] = 0; elements[2] = 0; }
	//Vector3(T x, T y, T z){ elements[0] = x; elements[1] = y; elements[2] = z; }
	// ��������
	~Vector3() = default;
	// ��������
	Vector3(const Vector3& other)
	{
		elements[0] = other.x();
		elements[1] = other.y();
		elements[2] = other.z();
	}
	// �������������͵�Vector3����
	template<typename S>
	explicit Vector3(const Vector3<S>& other)
	{
		x() = (T)other.x();
		y() = (T)other.y();
		z() = (T)other.z();
	}
	// �����鹹�죨Ҫ������3��Ԫ�أ�
	explicit Vector3(const T_ptr& pval)
	{
		elements[0] = pval[0];
		elements[1] = pval[1];
		elements[2] = pval[2];
	}
	// �����(a, a, a)
	explicit Vector3(T val)
	{
		elements[0] = elements[1] = elements[2] = val;
	}
	// �����(x, y, z)
	explicit Vector3(T x, T y, T z)
	{
		elements[0] = x;
		elements[1] = y;
		elements[2] = z;
	}
	// �������������͵�Vector2����ɣ�x, y, 1������񻯶�ά�������
	template<typename S>
	explicit Vector3(const Vector2<S>& v)
	{
		elements[0] = (T)v.x();
		elements[1] = (T)v.y();
		elements[2] = (T)1;
	}
	// �������������͵�Vector2����ɣ�x, y, z��
	template<typename S>
	explicit Vector3(const Vector2<S>& v, T z)
	{
		elements[0] = (T)v.x();
		elements[1] = (T)v.y();
		elements[2] = z;
	}
	// ����Ԫ�أ���Ϊһ����ά������(x,y,z)
	const T& x() const { return elements[0]; }
	const T& y() const { return elements[1]; }
	const T& z() const { return elements[2]; }
	T& x() { return elements[0]; }
	T& y() { return elements[1]; }
	T& z() { return elements[2]; }
	// ����Ԫ������ָ��
	T* ptr() { return elements; }
	const T* ptr() const { return elements; }
	// ����ǰ����Ԫ���γɵ�Vector2
	Vector2<T> xy() const { return Vector2<T>(x(), y()); }
	// ���������
	Vector3 operator+(const Vector3& other) const
	{
		return Vector3(x() + other.x(), y() + other.y(), z() + other.z());
	}
	Vector3 operator-(const Vector3& other) const
	{
		return Vector3(x() - other.x(), y() - other.y(), z() - other.z());
	}
	Vector3 operator*(const Vector3& other) const
	{
		return Vector3(x() * other.x(), y() * other.y(), z() * other.z());
	}
	Vector3 operator/(const Vector3& other) const
	{
		return Vector3(x() / other.x(), y() / other.y(), z() / other.z());
	}
	Vector3 operator+(T val) const
	{
		return Vector3(x() + val, y() + val, z() + val);
	}
	Vector3 operator-(T val) const
	{
		return Vector3(x() - val, y() - val, z() - val);
	}
	Vector3 operator*(T val) const
	{
		return Vector3(x() * val, y() * val, z() * val);
	}
	Vector3 operator/(T val) const
	{
		return Vector3(x() / val, y() / val, z() / val);
	}
	Vector3 operator-() const
	{
		return Vector3(-x(), -y(), -z());
	}
	Vector3& negate()
	{
		x() = -x();
		y() = -y();
		z() = -z();
		return *this;
	}
	Vector3& operator+=(const Vector3 & other)
	{
		x() += other.x();
		y() += other.y();
		z() += other.z();
		return *this;
	}
	Vector3& operator-=(const Vector3 & other)
	{
		x() -= other.x();
		y() -= other.y();
		z() -= other.z();
		return *this;
	}
	Vector3& operator*=(const Vector3 & other)
	{
		x() *= other.x();
		y() *= other.y();
		z() *= other.z();
		return *this;
	}
	Vector3& operator/=(const Vector3 & other)
	{
		x() /= other.x();
		y() /= other.y();
		z() /= other.z();
		return *this;
	}
	Vector3& operator%=(const Vector3 & other)
	{
		T a = y() * other.z() - z() * other.y();
		T b = z() * other.x() - x() * other.z();
		T c = x() * other.y() - y() * other.x();
		x() = a;
		y() = b;
		z() = c;
		return *this;
	}
	Vector3& operator+=(T val)
	{
		x() += val;
		y() += val;
		z() += val;
		return *this;
	}
	Vector3& operator-=(T val)
	{
		x() -= val;
		y() -= val;
		z() -= val;
		return *this;
	}
	Vector3& operator*=(T val)
	{
		x() *= val;
		y() *= val;
		z() *= val;
		return *this;
	}
	Vector3& operator/=(T val)
	{
		x() /= val;
		y() /= val;
		z() /= val;
		return *this;
	}
	Vector3& operator=(const Vector3& other)
	{
		if (this != &other)
		{
			x() = other.x();
			y() = other.y();
			z() = other.z();
		}
		return *this;
	}
	Vector3& operator=(T val)
	{
		x() = y() = z() = val;
		return *this;
	}
	template<typename S>
	bool operator==(const Vector3<S>& other) const
	{
		return x() == other.x() && y() == other.y() && z() == other.z();
	}
	template<typename S>
	bool operator!=(const Vector3<S>& other) const
	{
		return !operator==(other);
	}
	template<typename S>
	bool operator<(const Vector3<S>& other) const
	{
		if (x() != other.x())
			return x() < other.x();
		else
			if (y() != other.y())
				return y() < other.y();
			else
				return z() < other.z();
	}
	bool equalWithTolerance(const Vector3& other, T e) const
	{
		for (int i = 0; i < 3; i++)
			if ((((*this)[i] > other[i]) ? (*this)[i] - other[i] : other[i] - (*this)[i]) > e)
				return false;
		return true;
	}
	//���
	T dot(const Vector3& other) const
	{
		return x() * other.x() + y() * other.y() + z() * other.z();
	}
	//���*this * other���������������򣨵�ǰ����ת��other�����õ�����������ֱ������
	Vector3 cross(const Vector3& other) const
	{
		return Vector3(y() * other.z() - z() * other.y(), z() * other.x() - x() * other.z(), x() *
			other.y() - y() * other.x());
	}
	//��������
	T length() const { return ::sqrt(x() * x() + y() * y() + z() * z()); }
	//�������ȵ�ƽ��
	T lengthSquared() const { return x() * x() + y() * y() + z() * z(); }
	bool isNull() const { return !x() && !y() && !z(); }
	//�淶�����ɷ���ԭ���ȡ��Ƿ�ɹ���
	const Vector3& normalize(T* len = nullptr, bool* success = nullptr)
	{
		T leng = length();
		if (len)
			*len = leng;
		if (leng)
		{
			x() /= leng;
			y() /= leng;
			z() /= leng;
			if (success)
				*success = true;
		}
		else {
			if (success)
				*success = false;
		}
		return *this;
	}
	//���ع淶���������ɷ���ԭ���ȡ��Ƿ�ɹ���
	Vector3 normalized(T* len = nullptr, bool* success = nullptr) const
	{
		T leng = length();
		if (len)
			*len = leng;
		if (leng)
		{
			if (success)
				*success = true;
			return Vector3(x() / leng, y() / leng, z() / leng);
		}
		else
		{
			if (success)
				*success = false;
			return Vector3(T(0));
		}
	}
	//�±��������Ԫ�أ�Ҫ���±겻Խ�磩
	const T& operator[](unsigned i) const { return elements[i]; }
	T& operator[](unsigned i) { return elements[i]; }
	//�������
	T operator^(const Vector3& other) const
	{
		return dot(other);
	}
	//�������this * other���������������򣨵�ǰ����ת��other�����õ�����������ֱ������
	Vector3 operator%(const Vector3 & other) const
	{
		return cross(other);
	}
	// ����������Ԫ��ֵ
	template <typename S> void setValue(S a, S b, S c)
	{
		x() = T(a);
		y() = T(b);
		z() = T(c);
	}
	template <typename S> void setValue(const Vector3<S>&other)
	{
		x() = T(other.x());
		y() = T(other.y());
		z() = T(other.z());
	}
	// ����ȡ��Ԫ�ص�ֵ
	template <typename S> void getValue(S & a, S & b, S & c) const
	{
		a = S(x());
		b = S(y());
		c = S(z());
	}
	template <typename S> void getValue(Vector3<S>& other) const
	{
		other.x() = S(x());
		other.y() = S(y());
		other.z() = S(z());
	}
	// Ԫ�ظ���
	constexpr static unsigned int dimensions() { return element_count; }
	// ������Сֵ��ͨ���Ǹ�ֵ��
	constexpr static T baseTypeLowest() { return std::numeric_limits<T>::lowest(); }
	// �������ֵ��ͨ������ֵ��
	constexpr static T baseTypeMax() { return std::numeric_limits<T>::max(); }
	// ������Сֵ��ͨ���Ǹ�ֵ��
	constexpr static T baseTypeSmallest() { return std::numeric_limits<T>::min(); }
	// ����Сֵe�� 1+e != 1
	constexpr static T baseTypeEpsilon() { return std::numeric_limits<T>::epsilon(); }
	// ����ǰ����Ԫ���γɵ�Vector2
	Vector2<T> st() const { return Vector2<T>(x(), y()); }
protected:
	T elements[element_count];
};
template<typename T>
inline const Vector3<T> operator*(T val, const Vector3<T>& v)
{
	return v * val;
}
//Ԥ������ģ���࣬����ֱ��ʹ��
typedef Vector3<int> Vec3i;
typedef Vector3<unsigned int> Vec3u;
typedef Vector3<float> Vec3f;
typedef Vector3<double> Vec3d;
typedef Vec3d Vec3;
typedef Vector3<int> Pos3i;
typedef Vector3<unsigned int> Pos3u;
typedef Vector3<float> Pos3f;
typedef Vector3<double> Pos3d;
typedef Pos3d Pos3;
typedef std::vector<Vec3i> Vec3iArray;
typedef std::vector<Vec3u> Vec3uArray;
typedef std::vector<Vec3f> Vec3fArray;
typedef std::vector<Vec3d> Vec3dArray;
typedef std::vector<Pos3i> Pos3iArray;
typedef std::vector<Pos3u> Pos3uArray;
typedef std::vector<Pos3f> Pos3fArray;
typedef std::vector<Pos3d> Pos3dArray;
//�ػ��Ĳ��ֳ�Ա����
//���
inline float dot(const Vec3i& v1, const Vec3i& v2) {
	return (float)(v1.x() * v2.x() + v1.y() *
		v2.y() + v1.z() * v2.z());
}
inline float dot(const Vec3u& v1, const Vec3u& v2) {
	return (float)(v1.x() * v2.x() + v1.y() *
		v2.y() + v1.z() * v2.z());
}
inline float dot(const Vec3f& v1, const Vec3f& v2) {
	return v1.x() * v2.x() + v1.y() * v2.y() +
		v1.z() * v2.z();
}
inline double dot(const Vec3d& v1, const Vec3d& v2) {
	return v1.x() * v2.x() + v1.y() * v2.y() +
		v1.z() * v2.z();
}
//���
inline Vec3f cross(const Vec3f& v1, const Vec3f& v2)
{
	Vec3f t;
	t.x() = v1.y() * v2.z() - v1.z() * v2.y();
	t.y() = v1.z() * v2.x() - v1.x() * v2.z();
	t.z() = v1.x() * v2.y() - v1.y() * v2.x();
	return t;
}
inline Vec3d cross(const Vec3d& v1, const Vec3d& v2)
{
	Vec3d t;
	t.x() = v1.y() * v2.z() - v1.z() * v2.y();
	t.y() = v1.z() * v2.x() - v1.x() * v2.z();
	t.z() = v1.x() * v2.y() - v1.y() * v2.x();
	return t;
}

//�������
template <typename T> std::ostream& operator<< (std::ostream& s, const Vector3<T>& v)
{
	return s << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ')';
}
#endif //_Vector3_H_INCLUDED
