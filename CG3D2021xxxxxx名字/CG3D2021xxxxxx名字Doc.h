// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û�����
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο�����
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// CG3D2021xxxxxx����Doc.h: CCG3D2021xxxxxx����Doc ��Ľӿ�
//


#pragma once
#include "CG3DScene.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 
#include "CG3DRenderable.h" 
#include "CG3DRubiksCube.h"
#include "CG3DSphere.h"
#include "CG3DCone.h"
#include "CG3DCylinder.h"

class CCG3D2021xxxxxx����Doc : public CDocument
{
	friend class CCG3D2021xxxxxx����View;
protected: // �������л�����
	CCG3D2021xxxxxx����Doc() noexcept;
	DECLARE_DYNCREATE(CCG3D2021xxxxxx����Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CCG3D2021xxxxxx����Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	CG3DScene* scene() { return mScene; }
	CG3DCamera* defaultCamera() { return mCameras.GetAt(0); }
	CG3DSphere* sphere = nullptr;
	CG3DCone* cone = nullptr;
	CG3DCylinder* cylinder = nullptr;
	CGLight* mLight = nullptr, * mLight2 = nullptr;
	Vec4f mLightRBG;
	int mLightMark;
private:
	CG3DScene* mScene;  //���� 
	CG3DRubiksCube* mRubiksCube= nullptr; //ħ��
	CTypedPtrArray<CObArray, CG3DCamera*> mCameras; //��� 
public:
	//��Ⱦ������ָ���ͻ��� 
	bool RenderScene(CG3DRenderContext* pRC);
	//ͼ�ζ�����ӵ����� 
	bool addRenderable(CG3DRenderable* r);
	bool delReaderable(CG3DRenderable* r);
	afx_msg void OnUpdatePenColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenWidth(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenFill(CCmdUI* pCmdUI);
	void AddRenderable(CG3DRenderable* R);
	afx_msg void RemoveAll();
	afx_msg void OnUpdateRotate(CCmdUI* pCmdUI);
	afx_msg void OnUpRotatePos();
	afx_msg void OnUpRotateNeg();
	afx_msg void OnRightRotatePos();
	afx_msg void OnRightRotateNeg();
	afx_msg void OnFrontRotatePos();
	afx_msg void OnFrontRotateNeg();
	afx_msg void OnLeftRotatePos();
	afx_msg void OnLeftRotateNeg();
	afx_msg void OnBackRotatePos();
	afx_msg void OnBackRotateNeg();
	afx_msg void OnDownRotatePos();
	afx_msg void OnDownRotateNeg();
	afx_msg void OnLeftView();
	afx_msg void OnRightView();
	afx_msg void OnFrontView();
	afx_msg void OnBackView();
	afx_msg void OnCreateRubikscube();
	afx_msg void OnDownView();
	afx_msg void OnUpView();
	afx_msg void OnSubView();
	afx_msg void OnWindowsPos();
	afx_msg void OnWindowsNeg();
	afx_msg void OnInitScene();
	afx_msg void OnRemoveLastLight();
	afx_msg void OnRemoveAllLight();
	afx_msg void OnInitLight();
	afx_msg void OnUpdateMaterialColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBaseMaterial(CCmdUI* pCmdUI);
public:
	//������ʱ�ص�����������и�����Ҫ�ػ��򷵻�true�� 
	bool TimerCallback();
	afx_msg void Onanime1();
};
