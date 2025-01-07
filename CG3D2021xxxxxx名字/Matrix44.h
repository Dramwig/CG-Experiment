#ifndef _Matrix44_H_INCLUDED
#define _Matrix44_H_INCLUDED

#include "Vector4.h"
#include "Matrix33.h"
#include <cassert>

template <typename T> class Matrix44
{
public:
    typedef T BaseType;

    // Ĭ�Ϲ���ɵ�λ����
    Matrix44()
    {
        setIdentity();
    }

    ~Matrix44() = default;

    // ���������͵�Matrix44������
    template<typename S>
    explicit Matrix44(const Matrix44<S>& m)
    {
        e(0, 0) = (T)m.e(0, 0); e(1, 0) = (T)m.e(1, 0); e(2, 0) = (T)m.e(2, 0); e(3, 0) = (T)m.e(3, 0);
        e(0, 1) = (T)m.e(0, 1); e(1, 1) = (T)m.e(1, 1); e(2, 1) = (T)m.e(2, 1); e(3, 1) = (T)m.e(3, 1);
        e(0, 2) = (T)m.e(0, 2); e(1, 2) = (T)m.e(1, 2); e(2, 2) = (T)m.e(2, 2); e(3, 2) = (T)m.e(3, 2);
        e(0, 3) = (T)m.e(0, 3); e(1, 3) = (T)m.e(1, 3); e(2, 3) = (T)m.e(2, 3); e(3, 3) = (T)m.e(3, 3);
    }

    // ��������
    Matrix44(const Matrix44& other)
    {
        operator=(other);
    }

    // ���Խ�Ԫ��ָ��ֵ����
    explicit Matrix44(T n)
    {
        setIdentity();
        e(0, 0) = e(1, 1) = e(2, 2) = e(3, 3) = n;
    }

    // ʹ��16��Ԫ�ص����鹹�죨���У�
    explicit Matrix44(T* val)
    {
        fillPtr(val);
    }

    // ʹ��16��Ԫ�ع��죨���У�
    explicit Matrix44(T e00, T e01, T e02, T e03,
        T e10, T e11, T e12, T e13,
        T e20, T e21, T e22, T e23,
        T e30, T e31, T e32, T e33)
    {
        e(0, 0) = e00; e(0, 1) = e01; e(0, 2) = e02; e(0, 3) = e03;
        e(1, 0) = e10; e(1, 1) = e11; e(1, 2) = e12; e(1, 3) = e13;
        e(2, 0) = e20; e(2, 1) = e21; e(2, 2) = e22; e(2, 3) = e23;
        e(3, 0) = e30; e(3, 1) = e31; e(3, 2) = e32; e(3, 3) = e33;
    }

    // ��Ԫ����Ϊָ��ֵ
    Matrix44& fill(T val)
    {
        e(0, 0) = e(1, 0) = e(2, 0) = e(3, 0) =
            e(0, 1) = e(1, 1) = e(2, 1) = e(3, 1) =
            e(0, 2) = e(1, 2) = e(2, 2) = e(3, 2) =
            e(0, 3) = e(1, 3) = e(2, 3) = e(3, 3) = val;
        return *this;
    }

    // ʹ��16��Ԫ�ص������趨��Ԫ��ֵ
    Matrix44& fillPtr(T* val)
    {
        memcpy(ptr(), val, sizeof(T) * 16);
        return *this;
    }

    // ����X��������һ�У�1*3����
    Vector3<T> getX() const
    {
        return Vector3<T>(eVec[0].x(), eVec[0].y(), eVec[0].z());
    }

    // ����Y�������ڶ��У�1*3����
    Vector3<T> getY() const
    {
        return Vector3<T>(eVec[1].x(), eVec[1].y(), eVec[1].z());
    }

    // ����Z�����������У�1*3����
    Vector3<T> getZ() const
    {
        return Vector3<T>(eVec[2].x(), eVec[2].y(), eVec[2].z());
    }

    // ����ƽ�������������У�1*3����
    Vector3<T> getT() const
    {
        return Vector3<T>(eVec[3].x(), eVec[3].y(), eVec[3].z());
    }

    // ����X��������һ�У�1*3����
    Matrix44& setX(const Vector3<T>& v)
    {
        eVec[0].x() = v.x();
        eVec[0].y() = v.y();
        eVec[0].z() = v.z();
        return *this;
    }

    // ����Y�������ڶ��У�1*3����
    Matrix44& setY(const Vector3<T>& v)
    {
        eVec[1].x() = v.x();
        eVec[1].y() = v.y();
        eVec[1].z() = v.z();
        return *this;
    }

    // ����Z�����������У�1*3����
    Matrix44& setZ(const Vector3<T>& v)
    {
        eVec[2].x() = v.x();
        eVec[2].y() = v.y();
        eVec[2].z() = v.z();
        return *this;
    }

    // ����ƽ�������������У�1*3����
    Matrix44& setT(const Vector3<T>& v)
    {
        eVec[3].x() = v.x();
        eVec[3].y() = v.y();
        eVec[3].z() = v.z();
        return *this;
    }

    // ����3*3���󲻱䣬����Ԫ��Ϊ1�����һ�С�һ�е�����Ԫ����Ϊ0
    Matrix44 as3x3() const
    {
        Matrix44 t = *this;
        t[0][3] = 0;
        t[1][3] = 0;
        t[2][3] = 0;
        t[3][3] = 1;
        t[3][0] = 0;
        t[3][1] = 0;
        t[3][2] = 0;
        return t;
    }

    // ��������3*3����
    Matrix33<T> get3x3() const
    {
        Matrix33<T> t;
        t.e(0, 0) = e(0, 0); t.e(1, 0) = e(1, 0); t.e(2, 0) = e(2, 0);
        t.e(0, 1) = e(0, 1); t.e(1, 1) = e(1, 1); t.e(2, 1) = e(2, 1);
        t.e(0, 2) = e(0, 2); t.e(1, 2) = e(1, 2); t.e(2, 2) = e(2, 2);
        return t;
    }

    // ��������3*3��������Ԫ�ز���
    void set3x3(const Matrix33<T>& m)
    {
        e(0, 0) = m.e(0, 0); e(1, 0) = m.e(1, 0); e(2, 0) = m.e(2, 0);
        e(0, 1) = m.e(0, 1); e(1, 1) = m.e(1, 1); e(2, 1) = m.e(2, 1);
        e(0, 2) = m.e(0, 2); e(1, 2) = m.e(1, 2); e(2, 2) = m.e(2, 2);
    }

    //�ж��Ƿ���ͬ
    bool operator==(const Matrix44& m) const
    {
        return memcmp(m.eVec, eVec, sizeof(T) * 4 * 4) == 0;
    }

    //�ж��Ƿ񲻵�
    bool operator!=(const Matrix44& m) const
    {
        return !operator==(m);
    }

    //��ֵ
    Matrix44& operator=(const Matrix44& m)
    {
        memcpy(eVec, m.eVec, sizeof(T) * 16);
        return *this;
    }

    //��ֵ
    Matrix44& operator=(T val)
    {
        return fill(val);
    }

    // ������ӣ����غ�
    Matrix44 operator+(const Matrix44& m) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) + m.e(j, i);

        return t;
    }
    // ������������ز�
    Matrix44 operator-(const Matrix44& m) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) - m.e(j, i);

        return t;
    }
    // ��ʣ���󣬷��ؽ������
    Matrix44 operator*(const Matrix44& m) const
    {
        Matrix44<T> t;
        Matrix44<T>::multiply(t, *this, m);
        return t;
    }
    //��Ԫ�ؼ���ָ��ֵ�����ؽ������
    Matrix44 operator+(T d) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) + d;
        return t;
    }
    //��Ԫ�ؼ�ȥָ��ֵ�����ؽ������
    Matrix44 operator-(T d) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) - d;
        return t;
    }
    //��Ԫ�س���ָ��ֵ�����ؽ������
    Matrix44 operator*(T d) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }
    //��Ԫ�س���ָ��ֵ�����ؽ������
    Matrix44 operator/(T d) const
    {
        d = (T)1 / d;
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }

    // ����һ������
    Matrix44& operator+=(const Matrix44& m)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) += m.e(i, j);
        return *this;
    }
    // ��ȥһ������
    Matrix44& operator-=(const Matrix44& m)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) -= m.e(i, j);
        return *this;
    }
    //��ʣһ������
    Matrix44& operator*=(const Matrix44& m)
    {
        return postMultiply(m);
    }
    //��Ԫ�ؼ���ָ��ֵ
    Matrix44& operator+=(T d)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) += d;
        return *this;
    }
    //��Ԫ�ؼ�ȥָ��ֵ
    Matrix44& operator-=(T d)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) -= d;
        return *this;
    }
    //��Ԫ�س���ָ��ֵ
    Matrix44& operator*=(T d)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) *= d;
        return *this;
    }
    //��Ԫ�س���ָ��ֵ
    Matrix44& operator/=(T d)
    {
        d = (T)1 / d;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) *= d;
        return *this;
    }

    //���ظ�Ԫ���෴�ľ���
    Matrix44 operator-() const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = -e(j, i);
        return t;
    }
    const Matrix44& negate()
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) = -(j, i);
        return *this;
    }

    //������Ԫ��ָ�루��ֵ��
    T* ptr()
    {
        return &e(0, 0);
    }
    //������Ԫ��ָ�루��ֵ��
    const T* ptr() const
    {
        return &e(0, 0);
    }

    //ת��
    Matrix44& transpose()
    {
        T tmp;
        for (int i = 0; i < 4; ++i)
            for (int j = i; j < 4; ++j)
            {
                tmp = e(j, i);
                e(j, i) = e(i, j);
                e(i, j) = tmp;
            }
        return *this;
    }
    //���ض�Ӧ��ת�þ�����ֵ��
    Matrix44 getTransposed() const
    {
        Matrix44 m;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m.e(j, i) = e(i, j);
        return m;
    }
    //���ض�Ӧ��ת�þ�����ֵ��
    Matrix44& getTransposed(Matrix44& dest) const
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                dest.e(j, i) = e(i, j);
        return dest;
    }

    //�Ƿ�Ϊ�գ���Ԫ�ض�Ϊ0��
    bool isNull() const
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (e(i, j) != 0)
                    return false;
        return true;
    }
    //����Ϊ�գ���Ԫ�ض�Ϊ0��
    Matrix44& setNull()
    {
        fill(0);
        return *this;
    }
    //����һ���վ���
    static Matrix44& getNull(Matrix44& out)
    {
        out.fill(0);
        return out;
    }
    //����һ���վ���
    static Matrix44 getNull()
    {
        return Matrix44().fill(0);
    }

    //�ж��Ƿ�Ϊ��λ��
    bool isIdentity() const
    {
        Matrix44 i;
        return memcmp(ptr(), i.ptr(), sizeof(T) * 16) == 0;
    }
    //��λ��
    Matrix44& setIdentity()
    {
        static const T I4d[] =
        {
          (T)1, (T)0, (T)0, (T)0,
          (T)0, (T)1, (T)0, (T)0,
          (T)0, (T)0, (T)1, (T)0,
          (T)0, (T)0, (T)0, (T)1
        };
        memcpy(eVec, I4d, sizeof(T) * 16);
        return *this;
    }
    //����һ����λ����
    static Matrix44 getIdentity()
    {
        return Matrix44();
    }
    //����һ����λ����
    static Matrix44& getIdentity(Matrix44& out)
    {
        out.setIdentity();
        return out;
    }

    ////������������任����������ʽֵ
    //T getInverse(Matrix44& dest) const;
    //������󣬷�������ʽֵ
    Matrix44 getInverse(T* determinant = nullptr) const
    {
        Matrix44 tmp;
        T det = getInverse(tmp);
        if (determinant)
            *determinant = det;
        return tmp;
    }
    //���棬��������ʽֵ
    Matrix44& invert(T* determinant = nullptr)
    {
        T det = getInverse(*this);
        if (determinant)
            *determinant = det;
        return *this;
    }
    //������ʽֵ

    //������ˣ�out = p * q ��������� = ����� * �Ҿ���
    static Matrix44& multiply(Matrix44& out, const Matrix44& p, const Matrix44& q)
    {
        assert(out.ptr() != p.ptr() && out.ptr() != q.ptr());

        out.e(0, 0) = q.e(0, 0) * p.e(0, 0) + q.e(1, 0) * p.e(0, 1) + q.e(2, 0) * p.e(0, 2) + q.e(3, 0) * p.e(0, 3);
        out.e(0, 1) = q.e(0, 1) * p.e(0, 0) + q.e(1, 1) * p.e(0, 1) + q.e(2, 1) * p.e(0, 2) + q.e(3, 1) * p.e(0, 3);
        out.e(0, 2) = q.e(0, 2) * p.e(0, 0) + q.e(1, 2) * p.e(0, 1) + q.e(2, 2) * p.e(0, 2) + q.e(3, 2) * p.e(0, 3);
        out.e(0, 3) = q.e(0, 3) * p.e(0, 0) + q.e(1, 3) * p.e(0, 1) + q.e(2, 3) * p.e(0, 2) + q.e(3, 3) * p.e(0, 3);

        out.e(1, 0) = q.e(0, 0) * p.e(1, 0) + q.e(1, 0) * p.e(1, 1) + q.e(2, 0) * p.e(1, 2) + q.e(3, 0) * p.e(1, 3);
        out.e(1, 1) = q.e(0, 1) * p.e(1, 0) + q.e(1, 1) * p.e(1, 1) + q.e(2, 1) * p.e(1, 2) + q.e(3, 1) * p.e(1, 3);
        out.e(1, 2) = q.e(0, 2) * p.e(1, 0) + q.e(1, 2) * p.e(1, 1) + q.e(2, 2) * p.e(1, 2) + q.e(3, 2) * p.e(1, 3);
        out.e(1, 3) = q.e(0, 3) * p.e(1, 0) + q.e(1, 3) * p.e(1, 1) + q.e(2, 3) * p.e(1, 2) + q.e(3, 3) * p.e(1, 3);

        out.e(2, 0) = q.e(0, 0) * p.e(2, 0) + q.e(1, 0) * p.e(2, 1) + q.e(2, 0) * p.e(2, 2) + q.e(3, 0) * p.e(2, 3);
        out.e(2, 1) = q.e(0, 1) * p.e(2, 0) + q.e(1, 1) * p.e(2, 1) + q.e(2, 1) * p.e(2, 2) + q.e(3, 1) * p.e(2, 3);
        out.e(2, 2) = q.e(0, 2) * p.e(2, 0) + q.e(1, 2) * p.e(2, 1) + q.e(2, 2) * p.e(2, 2) + q.e(3, 2) * p.e(2, 3);
        out.e(2, 3) = q.e(0, 3) * p.e(2, 0) + q.e(1, 3) * p.e(2, 1) + q.e(2, 3) * p.e(2, 2) + q.e(3, 3) * p.e(2, 3);

        out.e(3, 0) = q.e(0, 0) * p.e(3, 0) + q.e(1, 0) * p.e(3, 1) + q.e(2, 0) * p.e(3, 2) + q.e(3, 0) * p.e(3, 3);
        out.e(3, 1) = q.e(0, 1) * p.e(3, 0) + q.e(1, 1) * p.e(3, 1) + q.e(2, 1) * p.e(3, 2) + q.e(3, 1) * p.e(3, 3);
        out.e(3, 2) = q.e(0, 2) * p.e(3, 0) + q.e(1, 2) * p.e(3, 1) + q.e(2, 2) * p.e(3, 2) + q.e(3, 2) * p.e(3, 3);
        out.e(3, 3) = q.e(0, 3) * p.e(3, 0) + q.e(1, 3) * p.e(3, 1) + q.e(2, 3) * p.e(3, 2) + q.e(3, 3) * p.e(3, 3);

        return out;
    }
    //�ҳ�һ���󣨵�ǰ���� <= ��ǰ���� * m��
    Matrix44& postMultiply(const Matrix44& m)
    {
        Matrix44<T> t;
        return *this = multiply(t, *this, m);
    }
    //���һ���󣨵�ǰ���� <= m * ��ǰ����
    Matrix44& preMultiply(const Matrix44& m)
    {
        Matrix44<T> t;
        return *this = multiply(t, m, *this);
    }

    //����һ���ƹ�ԭ��ֱ�ߣ�0��0��0��-��x, y, z����תָ���Ƕȣ��ȣ�����ת����
    static Matrix44& getRotation(Matrix44& out, T degrees, T x, T y, T z);
    //����һ���ƹ�ԭ��ֱ�ߣ�0��0��0��-��x, y, z����תָ���Ƕȣ��ȣ�����ת����
    static Matrix44 getRotation(T degrees, T x, T y, T z)
    {
        Matrix44 m;
        return getRotation(m, degrees, x, y, z);
    }
    //����һ���ƹ�ԭ��ֱ�ߣ�0��0��0��-��x, y, z����תָ���Ƕȣ��ȣ�����ת����
    static Matrix44 getRotation(T degrees, const Vector3<T>& v)
    {
        return getRotation(degrees, v.x(), v.y(), v.z());
    }
    //����һ������v2��ת������v1��ת�ľ���
    static Matrix44 getRotation(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2)
    {
        return getRotation(degrees1, v1.x(), v1.y(), v1.z()) * getRotation(degrees2, v2.x(), v2.y(), v2.z());
    }
    //����һ������v3��ת��Ȼ����v2��ת������v1��ת�ľ���
    static Matrix44 getRotation(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2, T degrees3, const Vector3<T>& v3)
    {
        return getRotation(degrees1, v1.x(), v1.y(), v1.z()) * getRotation(degrees2, v2.x(), v2.y(), v2.z()) * getRotation(degrees3, v3.x(), v3.y(), v3.z());
    }

    //��һ��ԭ��ֱ����ת����ǰ�������һ����ת����
    Matrix44& rotate(T degrees, const Vector3<T>& v)
    {
        return rotate(degrees, v.x(), v.y(), v.z());
    }
    //��һ��ԭ��ֱ����ת����ǰ�������һ����ת����
    Matrix44& rotate(T degrees, T x, T y, T z)
    {
        return preMultiply(getRotation(degrees, x, y, z));
    }
    //����v2��ת������v1��ת
    Matrix44& rotate(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2)
    {
        return preMultiply(getRotation(degrees1, v1, degrees2, v2));
    }
    //����v3��ת��Ȼ����v2��ת������v1��ת
    Matrix44& rotate(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2, T degrees3, const Vector3<T>& v3)
    {
        return preMultiply(getRotation(degrees1, v1, degrees2, v2, degrees3, v3));
    }

    //����һ����Z����ת������Y����ת������X����ת�ľ���
    static Matrix44 getRotationXYZ(T degX, T degY, T degZ)
    {
        return getRotation(degX, 1, 0, 0) * getRotation(degY, 0, 1, 0) * getRotation(degZ, 0, 0, 1);
    }
    //��Z����ת������Y����ת������X����ת
    Matrix44& rotateXYZ(T degX, T degY, T degZ)
    {
        return preMultiply(getRotationXYZ(degX, degY, degZ));
    }

    //����һ����X����ת������Y����ת������Z����ת�ľ���
    static Matrix44 getRotationZYX(T degZ, T degY, T degX)
    {
        return getRotation(degZ, 0, 0, 1) * getRotation(degY, 0, 1, 0) * getRotation(degX, 1, 0, 0);
    }
    //��X����ת������Y����ת������Z����ת
    Matrix44& rotateZYX(T degZ, T degY, T degX)
    {
        return preMultiply(getRotationZYX(degZ, degY, degX));
    }

    ////����һ����from��ת��to�����ǹ�ԭ���ֱ�ߣ��ľ���
    //static Matrix44& getRotation(Matrix44& out, const Vector3<T>& from, const Vector3<T>& to);
    //����һ����from��ת��to�����ǹ�ԭ���ֱ�ߣ��ľ���
    static Matrix44 getRotation(const Vector3<T>& from, const Vector3<T>& to)
    {
        Matrix44 m;
        return getRotation(m, from, to);
    }

    //��from��ת��to�����ǹ�ԭ���ֱ�ߣ�����ǰ������߳���һ����ת����
    Matrix44& rotate(const Vector4<T>& from, const Vector4<T>& to)
    {
        return preMultiply(getRotation(from, to));
    }
    //��from��ת��to�����ǹ�ԭ���ֱ�ߣ�����ǰ������߳���һ����ת����
    Matrix44& rotate(const Vector3<T>& from, const Vector3<T>& to)
    {
        return preMultiply(getRotation(from, to));
    }

    //����ƽ��ʸ������һ��ƽ�ƾ�����������ʽ��
    static Matrix44& getTranslation(Matrix44& out, const Vector3<T>& v)
    {
        return getTranslation(out, v.x(), v.y(), v.z());
    }
    //����ƽ��ʸ������һ��ƽ�ƾ�����������ʽ��
    static Matrix44 getTranslation(const Vector3<T>& v)
    {
        Matrix44 m;
        return getTranslation(m, v.x(), v.y(), v.z());
    }
    //����ƽ��ʸ������һ��ƽ�ƾ�����������ʽ��
    static Matrix44 getTranslation(T x, T y, T z)
    {
        Matrix44 m;
        return getTranslation(m, x, y, z);
    }
    //����ƽ��ʸ������һ��ƽ�ƾ�����������ʽ����3�б�ʾƽ�ƣ�
    static Matrix44& getTranslation(Matrix44& out, T x, T y, T z)
    {
        out.setIdentity();
        out.e(0, 3) = x;
        out.e(1, 3) = y;
        out.e(2, 3) = z;
        return out;
    }

    //ƽ�ƣ����ݸ���ƽ��ʸ����
    Matrix44& translate(T x, T y, T z)
    {
        return preMultiply(getTranslation(x, y, z));
    }
    //ƽ�ƣ����ݸ���ƽ��ʸ����
    Matrix44& translate(const Vector3<T>& v)
    {
        return preMultiply(getTranslation(v));
    }

    //���ݱ���ϵ������һ�������任����
    static Matrix44& getScaling(Matrix44& out, const Vector3<T>& v)
    {
        return getScaling(out, v.x(), v.y(), v.z());
    }
    //���ݱ���ϵ������һ�������任����
    static Matrix44 getScaling(const Vector3<T>& v)
    {
        Matrix44 m;
        return getScaling(m, v.x(), v.y(), v.z());
    }
    //���ݱ���ϵ������һ�������任����
    static Matrix44 getScaling(T x, T y, T z)
    {
        Matrix44 m;
        return getScaling(m, x, y, z);
    }
    //���ݱ���ϵ������һ�������任����
    static Matrix44& getScaling(Matrix44& out, T x, T y, T z)
    {
        out.setIdentity();
        out.e(0, 0) = x;
        out.e(1, 1) = y;
        out.e(2, 2) = z;
        return out;
    }

    //���ݱ���ϵ�����б����任�����һ�������任����
    Matrix44& scale(T x, T y, T z)
    {
        return preMultiply(getScaling(x, y, z));
    }
    //���ݱ���ϵ�����б����任�����һ�������任����
    Matrix44& scale(const Vector3<T> v)
    {
        return preMultiply(getScaling(v.x(), v.y(), v.z()));
    }

    //����ָ�����е�Ԫ�أ���ֵ��
    const T& e(int i, int j) const { return eVec[j][i]; }
    //����ָ�����е�Ԫ�أ���ֵ��
    T& e(int i, int j) { return eVec[j][i]; }

    //abs (this[i][j] - m[i][j]) <= e
    bool equalAbsWithTol(const Matrix44& m, T e) const
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (!equalAbsWithTo((*this)[i][j], m[i][j], e))
                    return false;

        return true;
    }
    //abs (this[i] - v[i][j]) <= e * abs (this[i][j])
    bool equalRelWithTol(const Matrix44& m, T e) const
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (!equalRelWithTo((*this)[i][j], m[i][j], e))
                    return false;

        return true;
    }

    //���ؾ���ά��
    static unsigned int dimensions()
    {
        return 4;
    }

