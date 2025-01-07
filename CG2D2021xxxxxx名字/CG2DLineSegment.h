#ifndef _CG2DLineSegment_H_INCLUDED
#define _CG2DLineSegment_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
class CG2DLineSegment : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DLineSegment)
public:
	CG2DLineSegment();
	CG2DLineSegment(const Vec2d& s, const Vec2d& e); //�������㹹��
	CG2DLineSegment(const Vec2d& s, const Vec2d& dir, double length); //������㡢���򡢳��ȹ���
	CG2DLineSegment(const CG2DLineSegment& other);
	virtual ~CG2DLineSegment();
public:
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƣ�ʹ��CGDI2DRenderContext��CGDI2DCamera
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override; //���ƶ���ʹ��ָ�����
	//��Χ����ʰȡ���
	virtual void computeBoundingBox(); //�����Χ��
protected:
	Vec2d mStart, mEnd; //��㡢�յ�����
public:
	virtual bool Picked(const Vec2d& p, double radius); //����ά���Ƿ�ʰȡ��
	virtual ABox2i BoundingABoxi(CG2DCamera* pCamera); //��ȡ���ӿ��ڵİ�Χ��(�����ڻ��ƶ���İ�Χ�У�
};
#endif //_CG2DLineSegment_H_INCLUDED
