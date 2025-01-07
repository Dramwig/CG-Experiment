#ifndef _Matrix33_H_INCLUDED
#define _Matrix33_H_INCLUDED

#include "Vector3.h"
#include "Matrix22.h"

template <typename T> class Matrix33
{
public:
    typedef T BaseType;

    // Ĭ�Ϲ���ɵ�λ����
    Matrix33()
    {
        setIdentity();
    }
    ~Matrix33() = default;

    // ���������͵�Matrix33������
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

    // ��������
    Matrix33(const Matrix33& other)
    {
        operator=(other);
    }

    // ���죬���Խ�Ԫ����Ϊָ��ֵ������Ԫ��Ϊ0
    explicit Matrix33(T n)
    {
        setIdentity();
        e(0, 0) = e(1, 1) = e(2, 2) = n;
    }

    // ���죬���и�������Ԫ��
    explicit Matrix33(T e00, T e01, T e02, T e10, T e11, T e12, T e20, T e21, T e22)
    {
        e(0, 0) = e00; e(0, 1) = e01; e(0, 2) = e02;
        e(1, 0) = e10; e(1, 1) = e11; e(1, 2) = e12;
        e(2, 0) = e20; e(2, 1) = e21; e(2, 2) = e22;
    }

    // ���죬��3x3���鹹��
    //     a[0][0] a[0][1] a[0][2]
    //     a[1][0] a[1][1] a[1][2]
    //     a[2][0] a[2][1] a[2][2]
    explicit Matrix33(T a[3][3])
    {
        e(0, 0) = a[0][0]; e(0, 1) = a[0][1]; e(0, 2) = a[0][2];
        e(1, 0) = a[1][0]; e(1, 1) = a[1][1]; e(1, 2) = a[1][2];
        e(2, 0) = a[2][0]; e(2, 1) = a[2][1]; e(2, 2) = a[2][2];
    }

    // ������Ԫ����Ϊָ��ֵ
    Matrix33& fill(T val)
    {
        e(0, 0) = e(1, 0) = e(2, 0) = e(0, 1) = e(1, 1) = e(2, 1) = e(0, 2) = e(1, 2) = e(2, 2) = val;
        return *this;
    }

    // ��ֵ����һ����
    template<typename S>
    void getValue(Matrix33<S>& m) const
    {
        m.e(0, 0) = (S)e(0, 0); m.e(1, 0) = (S)e(1, 0); m.e(2, 0) = (S)e(2, 0);
        m.e(0, 1) = (S)e(0, 1); m.e(1, 1) = (S)e(1, 1); m.e(2, 1) = (S)e(2, 1);
        m.e(0, 2) = (S)e(0, 2); m.e(1, 2) = (S)e(1, 2); m.e(2, 2) = (S)e(2, 2);
    }

    // ����һ����ֵ
    template<typename S>
    Matrix33& setValue(const Matrix33<S>& m)
    {
        e(0, 0) = (T)m.e(0, 0); e(1, 0) = (T)m.e(1, 0); e(2, 0) = (T)m.e(2, 0);
        e(0, 1) = (T)m.e(0, 1); e(1, 1) = (T)m.e(1, 1); e(2, 1) = (T)m.e(2, 1);
        e(0, 2) = (T)m.e(0, 2); e(1, 2) = (T)m.e(1, 2); e(2, 2) = (T)m.e(2, 2);
        return *this;
    }

    //x�᷽������������2*1����
    Vector2<T> getX() const
    {
        Vector2<T> v;
        v.x() = e(0, 0);
        v.y() = e(1, 0);
        return v;
    }
    //y�᷽����������м�2*1����
    Vector2<T> getY() const
    {
        Vector2<T> v;
        v.x() = e(0, 1);
        v.y() = e(1, 1);
        return v;
    }
    //ƽ���������ұ�2*1����
    Vector2<T> getT() const
    {
        Vector2<T> v;
        v.x() = e(0, 2);
        v.y() = e(1, 2);
        return v;
    }

    //����X���������2*1����
    Matrix33& setX(const Vector2<T>& v)
    {
        e(0, 0) = v.x();
        e(1, 0) = v.y();
        return *this;
    }
    //����Y�������м�2*1����
    Matrix33& setY(const Vector2<T>& v)
    {
        e(0, 1) = v.x();
        e(1, 1) = v.y();
        return *this;
    }
    //����ƽ���������ұ�2*1����
    Matrix33& setT(const Vector2<T>& v)
    {
        e(0, 2) = v.x();
        e(1, 2) = v.y();
        return *this;
    }

    //�������ϵ�2*2����
    Matrix22<T> get2x2() const
    {
        Matrix22<T> t;
        t.e(0, 0) = e(0, 0); t.e(1, 0) = e(1, 0);
        t.e(0, 1) = e(0, 1); t.e(1, 1) = e(1, 1);
        return t;
    }
    //��������2x2����
    void set2x2(const Matrix22<T>& m)
    {
        e(0, 0) = m.e(0, 0); e(1, 0) = m.e(1, 0);
        e(0, 1) = m.e(0, 1); e(1, 1) = m.e(1, 1);
    }

    // ����������Ĳ���
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

    // �ж�����һ�����Ƿ���ȫ���
    bool operator==(const Matrix33& m) const
    {
        return memcmp(m.eVec, eVec, sizeof(T) * 9) == 0;
    }
    // �ж�����һ�����Ƿ񲻵�
    bool operator!=(const Matrix33& m) const
    {
        return !operator==(m);
    }

    // ���ظ�ֵ�����
    Matrix33& operator=(const Matrix33& m)
    {
        memcpy(eVec, m.eVec, sizeof(T) * 9);
        return *this;
    }
    // ���ظ�ֵ�����
    Matrix33& operator=(T val)
    {
        return fill(val);
    }

    //���ؼ��������������һ�����󣬷��غ;���
    Matrix33 operator+(const Matrix33& m) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) + m.e(j, i);
        return t;
    }
    //���ؼ����������ȥ��һ�����󣬷��ز����
    Matrix33 operator-(const Matrix33& m) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) - m.e(j, i);
        return t;
    }
    // ��ʣһ���󣬷��ؽ������
    Matrix33 operator*(const Matrix33& m) const
    {
        Matrix33<T> t;
        Matrix33<T>::multiply(t, *this, m);
        return t;
    }
    //����+���������Ԫ�ؼ���ָ��ֵ�����غ;���
    Matrix33 operator+(T d) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) + d;
        return t;
    }
    //����-���������Ԫ�ؼ�ȥָ��ֵ�����ز����
    Matrix33 operator-(T d) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) - d;
        return t;
    }
    //����*���������Ԫ�س���ָ��ֵ�����ػ�����
    Matrix33 operator*(T d) const
    {
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }
    //����*���������Ԫ�س���ָ��ֵ�������̾���
    Matrix33 operator/(T d) const
    {
        d = (T)1 / d;
        Matrix33 t;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                t.e(j, i) = e(j, i) * d;
        return t;
    }

    //����+=�����
    Matrix33& operator+=(const Matrix33& m)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) += m.e(j, i);
        return *this;
    }
    //����-=�����
    Matrix33& operator-=(const Matrix33& m)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) -= m.e(j, i);
        return *this;
    }
    //����*=��������ҳ���һ����*this * m��
    Matrix33& operator*=(const Matrix33& m)
    {
        return postMultiply(m);
    }
    //����+=���������Ԫ�ؼ���ָ��ֵ
    Matrix33& operator+=(T d)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) += d;
        return *this;
    }
    //����-=���������Ԫ�ؼ�ȥָ��ֵ
    Matrix33& operator-=(T d)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) -= d;
        return *this;
    }
    //����*=���������Ԫ�س���ָ��ֵ
    Matrix33& operator*=(T d)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) *= d;
        return *this;
    }
    //����/=���������Ԫ�س���ָ��ֵ������Ϊ0�������0���쳣��
    Matrix33& operator/=(T d)
    {
        d = (T)1 / d;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                e(j, i) *= d;
        return *this;
    }

    //����-���������Ԫ��ȡ����
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

    //����������Ԫ��ָ��
    T* ptr()
    {
        return &e(0, 0);
    }
    //����������Ԫ��ָ��
    const T* ptr() const
    {
        return &e(0, 0);
    }

    //ת��
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
    //����ת�þ���
    Matrix33 getTransposed() const
    {
        Matrix33 m;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m.e(j, i) = e(i, j);
        return m;
    }
    //��ָ���ľ�����Ϊ��ǰ�����ת�þ��󣬷���ת�þ�����ֵ��
    Matrix33& getTransposed(Matrix33& dest) const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                dest.e(j, i) = e(i, j);
        return dest;
    }

    //�ж��Ƿ�Ԫ��ȫΪ0
    bool isNull() const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (eVec[j][i] != 0)
                    return false;
        return true;
    }
    //��Ϊ�վ���Ԫ��ȫΪ0��
    Matrix33& setNull()
    {
        fill(0);
        return *this;
    }

    //��ָ��������Ϊ�վ���Ԫ��ȫΪ0�������ش������
    static Matrix33& getNull(Matrix33& out)
    {
        out.fill(0);
        return out;
    }
    //����һ���վ���
    static Matrix33 getNull()
    {
        return Matrix33().fill(0);
    }

    //�ж��Ƿ�λ����
    bool isIdentity() const
    {
        Matrix33 i;
        return memcmp(ptr(), i.ptr(), sizeof(T) * 9) == 0;
    }
    //����Ϊ��λ����
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
    //����һ����λ����
    static Matrix33 getIdentity()
    {
        return Matrix33();
    }
    //�����������Ϊ��λ�󲢽��䷵�أ���ֵ��
    static Matrix33& getIdentity(Matrix33& out)
    {
        out.setIdentity();
        return out;
    }

    //���������ص�ǰ���������󲢷�������ʽ��ֵ
    T getInverse(Matrix33& dest) const;
    //���ص�ǰ���������󣬲���������ʽ��ֵ
    Matrix33 getInverse(T* determinant = nullptr) const
    {
        Matrix33 tmp;
        T det = getInverse(tmp);
        if (determinant)
            *determinant = det;
        return tmp;
    }

    //�棬����������ʽ��ֵ
    Matrix33& invert(T* determinant = nullptr)
    {
        T det = getInverse(*this);
        if (determinant)
            *determinant = det;
        return *this;
    }
    //������ʽֵ
    T determinant() const
    {
        return e(0, 0) * (e(1, 1) * e(2, 2) - e(1, 2) * e(2, 1)) +
            e(0, 1) * (e(1, 2) * e(2, 0) - e(1, 0) * e(2, 2)) +
            e(0, 2) * (e(1, 0) * e(2, 1) - e(1, 1) * e(2, 0));
    }

    //������ˣ�out = p * q ��������� = ����� * �Ҿ��󣩣��������out
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
    //�ҳ�һ���󣨵�ǰ���� <= ��ǰ���� * m��
    Matrix33& postMultiply(const Matrix33& m)
    {
        Matrix33<T> t;
        return *this = multiply(t, *this, m);
    }
    //���һ���󣨵�ǰ���� <= m * ��ǰ����
    Matrix33& preMultiply(const Matrix33& m)
    {
        Matrix33<T> t;
        return *this = multiply(t, m, *this);
    }

    //����������ԭ����ת�Ƕȣ���λ���ȣ���ʱ��Ϊ������ȡ��Ӧ��ת���󣨶�άͼ�α任�����������������ʽ������˾���
    static Matrix33 getRotation(T degrees);
    //������ת�Ƕȣ���λ���ȣ���ʱ��Ϊ��������ת���ģ����ض�Ӧ��ת���󣨶�άͼ�α任�����������������ʽ������˾���
    static Matrix33 getRotation(T degrees, const Vector2<T>& v)
    {
        //1��ƽ�Ƶ�������ԭ���غ�getTranslation(-v)
        //2����תgetRotation(degrees)
        //3��ƽ�Ƶ����Ļص�ԭλ��getTranslation(v)
        return getTranslation(v) * getRotation(degrees) * getTranslation(-v);
    }
    //��ԭ����תָ���Ƕȣ���λ���ȣ���ʱ��Ϊ������this = R * this�������������������ʽ�����������ת����ʽ��
    Matrix33& rotate(T degrees)
    {
        return preMultiply(getRotation(degrees));
    }

    //����ƽ��ʸ����������ľ�����Ϊƽ�ƾ��󲢷��ش��������ֵ������άͼ�α任�����������������ʽ��
    static Matrix33& getTranslation(Matrix33& out, const Vector2<T>& v)
    {
        return getTranslation(out, v.x(), v.y());
    }
    //����ƽ��ʸ��������һ��ƽ�ƾ��󣨶�άͼ�α任�����������������ʽ��
    static Matrix33 getTranslation(const Vector2<T>& v)
    {
        return getTranslation(v.x(), v.y());
    }
    //����ƽ��ʸ��������һ��ƽ�ƾ��󣨶�άͼ�α任�����������������ʽ��
    static Matrix33 getTranslation(T x, T y)
    {
        Matrix33 m;
        return getTranslation(m, x, y);
    }
    //����ƽ��ʸ����������ľ�����Ϊƽ�ƾ�������1*2���󣩲����ش��������ֵ��
    static Matrix33& getTranslation(Matrix33& out, T x, T y)
    {
        out.setIdentity();
        out.e(0, 2) = x;    //����ͼ�α任ʱ������������������ʾ�ģ���˾���
        out.e(1, 2) = y;
        return out;
    }

    //ƽ�ƣ������������������ʽ�����������ת����ʽ��
    Matrix33& translate(T x, T y)
    {
        return preMultiply(getTranslation(x, y));
    }
    //ƽ�ƣ������������������ʽ�����������ת����ʽ��
    Matrix33& translate(const Vector2<T>& v)
    {
        return preMultiply(getTranslation(v));
    }

    //��������ϵ����������ľ�����Ϊ���ž��󲢷��ش��������ֵ��
    static Matrix33& getScaling(Matrix33& out, const Vector2<T>& v)
    {
        return getScaling(out, v.x(), v.y());
    }
    //��������ϵ�����������ž���
    static Matrix33 getScaling(const Vector2<T>& v)
    {
        Matrix33 m;
        return getScaling(m, v.x(), v.y());
    }
    //��������ϵ�����������ž���
    static Matrix33 getScaling(T x, T y)
    {
        Matrix33 m;
        return getScaling(m, x, y);
    }
    //��������ϵ����������ľ�����Ϊ���ž��󲢷��ش��������ֵ��
    static Matrix33& getScaling(Matrix33& out, T x, T y)
    {
        out.setIdentity();
        out.e(0, 0) = x;
        out.e(1, 1) = y;
        return out;
    }
    //��������ϵ�������Ųο��㣨����㣬�൱�ڹ淶��������꣩�������ž���
    static Matrix33 getScaling(const Vector2<T>& c, const Vector2<T>& ref)
    {
        //1��ƽ�Ƶ��ο�����ԭ���غ�getTranslation(-ref)
        //2������getScaling(c)
        //3����1������任getTranslation(ref)
        //ע������������������˾���ʽ����һ���任�����ұߣ�
        return getTranslation(ref) * getScaling(c) * getTranslation(-ref);
    }
    //����������ϵ�����ţ��������������������������ʽ�����������ת����ʽ��
    Matrix33& scale(T x, T y)
    {
        return preMultiply(getScaling(x, y));
    }
    //����������ϵ�����ţ��������������������������ʽ�����������ת����ʽ��
    Matrix33& scale(const Vector2<T>& v)
    {
        return preMultiply(getScaling(v.x(), v.y()));
    }

    //���ع���x��ԳƵľ�����������ʽ��
    static Matrix33 getMirrorXAxis()
    {
        Matrix33 m;
        m.e(1, 1) = (T)-1;
        return m;
    }
    //���ع���y��ԳƵľ�����������ʽ��
    static Matrix33 getMirrorYAxis()
    {
        Matrix33 m;
        m.e(0, 0) = (T)-1;
        return m;
    }
    //���ع���ԭ��ԳƵľ�����������ʽ��
    static Matrix33 getMirrorOrigin()
    {
        Matrix33 m;
        m.e(0, 0) = (T)-1;
        m.e(1, 1) = (T)-1;
        return m;
    }
    //���ع���y=x�߶ԳƵľ�����������ʽ��
    static Matrix33 getMirrorYepX()
    {
        Matrix33 m = getNull();
        m.e(0, 1) = (T)1;
        m.e(1, 0) = (T)1;
        m.e(2, 2) = (T)1;
        return m;
    }
    //���ع���y=-x��ԳƵľ�����������ʽ��
    static Matrix33 getMirrorYenX()
    {
        Matrix33 m = getNull();
        m.e(0, 1) = (T)-1;
        m.e(1, 0) = (T)-1;
        m.e(2, 2) = (T)1;
        return m;
    }

    //����x��Գƣ���������ʽ��
    Matrix33& mirrorXAxis()
    {
        return preMultiply(getMirrorXAxis());
    }
    //����y��Գƣ���������ʽ��
    Matrix33& mirrorYAxis()
    {
        return preMultiply(getMirrorYAxis());
    }
    //����ԭ��Գƣ���������ʽ��
    Matrix33& mirrorOrigin()
    {
        return preMultiply(getMirrorOrigin());
    }
    //����y = x�߶Գƣ���������ʽ��
    Matrix33& mirrorYepX()
    {
        return preMultiply(getMirrorYepX());
    }
    //����y=-x��Գƣ���������ʽ��
    Matrix33& mirrorYenX()
    {
        return preMultiply(getMirrorYenX());
    }

    //����x�᷽����о�����������ʽ��
    static Matrix33 getShearXAxis(T shx)
    {
        Matrix33 m;
        m.e(0, 1) = shx;
        return m;
    }
    //����y�᷽����о�����������ʽ��
    static Matrix33 getShearYAxis(T shy)
    {
        Matrix33 m;
        m.e(1, 0) = shy;
        return m;
    }
    //���ش��о���ָ��x��y����������ӣ�
    static Matrix33 getShear(T shx, T shy)
    {
        Matrix33 m;
        m.e(0, 1) = shx;
        m.e(1, 0) = shy;
        return m;
    }
    //x�᷽�����
    Matrix33& shearXAxis(T shx)
    {
        return preMultiply(getShearXAxis(shx));
    }
    //y�᷽�����
    Matrix33& shearYAxis(T shy)
    {
        return preMultiply(getShearYAxis(shy));
    }
    //���У�ָ��x��y����������ӣ�
    Matrix33& shear(T shx, T shy)
    {
        return preMultiply(getShear(shx, shy));
    }

    //����ָ�����е�Ԫ�أ���ֵ��
    const T& e(int i, int j) const { return eVec[j][i]; }
    //����ָ�����е�Ԫ�أ���ֵ��
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

    //���ؾ���ά��
    static unsigned int dimensions()
    {
        return 3;
    }
