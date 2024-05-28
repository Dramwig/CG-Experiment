#pragma once
#include "CG3DRenderable.h" 
#include "CG3DClosedFoldedLine.h"

class CG3DFoldedLine : public CG3DClosedFoldedLine
{
	DECLARE_SERIAL(CG3DFoldedLine)
public:
	CG3DFoldedLine();
	CG3DFoldedLine(const CG3DFoldedLine& other);
	virtual ~CG3DFoldedLine();

	//»æÖÆ 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);


};
