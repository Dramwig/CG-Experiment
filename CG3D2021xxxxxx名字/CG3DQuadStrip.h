#pragma once
#include "CG3DClosedFoldedLine.h" 

class CG3DQuadStrip : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DQuadStrip)
public:
	CG3DQuadStrip();
	CG3DQuadStrip(const CG3DQuadStrip& other);
	virtual ~CG3DQuadStrip();

	//���� 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);
};
