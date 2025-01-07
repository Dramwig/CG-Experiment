#ifndef _AABBox3_H_INCLUDED
#define _AABBox3_H_INCLUDED

#include "Vector3.h"
#include "Matrix44.h"

/// <summary>
/// AABBox3 轴对齐包围盒（三维：长方体）
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T> class AABBox3
{
public:
    // 构造成null，空。不能包含任何内容
    AABBox3() { setNull(); }
    AABBox3(const AABBox3& other)
    {
        mMax = other.maxCorner();
        mMin = other.minCorner();
    };
    // 构造成能容纳给定中心和半径的球体的包围盒
    AABBox3(const Vector3<T>& center, T radius)
    {
        mMax = center + radius;
        mMin = center - radius;
    }
    // 构造成包含一个点的包围盒
    AABBox3(const Vector3<T>& point)
    {
        mMax = point;
        mMin = point;
    }
    // 构造成包含两个给定点的包围盒，并扩大
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

    //设置为无限大包围盒
    void setInfinite()
    {
        mMin = mMin.baseTypeLowest();
        mMax = mMax.baseTypeMax();
    }
    //是否无限大包围盒
    bool isInfinite() const
    {
        if (mMin.x() != mMin.baseTypeLowest() || mMax.x() != mMax.baseTypeMax() ||
            mMin.y() != mMin.baseTypeLowest() || mMax.y() != mMax.baseTypeMax() ||
            mMin.z() != mMin.baseTypeLowest() || mMax.z() != mMax.baseTypeMax())
            return false;
        return true;
    }

    //设置成null，空。不能包含任何内容
    void setNull() { mMin = 1; mMax = -1; }
    // 是否为null包围盒。
    bool isNull()  const { return mMin.x() > mMax.x() || mMin.y() > mMax.y() || mMin.z() > mMax.z(); }

    // 包围盒是否只包含一个点（min、max点相同）
    bool isPoint() const { return mMin == mMax; }

    // 各方向扩大包围盒
    void enlarge(T displace)
    {
        if (isNull())
            return;

        mMax = mMax + displace;
        mMin = mMin - displace;
    }

    // 是否与给定包围盒相交
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

    // 裁剪给定点到包围盒范围内
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

    // 给定点是否在包围盒内（可分别判断几个方向）
    bool isInside(const Vector3<T>& v, bool clipx, bool clipy, bool clipz) const
    {
        Vector3<T> t = v;
        return v == clip(t, clipx, clipy, clipz);
    }

    // 给定点是否在包围盒内
    bool isInside(const Vector3<T>& v) const
    {
        return v.x() >= minCorner().x() && v.x() <= maxCorner().x() &&
            v.y() >= minCorner().y() && v.y() <= maxCorner().y() &&
            v.z() >= minCorner().z() && v.z() <= maxCorner().z();
    }

    // 包围盒宽度 max.x - min.x
    T width() const
    {
        if (isNull())
            return 0;
        else
            return mMax.x() - mMin.x();
    }

    // 包围盒高度 max.y - min.y
    T height() const
    {
        if (isNull())
            return 0;
        else
            return mMax.y() - mMin.y();
    }

    // 包围盒深度 max.z - min.z
    T depth() const
    {
        if (isNull())
            return 0;
        else
            return mMax.z() - mMin.z();
    }

    // 包围盒大小 max - min
    Vector3<T> size() const
    {
        if (isNull())
            return Vector3<T>(0);
        return mMax - mMin;
    }

    // 是否相等
    bool operator==(const AABBox3& box) const
    {
        return mMin == box.mMin && mMax == box.mMax;
    }

    // 是否不等
    bool operator!=(const AABBox3& box) const
    {
        return !operator==(box);
    }

    // 返回包含此包围盒与给定包围盒的包围盒
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

    // 扩展此包围盒（如果必要）以包围给定包围盒
    AABBox3& operator+=(const AABBox3& other)
    {
        *this = *this + other;
        return *this;
    }
    // 扩展此包围盒（如果必要）以包围给定包围盒
    AABBox3& extend(const AABBox3& other)
    {
        *this = *this + other;
        return *this;
    }
    // 返回包含此包围盒与给定点的包围盒
    AABBox3 operator+(const Vector3<T>& p)
    {
        AABBox3 AABBox3 = *this;
        AABBox3 += p;
        return AABBox3;
    }
    // 扩展此包围盒（如果必要）以包围给定点
    AABBox3& extend(const Vector3<T>& p)
    {
        AABBox3 AABBox3 = *this;
        AABBox3 += p;
        return AABBox3;
    }
    // 扩展此包围盒（如果必要）以包围给定点
    const AABBox3& operator+=(const Vector3<T>& p)
    {
        addPoint(p);
        return *this;
    }

    // 返回包围盒的中心
    Vector3<T> center() const
    {
        Vector3<T> c = (minCorner() + maxCorner()) / 2.0f;
        return c;
    }

    // 返回最长方向的长度
    T longestSideLength() const
    {
        T side = width();
        if (height() > side)
            side = height();
        if (depth() > side)
            side = depth();
        return side;
    }

    // 扩展此包围盒以包围给定点（以点为中心一定半径的球体）
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

    // 扩展此包围盒以包围给定点）
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

    // 返回使用给定矩阵变换后的包围盒
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

    // 返回使用给定矩阵变换后的包围盒
    AABBox3 transformed(const Matrix44<T>& mat) const
    {
        AABBox3 box;
        transformed(box, mat);
        return box;
    }

    // 返回包围盒x y z坐标最小值
    const Vector3<T>& minCorner() const { return mMin; }
    Vector3<T>& minCorner() { return mMin; }

    // 返回包围盒x y z坐标最大值
    const Vector3<T>& maxCorner() const { return mMax; }
    Vector3<T>& maxCorner() { return mMax; }

    // 设置包围盒x y z坐标最小值
    void setMinCorner(T x, T y, T z) { mMin.x() = x; mMin.y() = y; mMin.z() = z; }

    // 设置包围盒x y z坐标最小值
    void setMinCorner(const Vector3<T>& v) { mMin = v; }

    // 设置包围盒x y z坐标最大值
    void setMaxCorner(T x, T y, T z) { mMax.x() = x; mMax.y() = y; mMax.z() = z; }

    // 设置包围盒x y z坐标最大值
    void setMaxCorner(const Vector3<T>& v) { mMax = v; }

    // 返回包围盒容积
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
    // 包围盒主轴
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
