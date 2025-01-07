#ifndef _CG2DScene_H_INCLUDED
#define _CG2DScene_H_INCLUDED
#include "CGObject.h"
#include "AABBox2.h"
#include "Matrix33.h"
#include "ParticleSystem2D.h"
//使用到如下类的指针，进行类预声明
class CG2DRenderable;
class CG2DCamera;
class CG2DRenderContext;
class CG2DScene : public CGObject
{
	DECLARE_SERIAL(CG2DScene)
public:
	CG2DScene();
	virtual ~CG2DScene();
	virtual void Serialize(CArchive& ar) override;
	//管理场景中的图形对象
	bool addRenderable(CG2DRenderable*);
	bool delRenderable(CG2DRenderable*);
	void removeAllRenderable();
	CG2DRenderable* getRenderable(unsigned int index);
	CG2DRenderable* detachRenderable(CG2DRenderable*);
	//渲染场景
	bool Render(CG2DRenderContext* pRC, CG2DCamera* pCamera);
	//二维场景包围盒计算
	ABox2d BoundingABox();
	ABox2d BoundingABoxi(CG2DCamera* pCamera);
protected:
	//图形对象列表
	CTypedPtrArray<CObArray, CG2DRenderable*> mRenderables;
	//图形对象选择集
	CTypedPtrArray<CObArray, CG2DRenderable*> mSelections;
//定义场景中图形对象选中相关成员函数
public:
	//更新选择（如果拾取对象成功，则替换选择集，返回拾取的对象）
	CG2DRenderable* UpdatePicked(const Vec2d& p, double radius); //点选
	CG2DRenderable* UpdatePicked(const ABox2d& box, bool inner = true); //框选（包含才选中？）
	//添加选择（如果拾取对象成功，则加入选择集，返回拾取的对象）
	CG2DRenderable* AppendPicked(const Vec2d& p, double radius); //点选
	CG2DRenderable* AppendPicked(const ABox2d& box, bool inner = true); //框选（包含才选中？）
	//按图形对象名称选取（如有该对象，则加入选择集，返回选取的对象）
	CG2DRenderable* Selected(const CString& name);
	bool Unselect(const CString& name); //撤销指定对象选中状态
	bool Unselect(CG2DRenderable* r); //撤销指定对象选中状态
	bool UnselectAll(); //撤销所有对象选中状态
	bool SelectAll(); //所有对象设为选中
public:
	//图形几何变换
	bool Translate(double tx, double ty); //平移
	bool Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	bool Scale(double sx, double sy); //缩放（关于坐标原点缩放）
	bool Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	bool MirrorXAxis(); //关于X轴对称（二维）
	bool MirrorYAxis(); //关于Y轴对称（二维）
	bool MirrorYeqPosX(); //关于y=x对称（二维）
	bool MirrorYeNegPX(); //关于y=-x对称（二维）
	bool MirrorOrigin(); //关于原点对称（二维）
	bool Mirror(const Vec2d& vs, const Vec2d& ve); //关于线段se对称（二维）
	bool ShearXAxis(double shx); //沿X轴错切
	bool ShearYAxis(double shy); //沿Y轴错切
	bool ShearXYAxis(double shx, double shy); //沿X、Y轴错切
	bool Transform(const Mat3d& mat); //几何变换（左乘给定矩阵）
public: //实验参考6
	//定时回调（用于实现动画） 
	bool TimerCallback();
public:
	bool addParticleSystem(ParticleSystem2D*);
	bool delParticleSystem(ParticleSystem2D*);
	void removeAllParticleSystem();
protected:
	CTypedPtrArray<CObArray, ParticleSystem2D*> mParticleSystems;
};
#endif //_CG2DScene_H_INCLUDED
