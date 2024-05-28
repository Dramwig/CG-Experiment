#pragma once
#include "CG3DRenderable.h" 

class CG3DClosedFoldedLine : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DClosedFoldedLine)
public:
	CG3DClosedFoldedLine();
	CG3DClosedFoldedLine(const CString& name);
	CG3DClosedFoldedLine(const CG3DClosedFoldedLine& other);
	virtual ~CG3DClosedFoldedLine();

	//序列化 
	virtual void Serialize(CArchive& ar);
	//绘制 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//计算包围盒（重写基类虚函数） 
	virtual void computeBoundingBox();

	void setPoints(const Vec3fArray& points) {
		mPoints = points;
	}
	void addPoint(const Vec3f& point) {
		mPoints.push_back(point);
	}
	const Vec3fArray& getPoints() const {
		return mPoints;
	}
	void clearPoints() {
		mPoints.clear();
	}

protected:
	Vec3fArray mPoints;
};