private:
    const Vector4<T>& operator[](unsigned int i) const { assert(i < 4); return eVec[i]; }
    Vector4<T>& operator[](unsigned int i) { assert(i < 4); return eVec[i]; }
protected:
    Vector4<T> eVec[4]; //������
};

//����������Ļ���p * q��
template<typename T>
inline Matrix44<T> operator*(const Matrix44<T>& p, const Matrix44<T>& q)
{
    Matrix44<T> t;
    Matrix44<T>::multiply(t, p, q);
    return t;
}

// ����ֵ�����ĺͣ�T + q����q�ĸ�Ԫ�ؼ���ָ��ֵ��
template<typename T>
inline Matrix44<T> operator+(T d, const Matrix44<T>& m)
{
    return m + d;
}

// ����ֵ�����Ļ���T * q����q�ĸ�Ԫ�س���ָ��ֵ��
template<typename T>
inline Matrix44<T> operator*(T d, const Matrix44<T>& m)
{
    return m * d;
}

// ���������ұ��ҳ�һ��Vector4�����������ؽ��������Vector4
template<typename T>
inline Vector4<T> operator*(const Matrix44<T>& m, const Vector4<T>& v)
{
    return Vector4<T>(
        v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + v.z() * m.e(0, 2) + v.w() * m.e(0, 3),
        v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + v.z() * m.e(1, 2) + v.w() * m.e(1, 3),
        v.x() * m.e(2, 0) + v.y() * m.e(2, 1) + v.z() * m.e(2, 2) + v.w() * m.e(2, 3),
        v.x() * m.e(3, 0) + v.y() * m.e(3, 1) + v.z() * m.e(3, 2) + v.w() * m.e(3, 3)
    );
}

