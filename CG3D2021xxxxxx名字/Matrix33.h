#ifndef _Matrix33_H_INCLUDED
#define _Matrix33_H_INCLUDED

#include "Vector3.h"
#include "Matrix22.h"

template <typename T> class Matrix33
{
public:
    typedef T BaseType;

    // 默认构造成单位矩阵
    Matrix33()
    {
        setIdentity();
    }
    ~Matrix33() = default;

    // 从其他类型的Matrix33矩阵构造
    template<typename S>
    explicit Matrix33(const Matrix33<S>& m)
    {
        e(0, 0) = (T)m.e(0, 0); e(1, 0) = (T)m.e(1, 0); e(2, 0) = (T)m.e(2, 0);
        e(0, 1) = (T)m.e(0, 1); e(1, 1) = (T)m.e(1, 1); e(2, 1) = (T)m.e(2, 1);
        e(0, 2) = (T)m.e(0, 2); e(1, 2) = (T)m.e(1, 2); e(2, 2) = (T)m.e(2, 2);
    }

    T scalex() {
        return sqrt(e(0, 0) * e(0, 0) + e(1, 0) * e(1, 0) + e(2, 0) * e(2, 0));
    }
    T scaley() {
        return sqrt(e(0, 1) * e(0, 1) + e(1, 1) * e(1, 1) + e(2, 1) * e(2, 1));
    }
    //T scalez() {
    //    return e(2, 2);
    //}

    // 拷贝构造
    Matrix33(const Matrix33& other)
    {
        operator=(other);
    }

    // 构造，主对角元素设为指定值，其他元素为0
    explicit Matrix33(T n)
    {
        setIdentity();
        e(0, 0) = e(1, 1) = e(2, 2) = n;
    }

    // 构造，按行给出所有元素
    explicit Matrix33(T e00, T e01, T e02, T e10, T e11, T e12, T e20, T e21, T e22)
    {
        e(0, 0) = e00; e(0, 1) = e01; e(0, 2) = e02;
        e(1, 0) = e10; e(1, 1) = e11; e(1, 2) = e12;
        e(2, 0) = e20; e(2, 1) = e21; e(2, 2) = e22;
    }

    // 构造，从3x3数组构造
    //     a[0][0] a[0][1] a[0][2]
    //     a[1][0] a[1][1] a[1][2]
    //     a[2][0] a[2][1] a[2][2]
    explicit Matrix33(T a[3][3])
    {
        e(0, 0) = a[0][0]; e(0, 1) = a[0][1]; e(0, 2) = a[0][2];
        e(1, 0) = a[1][0]; e(1, 1) = a[1][1]; e(1, 2) = a[1][2];
        e(2, 0) = a[2][0]; e(2, 1) = a[2][1]; e(2, 2) = a[2][2];
    }

    // 将所有元素设为指定值
    Matrix33& fill(T val)
    {
        e(0, 0) = e(1, 0) = e(2, 0) = e(0, 1) = e(1, 1) = e(2, 1) = e(0, 2) = e(1, 2) = e(2, 2) = val;
        return *this;
    }

    // 赋值到另一矩阵
    template<typename S>
    void getValue(Matrix33<S>& m) const
    {
        m.e(0, 0) = (S)e(0, 0); m.e(1, 0) = (S)e(1, 0); m.e(2, 0) = (S)e(2, 0);
        m.e(0, 1) = (S)e(0, 1); m.e(1, 1) = (S)e(1, 1); m.e(2, 1) = (S)e(2, 1);
        m.e(0, 2) = (S)e(0, 2); m.e(1, 2) = (S)e(1, 2); m.e(2, 2) = (S)e(2, 2);
    }

    // 从另一矩阵赋值
    template<typename S>
    Matrix33& setValue(const Matrix33<S>& m)
    {
        e(0, 0) = (T)m.e(0, 0); e(1, 0) = (T)m.e(1, 0); e(2, 0) = (T)m.e(2, 0);
        e(0, 1) = (T)m.e(0, 1); e(1, 1) = (T)m.e(1, 1); e(2, 1) = (T)m.e(2, 1);
        e(0, 2) = (T)m.e(0, 2); e(1, 2) = (T)m.e(1, 2); e(2, 2) = (T)m.e(2, 2);
        return *this;
    }

    //x轴方向的向量（左边2*1子阵）
    Vector2<T> getX() const
    {
        Vector2<T> v;
        v.x() = e(0, 0);
        v.y() = e(1, 0);
        return v;
    }
    //y轴方向的向量（中间2*1子阵）
    Vector2<T> getY() const
    {
        Vector2<T> v;
        v.x() = e(0, 1);
        v.y() = e(1, 1);
        return v;
    }
    //平移向量（右边2*1子阵）
    Vector2<T> getT() const
    {
        Vector2<T> v;
        v.x() = e(0, 2);
        v.y() = e(1, 2);
        return v;
    }

    //设置X向量（左边2*1子阵）
    Matrix33& setX(const Vector2<T>& v)
    {
        e(0, 0) = v.x();
        e(1, 0) = v.y();
        return *this;
    }
    //设置Y向量（中间2*1子阵）
    Matrix33& setY(const Vector2<T>& v)
    {
        e(0, 1) = v.x();
        e(1, 1) = v.y();
        return *this;
    }
    //设置平移向量（右边2*1子阵）
    Matrix33& setT(const Vector2<T>& v)
    {
        e(0, 2) = v.x();
        e(1, 2) = v.y();
        return *this;
    }

    //返回左上的2*2子阵
    Matrix22<T> get2x2() const
    {
        Matrix22<T> t;
        t.e(0, 0) = e(0, 0); t.e(1, 0) = e(1, 0);
        t.e(0, 1) = e(0, 1); t.e(1, 1) = e(1, 1);
        return t;
    }
    //设置左上2x2子阵
    void set2x2(const Matrix22<T>& m)
    {
        e(0, 0) = m.e(0, 0); e(1, 0) = m.e(1, 0);
        e(0, 1) = m.e(0, 1); e(1, 1) = m.e(1, 1);
    }

    // 与其他矩阵的差异
    T diff(const Matrix33& other) const
    {
        T err = 0;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (e(j, i) > other.e(j, i)) // avoid fabs/abs
                    err += e(j, i) - other.e(j, i);
                else
                    err += other.e(j, i) - e(j, i);
        return err;
    }

    // 判断与另一矩阵是否完全相等
    bool operator==(const Matrix33& m) const
    {
        return memcmp(m.eVec, eVec, sizeof(T) * 9) == 0;
    }
    // 判断与另一矩阵是否不等
    bool operator!=(const Matrix33& m) const
    {
        return !operator==(m);
    }

    // 重载赋值运算符
    Matrix33& operator=(const Matrix33& m)
    {
        memcpy(eVec, m.eVec, sizeof(T) * 9);
        return *this;
    }
    // 重载赋值运算符
    Matrix33& operator=(T val)
    {
        return fill(val);
    }

    //重载加运算符（加上另一个矩阵，返回和矩阵）
    Matrix33 operator+(const Matrix33& m) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) + m.e(j, i);
        return t;
    }
    //重载减运算符（减去另一个矩阵，返回差矩阵）
    Matrix33 operator-(const Matrix33& m) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) - m.e(j, i);
        return t;
    }
    // 右剩一矩阵，返回结果矩阵
    Matrix33 operator*(const Matrix33& m) const
    {
        Matrix33<T> t;
        Matrix33<T>::multiply(t, *this, m);
        return t;
    }
    //重载+运算符，各元素加上指定值，返回和矩阵
    Matrix33 operator+(T d) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) + d;
        return t;
    }
    //重载-运算符，各元素减去指定值，返回差矩阵
    Matrix33 operator-(T d) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) - d;
        return t;
    }
    //重载*运算符，各元素乘以指定值，返回积矩阵
    Matrix33 operator*(T d) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }
    //重载*运算符，各元素除以指定值，返回商矩阵
    Matrix33 operator/(T d) const
    {
        d = (T)1 / d;
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }

    //重载+=运算符
    Matrix33& operator+=(const Matrix33& m)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) += m.e(j, i);
        return *this;
    }
    //重载-=运算符
    Matrix33& operator-=(const Matrix33& m)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) -= m.e(j, i);
        return *this;
    }
    //重载*=运算符，右乘以一矩阵（*this * m）
    Matrix33& operator*=(const Matrix33& m)
    {
        return postMultiply(m);
    }
    //重载+=运算符，各元素加上指定值
    Matrix33& operator+=(T d)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) += d;
        return *this;
    }
    //重载-=运算符，各元素减去指定值
    Matrix33& operator-=(T d)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) -= d;
        return *this;
    }
    //重载*=运算符，各元素乘以指定值
    Matrix33& operator*=(T d)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) *= d;
        return *this;
    }
    //重载/=运算符，各元素除以指定值（不能为0，否则会0除异常）
    Matrix33& operator/=(T d)
    {
        d = (T)1 / d;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) *= d;
        return *this;
    }

    //重载-运算符（各元素取反）
    Matrix33 operator-() const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = -e(j, i);
        return t;
    }
    const Matrix33& negate()
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) = -e(j, i);
        return *this;
    }

    //返回左上首元素指针
    T* ptr()
    {
        return &e(0, 0);
    }
    //返回左上首元素指针
    const T* ptr() const
    {
        return &e(0, 0);
    }

    //转置
    Matrix33& transpose()
    {
        T tmp;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = i; j < 3; ++j)
            {
                tmp = e(j, i);
                e(j, i) = e(i, j);
                e(i, j) = tmp;
            }
        }
        return *this;
    }
    //返回转置矩阵
    Matrix33 getTransposed() const
    {
        Matrix33 m;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m.e(j, i) = e(i, j);
        return m;
    }
    //给指定的矩阵设为当前矩阵的转置矩阵，返回转置矩阵（左值）
    Matrix33& getTransposed(Matrix33& dest) const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                dest.e(j, i) = e(i, j);
        return dest;
    }

    //判断是否元素全为0
    bool isNull() const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (eVec[j][i] != 0)
                    return false;
        return true;
    }
    //设为空矩阵（元素全为0）
    Matrix33& setNull()
    {
        fill(0);
        return *this;
    }

    //将指定矩阵设为空矩阵（元素全为0）并返回传入矩阵
    static Matrix33& getNull(Matrix33& out)
    {
        out.fill(0);
        return out;
    }
    //返回一个空矩阵
    static Matrix33 getNull()
    {
        return Matrix33().fill(0);
    }

    //判断是否单位矩阵
    bool isIdentity() const
    {
        Matrix33 i;
        return memcmp(ptr(), i.ptr(), sizeof(T) * 9) == 0;
    }
    //设置为单位矩阵
    Matrix33& setIdentity()
    {
        static const T I3d[] =
        {
          (T)1, (T)0, (T)0,
          (T)0, (T)1, (T)0,
          (T)0, (T)0, (T)1,
        };
        memcpy(eVec, I3d, sizeof(T) * 9);
        return *this;
    }
    //返回一个单位矩阵
    static Matrix33 getIdentity()
    {
        return Matrix33();
    }
    //将传入矩阵设为单位阵并将其返回（左值）
    static Matrix33& getIdentity(Matrix33& out)
    {
        out.setIdentity();
        return out;
    }

    //传入矩阵带回当前矩阵的逆矩阵并返回行列式的值
    T getInverse(Matrix33& dest) const;
    //返回当前矩阵的逆矩阵，并返回行列式的值
    Matrix33 getInverse(T* determinant = nullptr) const
    {
        Matrix33 tmp;
        T det = getInverse(tmp);
        if (determinant)
            *determinant = det;
        return tmp;
    }

    //逆，并返回行列式的值
    Matrix33& invert(T* determinant = nullptr)
    {
        T det = getInverse(*this);
        if (determinant)
            *determinant = det;
        return *this;
    }
    //求行列式值
    T determinant() const
    {
        return e(0, 0) * (e(1, 1) * e(2, 2) - e(1, 2) * e(2, 1)) +
            e(0, 1) * (e(1, 2) * e(2, 0) - e(1, 0) * e(2, 2)) +
            e(0, 2) * (e(1, 0) * e(2, 1) - e(1, 1) * e(2, 0));
    }

    //矩阵相乘：out = p * q （结果矩阵 = 左矩阵 * 右矩阵），输出矩阵out
    static Matrix33& multiply(Matrix33& out, const Matrix33& p, const Matrix33& q)
    {
        //assert(out.ptr() != p.ptr() && out.ptr() != q.ptr());

        out.e(0, 0) = q.e(0, 0) * p.e(0, 0) + q.e(1, 0) * p.e(0, 1) + q.e(2, 0) * p.e(0, 2);
        out.e(0, 1) = q.e(0, 1) * p.e(0, 0) + q.e(1, 1) * p.e(0, 1) + q.e(2, 1) * p.e(0, 2);
        out.e(0, 2) = q.e(0, 2) * p.e(0, 0) + q.e(1, 2) * p.e(0, 1) + q.e(2, 2) * p.e(0, 2);

        out.e(1, 0) = q.e(0, 0) * p.e(1, 0) + q.e(1, 0) * p.e(1, 1) + q.e(2, 0) * p.e(1, 2);
        out.e(1, 1) = q.e(0, 1) * p.e(1, 0) + q.e(1, 1) * p.e(1, 1) + q.e(2, 1) * p.e(1, 2);
        out.e(1, 2) = q.e(0, 2) * p.e(1, 0) + q.e(1, 2) * p.e(1, 1) + q.e(2, 2) * p.e(1, 2);

        out.e(2, 0) = q.e(0, 0) * p.e(2, 0) + q.e(1, 0) * p.e(2, 1) + q.e(2, 0) * p.e(2, 2);
        out.e(2, 1) = q.e(0, 1) * p.e(2, 0) + q.e(1, 1) * p.e(2, 1) + q.e(2, 1) * p.e(2, 2);
        out.e(2, 2) = q.e(0, 2) * p.e(2, 0) + q.e(1, 2) * p.e(2, 1) + q.e(2, 2) * p.e(2, 2);

        return out;
    }
    //右乘一矩阵（当前矩阵 <= 当前矩阵 * m）
    Matrix33& postMultiply(const Matrix33& m)
    {
        Matrix33<T> t;
        return *this = multiply(t, *this, m);
    }
    //左乘一矩阵（当前矩阵 <= m * 当前矩阵）
    Matrix33& preMultiply(const Matrix33& m)
    {
        Matrix33<T> t;
        return *this = multiply(t, m, *this);
    }

    //给定绕坐标原点旋转角度（单位：度，逆时针为正）获取对应旋转矩阵（二维图形变换点坐标采用列向量形式，即左乘矩阵）
    static Matrix33 getRotation(T degrees);
    //给定旋转角度（单位：度，逆时针为正）和旋转中心，返回对应旋转矩阵（二维图形变换点坐标采用列向量形式，即左乘矩阵）
    static Matrix33 getRotation(T degrees, const Vector2<T>& v)
    {
        //1）平移到中心与原点重合getTranslation(-v)
        //2）旋转getRotation(degrees)
        //3）平移到中心回到原位置getTranslation(v)
        return getTranslation(v) * getRotation(degrees) * getTranslation(-v);
    }
    //绕原点旋转指定角度（单位：度，逆时针为正），this = R * this（点坐标采用列向量形式，采用左乘旋转矩阵方式）
    Matrix33& rotate(T degrees)
    {
        return preMultiply(getRotation(degrees));
    }

    //给定平移矢量，将传入的矩阵设为平移矩阵并返回传入矩阵（左值）（二维图形变换点坐标采用列向量形式）
    static Matrix33& getTranslation(Matrix33& out, const Vector2<T>& v)
    {
        return getTranslation(out, v.x(), v.y());
    }
    //给定平移矢量，返回一个平移矩阵（二维图形变换点坐标采用列向量形式）
    static Matrix33 getTranslation(const Vector2<T>& v)
    {
        return getTranslation(v.x(), v.y());
    }
    //给定平移矢量，返回一个平移矩阵（二维图形变换点坐标采用列向量形式）
    static Matrix33 getTranslation(T x, T y)
    {
        Matrix33 m;
        return getTranslation(m, x, y);
    }
    //给定平移矢量，将传入的矩阵设为平移矩阵（右上1*2子阵）并返回传入矩阵（左值）
    static Matrix33& getTranslation(Matrix33& out, T x, T y)
    {
        out.setIdentity();
        out.e(0, 2) = x;    //用于图形变换时，仅适用于列向量表示的（左乘矩阵）
        out.e(1, 2) = y;
        return out;
    }

    //平移（点坐标采用列向量形式，采用左乘旋转矩阵方式）
    Matrix33& translate(T x, T y)
    {
        return preMultiply(getTranslation(x, y));
    }
    //平移（点坐标采用列向量形式，采用左乘旋转矩阵方式）
    Matrix33& translate(const Vector2<T>& v)
    {
        return preMultiply(getTranslation(v));
    }

    //给定缩放系数，将传入的矩阵设为缩放矩阵并返回传入矩阵（左值）
    static Matrix33& getScaling(Matrix33& out, const Vector2<T>& v)
    {
        return getScaling(out, v.x(), v.y());
    }
    //给定缩放系数，返回缩放矩阵
    static Matrix33 getScaling(const Vector2<T>& v)
    {
        Matrix33 m;
        return getScaling(m, v.x(), v.y());
    }
    //给定缩放系数，返回缩放矩阵
    static Matrix33 getScaling(T x, T y)
    {
        Matrix33 m;
        return getScaling(m, x, y);
    }
    //给定缩放系数，将传入的矩阵设为缩放矩阵并返回传入矩阵（左值）
    static Matrix33& getScaling(Matrix33& out, T x, T y)
    {
        out.setIdentity();
        out.e(0, 0) = x;
        out.e(1, 1) = y;
        return out;
    }
    //给定缩放系数、缩放参考点（不变点，相当于规范化齐次坐标）返回缩放矩阵
    static Matrix33 getScaling(const Vector2<T>& c, const Vector2<T>& ref)
    {
        //1）平移到参考点与原点重合getTranslation(-ref)
        //2）缩放getScaling(c)
        //3）作1）的逆变换getTranslation(ref)
        //注意是用于列向量表达，左乘矩阵方式（第一步变换放在右边）
        return getTranslation(ref) * getScaling(c) * getTranslation(-ref);
    }
    //按给定缩放系数缩放（比例）（点坐标采用列向量形式，采用左乘旋转矩阵方式）
    Matrix33& scale(T x, T y)
    {
        return preMultiply(getScaling(x, y));
    }
    //按给定缩放系数缩放（比例）（点坐标采用列向量形式，采用左乘旋转矩阵方式）
    Matrix33& scale(const Vector2<T>& v)
    {
        return preMultiply(getScaling(v.x(), v.y()));
    }

    //返回关于x轴对称的矩阵（列向量方式）
    static Matrix33 getMirrorXAxis()
    {
        Matrix33 m;
        m.e(1, 1) = (T)-1;
        return m;
    }
    //返回关于y轴对称的矩阵（列向量方式）
    static Matrix33 getMirrorYAxis()
    {
        Matrix33 m;
        m.e(0, 0) = (T)-1;
        return m;
    }
    //返回关于原点对称的矩阵（列向量方式）
    static Matrix33 getMirrorOrigin()
    {
        Matrix33 m;
        m.e(0, 0) = (T)-1;
        m.e(1, 1) = (T)-1;
        return m;
    }
    //返回关于y=x线对称的矩阵（列向量方式）
    static Matrix33 getMirrorYepX()
    {
        Matrix33 m = getNull();
        m.e(0, 1) = (T)1;
        m.e(1, 0) = (T)1;
        m.e(2, 2) = (T)1;
        return m;
    }
    //返回关于y=-x轴对称的矩阵（列向量方式）
    static Matrix33 getMirrorYenX()
    {
        Matrix33 m = getNull();
        m.e(0, 1) = (T)-1;
        m.e(1, 0) = (T)-1;
        m.e(2, 2) = (T)1;
        return m;
    }

    //关于x轴对称（列向量方式）
    Matrix33& mirrorXAxis()
    {
        return preMultiply(getMirrorXAxis());
    }
    //关于y轴对称（列向量方式）
    Matrix33& mirrorYAxis()
    {
        return preMultiply(getMirrorYAxis());
    }
    //关于原点对称（列向量方式）
    Matrix33& mirrorOrigin()
    {
        return preMultiply(getMirrorOrigin());
    }
    //关于y = x线对称（列向量方式）
    Matrix33& mirrorYepX()
    {
        return preMultiply(getMirrorYepX());
    }
    //关于y=-x轴对称（列向量方式）
    Matrix33& mirrorYenX()
    {
        return preMultiply(getMirrorYenX());
    }

    //返回x轴方向错切矩阵（列向量方式）
    static Matrix33 getShearXAxis(T shx)
    {
        Matrix33 m;
        m.e(0, 1) = shx;
        return m;
    }
    //返回y轴方向错切矩阵（列向量方式）
    static Matrix33 getShearYAxis(T shy)
    {
        Matrix33 m;
        m.e(1, 0) = shy;
        return m;
    }
    //返回错切矩阵（指定x、y方向错切因子）
    static Matrix33 getShear(T shx, T shy)
    {
        Matrix33 m;
        m.e(0, 1) = shx;
        m.e(1, 0) = shy;
        return m;
    }
    //x轴方向错切
    Matrix33& shearXAxis(T shx)
    {
        return preMultiply(getShearXAxis(shx));
    }
    //y轴方向错切
    Matrix33& shearYAxis(T shy)
    {
        return preMultiply(getShearYAxis(shy));
    }
    //错切（指定x、y方向错切因子）
    Matrix33& shear(T shx, T shy)
    {
        return preMultiply(getShear(shx, shy));
    }

    //返回指定行列的元素（右值）
    const T& e(int i, int j) const { return eVec[j][i]; }
    //返回指定行列的元素（左值）
    T& e(int i, int j) { return eVec[j][i]; }

    //abs (this[i][j] - m[i][j]) <= e
    bool equalAbsWithTol(const Matrix33& m, T e) const
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!equalAbsWithTo((*this)[i][j], m[i][j], e))
                    return false;

        return true;
    }
    //abs (this[i] - v[i][j]) <= e * abs (this[i][j])
    bool equalRelWithTol(const Matrix33& m, T e) const
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!equalRelWithTo((*this)[i][j], m[i][j], e))
                    return false;

        return true;
    }

    //返回矩阵维数
    static unsigned int dimensions()
    {
        return 3;
    }
