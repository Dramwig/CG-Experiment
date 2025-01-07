#ifndef _AABBox2_H_INCLUDED
#define _AABBox2_H_INCLUDED
#include "Vector2.h"
/// <summary>
/// AABBox2 ������Χ�У���ά�����Σ�
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T> class AABBox2
{
public:
	// �����null���ա����ܰ����κ�����
	AABBox2() { setNull(); };
	AABBox2(const AABBox2& other)
	{
		mMax = other.maxCorner();
		mMin = other.minCorner();
	};
	// ����������ɸ������ĺͰ뾶��Բ�İ�Χ��
	AABBox2(const Vector2<T>& center, T radius)
	{
		mMax = center + radius;
		mMin = center - radius;
	}
	// ����ɰ���һ����İ�Χ��
	AABBox2(const Vector2<T>& point)
	{
		mMax = point;
		mMin = point;
	}
	// ����ɰ�������������İ�Χ�У�������
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

	//����Ϊ���޴��Χ��
	void setInfinite()
	{
		mMin = std::numeric_limits<T>::lowest();
		mMax = std::numeric_limits<T>::max();
	}
	//�Ƿ����޴��Χ��
	bool isInfinite() const
	{
		if (mMin.x() != std::numeric_limits<T>::lowest() || mMax.x() !=
			std::numeric_limits<T>::max() ||
			mMin.y() != std::numeric_limits<T>::lowest() || mMax.y() !=
			std::numeric_limits<T>::max())
			return false;
		return true;
	}

	//���ó�null���ա����ܰ����κ�����
	void setNull() { mMin = 1; mMax = -1; }
	// �Ƿ�Ϊnull��Χ�С�
	bool isNull() const { return mMin.x() > mMax.x() || mMin.y() > mMax.y(); }

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
	// �������Ƿ��ڰ�Χ����
	bool isInside(const Vector2<T>& v) const
	{
		return v.x() >= minCorner().x() && v.x() <= maxCorner().x() &&
			v.y() >= minCorner().y() && v.y() <= maxCorner().y();
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
	// ���ذ�Χ��x y������Сֵ
	const Vector2<T>& minCorner() const { return mMin; }
	Vector2<T>& minCorner() { return mMin; }
	// ���ذ�Χ��x y�������ֵ
	const Vector2<T>& maxCorner() const { return mMax; }
	Vector2<T>& maxCorner() { return mMax; }
	// ���ð�Χ��x y������Сֵ
	void setMinCorner(T x, T y) { mMin.x() = x; mMin.y() = y; }
	void setMinCorner(const Vector2<T>& v) { mMin = v; }
	// ���ð�Χ��x y�������ֵ
	void setMaxCorner(T x, T y) { mMax.x() = x; mMax.y() = y; }
	void setMaxCorner(const Vector2<T>& v) { mMax = v; }
	//��������㣨���뾶��Χ����չ��Χ�У�radius > 0��
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
	//�����������չ��Χ��
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
	//��չ�������Ҫ������Χ���԰���������Χ��
	AABBox2& operator+=(const AABBox2& other)
	{
		*this = *this + other;
		return *this;
	}
	//��չ�������Ҫ������Χ���԰���������Χ��
	AABBox2& extend(const AABBox2& other)
	{
		*this = *this + other;
		return *this;
	}
	//��չ����Χ�У������Ҫ���԰���������
	AABBox2& operator+=(const Vector2<T>& p)
	{
		addPoint(p);
		return *this;
	}
	//��������������Χ�е��°�Χ��
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
	//���ذ�������Χ�к͸�������°�Χ��
	AABBox2 operator+(const Vector2<T>& p)
	{
		AABBox2 AABBox2 = *this;
		AABBox2 += p;
		return AABBox2;
	}
	//���ذ�������Χ�к͸�������°�Χ��
	AABBox2 extend(const Vector2<T>& p)
	{
		AABBox2 AABBox2 = *this;
		AABBox2 += p;
		return AABBox2;
	}
	//�ж�����һ����Χ���Ƿ��ཻ
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
	//�ж�����Χ���Ƿ����
	bool operator==(const AABBox2& box) const
	{
		return mMin == box.mMin && mMax == box.mMax;
	}
	//�ж�����Χ���Ƿ񲻵�
	bool operator!=(const AABBox2& box) const
	{
		return !operator==(box);
	}
	//���ر���Χ�е�����
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
//Ԥ����ı��ģ����
typedef AABBox2<int> ABox2i;
typedef AABBox2<float> ABox2f;
typedef AABBox2<double> ABox2d;
typedef ABox2d ABox2;
typedef AABBox2<int> Recti;
typedef AABBox2<float> Rectf;
typedef AABBox2<double> Rectd;
#endif //_AABBox2_H_INCLUDED
