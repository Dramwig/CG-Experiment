#ifndef _CG2DViewPort_H_INCLUDED
#define _CG2DViewPort_H_INCLUDED
#include "AABBox2.h"
#include "Vector3.h"
#include "CGObject.h"
// �ӿڣ���ͼ�ͻ�����������ӿ�����ϵ��һ������������һ�����������
class CG2DViewPort : public CGObject
{
	DECLARE_SERIAL(CG2DViewPort)
public:
	//Ĭ�Ϲ��죨left=0, bottom=0, width=0, height=0��
	CG2DViewPort();
	CG2DViewPort(int left, int bottom, int width, int height);
	virtual ~CG2DViewPort() = default;
	virtual void Serialize(CArchive& ar);
	bool isNull() { return mWidth == 0 || mHeight == 0; }
	//���ú�����Ҫȷ��minCorner�����½ǡ�maxCorner�����Ͻ�
	//���ã�left��bottom��width��height��
	void set(int xl, int yb, int w, int h) { mXLeft = xl; mYBottom = yb; mWidth = w; mHeight = h; }
	void setLeft(int left) { mXLeft = left; }
	void setBottom(int bottom) { mYBottom = bottom; }
	void setWidth(int width) { mWidth = width; }
	void setHeith(int height) { mHeight = height; }
	void setX(int x) { mXLeft = x; }
	int x() const { return mXLeft; }
	void setY(int y) { mYBottom = y; }
	int y() const { return mYBottom; }
	int left() const { return mXLeft; }
	int bottom() const { return mYBottom; }
	int width() const { return mWidth; }
	int height() const { return mHeight; }
	Vec2f center() const { return Vec2f(mXLeft + mWidth / 2.0f, mYBottom + mHeight / 2.0f); }
	Recti rect() const { return Recti(Vec2i(left(), bottom()), Vec2i(width(), height())); }
	void setClearColor(COLORREF c) { mClearColor = c; }
	COLORREF clearColor() const { return mClearColor; }
	//������豸����ϵ�ĵ��Ƿ����ӿ���
	bool isPointInside(int x, int y) const;
protected:
	int mXLeft = 0; //���½�X���꣬������豸����ϵ
	int mYBottom = 0; //���½�Y���꣬������豸����ϵ
	int mWidth = 1; //�ӿڿ�ȣ�X����
	int mHeight = 1; //�ӿڸ߶ȣ�Y����
	COLORREF mClearColor = RGB(255, 255, 255); //����ɫ
};
#endif //_CG2DViewPort_H_INCLUDED
