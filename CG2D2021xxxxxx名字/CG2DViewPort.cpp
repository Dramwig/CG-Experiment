#include "pch.h"
#include "CG2DViewPort.h"
IMPLEMENT_SERIAL(CG2DViewPort, CGObject, 1)
CG2DViewPort::CG2DViewPort()
	:CGObject(CString("视口"))
{
}
CG2DViewPort::CG2DViewPort(int left, int bottom, int width, int height)
	:CGObject(CString("视口"))
	, mXLeft(left), mYBottom(bottom), mWidth(width), mHeight(height)
{
}
void CG2DViewPort::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mXLeft << mYBottom << mWidth << mHeight;
	}
	else
	{
		ar >> mXLeft >> mYBottom >> mWidth >> mHeight;
	}
}
bool CG2DViewPort::isPointInside(int x, int y) const
{
	if (x < 0 || y < 0 || x >= this->width() || y >= this->height())
		return false;
	else
		return true;
}
