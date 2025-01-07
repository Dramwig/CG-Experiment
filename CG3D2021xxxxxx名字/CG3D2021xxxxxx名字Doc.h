// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CG3D2021xxxxxx名字Doc.h: CCG3D2021xxxxxx名字Doc 类的接口
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

class CCG3D2021xxxxxx名字Doc : public CDocument
{
	friend class CCG3D2021xxxxxx名字View;
protected: // 仅从序列化创建
	CCG3D2021xxxxxx名字Doc() noexcept;
	DECLARE_DYNCREATE(CCG3D2021xxxxxx名字Doc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CCG3D2021xxxxxx名字Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
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
	CG3DScene* mScene;  //场景 
	CG3DRubiksCube* mRubiksCube= nullptr; //魔方
	CTypedPtrArray<CObArray, CG3DCamera*> mCameras; //相机 
public:
	//渲染场景到指定客户区 
	bool RenderScene(CG3DRenderContext* pRC);
	//图形对象添加到场景 
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
	//动画定时回调（如果场景有更新需要重绘则返回true） 
	bool TimerCallback();
	afx_msg void Onanime1();
};
