#ifndef _AABBox2_H_INCLUDED
#define _AABBox2_H_INCLUDED
#include "Vector2.h"
/// <summary>
/// AABBox2 轴对齐包围盒（二维：矩形）
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T> class AABBox2
{
public:
	// 构造成null，空。不能包含任何内容
	AABBox2() { setNull(); };
	AABBox2(const AABBox2& other)
	{
		mMax = other.maxCorner();
		mMin = other.minCorner();
	};
	// 构造成能容纳给定中心和半径的圆的包围盒
	AABBox2(const Vector2<T>& center, T radius)
	{
		mMax = center + radius;
		mMin = center - radius;
	}
	// 构造成包含一个点的包围盒
	AABBox2(const Vector2<T>& point)
	{
		mMax = point;
		mMin = point;
	}
	// 构造成包含两个给定点的包围盒，并扩大
	AABBox2(const Vector2<T>& pt1, const Vector2<T>& pt2, T displace = 0)
	{
		mMax = mMin = pt1;
		if (mMax.x() < pt2.x()) mMax.x() = pt2.x();
		if (mMax.y() < pt2.y()) mMax.y() = pt2.y();
		if (mMin.x() > pt2.x()) mMin.x() = pt2.x();
		if (mMin.y() > pt2.y()) mMin.y() = pt2.y();
		mMax = mMax + displace;
		mMin = mMin - displace;
	}

	//设置为无限大包围盒
	void setInfinite()
	{
		mMin = std::numeric_limits<T>::lowest();
		mMax = std::numeric_limits<T>::max();
	}
	//是否无限大包围盒
	bool isInfinite() const
	{
		if (mMin.x() != std::numeric_limits<T>::lowest() || mMax.x() !=
			std::numeric_limits<T>::max() ||
			mMin.y() != std::numeric_limits<T>::lowest() || mMax.y() !=
			std::numeric_limits<T>::max())
			return false;
		return true;
	}

	//设置成null，空。不能包含任何内容
	void setNull() { mMin = 1; mMax = -1; }
	// 是否为null包围盒。
	bool isNull() const { return mMin.x() > mMax.x() || mMin.y() > mMax.y(); }

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
	// 给定点是否在包围盒内
	bool isInside(const Vector2<T>& v) const
	{
		return v.x() >= minCorner().x() && v.x() <= maxCorner().x() &&
			v.y() >= minCorner().y() && v.y() <= maxCorner().y();
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
	// 返回包围盒x y坐标最小值
	const Vector2<T>& minCorner() const { return mMin; }
	Vector2<T>& minCorner() { return mMin; }
	// 返回包围盒x y坐标最大值
	const Vector2<T>& maxCorner() const { return mMax; }
	Vector2<T>& maxCorner() { return mMax; }
	// 设置包围盒x y坐标最小值
	void setMinCorner(T x, T y) { mMin.x() = x; mMin.y() = y; }
	void setMinCorner(const Vector2<T>& v) { mMin = v; }
	// 设置包围盒x y坐标最大值
	void setMaxCorner(T x, T y) { mMax.x() = x; mMax.y() = y; }
	void setMaxCorner(const Vector2<T>& v) { mMax = v; }
	//加入给定点（及半径范围）扩展包围盒（radius > 0）
	AABBox2& addPoint(const Vector2<T>& v, T radius)
	{
		if (isNull())
		{
			mMax = v;
			mMin = v;
		}
		if (mMax.x() < v.x() + radius) mMax.x() = v.x() + radius;
		if (mMax.y() < v.y() + radius) mMax.y() = v.y() + radius;
		if (mMin.x() > v.x() - radius) mMin.x() = v.x() - radius;
		if (mMin.y() > v.y() - radius) mMin.y() = v.y() - radius;
		return *this;
	}
	//加入给定点扩展包围盒
	AABBox2& addPoint(const Vector2<T>& p)
	{
		if (isNull())
		{
			mMax = p;
			mMin = p;
			return *this;
		}
		if (mMax.x() < p.x()) mMax.x() = p.x();
		if (mMax.y() < p.y()) mMax.y() = p.y();
		if (mMin.x() > p.x()) mMin.x() = p.x();
		if (mMin.y() > p.y()) mMin.y() = p.y();
		return *this;
	}
	//扩展（如果必要）本包围盒以包含给定包围盒
	AABBox2& operator+=(const AABBox2& other)
	{
		*this = *this + other;
		return *this;
	}
	//扩展（如果必要）本包围盒以包含给定包围盒
	AABBox2& extend(const AABBox2& other)
	{
		*this = *this + other;
		return *this;
	}
	//扩展本包围盒（如果必要）以包含给定点
	AABBox2& operator+=(const Vector2<T>& p)
	{
		addPoint(p);
		return *this;
	}
	//返回容纳两个包围盒的新包围盒
	AABBox2 operator+(const AABBox2& box) const
	{
		if (isNull())
			return box;
		if (box.isNull())
			return *this;
		AABBox2 tmp = box;
		tmp.addPoint(mMin);
		tmp.addPoint(mMax);
		return tmp;
	}
	//返回包含本包围盒和给定点的新包围盒
	AABBox2 operator+(const Vector2<T>& p)
	{
		AABBox2 AABBox2 = *this;
		AABBox2 += p;
		return AABBox2;
	}
	//返回包含本包围盒和给定点的新包围盒
	AABBox2 extend(const Vector2<T>& p)
	{
		AABBox2 AABBox2 = *this;
		AABBox2 += p;
		return AABBox2;
	}
	//判断与另一个包围盒是否相交
	bool intersects(const AABBox2& bb) const
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
		return true;
	}
	//判断两包围盒是否相等
	bool operator==(const AABBox2& box) const
	{
		return mMin == box.mMin && mMax == box.mMax;
	}
	//判断两包围盒是否不等
	bool operator!=(const AABBox2& box) const
	{
		return !operator==(box);
	}
	//返回本包围盒的中心
	Vector2<T> center() const
	{
		Vector2<T> c = (minCorner() + maxCorner()) / 2.0f;
		return c;
	}
	T left() const { return mMin.x(); }
	T right() const { return mMax.x(); }
	T top() const { return mMax.y(); }
	T bottom() const { return mMin.y(); }
protected:
	Vector2<T> mMin;
	Vector2<T> mMax;
};
//预定义的便捷模板类
typedef AABBox2<int> ABox2i;
typedef AABBox2<float> ABox2f;
typedef AABBox2<double> ABox2d;
typedef ABox2d ABox2;
typedef AABBox2<int> Recti;
typedef AABBox2<float> Rectf;
typedef AABBox2<double> Rectd;
#endif //_AABBox2_H_INCLUDED
