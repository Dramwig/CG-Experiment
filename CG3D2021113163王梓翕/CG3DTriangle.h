#pragma once
#include "CG3DClosedFoldedLine.h" 

class CG3DTriangle : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DTriangle)
public:
	CG3DTriangle();
	CG3DTriangle(const CG3DTriangle& other);
	virtual ~CG3DTriangle();

	//»æÖÆ 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);
	
};