private:
    //��ȡָ���У���ֵ��
    const Vector3<T>& operator[](unsigned int i) const { assert(i < 3); return eVec[i]; }
    //��ȡָ���У���ֵ��
    Vector3<T>& operator[](unsigned int i) { assert(i < 3); return eVec[i]; }
protected:
    Vector3<T> eVec[3]; //������
};

//��Ԫ���������
//����������Ļ���p * q��
template<typename T>
inline Matrix33<T> operator*(const Matrix33<T>& p, const Matrix33<T>& q);

//����ֵ�����ĺͣ�T + q����q�ĸ�Ԫ�ؼ���ָ��ֵ��
template<typename T>
inline Matrix33<T> operator+(T d, const Matrix33<T>& m);

//����ֵ�����Ļ���T * q����q�ĸ�Ԫ�س���ָ��ֵ��
template<typename T>
inline Matrix33<T> operator*(T d, const Matrix33<T>& m);

// ���������ұ��ҳ�һ�������������ؽ��������
template<typename T>
inline Vector3<T> operator*(const Matrix33<T>& m, const Vector3<T>& v);

// ���������ұ��ҳ�һ�����������ٶ�z=0�������ؽ��������
template<typename T>
inline Vector2<T> operator*(const Matrix33<T>& m, const Vector2<T>& v);

