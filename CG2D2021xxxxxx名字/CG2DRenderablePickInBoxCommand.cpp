#include "pch.h"
#include "CG2D2021xxxxxx����Doc.h" //����View֮ǰҪ����Doc
#include "CG2D2021xxxxxx����View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CG2DRenderablePickInBoxCommand.h"
CG2DRenderablePickInBoxCommand::CG2DRenderablePickInBoxCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview)
{
	mStep = 0;
	mStartPos = CPoint(0, 0);
	prePos = CPoint(0, 0);
	mIsLongPress = false;
}
int CG2DRenderablePickInBoxCommand::GetType() //��������
{
	return static_cast<int>(CommandType::cmd2dPickInBoxRenderable); //UIEventListener.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���ֱ�߶�
}
//����¼�����������������ʰȡ��
int CG2DRenderablePickInBoxCommand::OnLButtonDown(UINT nFlags, CPoint pos)
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
		view->Prompt(_T("�϶����ѡ��ͼ�ζ���"));
	}
	return 0;
}

void CG2DRenderablePickInBoxCommand::DrawRect(CView* mView, CPoint start, CPoint end)
{
	CClientDC dc(mView);
	CPen pen(PS_DOT, 1, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);
	int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT

	int left = std::min(start.x, end.x);
	int top = std::min(start.y, end.y);
	int right = std::max(start.x, end.x);
	int bottom = std::max(start.y, end.y);
	if (abs(left - right)<=1 || abs(top - bottom)<=1) {
		dc.MoveTo(start);
		dc.LineTo(end);
	}
	else {
		dc.DrawFocusRect(CRect(left, top, right, bottom));
	}

	dc.SelectObject(pOldPen);
	dc.SetROP2(mode);
}

int CG2DRenderablePickInBoxCommand::OnLButtonUp(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;

	if(mStep == 1 && mIsLongPress)
	{
		mStep = 0;
		mIsLongPress = false;
		Vec2d s = view->ViewPorttoWorld(Vec2i(mStartPos.x, mStartPos.y));
		Vec2d t = view->ViewPorttoWorld(Vec2i(pos.x, pos.y));
		ABox2d box(s, t);
		if (nFlags & MK_CONTROL)  //Ctrl������
			view->AppendPicked(box,true);
		else
			view->UpdatePicked(box, true);
		DrawRect(mView, mStartPos, prePos);
	}

	return 0;
}
int CG2DRenderablePickInBoxCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		view->Prompt(_T("��갴�¿�ѡͼ�ζ���"));
	}
	else if (mStep == 1)
	{
		view->Prompt(_T("�ͷ����ѡ�п�ѡͼ�ζ���"));
		DrawRect(mView, mStartPos, prePos);
		DrawRect(mView, mStartPos, pos);

		prePos = pos; // Update position
	}
	return 0;
}

//ȡ��Esc
int CG2DRenderablePickInBoxCommand::Cancel()
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

