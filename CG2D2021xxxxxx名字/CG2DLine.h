#ifndef _CG2DLine_H_INCLUDED
#define _CG2DLine_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
class CG2DLine : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DLine)
public:
	CG2DLine();
	CG2DLine(const Vec2d& s, const Vec2d& e); //�������㹹��
	CG2DLine(const CG2DLine& other);
	virtual ~CG2DLine();
public:
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƣ�ʹ��CGDI2DRenderContext��CGDI2DCamera
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override; //���ƶ���ʹ��ָ�����
	//��Χ����ʰȡ���
	virtual void computeBoundingBox(); //�����Χ��
protected:
	Vec2d mStart, mEnd; //��㡢�յ�����
};
#endif //_CG2DLineSegment_H_INCLUDED
