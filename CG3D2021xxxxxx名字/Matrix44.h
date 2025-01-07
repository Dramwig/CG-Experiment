#ifndef _Matrix44_H_INCLUDED
#define _Matrix44_H_INCLUDED

#include "Vector4.h"
#include "Matrix33.h"
#include <cassert>

template <typename T> class Matrix44
{
public:
    typedef T BaseType;

    // 默认构造成单位矩阵
    Matrix44()
    {
        setIdentity();
    }

    ~Matrix44() = default;

    // 从其他类型的Matrix44矩阵构造
    template<typename S>
    explicit Matrix44(const Matrix44<S>& m)
    {
        e(0, 0) = (T)m.e(0, 0); e(1, 0) = (T)m.e(1, 0); e(2, 0) = (T)m.e(2, 0); e(3, 0) = (T)m.e(3, 0);
        e(0, 1) = (T)m.e(0, 1); e(1, 1) = (T)m.e(1, 1); e(2, 1) = (T)m.e(2, 1); e(3, 1) = (T)m.e(3, 1);
        e(0, 2) = (T)m.e(0, 2); e(1, 2) = (T)m.e(1, 2); e(2, 2) = (T)m.e(2, 2); e(3, 2) = (T)m.e(3, 2);
        e(0, 3) = (T)m.e(0, 3); e(1, 3) = (T)m.e(1, 3); e(2, 3) = (T)m.e(2, 3); e(3, 3) = (T)m.e(3, 3);
    }

    // 拷贝构造
    Matrix44(const Matrix44& other)
    {
        operator=(other);
    }

    // 主对角元素指定值构造
    explicit Matrix44(T n)
    {
        setIdentity();
        e(0, 0) = e(1, 1) = e(2, 2) = e(3, 3) = n;
    }

    // 使用16个元素的数组构造（按行）
    explicit Matrix44(T* val)
    {
        fillPtr(val);
    }

    // 使用16个元素构造（按行）
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

    // 各元素设为指定值
    Matrix44& fill(T val)
    {
        e(0, 0) = e(1, 0) = e(2, 0) = e(3, 0) =
            e(0, 1) = e(1, 1) = e(2, 1) = e(3, 1) =
            e(0, 2) = e(1, 2) = e(2, 2) = e(3, 2) =
            e(0, 3) = e(1, 3) = e(2, 3) = e(3, 3) = val;
        return *this;
    }

    // 使用16个元素的数组设定各元素值
    Matrix44& fillPtr(T* val)
    {
        memcpy(ptr(), val, sizeof(T) * 16);
        return *this;
    }

    // 返回X向量（第一列，1*3子阵）
    Vector3<T> getX() const
    {
        return Vector3<T>(eVec[0].x(), eVec[0].y(), eVec[0].z());
    }

    // 返回Y向量（第二列，1*3子阵）
    Vector3<T> getY() const
    {
        return Vector3<T>(eVec[1].x(), eVec[1].y(), eVec[1].z());
    }

    // 返回Z向量（第三列，1*3子阵）
    Vector3<T> getZ() const
    {
        return Vector3<T>(eVec[2].x(), eVec[2].y(), eVec[2].z());
    }

    // 返回平移向量（第四列，1*3子阵）
    Vector3<T> getT() const
    {
        return Vector3<T>(eVec[3].x(), eVec[3].y(), eVec[3].z());
    }

    // 设置X向量（第一列，1*3子阵）
    Matrix44& setX(const Vector3<T>& v)
    {
        eVec[0].x() = v.x();
        eVec[0].y() = v.y();
        eVec[0].z() = v.z();
        return *this;
    }

    // 设置Y向量（第二列，1*3子阵）
    Matrix44& setY(const Vector3<T>& v)
    {
        eVec[1].x() = v.x();
        eVec[1].y() = v.y();
        eVec[1].z() = v.z();
        return *this;
    }

    // 设置Z向量（第三列，1*3子阵）
    Matrix44& setZ(const Vector3<T>& v)
    {
        eVec[2].x() = v.x();
        eVec[2].y() = v.y();
        eVec[2].z() = v.z();
        return *this;
    }

    // 设置平移向量（第四列，1*3子阵）
    Matrix44& setT(const Vector3<T>& v)
    {
        eVec[3].x() = v.x();
        eVec[3].y() = v.y();
        eVec[3].z() = v.z();
        return *this;
    }

    // 左上3*3子阵不变，右下元素为1，最后一行、一列的其他元素设为0
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

    // 返回左上3*3子阵
    Matrix33<T> get3x3() const
    {
        Matrix33<T> t;
        t.e(0, 0) = e(0, 0); t.e(1, 0) = e(1, 0); t.e(2, 0) = e(2, 0);
        t.e(0, 1) = e(0, 1); t.e(1, 1) = e(1, 1); t.e(2, 1) = e(2, 1);
        t.e(0, 2) = e(0, 2); t.e(1, 2) = e(1, 2); t.e(2, 2) = e(2, 2);
        return t;
    }

    // 设置左上3*3子阵，其他元素不变
    void set3x3(const Matrix33<T>& m)
    {
        e(0, 0) = m.e(0, 0); e(1, 0) = m.e(1, 0); e(2, 0) = m.e(2, 0);
        e(0, 1) = m.e(0, 1); e(1, 1) = m.e(1, 1); e(2, 1) = m.e(2, 1);
        e(0, 2) = m.e(0, 2); e(1, 2) = m.e(1, 2); e(2, 2) = m.e(2, 2);
    }

    //判断是否相同
    bool operator==(const Matrix44& m) const
    {
        return memcmp(m.eVec, eVec, sizeof(T) * 4 * 4) == 0;
    }

    //判断是否不等
    bool operator!=(const Matrix44& m) const
    {
        return !operator==(m);
    }

    //赋值
    Matrix44& operator=(const Matrix44& m)
    {
        memcpy(eVec, m.eVec, sizeof(T) * 16);
        return *this;
    }

    //赋值
    Matrix44& operator=(T val)
    {
        return fill(val);
    }

    // 矩阵相加，返回和
    Matrix44 operator+(const Matrix44& m) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) + m.e(j, i);

        return t;
    }
    // 矩阵相减，返回差
    Matrix44 operator-(const Matrix44& m) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) - m.e(j, i);

        return t;
    }
    // 右剩矩阵，返回结果矩阵
    Matrix44 operator*(const Matrix44& m) const
    {
        Matrix44<T> t;
        Matrix44<T>::multiply(t, *this, m);
        return t;
    }
    //各元素加上指定值，返回结果矩阵
    Matrix44 operator+(T d) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) + d;
        return t;
    }
    //各元素减去指定值，返回结果矩阵
    Matrix44 operator-(T d) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) - d;
        return t;
    }
    //各元素乘以指定值，返回结果矩阵
    Matrix44 operator*(T d) const
    {
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }
    //各元素除以指定值，返回结果矩阵
    Matrix44 operator/(T d) const
    {
        d = (T)1 / d;
        Matrix44 t;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }

    // 加上一个矩阵
    Matrix44& operator+=(const Matrix44& m)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) += m.e(i, j);
        return *this;
    }
    // 减去一个矩阵
    Matrix44& operator-=(const Matrix44& m)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) -= m.e(i, j);
        return *this;
    }
    //右剩一个矩阵
    Matrix44& operator*=(const Matrix44& m)
    {
        return postMultiply(m);
    }
    //各元素加上指定值
    Matrix44& operator+=(T d)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) += d;
        return *this;
    }
    //各元素减去指定值
    Matrix44& operator-=(T d)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) -= d;
        return *this;
    }
    //各元素乘以指定值
    Matrix44& operator*=(T d)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) *= d;
        return *this;
    }
    //各元素除以指定值
    Matrix44& operator/=(T d)
    {
        d = (T)1 / d;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                e(j, i) *= d;
        return *this;
    }

    //返回各元素相反的矩阵
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

    //返回首元素指针（左值）
    T* ptr()
    {
        return &e(0, 0);
    }
    //返回首元素指针（右值）
    const T* ptr() const
    {
        return &e(0, 0);
    }

    //转置
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
    //返回对应的转置矩阵（右值）
    Matrix44 getTransposed() const
    {
        Matrix44 m;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m.e(j, i) = e(i, j);
        return m;
    }
    //返回对应的转置矩阵（左值）
    Matrix44& getTransposed(Matrix44& dest) const
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                dest.e(j, i) = e(i, j);
        return dest;
    }

    //是否为空（各元素都为0）
    bool isNull() const
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (e(i, j) != 0)
                    return false;
        return true;
    }
    //设置为空（各元素都为0）
    Matrix44& setNull()
    {
        fill(0);
        return *this;
    }
    //返回一个空矩阵
    static Matrix44& getNull(Matrix44& out)
    {
        out.fill(0);
        return out;
    }
    //返回一个空矩阵
    static Matrix44 getNull()
    {
        return Matrix44().fill(0);
    }

    //判断是否为单位阵
    bool isIdentity() const
    {
        Matrix44 i;
        return memcmp(ptr(), i.ptr(), sizeof(T) * 16) == 0;
    }
    //单位化
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
    //返回一个单位矩阵
    static Matrix44 getIdentity()
    {
        return Matrix44();
    }
    //返回一个单位矩阵
    static Matrix44& getIdentity(Matrix44& out)
    {
        out.setIdentity();
        return out;
    }

    ////给定矩阵求逆变换，返回行列式值
    //T getInverse(Matrix44& dest) const;
    //求逆矩阵，返回行列式值
    Matrix44 getInverse(T* determinant = nullptr) const
    {
        Matrix44 tmp;
        T det = getInverse(tmp);
        if (determinant)
            *determinant = det;
        return tmp;
    }
    //求逆，返回行列式值
    Matrix44& invert(T* determinant = nullptr)
    {
        T det = getInverse(*this);
        if (determinant)
            *determinant = det;
        return *this;
    }
    //求行列式值

    //矩阵相乘：out = p * q （结果矩阵 = 左矩阵 * 右矩阵）
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
    //右乘一矩阵（当前矩阵 <= 当前矩阵 * m）
    Matrix44& postMultiply(const Matrix44& m)
    {
        Matrix44<T> t;
        return *this = multiply(t, *this, m);
    }
    //左乘一矩阵（当前矩阵 <= m * 当前矩阵）
    Matrix44& preMultiply(const Matrix44& m)
    {
        Matrix44<T> t;
        return *this = multiply(t, m, *this);
    }

    //返回一个绕过原点直线（0，0，0）-（x, y, z）旋转指定角度（度）的旋转矩阵
    static Matrix44& getRotation(Matrix44& out, T degrees, T x, T y, T z);
    //返回一个绕过原点直线（0，0，0）-（x, y, z）旋转指定角度（度）的旋转矩阵
    static Matrix44 getRotation(T degrees, T x, T y, T z)
    {
        Matrix44 m;
        return getRotation(m, degrees, x, y, z);
    }
    //返回一个绕过原点直线（0，0，0）-（x, y, z）旋转指定角度（度）的旋转矩阵
    static Matrix44 getRotation(T degrees, const Vector3<T>& v)
    {
        return getRotation(degrees, v.x(), v.y(), v.z());
    }
    //返回一个先绕v2旋转后再绕v1旋转的矩阵
    static Matrix44 getRotation(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2)
    {
        return getRotation(degrees1, v1.x(), v1.y(), v1.z()) * getRotation(degrees2, v2.x(), v2.y(), v2.z());
    }
    //返回一个先绕v3旋转，然后绕v2旋转后再绕v1旋转的矩阵
    static Matrix44 getRotation(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2, T degrees3, const Vector3<T>& v3)
    {
        return getRotation(degrees1, v1.x(), v1.y(), v1.z()) * getRotation(degrees2, v2.x(), v2.y(), v2.z()) * getRotation(degrees3, v3.x(), v3.y(), v3.z());
    }

    //绕一过原点直线旋转（当前矩阵被左乘一个旋转矩阵）
    Matrix44& rotate(T degrees, const Vector3<T>& v)
    {
        return rotate(degrees, v.x(), v.y(), v.z());
    }
    //绕一过原点直线旋转（当前矩阵被左乘一个旋转矩阵）
    Matrix44& rotate(T degrees, T x, T y, T z)
    {
        return preMultiply(getRotation(degrees, x, y, z));
    }
    //先绕v2旋转后再绕v1旋转
    Matrix44& rotate(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2)
    {
        return preMultiply(getRotation(degrees1, v1, degrees2, v2));
    }
    //先绕v3旋转，然后绕v2旋转后再绕v1旋转
    Matrix44& rotate(T degrees1, const Vector3<T>& v1, T degrees2, const Vector3<T>& v2, T degrees3, const Vector3<T>& v3)
    {
        return preMultiply(getRotation(degrees1, v1, degrees2, v2, degrees3, v3));
    }

    //返回一个绕Z轴旋转、再绕Y轴旋转、再绕X轴旋转的矩阵
    static Matrix44 getRotationXYZ(T degX, T degY, T degZ)
    {
        return getRotation(degX, 1, 0, 0) * getRotation(degY, 0, 1, 0) * getRotation(degZ, 0, 0, 1);
    }
    //绕Z轴旋转、再绕Y轴旋转、再绕X轴旋转
    Matrix44& rotateXYZ(T degX, T degY, T degZ)
    {
        return preMultiply(getRotationXYZ(degX, degY, degZ));
    }

    //返回一个绕X轴旋转、再绕Y轴旋转、再绕Z轴旋转的矩阵
    static Matrix44 getRotationZYX(T degZ, T degY, T degX)
    {
        return getRotation(degZ, 0, 0, 1) * getRotation(degY, 0, 1, 0) * getRotation(degX, 1, 0, 0);
    }
    //绕X轴旋转、再绕Y轴旋转、再绕Z轴旋转
    Matrix44& rotateZYX(T degZ, T degY, T degX)
    {
        return preMultiply(getRotationZYX(degZ, degY, degX));
    }

    ////返回一个从from旋转到to（都是过原点的直线）的矩阵
    //static Matrix44& getRotation(Matrix44& out, const Vector3<T>& from, const Vector3<T>& to);
    //返回一个从from旋转到to（都是过原点的直线）的矩阵
    static Matrix44 getRotation(const Vector3<T>& from, const Vector3<T>& to)
    {
        Matrix44 m;
        return getRotation(m, from, to);
    }

    //从from旋转到to（都是过原点的直线）（当前矩阵左边乘以一个旋转矩阵）
    Matrix44& rotate(const Vector4<T>& from, const Vector4<T>& to)
    {
        return preMultiply(getRotation(from, to));
    }
    //从from旋转到to（都是过原点的直线）（当前矩阵左边乘以一个旋转矩阵）
    Matrix44& rotate(const Vector3<T>& from, const Vector3<T>& to)
    {
        return preMultiply(getRotation(from, to));
    }

    //根据平移矢量返回一个平移矩阵（列向量形式）
    static Matrix44& getTranslation(Matrix44& out, const Vector3<T>& v)
    {
        return getTranslation(out, v.x(), v.y(), v.z());
    }
    //根据平移矢量返回一个平移矩阵（列向量形式）
    static Matrix44 getTranslation(const Vector3<T>& v)
    {
        Matrix44 m;
        return getTranslation(m, v.x(), v.y(), v.z());
    }
    //根据平移矢量返回一个平移矩阵（列向量形式）
    static Matrix44 getTranslation(T x, T y, T z)
    {
        Matrix44 m;
        return getTranslation(m, x, y, z);
    }
    //根据平移矢量返回一个平移矩阵（列向量形式，第3列表示平移）
    static Matrix44& getTranslation(Matrix44& out, T x, T y, T z)
    {
        out.setIdentity();
        out.e(0, 3) = x;
        out.e(1, 3) = y;
        out.e(2, 3) = z;
        return out;
    }

    //平移（根据给定平移矢量）
    Matrix44& translate(T x, T y, T z)
    {
        return preMultiply(getTranslation(x, y, z));
    }
    //平移（根据给定平移矢量）
    Matrix44& translate(const Vector3<T>& v)
    {
        return preMultiply(getTranslation(v));
    }

    //根据比例系数返回一个比例变换矩阵
    static Matrix44& getScaling(Matrix44& out, const Vector3<T>& v)
    {
        return getScaling(out, v.x(), v.y(), v.z());
    }
    //根据比例系数返回一个比例变换矩阵
    static Matrix44 getScaling(const Vector3<T>& v)
    {
        Matrix44 m;
        return getScaling(m, v.x(), v.y(), v.z());
    }
    //根据比例系数返回一个比例变换矩阵
    static Matrix44 getScaling(T x, T y, T z)
    {
        Matrix44 m;
        return getScaling(m, x, y, z);
    }
    //根据比例系数返回一个比例变换矩阵
    static Matrix44& getScaling(Matrix44& out, T x, T y, T z)
    {
        out.setIdentity();
        out.e(0, 0) = x;
        out.e(1, 1) = y;
        out.e(2, 2) = z;
        return out;
    }

    //根据比例系数进行比例变换（左乘一个比例变换矩阵）
    Matrix44& scale(T x, T y, T z)
    {
        return preMultiply(getScaling(x, y, z));
    }
    //根据比例系数进行比例变换（左乘一个比例变换矩阵）
    Matrix44& scale(const Vector3<T> v)
    {
        return preMultiply(getScaling(v.x(), v.y(), v.z()));
    }

    //返回指定行列的元素（右值）
    const T& e(int i, int j) const { return eVec[j][i]; }
    //返回指定行列的元素（左值）
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

    //返回矩阵维数
    static unsigned int dimensions()
    {
        return 4;
    }