// ������v�ҳ�һ������m�����ؽ������������ֵ��
template<typename T, typename S>
inline Vector3<T>& operator*=(Vector3<T>& v, const Matrix33<S>& m);

// ������v�ҳ�һ������m�����ؽ������������ֵ��
template<typename T, typename S>
inline Vector3<T> operator*(const Vector3<T>& v, const Matrix33<S>& m);

//! ������v���ٶ�z=0���ҳ�һ������m�����ؽ������������ֵ��
template<typename T, typename S>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix33<S>& m);

//���ظ����Ƕȣ��ȣ�����ת���󣨵����������������ʽ��
template<typename T>
Matrix33<T> Matrix33<T>::getRotation(T degrees);

//���ؾ��������󲢷�������ʽֵ
template<typename T>
T Matrix33<T>::getInverse(Matrix33<T>& dest) const;


//����ʵ��
//����������Ļ���out = p * q��
template<typename T>
inline Matrix33<T> operator*(const Matrix33<T>& p, const Matrix33<T>& q)
{
    Matrix33<T> t;
    Matrix33<T>::multiply(t, p, q);
    return t;
}

//����ֵ�����ĺͣ�out = T + q����q�ĸ�Ԫ�ؼ���ָ��ֵ��
template<typename T>
inline Matrix33<T> operator+(T d, const Matrix33<T>& m)
{
    return m + d;
}

