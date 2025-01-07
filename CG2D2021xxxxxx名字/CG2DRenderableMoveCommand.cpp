#include "pch.h"
#include "CG2D2021xxxxxx����Doc.h" //����View֮ǰҪ����Doc
#include "CG2D2021xxxxxx����View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CG2DRenderableMoveCommand.h"

CG2DRenderableMoveCommand::CG2DRenderableMoveCommand(CView* pview/* = nullptr*/, CCG2D2021xxxxxx����Doc* pDoc/* = nullptr*/)
	:UIEventListener(pview), mDoc(pDoc)
{
	mStep = 0;
	mStartPos = CPoint(0, 0);
	prePos = CPoint(0, 0);
}

int CG2DRenderableMoveCommand::GetType() //��������
{
	return static_cast<int>(CommandType::cmd2dMoveRenderable); //UIEventListener.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���ֱ�߶�
}

//����¼�����������������ʰȡ��
int CG2DRenderableMoveCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;

	mStep++; //ÿ�ε���������ʱ�������������һ
	if (mStep == 1)
	{
		view->Prompt(_T("�϶����ѡ��ͼ�ζ���"));
		mStartPos = pos;
		prePos = pos;
	}
	else if (mStep == 2)
	{
		view->Prompt(_T("�ƶ����"));
		mStep = 0;
		mStartPos = CPoint(0, 0);
		prePos = CPoint(0, 0);
	}
	return 0;
}

int CG2DRenderableMoveCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		view->Prompt(_T("��갴��ѡ��ο���"));
	}
	else if (mStep == 1)
	{
		view->Prompt(_T("��갴��ѡ���ƶ��յ�"));
		if (mDoc)
		{
			Vec2d s = view->ViewPorttoWorld(Vec2i(prePos.x, prePos.y));
			Vec2d t = view->ViewPorttoWorld(Vec2i(pos.x, pos.y));
			mDoc->Translate(t.x() - s.x(), t.y() - s.y());
			prePos = pos;
			if (mView) {
				mView->Invalidate(true);
				mView->UpdateWindow();
			}
		}
	}
	return 0;
}

//ȡ��Esc
int CG2DRenderableMoveCommand::Cancel()
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

