#pragma once
#include "CG3DRenderable.h" 
#include "CG3DClosedFoldedLine.h"

class CG3DTriangularStrip : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DTriangularStrip)
public:
	CG3DTriangularStrip();
	CG3DTriangularStrip(const CG3DTriangularStrip& other);
	virtual ~CG3DTriangularStrip();
	//»æÖÆ 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

};