private:
    const Vector4<T>& operator[](unsigned int i) const { assert(i < 4); return eVec[i]; }
    Vector4<T>& operator[](unsigned int i) { assert(i < 4); return eVec[i]; }
protected:
    Vector4<T> eVec[4]; //列向量
};

//返回两矩阵的积（p * q）
template<typename T>
inline Matrix44<T> operator*(const Matrix44<T>& p, const Matrix44<T>& q)
{
    Matrix44<T> t;
    Matrix44<T>::multiply(t, p, q);
    return t;
}

// 返回值与矩阵的和（T + q），q的各元素加上指定值。
template<typename T>
inline Matrix44<T> operator+(T d, const Matrix44<T>& m)
{
    return m + d;
}

// 返回值与矩阵的积（T * q），q的各元素乘以指定值。
template<typename T>
inline Matrix44<T> operator*(T d, const Matrix44<T>& m)
{
    return m * d;
}

// 给定矩阵右边右乘一个Vector4列向量，返回结果列向量Vector4
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

// 给定矩阵右边右乘一个Vector3列向量（假定Vector4<T>的w=1），返回结果列向量Vector3
template<typename T>
inline Vector3<T> operator*(const Matrix44<T>& m, const Vector3<T>& v)
{
    return Vector3<T>(
        v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + v.z() * m.e(0, 2) + /*1**/m.e(0, 3),
        v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + v.z() * m.e(1, 2) + /*1**/m.e(1, 3),
        v.x() * m.e(2, 0) + v.y() * m.e(2, 1) + v.z() * m.e(2, 2) + /*1**/m.e(2, 3)
    );
}

