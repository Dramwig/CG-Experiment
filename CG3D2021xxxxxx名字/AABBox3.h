#ifndef _AABBox3_H_INCLUDED
#define _AABBox3_H_INCLUDED

#include "Vector3.h"
#include "Matrix44.h"

/// <summary>
/// AABBox3 ������Χ�У���ά�������壩
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T> class AABBox3
{
public:
    // �����null���ա����ܰ����κ�����
    AABBox3() { setNull(); }
    AABBox3(const AABBox3& other)
    {
        mMax = other.maxCorner();
        mMin = other.minCorner();
    };
    // ����������ɸ������ĺͰ뾶������İ�Χ��
    AABBox3(const Vector3<T>& center, T radius)
    {
        mMax = center + radius;
        mMin = center - radius;
    }
    // ����ɰ���һ����İ�Χ��
    AABBox3(const Vector3<T>& point)
    {
        mMax = point;
        mMin = point;
    }
    // ����ɰ�������������İ�Χ�У�������
    AABBox3(const Vector3<T>& pt1, const Vector3<T>& pt2, T displace = 0)
    {
        mMax = mMin = pt1;
        if (mMax.x() < pt2.x()) mMax.x() = pt2.x();
        if (mMax.y() < pt2.y()) mMax.y() = pt2.y();
        if (mMax.z() < pt2.z()) mMax.z() = pt2.z();
        if (mMin.x() > pt2.x()) mMin.x() = pt2.x();
        if (mMin.y() > pt2.y()) mMin.y() = pt2.y();
        if (mMin.z() > pt2.z()) mMin.z() = pt2.z();

        mMax = mMax + displace;
        mMin = mMin - displace;
    }

    //����Ϊ���޴��Χ��
    void setInfinite()
    {
        mMin = mMin.baseTypeLowest();
        mMax = mMax.baseTypeMax();
    }
    //�Ƿ����޴��Χ��
    bool isInfinite() const
    {
        if (mMin.x() != mMin.baseTypeLowest() || mMax.x() != mMax.baseTypeMax() ||
            mMin.y() != mMin.baseTypeLowest() || mMax.y() != mMax.baseTypeMax() ||
            mMin.z() != mMin.baseTypeLowest() || mMax.z() != mMax.baseTypeMax())
            return false;
        return true;
    }

    //���ó�null���ա����ܰ����κ�����
    void setNull() { mMin = 1; mMax = -1; }
    // �Ƿ�Ϊnull��Χ�С�
    bool isNull()  const { return mMin.x() > mMax.x() || mMin.y() > mMax.y() || mMin.z() > mMax.z(); }

    // ��Χ���Ƿ�ֻ����һ���㣨min��max����ͬ��
    bool isPoint() const { return mMin == mMax; }

    // �����������Χ��
    void enlarge(T displace)
    {
        if (isNull())
            return;

        mMax = mMax + displace;
        mMin = mMin - displace;
    }

    // �Ƿ��������Χ���ཻ
    bool intersects(const AABBox3& bb) const
    {
        if (isNull() || bb.isNull())
            return false;

        if (mMax.x() < bb.mMin.x())
            return false;

        if (mMin.x() > bb.mMax.x())
            return false;

        if (mMax.y() < bb.mMin.y())
            return false;

        if (mMin.y() > bb.mMax.y())
            return false;

        if (mMax.z() < bb.mMin.z())
            return false;

        if (mMin.z() > bb.mMax.z())
            return false;

        return true;
    }

    // �ü������㵽��Χ�з�Χ��
    Vector3<T> clip(const Vector3<T>& v, bool clipx = true, bool clipy = true, bool clipz = true) const
    {
        if (isNull())
            return v;

        Vector3<T> tmp = v;

        if (clipx) {
            if (v.x() > mMax.x())
                tmp.x() = mMax.x();
            if (v.x() < mMin.x())
                tmp.x() = mMin.x();
        }

        if (clipy) {
            if (v.y() > mMax.y())
                tmp.y() = mMax.y();
            if (v.y() < mMin.y())
                tmp.y() = mMin.y();
        }

        if (clipz) {
            if (v.z() > mMax.z())
                tmp.z() = mMax.z();
            if (v.z() < mMin.z())
                tmp.z() = mMin.z();
        }
        return tmp;
    }

    // �������Ƿ��ڰ�Χ���ڣ��ɷֱ��жϼ�������
    bool isInside(const Vector3<T>& v, bool clipx, bool clipy, bool clipz) const
    {
        Vector3<T> t = v;
        return v == clip(t, clipx, clipy, clipz);
    }

    // �������Ƿ��ڰ�Χ����
    bool isInside(const Vector3<T>& v) const
    {
        return v.x() >= minCorner().x() && v.x() <= maxCorner().x() &&
            v.y() >= minCorner().y() && v.y() <= maxCorner().y() &&
            v.z() >= minCorner().z() && v.z() <= maxCorner().z();
    }

    // ��Χ�п�� max.x - min.x
    T width() const
    {
        if (isNull())
            return 0;
        else
            return mMax.x() - mMin.x();
    }

    // ��Χ�и߶� max.y - min.y
    T height() const
    {
        if (isNull())
            return 0;
        else
            return mMax.y() - mMin.y();
    }

    // ��Χ����� max.z - min.z
    T depth() const
    {
        if (isNull())
            return 0;
        else
            return mMax.z() - mMin.z();
    }

    // ��Χ�д�С max - min
    Vector3<T> size() const
    {
        if (isNull())
            return Vector3<T>(0);
        return mMax - mMin;
    }

    // �Ƿ����
    bool operator==(const AABBox3& box) const
    {
        return mMin == box.mMin && mMax == box.mMax;
    }

    // �Ƿ񲻵�
    bool operator!=(const AABBox3& box) const
    {
        return !operator==(box);
    }

    // ���ذ����˰�Χ���������Χ�еİ�Χ��
    AABBox3 operator+(const AABBox3& box) const
    {
        if (isNull())
            return box;
        if (box.isNull())
            return *this;
        AABBox3 tmp = box;
        tmp.addPoint(mMin);
        tmp.addPoint(mMax);
        return tmp;
    }

    // ��չ�˰�Χ�У������Ҫ���԰�Χ������Χ��
    AABBox3& operator+=(const AABBox3& other)
    {
        *this = *this + other;
        return *this;
    }
    // ��չ�˰�Χ�У������Ҫ���԰�Χ������Χ��
    AABBox3& extend(const AABBox3& other)
    {
        *this = *this + other;
        return *this;
    }
    // ���ذ����˰�Χ���������İ�Χ��
    AABBox3 operator+(const Vector3<T>& p)
    {
        AABBox3 AABBox3 = *this;
        AABBox3 += p;
        return AABBox3;
    }
    // ��չ�˰�Χ�У������Ҫ���԰�Χ������
    AABBox3& extend(const Vector3<T>& p)
    {
        AABBox3 AABBox3 = *this;
        AABBox3 += p;
        return AABBox3;
    }
    // ��չ�˰�Χ�У������Ҫ���԰�Χ������
    const AABBox3& operator+=(const Vector3<T>& p)
    {
        addPoint(p);
        return *this;
    }

    // ���ذ�Χ�е�����
    Vector3<T> center() const
    {
        Vector3<T> c = (minCorner() + maxCorner()) / 2.0f;
        return c;
    }

    // ���������ĳ���
    T longestSideLength() const
    {
        T side = width();
        if (height() > side)
            side = height();
        if (depth() > side)
            side = depth();
        return side;
    }

    // ��չ�˰�Χ���԰�Χ�����㣨�Ե�Ϊ����һ���뾶�����壩
    void addPoint(const Vector3<T>& v, T radius)
    {
        if (isNull())
        {
            mMax = v;
            mMin = v;
        }

        if (mMax.x() < v.x() + radius) mMax.x() = v.x() + radius;
        if (mMax.y() < v.y() + radius) mMax.y() = v.y() + radius;
        if (mMax.z() < v.z() + radius) mMax.z() = v.z() + radius;
        if (mMin.x() > v.x() - radius) mMin.x() = v.x() - radius;
        if (mMin.y() > v.y() - radius) mMin.y() = v.y() - radius;
        if (mMin.z() > v.z() - radius) mMin.z() = v.z() - radius;
    }

    // ��չ�˰�Χ���԰�Χ�����㣩
    void addPoint(const Vector3<T>& p)
    {
        if (isNull())
        {
            mMax = p;
            mMin = p;
            return;
        }

        if (mMax.x() < p.x()) mMax.x() = p.x();
        if (mMax.y() < p.y()) mMax.y() = p.y();
        if (mMax.z() < p.z()) mMax.z() = p.z();
        if (mMin.x() > p.x()) mMin.x() = p.x();
        if (mMin.y() > p.y()) mMin.y() = p.y();
        if (mMin.z() > p.z()) mMin.z() = p.z();
    }

    // ����ʹ�ø�������任��İ�Χ��
    void transformed(AABBox3& out, const Matrix44<T>& mat) const
    {
        out.setNull();
        if (!isNull())
        {
            out.addPoint(mat * Vector3<T>(minCorner().x(), minCorner().y(), minCorner().z()));
            out.addPoint(mat * Vector3<T>(minCorner().x(), maxCorner().y(), minCorner().z()));
            out.addPoint(mat * Vector3<T>(maxCorner().x(), maxCorner().y(), minCorner().z()));
            out.addPoint(mat * Vector3<T>(maxCorner().x(), minCorner().y(), minCorner().z()));
            out.addPoint(mat * Vector3<T>(minCorner().x(), minCorner().y(), maxCorner().z()));
            out.addPoint(mat * Vector3<T>(minCorner().x(), maxCorner().y(), maxCorner().z()));
            out.addPoint(mat * Vector3<T>(maxCorner().x(), maxCorner().y(), maxCorner().z()));
            out.addPoint(mat * Vector3<T>(maxCorner().x(), minCorner().y(), maxCorner().z()));
        }
    }

    // ����ʹ�ø�������任��İ�Χ��
    AABBox3 transformed(const Matrix44<T>& mat) const
    {
        AABBox3 box;
        transformed(box, mat);
        return box;
    }

    // ���ذ�Χ��x y z������Сֵ
    const Vector3<T>& minCorner() const { return mMin; }
    Vector3<T>& minCorner() { return mMin; }

    // ���ذ�Χ��x y z�������ֵ
    const Vector3<T>& maxCorner() const { return mMax; }
    Vector3<T>& maxCorner() { return mMax; }

    // ���ð�Χ��x y z������Сֵ
    void setMinCorner(T x, T y, T z) { mMin.x() = x; mMin.y() = y; mMin.z() = z; }

    // ���ð�Χ��x y z������Сֵ
    void setMinCorner(const Vector3<T>& v) { mMin = v; }

    // ���ð�Χ��x y z�������ֵ
    void setMaxCorner(T x, T y, T z) { mMax.x() = x; mMax.y() = y; mMax.z() = z; }

    // ���ð�Χ��x y z�������ֵ
    void setMaxCorner(const Vector3<T>& v) { mMax = v; }

    // ���ذ�Χ���ݻ�
    T volume() const { return width() * height() * depth(); }
    bool hasVolume() const
    {
        for (unsigned int i = 0; i < mMin.dimensions(); i++)
        {
            if (mMax[i] <= mMin[i])
                return false;
        }

        return true;
    }
    // ��Χ������
    unsigned int majorAxis() const
    {
        unsigned int major = 0;
        Vector3<T> s = size();

        for (unsigned int i = 1; i < mMin.dimensions(); i++)
        {
            if (s[i] > s[major])
                major = i;
        }

        return major;
    }
protected:
    Vector3<T> mMin;
    Vector3<T> mMax;
};

typedef AABBox3<int>        ABox3i;
typedef AABBox3<float>      ABox3f;
typedef AABBox3<double>     ABox3d;

typedef ABox3d ABox3;

#endif //_AABBox3_H_INCLUDED