private:
    //获取指定列（右值）
    const Vector3<T>& operator[](unsigned int i) const { assert(i < 3); return eVec[i]; }
    //获取指定列（左值）
    Vector3<T>& operator[](unsigned int i) { assert(i < 3); return eVec[i]; }
protected:
    Vector3<T> eVec[3]; //列向量
};

//二元运算符重载
//返回两矩阵的积（p * q）
template<typename T>
inline Matrix33<T> operator*(const Matrix33<T>& p, const Matrix33<T>& q);

//返回值与矩阵的和（T + q），q的各元素加上指定值。
template<typename T>
inline Matrix33<T> operator+(T d, const Matrix33<T>& m);

//返回值与矩阵的积（T * q），q的各元素乘以指定值。
template<typename T>
inline Matrix33<T> operator*(T d, const Matrix33<T>& m);

// 给定矩阵右边右乘一个列向量，返回结果列向量
template<typename T>
inline Vector3<T> operator*(const Matrix33<T>& m, const Vector3<T>& v);

// 给定矩阵右边右乘一个列向量（假定z=0），返回结果列向量
template<typename T>
inline Vector2<T> operator*(const Matrix33<T>& m, const Vector2<T>& v);

// 行向量v右乘一个矩阵m，返回结果行向量（左值）
template<typename T, typename S>
inline Vector3<T>& operator*=(Vector3<T>& v, const Matrix33<S>& m);

