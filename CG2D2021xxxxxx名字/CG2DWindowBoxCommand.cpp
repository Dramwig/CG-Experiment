#include "pch.h"
#include "CG2D2021xxxxxx����Doc.h" //����View֮ǰҪ����Doc
#include "CG2D2021xxxxxx����View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CG2DWindowBoxCommand.h"

CG2DWindowBoxCommand::CG2DWindowBoxCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview)
{
	mStep = 0;
	mStartPos = CPoint(0, 0);
	prePos = CPoint(0, 0);
	mIsLongPress = false;
}
int CG2DWindowBoxCommand::GetType() //��������
{
	return static_cast<int>(CommandType::cmd2dWindowBox); //UIEventListener.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���ֱ�߶�
}
//����¼�����������������ʰȡ��
int CG2DWindowBoxCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;

	mStep++; //ÿ�ε���������ʱ�������������һ
	mStartPos = pos;
	mIsLongPress = true;
	prePos = mStartPos;
	if (mStep == 1)
	{
		view->Prompt(_T("�϶����ѡ�񴰿�"));
	}
	return 0;
}

void CG2DWindowBoxCommand::DrawRect(CView* mView, CPoint start, CPoint end)
{
	CClientDC dc(mView);
	CPen pen(PS_DOT, 1, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);
	int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT

	int left = std::min(start.x, end.x);
	int top = std::min(start.y, end.y);
	int right = std::max(start.x, end.x);
	int bottom = std::max(start.y, end.y);
	if (abs(left - right) <= 1 || abs(top - bottom) <= 1) {
		dc.MoveTo(start);
		dc.LineTo(end);
	}
	else {
		dc.DrawFocusRect(CRect(left, top, right, bottom));
	}

	dc.SelectObject(pOldPen);
	dc.SetROP2(mode);
}

int CG2DWindowBoxCommand::OnLButtonUp(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;

	if (mStep == 1 && mIsLongPress)
	{
		mStep = 0;
		mIsLongPress = false;
		DrawRect(mView, mStartPos, prePos);
		//Vec2d s = view->ViewPorttoWorld(Vec2i(mStartPos.x, mStartPos.y));
		//Vec2d t = view->ViewPorttoWorld(Vec2i(pos.x, pos.y));
		CCG2D2021xxxxxx����Doc* pDoc = view->GetDocument();
		Vec2d s = pDoc->defaultCamera()->DCStoNCS(Vec2i(mStartPos.x, mStartPos.y));
		s = pDoc->defaultCamera()->NCStoVCS(s);
		//s = pDoc->defaultCamera()->VCStoWCS(s);
		Vec2d t = pDoc->defaultCamera()->DCStoNCS(Vec2i(pos.x, pos.y));
		t = pDoc->defaultCamera()->NCStoVCS(t);
		//t = pDoc->defaultCamera()->VCStoWCS(t);

		double left = std::min(s.x(),t.x());
		double top = std::max(s.y(), t.y());
		double right = std::max(s.x(), t.x());
		double bottom = std::min(s.y(), t.y());
		view->CameraWindowSet(left, bottom, right, top);
		view->Prompt(_T("�϶����ѡ�񴰿�"));
	}

	return 0;
}
int CG2DWindowBoxCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		//CCG2D2021xxxxxx����Doc* pDoc = view->GetDocument();
		//Vec2d t = pDoc->defaultCamera()->DCStoNCS(Vec2i(pos.x, pos.y));
		//t = pDoc->defaultCamera()->NCStoVCS(t);
		//t = pDoc->defaultCamera()->VCStoWCS(t);
		

		//ABox2d box(s, t);
		//CString strPrompt; // ����һ��CString�������洢��ʽ������ʾ��Ϣ
		//strPrompt.Format(_T("��ǰ�յ㣺(%f, %f)"), t.y(), p.y());
		//view->Prompt(strPrompt);  // ��ʾ��ʾ��Ϣ
	}
	else if (mStep == 1)
	{
		view->Prompt(_T("�ͷ������봰��"));
		DrawRect(mView, mStartPos, prePos);
		DrawRect(mView, mStartPos, pos);

		prePos = pos; // Update position
	}
	return 0;
}

//ȡ��Esc
int CG2DWindowBoxCommand::Cancel()
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	mStep = 0;
	view->Prompt(_T("����"));
	return 0;
}

