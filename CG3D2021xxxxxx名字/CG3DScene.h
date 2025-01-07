#ifndef _CG3DScene_H_INCLUDED 
#define _CG3DScene_H_INCLUDED 
#include "CGObject.h" 
#include "AABBox3.h" 
#include "CGLightModel.h"
#include "CGLight.h"
#include "CGShadeModel.h"
//ʹ�õ��������ָ�룬������Ԥ���� 
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

	//�������е�ͼ�ζ��� 
	bool addRenderable(CG3DRenderable*);
	bool delRenderable(CG3DRenderable*);
	void removeAllRenderable();
	CG3DRenderable* getRenderable(unsigned int index);
	CG3DRenderable* detachRenderable(CG3DRenderable*);

	//��Ⱦ���� 
	bool Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//������Χ�м��� 
	ABox3d BoundingABox();
protected:
	//ͼ�ζ����б� 
	CTypedPtrArray<CObArray, CG3DRenderable*> mRenderables;

public: //ʵ��7
	//��ʱ�ص� 
	bool TimerCallback();
	//��Դ 
	bool AddLight(CGLight* light);
	bool deleteLight(int index);
	void RemoveLastLight();
	void RemoveAllLights();

	CGLightModel& LightModel() { return mLightModel; }
	CGShadeModel& ShadeModel() { return mShadeModel; }
	const CGLightModel& LightModel() const { return mLightModel; }
	const CGShadeModel& ShadeModel() const { return mShadeModel; }

protected:
	//��Դ 
	CTypedPtrArray<CObArray, CGLight*> mLights;
	//���ռ���ɫģʽ 
	CGLightModel mLightModel;
	CGShadeModel mShadeModel;
};

#endif //_CG3DScene_H_INCLUDED 
