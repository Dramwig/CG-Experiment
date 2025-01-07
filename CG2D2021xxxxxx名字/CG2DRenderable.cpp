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
//序列化
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
//绘制
void CG2DRenderable::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) //绘制对象，使用指定相机
{
	//派生类中实现
}
ABox2d& CG2DRenderable::BoundingABox() //AABB包围盒，可用于设置
{
	if (boundsDirty())
	{
		computeBoundingBox();
	}
	return mABox;
}

void CG2DRenderable::computeBoundingBox() //计算包围盒，需要在派生类中实现
{
	//派生类中实现，然后要调用如下函数
	setBoundsDirty(false);
}


bool CG2DRenderable::Picked(const Vec2d& p, double radius) //（二维）是否拾取到
{
	//此处只是简单根据包围盒是否相交进行判断，要更精确判定，则应在派生类中重写
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox))
		return true;
	return false;
}

bool CG2DRenderable::Picked(const ABox2d& box) //（二维）是否拾取到
{
	//此处只是简单根据包围盒是否相交进行判断，要更精确判定，则应在派生类中重写
	ABox2d abox = BoundingABox();
	ABox2d sbox(box);
	if (abox.intersects(sbox))
		return true;
	return false;
}

//此处仅以绘制对象包围盒的方式显示对象被选中，也可以自行确定选中显示方式
void CG2DRenderable::DrawSelectedBoundingBox(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera)
{
	if (renderable->status() == CG2DRenderable::sSelected) //对象处于选中状态
	{
		// 以包围盒绘制选中状态
		ABox2d abox = renderable->BoundingABox(); // 计算包围盒
		Vec2i v1 = pCamera->WorldtoViewPort(abox.minCorner());
		Vec2i v2 = pCamera->WorldtoViewPort(abox.maxCorner());
		CPen pen(PS_DASHDOT, 1, RGB(0, 0, 255));
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, (HBRUSH)GetStockObject(NULL_BRUSH));
			::Rectangle(hDC, v1.x(), v1.y(), v2.x(), v2.y()); // 绘制包围盒
			::SelectObject(hDC, hOldPen);
			::SelectObject(hDC, hOldBrush);
		}
	}
}

void CG2DRenderable::DrawSelectedBoundingBoxi(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera) //绘制选中包围盒
{
	if (status() == CG2DRenderable::sSelected) //对象处于选中状态
	{
		//以包围盒绘制选中状态
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

//二维图形对象的几何变换
void CG2DRenderable::Translate(double tx, double ty) //平移
{
	//使用矩阵运算示例：
	mMat.preMultiply(Mat3d::getTranslation(tx, ty));
	setBoundsDirty(true);
}
void CG2DRenderable::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getRotation(angle, Vector2<double>(cx,cy)));
	setBoundsDirty(true);
}
void CG2DRenderable::Scale(double sx, double sy) //缩放
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getScaling(sx,sy));
	setBoundsDirty(true);
}
void CG2DRenderable::Scale(double sx, double sy, double cx, double cy) //缩放
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getScaling(Vector2<double>(sx,sy), Vector2<double>(cx, cy)));
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorXAxis() //关于X轴对称（二维）
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getMirrorXAxis());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorYAxis() //关于Y轴对称（二维）
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getMirrorYAxis());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorYeqPosX() //关于y=x对称（二维）
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getMirrorYepX());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorYeNegPX() //关于y=-x对称（二维）
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getMirrorYenX());
	setBoundsDirty(true);
}
void CG2DRenderable::MirrorOrigin() //关于原点对称（二维）
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getMirrorOrigin());
	setBoundsDirty(true);
}
void CG2DRenderable::Mirror(const Vec2d& vs, const Vec2d& ve) //关于线段se对称（二维）
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

void CG2DRenderable::ShearXAxis(double shx) //沿X轴错切
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getShearXAxis(shx));
	setBoundsDirty(true);
}
void CG2DRenderable::ShearYAxis(double shy) //沿Y轴错切
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getShearYAxis(shy));
	setBoundsDirty(true);
}
void CG2DRenderable::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	//TODO：自行补充
	mMat.preMultiply(Mat3d::getShear(shx,shy));
	setBoundsDirty(true);
}
void CG2DRenderable::Transform(const Mat3d & mat) //几何变换（左乘给定矩阵）
{
	//TODO：自行补充
	mMat.preMultiply(mat);
	setBoundsDirty(true);
}

//获取在视口内的包围盒(仅用于绘制对象的包围盒），需要在派生类中重写
ABox2i CG2DRenderable::BoundingABoxi(CG2DCamera* pCamera)
{
	//派生类中实现
	return ABox2i();
}
