#ifndef _CG3DRenderable_H_INCLUDED 
#define _CG3DRenderable_H_INCLUDED 

#include "CGObject.h" 
#include "AABBox3.h" 
#include "Matrix44.h" 

class CG3DRenderContext;
class CG3DCamera;
class CG3DScene;

class CG3DRenderable : public CGObject
{
	DECLARE_SERIAL(CG3DRenderable)
public:
	CG3DRenderable();
	CG3DRenderable(const CString& name);
	virtual ~CG3DRenderable();

	//序列化 
	virtual void Serialize(CArchive& ar);

	//绘制对象（在派生类中重写） 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//三维图形对象包围盒 
	ABox3d& BoundingABox(); //AABB包围盒 
	bool boundsDirty() const { return mBoundsDirty; } //对象包围盒是否需要重新计算 
	void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; }
	virtual void computeBoundingBox(); //计算包围盒，需要在派生类中实现 

	//对象被添加到场景，建立与场景的关联 
	void addToScene(CG3DScene* s) { mScene = s; }
	CG3DScene* scene() const { return mScene; }

	//对象状态定义（也可用枚举类型） 
	static const int sNormal = 0; //正常状态 
	static const int sSelected = 1; //选中状态 
	int status() const { return mStatus; }
	void setStatus(int s) { mStatus = s; }

	//三维图形对象的几何变换 
	void Translate(double tx, double ty, double tz);   //平移（三维） 
	void Rotate(double angle, double cx, double cy, double cz); //旋转（三维） 
	void Scale(double sx, double sy, double sz);    //缩放（三维） 

	void setPenColor(COLORREF color) { mPenColor = color; }
	COLORREF penColor() const { return mPenColor; }
	void setPenWidth(int width) { mPenWidth = width; }
	int penWidth() const { return mPenWidth; }
	void setPenStyle(int style) { mPenStyle = style; }
	int penStyle() const { return mPenStyle; }
	void setPenFill(int style) { mPenFill = style; }
	int penFill() const { return mPenFill; }

protected:
	Mat4d mMat;  //到父级坐标系的变换（列向量形式），默认为单位矩阵（与父级坐标系重合） 
	ABox3d mABox; //轴对齐矩形包围盒，需要根据mBoundsDirty判断是否重新计算，默认为空 
	bool mBoundsDirty = true; //包围盒是否已改变 
	int mStatus = 0;   //状态，如选中状态等。0=正常 
	CG3DScene* mScene = nullptr;//对象实例所属的场景，当对象加入场景时自动进行设置。 
	COLORREF mPenColor = RGB(255, 0, 0); //轮廓颜色
	int mPenWidth = 1; //轮廓线宽
	int mPenStyle = PS_SOLID; //轮廓线型
	COLORREF mBrushColor = RGB(0, 0, 0); //画刷颜色
	int mPenFill = 0; //画刷样式
};

#endif //_CG3DRenderable_H_INCLUDED