//����ֵ�����Ļ���out = T * q����q�ĸ�Ԫ�س���ָ��ֵ��
template<typename T>
inline Matrix33<T> operator*(T d, const Matrix33<T>& m)
{
    return m * d;
}

// ���������ұ��ҳ�һ�������������ؽ����������out = m * v��
template<typename T>
inline Vector3<T> operator*(const Matrix33<T>& m, const Vector3<T>& v)
{
    Vector3<T> t;
    t.x() = v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + v.z() * m.e(0, 2);
    t.y() = v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + v.z() * m.e(1, 2);
    t.z() = v.x() * m.e(2, 0) + v.y() * m.e(2, 1) + v.z() * m.e(2, 2);
    return t;
}

// ���������ұ��ҳ�һ�����������ٶ�z=0�������ؽ����������out = m * v��
template<typename T>
inline Vector2<T> operator*(const Matrix33<T>& m, const Vector2<T>& v)
{
    Vector2<T> t;
    t.x() = v.x() * m.e(0, 0) + v.y() * m.e(0, 1) /*+ 0*m.e(0,2)*/;
    t.y() = v.x() * m.e(1, 0) + v.y() * m.e(1, 1) /*+ 0*m.e(1,2)*/;
    return t;
}

// �������ҳ�һ�����󣬷��ؽ������������ֵ��(out = v * m)������������㣬��Ҫ��Ϊͼ�α任��ͼ�α任�ٶ���������������
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