// ���������ұ��ҳ�һ��Vector3���������ٶ�Vector4<T>��w=1�������ؽ��������Vector3
template<typename T>
inline Vector3<T> operator*(const Matrix44<T>& m, const Vector3<T>& v)
{
    return Vector3<T>(
        v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + v.z() * m.e(0, 2) + /*1**/m.e(0, 3),
        v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + v.z() * m.e(1, 2) + /*1**/m.e(1, 3),
        v.x() * m.e(2, 0) + v.y() * m.e(2, 1) + v.z() * m.e(2, 2) + /*1**/m.e(2, 3)
    );
}

// ���������ұ��ҳ�һ��Vector2���������ٶ�Vector4<T>��z = 0, w=1�������ؽ��������Vector2
template<typename T>
inline Vector2<T> operator*(const Matrix44<T>& m, const Vector2<T>& v)
{
    return Vector2<T>(
        v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + /*0*m.e(0,2) +*/ /*1**/m.e(0, 3),
        v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + /*0*m.e(1,2) +*/ /*1**/m.e(1, 3)
    );
}

// �������ұ߳�һ�����󣬷��ؽ������������ֵ��
template<typename T, typename S>
inline Vector4<T>& operator*=(Vector4<T>& v, const Matrix44<S>& m)
{
    T x = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0) + v.w() * m.e(3, 0));
    T y = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1) + v.w() * m.e(3, 1));
    T z = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2) + v.w() * m.e(3, 2));
    T w = T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) + v.z() * m.e(2, 3) + v.w() * m.e(3, 3));
    v.x() = x;
    v.y() = y;
    v.z() = z;
    v.w() = w;
    return v;
}

