#pragma once
#include "CG3DRenderable.h" 
#include "CG3DClosedFoldedLine.h"

class CG3DPolygon : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DPolygon)
public:
	CG3DPolygon();
	CG3DPolygon(const CG3DPolygon& other);
	virtual ~CG3DPolygon();
	//»æÖÆ 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);
};
