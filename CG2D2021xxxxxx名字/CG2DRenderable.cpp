#include "pch.h"
#include "CG2DRenderable.h"
IMPLEMENT_SERIAL(CG2DRenderable, CGObject, 1)
CG2DRenderable::CG2DRenderable()
	:CGObject(CString("CG2DRenderable"))
{
}
CG2DRenderable::CG2DRenderable(const CString& name)
	: CGObject(CString(name))
{
}
//���л�
void CG2DRenderable::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mPenColor << mPenWidth << mPenStyle << mBrushColor << mBrushStyle << mHatchStyle;
	}
	else
	{
		ar >> mPenColor >> mPenWidth >> mPenStyle >> mBrushColor >> mBrushStyle >> mHatchStyle;
	}
}
//����
void CG2DRenderable::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) //���ƶ���ʹ��ָ�����
{
	//��������ʵ��
}
ABox2d& CG2DRenderable::BoundingABox() //AABB��Χ�У�����������
{
	if (boundsDirty())
	{
		computeBoundingBox();
	}
	return mABox;
}

void CG2DRenderable::computeBoundingBox() //�����Χ�У���Ҫ����������ʵ��
{
	//��������ʵ�֣�Ȼ��Ҫ�������º���
	setBoundsDirty(false);
}


bool CG2DRenderable::Picked(const Vec2d& p, double radius) //����ά���Ƿ�ʰȡ��
{
	//�˴�ֻ�Ǽ򵥸��ݰ�Χ���Ƿ��ཻ�����жϣ�Ҫ����ȷ�ж�����Ӧ������������д
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox))
		return true;
	return false;
}

bool CG2DRenderable::Picked(const ABox2d& box) //����ά���Ƿ�ʰȡ��
{
	//�˴�ֻ�Ǽ򵥸��ݰ�Χ���Ƿ��ཻ�����жϣ�Ҫ����ȷ�ж�����Ӧ������������д
	ABox2d abox = BoundingABox();
	ABox2d sbox(box);
	if (abox.intersects(sbox))
		return true;
	return false;
}

//�˴����Ի��ƶ����Χ�еķ�ʽ��ʾ����ѡ�У�Ҳ��������ȷ��ѡ����ʾ��ʽ
void CG2DRenderable::DrawSelectedBoundingBox(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera)
{
	if (renderable->status() == CG2DRenderable::sSelected) //������ѡ��״̬
	{
		// �԰�Χ�л���ѡ��״̬
		ABox2d abox = renderable->BoundingABox(); // �����Χ��
		Vec2i v1 = pCamera->WorldtoViewPort(abox.minCorner());
		Vec2i v2 = pCamera->WorldtoViewPort(abox.maxCorner());
		CPen pen(PS_DASHDOT, 1, RGB(0, 0, 255));
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, (HBRUSH)GetStockObject(NULL_BRUSH));
			::Rectangle(hDC, v1.x(), v1.y(), v2.x(), v2.y()); // ���ư�Χ��
			::SelectObject(hDC, hOldPen);
			::SelectObject(hDC, hOldBrush);
		}
	}
}

void CG2DRenderable::DrawSelectedBoundingBoxi(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera) //����ѡ�а�Χ��
{
	if (status() == CG2DRenderable::sSelected) //������ѡ��״̬
	{
		//�԰�Χ�л���ѡ��״̬
		ABox2i abox = BoundingABoxi(pCamera);
		Vec2i vb1 = abox.minCorner();
		Vec2i vb2 = abox.maxCorner();
		CPen pen(PS_DASHDOT, 1, RGB(0, 0, 255));
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, (HBRUSH)GetStockObject(NULL_BRUSH));
			::Rectangle(hDC, vb1.x(), vb1.y(), vb2.x(), vb2.y());
			::SelectObject(hDC, hOldPen);
			::SelectObject(hDC, hOldBrush);
		}
	}
}

//��άͼ�ζ���ļ��α任
void CG2DRenderable::Translate(double tx, double ty) //ƽ��
{
	//ʹ�þ�������ʾ����
	mMat.preMultiply(Mat3d::getTranslation(tx, ty));
	setBoundsDirty(true);
}
void CG2DRenderable::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ�����ȣ�
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getRotation(angle, Vector2<double>(cx,cy)));
	setBoundsDirty(true);
}
void CG2DRenderable::Scale(double sx, double sy) //����
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getScaling(sx,sy));
	setBoundsDirty(true);
}
void CG2DRenderable::Scale(double sx, double sy, double cx, double cy) //����
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getScaling(Vector2<double>(sx,sy), Vector2<double>(cx, cy)));
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorXAxis() //����X��Գƣ���ά��
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getMirrorXAxis());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorYAxis() //����Y��Գƣ���ά��
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getMirrorYAxis());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorYeqPosX() //����y=x�Գƣ���ά��
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getMirrorYepX());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorYeNegPX() //����y=-x�Գƣ���ά��
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getMirrorYenX());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorOrigin() //����ԭ��Գƣ���ά��
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getMirrorOrigin());
	setBoundsDirty(true);
}
void CG2DRenderable::Mirror(const Vec2d& vs, const Vec2d& ve) //�����߶�se�Գƣ���ά��
{
	#define M_PI       3.14159265358979323846
	// Calculate translation vector
	Vec2d translation = vs;

	// Calculate rotation angle to align the line with the x-axis
	Vec2d direction = ve - vs;
	double angle = atan2(direction.y(), direction.x()) * 180 / M_PI;

	// Step 1: Translate the line segment to pass through the origin
	Mat3d translateToOrigin = Mat3d::getTranslation(-translation.x(), -translation.y());

	// Step 2: Rotate to align with the x-axis
	Mat3d rotateToXAxis = Mat3d::getRotation(-angle);

	// Step 3: Mirror across the x-axis
	Mat3d mirrorXAxis = Mat3d::getMirrorXAxis();

	// Step 4: Rotate back to original orientation
	Mat3d rotateBack = Mat3d::getRotation(angle);

	// Step 5: Translate back to original position
	Mat3d translateBack = Mat3d::getTranslation(translation.x(), translation.y());

	// Combine all transformations
	Mat3d mirrorTransform = translateBack * rotateBack * mirrorXAxis * rotateToXAxis * translateToOrigin;

	// Apply the combined transformation
	mMat.preMultiply(mirrorTransform);
	setBoundsDirty(true);
}

void CG2DRenderable::ShearXAxis(double shx) //��X�����
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getShearXAxis(shx));
	setBoundsDirty(true);
}
void CG2DRenderable::ShearYAxis(double shy) //��Y�����
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getShearYAxis(shy));
	setBoundsDirty(true);
}
void CG2DRenderable::ShearXYAxis(double shx, double shy) //��X��Y�����
{
	//TODO�����в���
	mMat.preMultiply(Mat3d::getShear(shx,shy));
	setBoundsDirty(true);
}
void CG2DRenderable::Transform(const Mat3d & mat) //���α任����˸�������
{
	//TODO�����в���
	mMat.preMultiply(mat);
	setBoundsDirty(true);
}

//��ȡ���ӿ��ڵİ�Χ��(�����ڻ��ƶ���İ�Χ�У�����Ҫ������������д
ABox2i CG2DRenderable::BoundingABoxi(CG2DCamera* pCamera)
{
	//��������ʵ��
	return ABox2i();
}
