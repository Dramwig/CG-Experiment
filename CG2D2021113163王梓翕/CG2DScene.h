#ifndef _CG2DScene_H_INCLUDED
#define _CG2DScene_H_INCLUDED
#include "CGObject.h"
#include "AABBox2.h"
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
protected:
	//图形对象列表
	CTypedPtrArray<CObArray, CG2DRenderable*> mRenderables;
};
#endif //_CG2DScene_H_INCLUDED