// �������ұ߳�һ�����󣬷��ؽ������������ֵ��
template<typename T, typename S>
inline Vector4<T> operator*(const Vector4<T>& v, const Matrix44<S>& m)
{
    return Vector4<T>(
        T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0) + v.w() * m.e(3, 0)),
        T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1) + v.w() * m.e(3, 1)),
        T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2) + v.w() * m.e(3, 2)),
        T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) + v.z() * m.e(2, 3) + v.w() * m.e(3, 3))
    );
}

// ������Vector3������Vector4��w = 1���ҳ�һ�����󣬷��ؽ��������Vector3����ֵ��
template<typename T, typename S>
inline Vector3<T>& operator*=(Vector3<T>& v, const Matrix44<S>& m)
{
    T x = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0) + /*1**/m.e(3, 0));
    T y = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1) + /*1**/m.e(3, 1));
    T z = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2) + /*1**/m.e(3, 2));
    T w = T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) + v.z() * m.e(2, 3) + /*1**/m.e(3, 3));

    v.x() = x;  //v.x() = x / w;
    v.y() = y;  //v.y() = y / w;
    v.z() = z;  //v.z() = z / w;

    return v;
}

// ������Vector3������Vector4��w = 1���ҳ�һ�����󣬷��ؽ��������Vector3����ֵ��
template<typename T, typename S>
inline Vector3<T> operator*(const Vector3<T>& v, const Matrix44<S>& m)
{
    T x = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0) + /*1**/m.e(3, 0));
    T y = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1) + /*1**/m.e(3, 1));
    T z = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2) + /*1**/m.e(3, 2));
    T w = T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) + v.z() * m.e(2, 3) + /*1**/m.e(3, 3));

    return Vector3<T>(x, y, z);
    //return Vector3<T>(x / w, y / w, z / w);
}

