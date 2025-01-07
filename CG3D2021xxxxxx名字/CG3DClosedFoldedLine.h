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

	//���л� 
	virtual void Serialize(CArchive& ar);
	//���� 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//�����Χ�У���д�����麯���� 
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
