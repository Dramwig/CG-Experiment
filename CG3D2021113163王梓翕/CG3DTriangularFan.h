#pragma once
#include "CG3DClosedFoldedLine.h" 

class CG3DTriangularFan : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DTriangularFan)
public:
	CG3DTriangularFan();
	CG3DTriangularFan(const CG3DTriangularFan& other);
	virtual ~CG3DTriangularFan();

	//»æÖÆ 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);
};
