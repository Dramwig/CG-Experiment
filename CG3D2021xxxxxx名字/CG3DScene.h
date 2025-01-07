#ifndef _CG3DScene_H_INCLUDED 
#define _CG3DScene_H_INCLUDED 
#include "CGObject.h" 
#include "AABBox3.h" 
#include "CGLightModel.h"
#include "CGLight.h"
#include "CGShadeModel.h"
//使用到如下类的指针，进行类预声明 
class CG3DRenderable;
class CG3DCamera;
class CG3DRenderContext;
class CG3DScene : public CGObject
{
	DECLARE_SERIAL(CG3DScene)
public:
	CG3DScene();
	virtual ~CG3DScene();

	virtual void Serialize(CArchive& ar) override;

	//管理场景中的图形对象 
	bool addRenderable(CG3DRenderable*);
	bool delRenderable(CG3DRenderable*);
	void removeAllRenderable();
	CG3DRenderable* getRenderable(unsigned int index);
	CG3DRenderable* detachRenderable(CG3DRenderable*);

	//渲染场景 
	bool Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//场景包围盒计算 
	ABox3d BoundingABox();
protected:
	//图形对象列表 
	CTypedPtrArray<CObArray, CG3DRenderable*> mRenderables;

public: //实验7
	//定时回调 
	bool TimerCallback();
	//光源 
	bool AddLight(CGLight* light);
	bool deleteLight(int index);
	void RemoveLastLight();
	void RemoveAllLights();

	CGLightModel& LightModel() { return mLightModel; }
	CGShadeModel& ShadeModel() { return mShadeModel; }
	const CGLightModel& LightModel() const { return mLightModel; }
	const CGShadeModel& ShadeModel() const { return mShadeModel; }

protected:
	//光源 
	CTypedPtrArray<CObArray, CGLight*> mLights;
	//光照及着色模式 
	CGLightModel mLightModel;
	CGShadeModel mShadeModel;
};

#endif //_CG3DScene_H_INCLUDED 
