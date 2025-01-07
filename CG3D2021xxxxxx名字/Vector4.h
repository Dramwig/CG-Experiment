#ifndef _Vector4_H_INCLUDED
#define _Vector4_H_INCLUDED

#include "Vector3.h"

template <typename T> class Vector4
{
public:
    typedef T BaseType;
    typedef T* T_ptr;
    static const int element_count = 4;

    // 默认构造函数
    Vector4()
    {
        elements[0] = 0;
        elements[1] = 0;
        elements[2] = 0;
        elements[3] = 0;
    }
    // 析构函数
    ~Vector4() = default;

    // 拷贝构造
    Vector4(const Vector4& other)
    {
        elements[0] = other.x();
        elements[1] = other.y();
        elements[2] = other.z();
        elements[3] = other.w();
    }
    // 从其他基本类型的Vector4构造
    template<typename S>
    explicit Vector4(const  Vector4<S>& other)
    {
        x() = (T)other.x();
        y() = (T)other.y();
        z() = (T)other.z();
        w() = (T)other.w();
    }
    // 从数组构造（要求至少4个元素）
    explicit Vector4(const T_ptr& pval)
    {
        elements[0] = pval[0];
        elements[1] = pval[1];
        elements[2] = pval[2];
        elements[3] = pval[3];
    }
    // 构造成(a, a, a, a)
    explicit Vector4(T val)
    {
        elements[0] = elements[1] = elements[2] = elements[3] = val;
    }
    // 构造成(x, y, z, w)
    explicit Vector4(T x, T y, T z, T w)
    {
        elements[0] = x;
        elements[1] = y;
        elements[2] = z;
        elements[3] = w;
    }
    // 从其他基本类型的Vector3构造成（x, y, z, 1），规格化三维齐次坐标
    template<typename S>
    explicit Vector4(const Vector3<S>& v)
    {
        elements[0] = (T)v.x();
        elements[1] = (T)v.y();
        elements[2] = (T)v.z();
        elements[3] = (T)1;
    }
    // 从其他基本类型的Vector3构造成（x, y, z，w）
    template<typename S>
    explicit Vector4(const Vector3<S>& v, T w)
    {
        elements[0] = (T)v.x();
        elements[1] = (T)v.y();
        elements[2] = (T)v.z();
        elements[3] = w;
    }
    // 从其他基本类型的Vector2构造成（ux, uy, vx, vy）
    template<typename S>
    explicit Vector4(const Vector2<S>& u, const Vector2<S>& v)
    {
        elements[0] = (T)u.x();
        elements[1] = (T)u.y();
        elements[2] = (T)v.x();
        elements[3] = (T)v.y();
    }

    // 返回元素数组指针
    T* ptr() { return elements; }
    const T* ptr() const { return elements; }

    // 返回元素，作为一个三维点齐次坐标
    const T& x() const { return elements[0]; }
    const T& y() const { return elements[1]; }
    const T& z() const { return elements[2]; }
    const T& w() const { return elements[3]; }
    const T& r() const { return elements[0]; }
    const T& g() const { return elements[1]; }
    const T& b() const { return elements[2]; }
    const T& a() const { return elements[3]; }
    T& x() { return elements[0]; }
    T& y() { return elements[1]; }
    T& z() { return elements[2]; }
    T& w() { return elements[3]; }
    T& r() { return elements[0]; }
    T& g() { return elements[1]; }
    T& b() { return elements[2]; }
    T& a() { return elements[3]; }

    // 返回前两个元素形成的Vector3
    Vector3<T> xyz() const { return Vector3<T>(x(), y(), z()); }

    // 返回前两个元素形成的Vector2
    Vector2<T> xy() const { return Vector2<T>(x(), y()); }

    // 二元运算符重载
    Vector4 operator+(const Vector4& other) const
    {
        return Vector4(x() + other.x(), y() + other.y(), z() + other.z(), w() + other.w());
    }
    Vector4 operator-(const Vector4& other) const
    {
        return Vector4(x() - other.x(), y() - other.y(), z() - other.z(), w() - other.w());
    }
    Vector4 operator*(const Vector4& other) const
    {
        return Vector4(x() * other.x(), y() * other.y(), z() * other.z(), w() * other.w());
    }
    Vector4 operator/(const Vector4& other) const
    {
        return Vector4(x() / other.x(), y() / other.y(), z() / other.z(), w() / other.w());
    }
    Vector4 operator+(T val) const
    {
        return Vector4(x() + val, y() + val, z() + val, w() + val);
    }
    Vector4 operator-(T val) const
    {
        return Vector4(x() - val, y() - val, z() - val, w() - val);
    }
    Vector4 operator*(T val) const
    {
        return Vector4(x() * val, y() * val, z() * val, w() * val);
    }
    Vector4 operator/(T val) const
    {
        return Vector4(x() / val, y() / val, z() / val, w() / val);
    }
    Vector4 operator-() const
    {
        return Vector4(-x(), -y(), -z(), -w());
    }

    // 一元运算符
    Vector4& negate()
    {
        x() = -x();
        y() = -y();
        z() = -z();
        w() = -w();
        return *this;
    }

    Vector4& operator+=(const Vector4& other)
    {
        x() += other.x();
        y() += other.y();
        z() += other.z();
        w() += other.w();
        //*this = *this + other;
        return *this;
    }
    Vector4& operator-=(const Vector4& other)
    {
        x() -= other.x();
        y() -= other.y();
        z() -= other.z();
        w() -= other.w();
        //*this = *this - other;
        return *this;
    }
    Vector4& operator*=(const Vector4& other)
    {
        x() *= other.x();
        y() *= other.y();
        z() *= other.z();
        w() *= other.w();
        //*this = *this * other;
        return *this;
    }
    Vector4& operator/=(const Vector4& other)
    {
        x() /= other.x();
        y() /= other.y();
        z() /= other.z();
        w() /= other.w();
        //*this = *this / other;
        return *this;
    }
    Vector4& operator+=(T val)
    {
        x() += val;
        y() += val;
        z() += val;
        w() += val;
        //*this = *this + val;
        return *this;
    }
    Vector4& operator-=(T val)
    {
        x() -= val;
        y() -= val;
        z() -= val;
        w() -= val;
        //*this = *this - val;
        return *this;
    }
    Vector4& operator*=(T val)
    {
        x() *= val;
        y() *= val;
        z() *= val;
        w() *= val;
        //*this = *this * val;
        return *this;
    }
    Vector4& operator/=(T val)
    {
        x() /= val;
        y() /= val;
        z() /= val;
        w() /= val;
        //*this = *this / val;
        return *this;
    }

    Vector4& operator=(const Vector4& other)
    {
        if (this != &other)
        {
            x() = other.x();
            y() = other.y();
            z() = other.z();
            w() = other.w();
        }
        return *this;
    }
    Vector4& operator=(T val)
    {
        x() = y() = z() = w() = val;
        return *this;
    }

    //关系运算
    template<typename S>
    bool operator==(const Vector4<S>& other) const
    {
        return x() == other.x() && y() == other.y() && z() == other.z() && w() == other.w();
    }
    template<typename S>
    bool operator!=(const Vector4<S>& other) const
    {
        return !operator==(other);
    }
    template<typename S>
    bool operator<(const Vector4<S>& other) const
    {
        if (x() != other.x())
            return x() < other.x();
        else
            if (y() != other.y())
                return y() < other.y();
            else
                if (z() != other.z())
                    return z() < other.z();
                else
                    return w() < other.w();
    }

    bool equalWithTolerance(const Vector4& other, T e) const
    {
        for (int i = 0; i < 4; i++)
            if ((((*this)[i] > other[i]) ? (*this)[i] - other[i] : other[i] - (*this)[i]) > e)
                return false;

        return true;
    }

    //向量点积
    T dot(const Vector4& other) const
    {
        return x() * other.x() + y() * other.y() + z() * other.z() + w() * other.w();
    }
    T operator^(const Vector4& other) const
    {
        return dot(other);
    }

    //向量长度
    T length() const { return (T)::sqrt(x() * x() + y() * y() + z() * z() + w() * w()); }
    //向量长度平方
    T lengthSquared() const { return x() * x() + y() * y() + z() * z() + w() * w(); }

    bool isNull() const { return !x() && !y() && !z() && !w(); }
    //规范化（可返回原长度、是否成功）
    const Vector4& normalize(T* len = nullptr, bool* success = nullptr)
    {
        T l = length();
        if (len)
            *len = l;
        if (l)
        {
            x() /= l;
            y() /= l;
            z() /= l;
            w() /= l;
            if (success)
                *success = true;
            //*this *= (T)(1.0/l);//1.0/l可能溢出？
        }
        else {
            if (success)
                *success = false;
        }
        return *this;
    }
    //返回规范化向量（可返回原长度、是否成功）
    Vector4 normalized(T* len = nullptr, bool* success = nullptr) const
    {
        T l = length();
        if (len)
            *len = l;
        if (l)
        {
            if (success)
                *success = true;
            return Vector4(x() / l, y() / l, z() / l, w() / l);
        }
        else
        {
            if (success)
                *success = false;
            return Vector4(T(0));
        }
    }
    //下标运算访问元素（要求下标不越界）
    const T& operator[](unsigned i) const { return elements[i]; }
    T& operator[](unsigned i) { return elements[i]; }

    /// 元素个数
    constexpr static unsigned int dimensions() { return 4; }
    /// 类型最下值（通常是负值）
    constexpr static T baseTypeLowest() { return std::numeric_limits<T>::lowest(); }
    /// 类型最大值（通常是正值）
    constexpr static T baseTypeMax() { return std::numeric_limits<T>::max(); }
    /// 类型最小值（通常是负值）
    constexpr static T baseTypeSmallest() { return std::numeric_limits<T>::min(); }
    /// 类型小值e则 1+e != 1
    constexpr static T baseTypeEpsilon() { return std::numeric_limits<T>::epsilon(); }
protected:
    T elements[element_count];
};

template<typename T>
inline const Vector4<T> operator*(T val, const Vector4<T>& v)
{
    return v * val;
}

typedef Vector4<int>            Vec4i;
typedef Vector4<unsigned int>   Vec4u;
typedef Vector4<float>          Vec4f;
typedef Vector4<double>         Vec4d;
typedef Vec4d Vec4;

typedef std::vector<Vec4i> Vec4iArray;
typedef std::vector<Vec4u> Vec4uArray;
typedef std::vector<Vec4f> Vec4fArray;
typedef std::vector<Vec4d> Vec4dArray;

inline float dot(const Vec4i& v1, const Vec4i& v2) { return (float)(v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w()); }
inline float dot(const Vec4u& v1, const Vec4u& v2) { return (float)(v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w()); }
inline float dot(const Vec4f& v1, const Vec4f& v2) { return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w(); }
inline double dot(const Vec4d& v1, const Vec4d& v2) { return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w(); }

//输出测试
template <typename T> std::ostream& operator<< (std::ostream& s, const Vector4<T>& v)
{
    return s << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ' ' << v.w() << ')';
}

#endif //_Vector4_H_INCLUDED
