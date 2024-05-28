#pragma once
#include "CG3DClosedFoldedLine.h" 

class CG3DQuad : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DQuad)
public:
	CG3DQuad();
	CG3DQuad(const CG3DQuad& other);
	virtual ~CG3DQuad();

	//»æÖÆ 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);
};