// 给定矩阵右边右乘一个Vector2列向量（假定Vector4<T>的z = 0, w=1），返回结果列向量Vector2
template<typename T>
inline Vector2<T> operator*(const Matrix44<T>& m, const Vector2<T>& v)
{
    return Vector2<T>(
        v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + /*0*m.e(0,2) +*/ /*1**/m.e(0, 3),
        v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + /*0*m.e(1,2) +*/ /*1**/m.e(1, 3)
    );
}

// 行向量右边乘一个矩阵，返回结果行向量（左值）
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

// 行向量右边乘一个矩阵，返回结果行向量（右值）
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

// 行向量Vector3（用作Vector4，w = 1）右乘一个矩阵，返回结果行向量Vector3（左值）
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

// 行向量Vector3（用作Vector4，w = 1）右乘一个矩阵，返回结果行向量Vector3（右值）
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

// 行向量Vector2（用作Vector4，z = 0，w = 1）右乘一个矩阵，返回结果行向量Vector2（右值）
template<typename T>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix44<T>& m)
{
    return Vector2<T>(
        v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + /*0*m.e(2,0) +*/ /*1**/m.e(3, 0),
        v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + /*0*m.e(2,1) +*/ /*1**/m.e(3, 1)
    );
}

// 返回一个绕过原点的直线旋转的矩阵
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
