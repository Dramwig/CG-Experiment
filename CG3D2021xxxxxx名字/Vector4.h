#ifndef _Vector4_H_INCLUDED
#define _Vector4_H_INCLUDED

#include "Vector3.h"

template <typename T> class Vector4
{
public:
    typedef T BaseType;
    typedef T* T_ptr;
    static const int element_count = 4;

    // Ĭ�Ϲ��캯��
    Vector4()
    {
        elements[0] = 0;
        elements[1] = 0;
        elements[2] = 0;
        elements[3] = 0;
    }
    // ��������
    ~Vector4() = default;

    // ��������
    Vector4(const Vector4& other)
    {
        elements[0] = other.x();
        elements[1] = other.y();
        elements[2] = other.z();
        elements[3] = other.w();
    }
    // �������������͵�Vector4����
    template<typename S>
    explicit Vector4(const  Vector4<S>& other)
    {
        x() = (T)other.x();
        y() = (T)other.y();
        z() = (T)other.z();
        w() = (T)other.w();
    }
    // �����鹹�죨Ҫ������4��Ԫ�أ�
    explicit Vector4(const T_ptr& pval)
    {
        elements[0] = pval[0];
        elements[1] = pval[1];
        elements[2] = pval[2];
        elements[3] = pval[3];
    }
    // �����(a, a, a, a)
    explicit Vector4(T val)
    {
        elements[0] = elements[1] = elements[2] = elements[3] = val;
    }
    // �����(x, y, z, w)
    explicit Vector4(T x, T y, T z, T w)
    {
        elements[0] = x;
        elements[1] = y;
        elements[2] = z;
        elements[3] = w;
    }
    // �������������͵�Vector3����ɣ�x, y, z, 1���������ά�������
    template<typename S>
    explicit Vector4(const Vector3<S>& v)
    {
        elements[0] = (T)v.x();
        elements[1] = (T)v.y();
        elements[2] = (T)v.z();
        elements[3] = (T)1;
    }
    // �������������͵�Vector3����ɣ�x, y, z��w��
    template<typename S>
    explicit Vector4(const Vector3<S>& v, T w)
    {
        elements[0] = (T)v.x();
        elements[1] = (T)v.y();
        elements[2] = (T)v.z();
        elements[3] = w;
    }
    // �������������͵�Vector2����ɣ�ux, uy, vx, vy��
    template<typename S>
    explicit Vector4(const Vector2<S>& u, const Vector2<S>& v)
    {
        elements[0] = (T)u.x();
        elements[1] = (T)u.y();
        elements[2] = (T)v.x();
        elements[3] = (T)v.y();
    }

    // ����Ԫ������ָ��
    T* ptr() { return elements; }
    const T* ptr() const { return elements; }

    // ����Ԫ�أ���Ϊһ����ά���������
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

    // ����ǰ����Ԫ���γɵ�Vector3
    Vector3<T> xyz() const { return Vector3<T>(x(), y(), z()); }

    // ����ǰ����Ԫ���γɵ�Vector2
    Vector2<T> xy() const { return Vector2<T>(x(), y()); }

    // ��Ԫ���������
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

    // һԪ�����
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

    //��ϵ����
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

    //�������
    T dot(const Vector4& other) const
    {
        return x() * other.x() + y() * other.y() + z() * other.z() + w() * other.w();
    }
    T operator^(const Vector4& other) const
    {
        return dot(other);
    }

    //��������
    T length() const { return (T)::sqrt(x() * x() + y() * y() + z() * z() + w() * w()); }
    //��������ƽ��
    T lengthSquared() const { return x() * x() + y() * y() + z() * z() + w() * w(); }

    bool isNull() const { return !x() && !y() && !z() && !w(); }
    //�淶�����ɷ���ԭ���ȡ��Ƿ�ɹ���
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
            //*this *= (T)(1.0/l);//1.0/l���������
        }
        else {
            if (success)
                *success = false;
        }
        return *this;
    }
    //���ع淶���������ɷ���ԭ���ȡ��Ƿ�ɹ���
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
    //�±��������Ԫ�أ�Ҫ���±겻Խ�磩
    const T& operator[](unsigned i) const { return elements[i]; }
    T& operator[](unsigned i) { return elements[i]; }

    /// Ԫ�ظ���
    constexpr static unsigned int dimensions() { return 4; }
    /// ��������ֵ��ͨ���Ǹ�ֵ��
    constexpr static T baseTypeLowest() { return std::numeric_limits<T>::lowest(); }
    /// �������ֵ��ͨ������ֵ��
    constexpr static T baseTypeMax() { return std::numeric_limits<T>::max(); }
    /// ������Сֵ��ͨ���Ǹ�ֵ��
    constexpr static T baseTypeSmallest() { return std::numeric_limits<T>::min(); }
    /// ����Сֵe�� 1+e != 1
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

//�������
template <typename T> std::ostream& operator<< (std::ostream& s, const Vector4<T>& v)
{
    return s << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ' ' << v.w() << ')';
}

#endif //_Vector4_H_INCLUDED
