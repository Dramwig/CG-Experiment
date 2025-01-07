#ifndef _Vector3_H_INCLUDED
#define _Vector3_H_INCLUDED
#include "Vector2.h"
template <typename T> class Vector3
{
public:
	typedef T BaseType;
	typedef T* T_ptr;
	static const int element_count = 3;
	// 默认构造
	Vector3() { elements[0] = 0; elements[1] = 0; elements[2] = 0; }
	//Vector3(T x, T y, T z){ elements[0] = x; elements[1] = y; elements[2] = z; }
	// 析构函数
	~Vector3() = default;
	// 拷贝构造
	Vector3(const Vector3& other)
	{
		elements[0] = other.x();
		elements[1] = other.y();
		elements[2] = other.z();
	}
	// 从其他基本类型的Vector3构造
	template<typename S>
	explicit Vector3(const Vector3<S>& other)
	{
		x() = (T)other.x();
		y() = (T)other.y();
		z() = (T)other.z();
	}
	// 从数组构造（要求至少3个元素）
	explicit Vector3(const T_ptr& pval)
	{
		elements[0] = pval[0];
		elements[1] = pval[1];
		elements[2] = pval[2];
	}
	// 构造成(a, a, a)
	explicit Vector3(T val)
	{
		elements[0] = elements[1] = elements[2] = val;
	}
	// 构造成(x, y, z)
	explicit Vector3(T x, T y, T z)
	{
		elements[0] = x;
		elements[1] = y;
		elements[2] = z;
	}
	// 从其他基本类型的Vector2构造成（x, y, 1），规格化二维齐次坐标
	template<typename S>
	explicit Vector3(const Vector2<S>& v)
	{
		elements[0] = (T)v.x();
		elements[1] = (T)v.y();
		elements[2] = (T)1;
	}
	// 从其他基本类型的Vector2构造成（x, y, z）
	template<typename S>
	explicit Vector3(const Vector2<S>& v, T z)
	{
		elements[0] = (T)v.x();
		elements[1] = (T)v.y();
		elements[2] = z;
	}
	// 返回元素，作为一个三维点坐标(x,y,z)
	const T& x() const { return elements[0]; }
	const T& y() const { return elements[1]; }
	const T& z() const { return elements[2]; }
	T& x() { return elements[0]; }
	T& y() { return elements[1]; }
	T& z() { return elements[2]; }
	// 返回元素数组指针
	T* ptr() { return elements; }
	const T* ptr() const { return elements; }
	// 返回前两个元素形成的Vector2
	Vector2<T> xy() const { return Vector2<T>(x(), y()); }
	// 运算符重载
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
	//点积
	T dot(const Vector3& other) const
	{
		return x() * other.x() + y() * other.y() + z() * other.z();
	}
	//叉积*this * other，按右手螺旋规则（当前向量转到other），得到与两向量垂直的向量
	Vector3 cross(const Vector3& other) const
	{
		return Vector3(y() * other.z() - z() * other.y(), z() * other.x() - x() * other.z(), x() *
			other.y() - y() * other.x());
	}
	//向量长度
	T length() const { return ::sqrt(x() * x() + y() * y() + z() * z()); }
	//向量长度的平方
	T lengthSquared() const { return x() * x() + y() * y() + z() * z(); }
	bool isNull() const { return !x() && !y() && !z(); }
	//规范化（可返回原长度、是否成功）
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
	//返回规范化向量（可返回原长度、是否成功）
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
	//下标运算访问元素（要求下标不越界）
	const T& operator[](unsigned i) const { return elements[i]; }
	T& operator[](unsigned i) { return elements[i]; }
	//向量点积
	T operator^(const Vector3& other) const
	{
		return dot(other);
	}
	//向量叉积this * other，按右手螺旋规则（当前向量转到other），得到与两向量垂直的向量
	Vector3 operator%(const Vector3 & other) const
	{
		return cross(other);
	}
	// 按类型设置元素值
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
	// 按需取出元素的值
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
	// 元素个数
	constexpr static unsigned int dimensions() { return element_count; }
	// 类型最小值（通常是负值）
	constexpr static T baseTypeLowest() { return std::numeric_limits<T>::lowest(); }
	// 类型最大值（通常是正值）
	constexpr static T baseTypeMax() { return std::numeric_limits<T>::max(); }
	// 类型最小值（通常是负值）
	constexpr static T baseTypeSmallest() { return std::numeric_limits<T>::min(); }
	// 类型小值e则 1+e != 1
	constexpr static T baseTypeEpsilon() { return std::numeric_limits<T>::epsilon(); }
	// 返回前两个元素形成的Vector2
	Vector2<T> st() const { return Vector2<T>(x(), y()); }
protected:
	T elements[element_count];
};
template<typename T>
inline const Vector3<T> operator*(T val, const Vector3<T>& v)
{
	return v * val;
}
//预声明的模板类，可以直接使用
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
//特化的部分成员函数
//点积
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
//叉积
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

//输出测试
template <typename T> std::ostream& operator<< (std::ostream& s, const Vector3<T>& v)
{
	return s << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ')';
}
#endif //_Vector3_H_INCLUDED