// �������ҳ�һ�����󣬷��ؽ������������ֵ����out = v * m��������������㣬��Ҫ��Ϊͼ�α任��ͼ�α任�ٶ���������������
template<typename T, typename S>
inline Vector3<T> operator*(const Vector3<T>& v, const Matrix33<S>& m)
{
    Vector3<T> t;
    t.x() = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0));
    t.y() = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1));
    t.z() = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2));
    return t;
}

// ������v���ٶ�z=0���ҳ�һ������m�����ؽ������������ֵ����out = v * m��������������㣬��Ҫ��Ϊͼ�α任��ͼ�α任�ٶ���������������
template<typename T, typename S>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix33<S>& m)
{
    Vector2<T> t;
    t.x() = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) /*+ 0*m.e(2,0)*/);
    t.y() = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) /*+ 0*m.e(2,1)*/);
    return t;
}

//���ظ����Ƕȣ���λ���ȣ���ʱ��Ϊ��������ת���󣨵����������������ʽ����ͼ����ת�任����������ԭ�㣩��ͼ����������������ʾ��
template<typename T>
Matrix33<T> Matrix33<T>::getRotation(T degrees)
{
    Matrix33<T> rot;
    degrees = degrees * (T)dDEG_TO_RAD;
    T s = (T)sin(degrees);
    T c = (T)cos(degrees);
    rot.e(0, 0) = (T)c;     //cos  -sin   0 //��������������ʱ����ת������ʽ
    rot.e(1, 1) = (T)c;     //sin   cos   0
    rot.e(1, 0) = (T)s;     //0     0     1
    rot.e(0, 1) = -(T)s;    //������ʹ����������ʽ
    return rot;     //���صľ����������������������(M * V)
}

//���ؾ��������󲢷�������ʽֵ������������㣬����ͼ�α任ʱҪע�⡣
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