// 行向量v右乘一个矩阵m，返回结果行向量（右值）
template<typename T, typename S>
inline Vector3<T> operator*(const Vector3<T>& v, const Matrix33<S>& m);

//! 行向量v（假定z=0）右乘一个矩阵m，返回结果行向量（右值）
template<typename T, typename S>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix33<S>& m);

//返回给定角度（度）的旋转矩阵（点坐标采用列向量形式）
template<typename T>
Matrix33<T> Matrix33<T>::getRotation(T degrees);

//带回矩阵的逆矩阵并返回行列式值
template<typename T>
T Matrix33<T>::getInverse(Matrix33<T>& dest) const;


//具体实现
//返回两矩阵的积（out = p * q）
template<typename T>
inline Matrix33<T> operator*(const Matrix33<T>& p, const Matrix33<T>& q)
{
    Matrix33<T> t;
    Matrix33<T>::multiply(t, p, q);
    return t;
}

//返回值与矩阵的和（out = T + q），q的各元素加上指定值。
template<typename T>
inline Matrix33<T> operator+(T d, const Matrix33<T>& m)
{
    return m + d;
}

//返回值与矩阵的积（out = T * q），q的各元素乘以指定值。
template<typename T>
inline Matrix33<T> operator*(T d, const Matrix33<T>& m)
{
    return m * d;
}

