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

// CG2D2021xxxxxx名字Doc.h: CCG2D2021xxxxxx名字Doc 类的接口
//


#pragma once
#include "CG2DScene.h"
#include "CG2DCamera.h"
#include "CG2DRenderContext.h"
#include "CG2DRenderable.h"
#include "AABBox2.h"

class CCG2D2021xxxxxx名字Doc : public CDocument
{
protected: // 仅从序列化创建
	CCG2D2021xxxxxx名字Doc() noexcept;
	DECLARE_DYNCREATE(CCG2D2021xxxxxx名字Doc)

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
	virtual ~CCG2D2021xxxxxx名字Doc();
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
	CG2DScene* scene() { return mScene; }
	CG2DCamera* defaultCamera() { return mCameras.GetAt(0); }
private:
	CG2DScene* mScene; //场景
	CTypedPtrArray<CObArray, CG2DCamera*> mCameras; //相机
public:
	//渲染场景到指定客户区
	bool RenderScene(CG2DRenderContext* pRC);
	//图形对象添加到场景
	bool addRenderable(CG2DRenderable* r);
	bool delReaderable(CG2DRenderable* r);
	void clearScene();
	afx_msg void OnUpdatePenColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenWidth(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrushColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrushStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrushHatch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorPolygon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorSeedfill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBoundColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInnerColor(CCmdUI* pCmdUI);

//3-2
public:
	//根据视口坐标获取对应场景坐标（二维）-调用默认相机的转换函数
	Vec2d ViewPorttoWorld(const Vec2i& p);
	Vec2d ViewPorttoWorld(const Vec2d& p);
	Vec2i WorldtoViewPort(const Vec2d& p);
public:
	//更新选择（如果拾取对象成功，则替换选择集，返回拾取的对象）
	CG2DRenderable* UpdatePicked(const Vec2d& p, double radius); //点选
	CG2DRenderable* UpdatePicked(const ABox2d& box, bool inner = true); //框选（包含才选中？）
	//添加选择（如果拾取对象成功，则加入选择集，返回拾取的对象）
	CG2DRenderable* AppendPicked(const Vec2d& p, double radius); //点选
	CG2DRenderable* AppendPicked(const ABox2d& box, bool inner = true); //框选（包含才选中？）
	bool UnselectAll(); //撤销所有对象选中状态
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
public:
	//默认相机的观察坐标系
	void MoveCamera(double tx, double ty); //平移相机（观察坐标系）
	void RotateCamera(double degree); //转动相机（观察坐标系）
	void ResetCamera(); //重置相机到默认参数（观察坐标系）
	//默认相机的观察窗口
	void ZoomCamera(const Vec2d& lb, const Vec2d& rt); //观察窗口左下角、右上角
	void ZoomCamera(double ratio); //给定观察窗口的缩放比例（）
	void CameraShowAll(); //显示全部场景
	void CameraWindowOffset(double offleft, double offbottom, double offright, double offtop); //边界移动
	void CameraWindowSet(double left, double bottom, double right, double top); //设置观察窗口
	void WindowReset(); //重置到默认观察窗口
	void CameraWindowOverall(); //整体观察窗口
	//默认相机的视口
	void CameraViewportOffset(int offleft, int offbottom, int offright, int offtop); //边界移动
	void CameraViewportSet(int width, int height);
	void CameraViewportReset();
	void CameraAspectRatio();
public: //实验参考6
	//动画定时回调（如果场景有更新需要重绘则返回true） 
	bool TimerCallback();
	afx_msg void OnBtnParticle();
	afx_msg void OnBtnFireworks();
	afx_msg void OnBtnRemoveall();
};