// ������Vector2������Vector4��z = 0��w = 1���ҳ�һ�����󣬷��ؽ��������Vector2����ֵ��
template<typename T>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix44<T>& m)
{
    return Vector2<T>(
        v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + /*0*m.e(2,0) +*/ /*1**/m.e(3, 0),
        v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + /*0*m.e(2,1) +*/ /*1**/m.e(3, 1)
    );
}

// ����һ���ƹ�ԭ���ֱ����ת�ľ���
template<typename T>
Matrix44<T>& Matrix44<T>::getRotation(Matrix44<T>& out, T degrees, T x, T y, T z)
{
    out.setIdentity();

    if (degrees == 0 || (x == 0 && y == 0 && z == 0))
        return out;

    degrees = T(degrees * dDEG_TO_RAD);

    T xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;

    s = (T)sin(degrees);
    c = (T)cos(degrees);

    if (x == 0)
    {
        if (y == 0)
        {
            if (z != 0)
            {
                out.e(0, 0) = (T)c;
                out.e(1, 1) = (T)c;
                if (z < 0)
                {
                    out.e(1, 0) = -(T)s;
                    out.e(0, 1) = (T)s;
                }
                else
                {
                    out.e(1, 0) = (T)s;
                    out.e(0, 1) = -(T)s;
                }
                return out;
            }
        }
        else if (z == 0)
        {
            out.e(0, 0) = (T)c;
            out.e(2, 2) = (T)c;
            if (y < 0)
            {
                out.e(2, 0) = (T)s;
                out.e(0, 2) = -(T)s;
            }
            else
            {
                out.e(2, 0) = -(T)s;
                out.e(0, 2) = (T)s;
            }
            return out;
        }
    }
    else if (y == 0)
    {
        if (z == 0)
        {
            out.e(1, 1) = (T)c;
            out.e(2, 2) = (T)c;
            if (x < 0)
            {
                out.e(2, 1) = -(T)s;
                out.e(1, 2) = (T)s;
            }
            else
            {
                out.e(2, 1) = (T)s;
                out.e(1, 2) = -(T)s;
            }
            return out;
        }
    }

    T dot = x * x + y * y + z * z;

    if (dot > (T)((T)1.0001) || dot < (T)0.99999)
    {
        T mag = (T)sqrt(dot);
        x /= mag;
        y /= mag;
        z /= mag;
    }

    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = ((T)1) - c;

    out.e(0, 0) = (T)((one_c * xx) + c); out.e(1, 0) = (T)((one_c * xy) + zs); out.e(2, 0) = (T)((one_c * zx) - ys);
    out.e(0, 1) = (T)((one_c * xy) - zs); out.e(1, 1) = (T)((one_c * yy) + c); out.e(2, 1) = (T)((one_c * yz) + xs);
    out.e(0, 2) = (T)((one_c * zx) + ys); out.e(1, 2) = (T)((one_c * yz) - xs); out.e(2, 2) = (T)((one_c * zz) + c);
    return out;
}

typedef Matrix44<int>  Mat4i;
typedef Matrix44<float> Mat4f;
typedef Matrix44<double> Mat4d;

typedef Mat4d Mat4;

#endif //_Matrix44_H_INCLUDED