// 给定矩阵右边右乘一个列向量，返回结果列向量（out = m * v）
template<typename T>
inline Vector3<T> operator*(const Matrix33<T>& m, const Vector3<T>& v)
{
    Vector3<T> t;
    t.x() = v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + v.z() * m.e(0, 2);
    t.y() = v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + v.z() * m.e(1, 2);
    t.z() = v.x() * m.e(2, 0) + v.y() * m.e(2, 1) + v.z() * m.e(2, 2);
    return t;
}

// 给定矩阵右边右乘一个列向量（假定z=0），返回结果列向量（out = m * v）
template<typename T>
inline Vector2<T> operator*(const Matrix33<T>& m, const Vector2<T>& v)
{
    Vector2<T> t;
    t.x() = v.x() * m.e(0, 0) + v.y() * m.e(0, 1) /*+ 0*m.e(0,2)*/;
    t.y() = v.x() * m.e(1, 0) + v.y() * m.e(1, 1) /*+ 0*m.e(1,2)*/;
    return t;
}

// 行向量右乘一个矩阵，返回结果行向量（左值）(out = v * m)，纯粹矩阵运算，不要作为图形变换（图形变换假定的是用列向量）
template<typename T, typename S>
inline Vector3<T>& operator*=(Vector3<T>& v, const Matrix33<S>& m)
{
    T x = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0));
    T y = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1));
    T z = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2));
    v.x() = x;
    v.y() = y;
    v.z() = z;
    return v;
}

