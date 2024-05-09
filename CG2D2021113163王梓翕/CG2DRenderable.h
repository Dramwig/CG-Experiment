#ifndef _CG2DRenderable_H_INCLUDED
#define _CG2DRenderable_H_INCLUDED
#include "CGObject.h"
#include "AABBox2.h"
#include "Matrix33.h"
#include "CG2DCamera.h"
//使用到如下类的指针，进行类预声明
class CG2DRenderContext;
class CG2DCamera;
class CG2DScene;
class CG2DRenderable : public CGObject
{
	DECLARE_SERIAL(CG2DRenderable)
public:
	CG2DRenderable();
	CG2DRenderable(const CString& name);
	CG2DRenderable(const CG2DRenderable& other) = default;
	virtual ~CG2DRenderable() = default;
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//对象被添加到场景，建立与场景的关联
	void addToScene(CG2DScene* s) { mScene = s; }
	CG2DScene* scene() const { return mScene; }
	//绘制
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera); //绘制对象，使用指定相机
	//一般二维图形属性（线宽、线型、颜色）
	void setPenColor(COLORREF color) { mPenColor = color; }
	COLORREF penColor() const { return mPenColor; }
	void setPenWidth(int width) { mPenWidth = width; }
	int penWidth() const { return mPenWidth; }
	void setPenStyle(int style) { mPenStyle = style; }
	int penStyle() const { return mPenStyle; }
	//二维封闭图形填充属性
	void setBrushColor(COLORREF color) { mBrushColor = color; }
	COLORREF brushColor() const { return mBrushColor; }
	void setBrushStyle(int style) { mBrushStyle = style; }
	int brushStyle() const { return mBrushStyle; }
	void setHatchStyle(int style) { mHatchStyle = style; }
	int hatchStyle() const { return mHatchStyle; }
	//包围盒与拾取相关
	ABox2d& BoundingABox(); //AABB包围盒，可用于设置
	bool boundsDirty() const { return mBoundsDirty; } //对象包围盒是否需要重新计算
	void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; } //设置包围盒是否需要重新计算
	virtual void computeBoundingBox(); //计算对象的包围盒,必须在派生类中重写
	//对象状态定义（也可用枚举类型）
	static const int sNormal = 0; //正常状态
	static const int sSelected = 1; //选中状态
	int status() const { return mStatus; }
	void setStatus(int s) { mStatus = s; }
protected:
	COLORREF mPenColor = RGB(0, 0, 0); //轮廓颜色
	int mPenWidth = 1; //轮廓线宽
	int mPenStyle = PS_SOLID; //轮廓线型
	COLORREF mBrushColor = RGB(0, 0, 0); //画刷颜色
	int mBrushStyle = BS_SOLID; //画刷样式
	int mHatchStyle = HS_HORIZONTAL; //阴影样式
	CG2DScene* mScene = nullptr; //对象实例所属的场景，当对象加入场景时自动进行设置。
	ABox2d mABox;//轴对齐矩形包围盒，需要根据mBoundsDirty判断是否重新计算
	bool mBoundsDirty = true; //包围盒是否已改变
	int mStatus = 0; //状态
public:
	virtual bool Picked(const Vec2d& p, double radius); //（二维）是否拾取到
	virtual bool Picked(const ABox2d& box); //（二维）是否拾取到
	virtual void DrawSelectedBoundingBox(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera); //绘制选中包围盒
	virtual void DrawSelectedBoundingBoxi(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera); //绘制选中包围盒
	//图形几何变换
	virtual void Translate(double tx, double ty); //平移
	virtual void Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	virtual void Scale(double sx, double sy); //缩放（关于坐标原点缩放）
	virtual void Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	virtual void MirrorXAxis(); //关于X轴对称（二维）
	virtual void MirrorYAxis(); //关于Y轴对称（二维）
	virtual void MirrorYeqPosX(); //关于y=x对称（二维）
	virtual void MirrorYeNegPX(); //关于y=-x对称（二维）
	virtual void MirrorOrigin(); //关于原点对称（二维）
	virtual void Mirror(const Vec2d& vs, const Vec2d& ve); //关于线段se对称（二维）
	virtual void ShearXAxis(double shx); //沿X轴错切
	virtual void ShearYAxis(double shy); //沿Y轴错切
	virtual void ShearXYAxis(double shx, double shy); //沿X、Y轴错切
	virtual void Transform(const Mat3d& mat); //几何变换（左乘给定矩阵）
protected:
	Mat3d mMat; //到父级坐标系的变换（列向量形式）
public: //实验参考5
	//获取在视口内的包围盒(仅用于绘制对象的包围盒），需要在派生类中重写
	virtual ABox2i BoundingABoxi(CG2DCamera* pCamera);
public: //实验参考6
	//定时器回调，需要在派生类中重写实现多态 
	virtual bool TimerCallback() { return false; }
	bool TimerCallbackEnabled() const { return mTimerCallbackEnabled; }
	void EnableTimerCallback(bool e = true) { mTimerCallbackEnabled = e; }
protected:
	//默认情况下，时间回调不起作用，需要在动态对象中启用 
	bool mTimerCallbackEnabled = false;
};
#endif //_CG2DRenderable_H_INCLUDED
