#pragma once
#include "CG3DClosedFoldedLine.h" 

class CG3DLineSegment : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DLineSegment)
public:
	CG3DLineSegment();
	CG3DLineSegment(const CG3DLineSegment& other);
	virtual ~CG3DLineSegment();
	//»æÖÆ 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

};