// 行向量右乘一个矩阵，返回结果行向量（右值）（out = v * m），纯粹矩阵运算，不要作为图形变换（图形变换假定的是用列向量）
template<typename T, typename S>
inline Vector3<T> operator*(const Vector3<T>& v, const Matrix33<S>& m)
{
    Vector3<T> t;
    t.x() = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0));
    t.y() = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1));
    t.z() = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2));
    return t;
}

// 行向量v（假定z=0）右乘一个矩阵m，返回结果行向量（右值）（out = v * m），纯粹矩阵运算，不要作为图形变换（图形变换假定的是用列向量）
template<typename T, typename S>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix33<S>& m)
{
    Vector2<T> t;
    t.x() = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) /*+ 0*m.e(2,0)*/);
    t.y() = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) /*+ 0*m.e(2,1)*/);
    return t;
}

//返回给定角度（单位：度，逆时针为正）的旋转矩阵（点坐标采用列向量形式）（图形旋转变换矩阵（绕坐标原点），图形坐标用列向量表示）
template<typename T>
Matrix33<T> Matrix33<T>::getRotation(T degrees)
{
    Matrix33<T> rot;
    degrees = degrees * (T)dDEG_TO_RAD;
    T s = (T)sin(degrees);
    T c = (T)cos(degrees);
    rot.e(0, 0) = (T)c;     //cos  -sin   0 //点坐标是列向量时的旋转矩阵形式
    rot.e(1, 1) = (T)c;     //sin   cos   0
    rot.e(1, 0) = (T)s;     //0     0     1
    rot.e(0, 1) = -(T)s;    //点坐标使用列向量形式
    return rot;     //返回的矩阵将用于左乘列向量点坐标(M * V)
}

