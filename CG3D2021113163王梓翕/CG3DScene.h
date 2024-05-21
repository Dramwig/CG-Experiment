#ifndef _CG3DScene_H_INCLUDED 
#define _CG3DScene_H_INCLUDED 
#include "CGObject.h" 
#include "AABBox3.h" 
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
};

#endif //_CG3DScene_H_INCLUDED 