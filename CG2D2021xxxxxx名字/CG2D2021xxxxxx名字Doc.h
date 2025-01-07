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

// CG2D2021xxxxxx����Doc.h: CCG2D2021xxxxxx����Doc ��Ľӿ�
//


#pragma once
#include "CG2DScene.h"
#include "CG2DCamera.h"
#include "CG2DRenderContext.h"
#include "CG2DRenderable.h"
#include "AABBox2.h"

class CCG2D2021xxxxxx����Doc : public CDocument
{
protected: // �������л�����
	CCG2D2021xxxxxx����Doc() noexcept;
	DECLARE_DYNCREATE(CCG2D2021xxxxxx����Doc)

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
	virtual ~CCG2D2021xxxxxx����Doc();
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
	CG2DScene* scene() { return mScene; }
	CG2DCamera* defaultCamera() { return mCameras.GetAt(0); }
private:
	CG2DScene* mScene; //����
	CTypedPtrArray<CObArray, CG2DCamera*> mCameras; //���
public:
	//��Ⱦ������ָ���ͻ���
	bool RenderScene(CG2DRenderContext* pRC);
	//ͼ�ζ�����ӵ�����
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
	//�����ӿ������ȡ��Ӧ�������꣨��ά��-����Ĭ�������ת������
	Vec2d ViewPorttoWorld(const Vec2i& p);
	Vec2d ViewPorttoWorld(const Vec2d& p);
	Vec2i WorldtoViewPort(const Vec2d& p);
public:
	//����ѡ�����ʰȡ����ɹ������滻ѡ�񼯣�����ʰȡ�Ķ���
	CG2DRenderable* UpdatePicked(const Vec2d& p, double radius); //��ѡ
	CG2DRenderable* UpdatePicked(const ABox2d& box, bool inner = true); //��ѡ��������ѡ�У���
	//���ѡ�����ʰȡ����ɹ��������ѡ�񼯣�����ʰȡ�Ķ���
	CG2DRenderable* AppendPicked(const Vec2d& p, double radius); //��ѡ
	CG2DRenderable* AppendPicked(const ABox2d& box, bool inner = true); //��ѡ��������ѡ�У���
	bool UnselectAll(); //�������ж���ѡ��״̬
public:
	//ͼ�μ��α任
	bool Translate(double tx, double ty); //ƽ��
	bool Rotate(double angle, double cx, double cy); //��ת����ʱ��Ϊ�����ȣ�
	bool Scale(double sx, double sy); //���ţ���������ԭ�����ţ�
	bool Scale(double sx, double sy, double cx, double cy); //���ţ�����ָ���ο������ţ�
	bool MirrorXAxis(); //����X��Գƣ���ά��
	bool MirrorYAxis(); //����Y��Գƣ���ά��
	bool MirrorYeqPosX(); //����y=x�Գƣ���ά��
	bool MirrorYeNegPX(); //����y=-x�Գƣ���ά��
	bool MirrorOrigin(); //����ԭ��Գƣ���ά��
	bool Mirror(const Vec2d& vs, const Vec2d& ve); //�����߶�se�Գƣ���ά��
	bool ShearXAxis(double shx); //��X�����
	bool ShearYAxis(double shy); //��Y�����
	bool ShearXYAxis(double shx, double shy); //��X��Y�����
	bool Transform(const Mat3d& mat); //���α任����˸�������
public:
	//Ĭ������Ĺ۲�����ϵ
	void MoveCamera(double tx, double ty); //ƽ��������۲�����ϵ��
	void RotateCamera(double degree); //ת��������۲�����ϵ��
	void ResetCamera(); //���������Ĭ�ϲ������۲�����ϵ��
	//Ĭ������Ĺ۲촰��
	void ZoomCamera(const Vec2d& lb, const Vec2d& rt); //�۲촰�����½ǡ����Ͻ�
	void ZoomCamera(double ratio); //�����۲촰�ڵ����ű�������
	void CameraShowAll(); //��ʾȫ������
	void CameraWindowOffset(double offleft, double offbottom, double offright, double offtop); //�߽��ƶ�
	void CameraWindowSet(double left, double bottom, double right, double top); //���ù۲촰��
	void WindowReset(); //���õ�Ĭ�Ϲ۲촰��
	void CameraWindowOverall(); //����۲촰��
	//Ĭ��������ӿ�
	void CameraViewportOffset(int offleft, int offbottom, int offright, int offtop); //�߽��ƶ�
	void CameraViewportSet(int width, int height);
	void CameraViewportReset();
	void CameraAspectRatio();
public: //ʵ��ο�6
	//������ʱ�ص�����������и�����Ҫ�ػ��򷵻�true�� 
	bool TimerCallback();
	afx_msg void OnBtnParticle();
	afx_msg void OnBtnFireworks();
	afx_msg void OnBtnRemoveall();
};