//带回矩阵的逆矩阵并返回行列式值，纯粹矩阵运算，用于图形变换时要注意。
template<typename T>
T Matrix33<T>::getInverse(Matrix33<T>& dest) const
{
    if (&dest == this)
    {
        Matrix33<T> tmp;
        T det = getInverse(tmp);
        dest = tmp;
        return det;
    }
    else
    {
        const T& a11 = e(0, 0);
        const T& a21 = e(1, 0);
        const T& a31 = e(2, 0);
        const T& a12 = e(0, 1);
        const T& a22 = e(1, 1);
        const T& a32 = e(2, 1);
        const T& a13 = e(0, 2);
        const T& a23 = e(1, 2);
        const T& a33 = e(2, 2);

        T A = a22 * a33 - a32 * a23;
        T B = a23 * a31 - a33 * a21;
        T C = a21 * a32 - a31 * a22;

        T det = a11 * A + a12 * B + a13 * C;

        if (det == 0)
            dest.fill(0);
        else
            dest = Matrix33<T>(A, a13 * a32 - a33 * a12, a12 * a23 - a22 * a13,
                B, a11 * a33 - a31 * a13, a13 * a21 - a23 * a11,
                C, a12 * a31 - a32 * a11, a11 * a22 - a21 * a12) / det;
        return det;
    }
}
typedef Matrix33<int>   Mat3i;
typedef Matrix33<float>  Mat3f;
typedef Matrix33<double>  Mat3d;

typedef Mat3d Mat3;

#endif //_Matrix33_H_INCLUDED
