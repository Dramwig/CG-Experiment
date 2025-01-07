#include "pch.h"
#include "CG2DLineSegmentCreateCommand.h"
#include "CG2D2021xxxxxx����Doc.h" //����View֮ǰҪ����Doc
#include "CG2D2021xxxxxx����View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CG2DLineSegment.h" //��������ͼ�ζ���ֱ�߶�
#include <cstring>

CG2DLineSegmentCreateCommand::CG2DLineSegmentCreateCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
int CG2DLineSegmentCreateCommand::GetType() //��������
{
	return static_cast<int>(CommandType::cmd2dLineSegment); //UIEventListener.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���ֱ�߶�
}
int CG2DLineSegmentCreateCommand::OnLButtonDown(UINT nFlags, CPoint pos)//
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ

	if (mStep == 1) //��һ�ε�������������¼�����λ����Ϊ�������߶ε����
	{
		mStart = mEnd = pos;
		view->Prompt(_T("������ֱ�߶ε��յ�")); //ͨ�������¼���View��ʾ��״̬��
	}
	else if (mStep == 2) //�ڶ��ε�������������¼�����λ����Ϊ�������߶ε��յ�
	{
		if (pos == mStart)
		{
			mStep = 1;
			view->Prompt(_T("���һ���غϣ�������ֱ�߶ε��յ�"));
			return -1;
		}
		//���������Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(mEnd.x, mEnd.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		//�ж��Ƿ���SHIFT��������ǣ������X��Y�����������С��������ˮƽ�߻�ֱ��
		if (nFlags & MK_SHIFT)//������MK_SHIFT��
		{
			if (abs(pos.x - mStart.x) <= abs(pos.y - mStart.y)) //x����仯С����ֱ��
			{
				mEnd.x = mStart.x; //X���ֲ���
				mEnd.y = pos.y;
			}
			else //x����仯��ˮƽ��
			{
				mEnd.x = pos.x;
				mEnd.y = mStart.y; //Y���ֲ���
			}
		}
		else //һ��ֱ�߶Σ���ˮƽ����ֱ������¼�յ㡣
		{
			mEnd = pos;
		}
		//�������ڶ��ε�����ֱ�߶δ�������㡢�յ��ѻ�ȡ��
		//��������Ҫע������ת������������������Ӧ������
		//��ȡ��㡢�յ��Ӧ�ĳ����������ڴ���ֱ�߶ζ���
		Vec2d start = view->ViewPorttoWorld(Vec2i(mStart.x, mStart.y));
		Vec2d end = view->ViewPorttoWorld(Vec2i(mEnd.x, mEnd.y));
		//�����߶β���ӵ�����
		CG2DLineSegment* pLine = new CG2DLineSegment(start, end);
		pLine->setPenColor(view->PenColor());
		pLine->setPenWidth(view->PenWidth());
		pLine->setPenStyle(view->PenStyle());
		view->addRenderable(pLine); //�����ɹ�����ӵ�����
		view->Invalidate(); //�ͻ�����Ҫ�ػ�
		view->UpdateWindow(); //�ͻ���ִ���ػ�
		mStep = 0; //��Ϊ0����д��ʼ�����߶ζ����õ����������ϵ��߶ΰ�ť
		mStart.x = mStart.y = mEnd.x = mEnd.y = 0;
		view->Prompt(_T("������ֱ�߶ε����")); //״̬����ʾ
	}
	else
	{
	}
	return 0;
}

int CG2DLineSegmentCreateCommand::OnMouseMove(UINT nFlags, CPoint pos)
{ 
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0) //��û�����һ���㣨��ȡ�߶���㣩
	{
		view->Prompt(_T("������ֱ�߶ε����")); //״̬����ʾ
		//CString strPrompt; // ����һ��CString�������洢��ʽ������ʾ��Ϣ
		//strPrompt.Format(_T("������ֱ�߶ε���㣬��ǰ��(%d, %d)"), pos.x, pos.y);
		//view->Prompt(strPrompt);  // ��ʾ��ʾ��Ϣ
	}
	else if (mStep == 1) //�Ѿ����������󣬵�ǰ����ƶ���λ��������γ���Ƥ��
	{
		if (pos == mStart)
		{
			return -1; //�����غϣ���������
		}
		CPoint prePos, curPos;
		prePos = mEnd;
		//�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
		if (nFlags & MK_SHIFT)
		{
			if (abs(pos.x - mStart.x) <= abs(pos.y - mStart.y)) //x����仯С����ֱ��
			{
				curPos.x = mStart.x;
				curPos.y = pos.y;
			}
			else
			{
				curPos.x = pos.x;
				curPos.y = mStart.y;
			}
		}
		else
		{
			curPos = pos;
		}
		//CString strPrompt; // ����һ��CString�������洢��ʽ������ʾ��Ϣ
		//strPrompt.Format(_T("������ֱ�߶ε��յ㣬��ǰ��(%d, %d)"), curPos.x, curPos.y);
		//view->Prompt(strPrompt);  // ��ʾ��ʾ��Ϣ
		//��������Ƥ��ʱ�Ȳ����ϴε���Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(prePos.x, prePos.y));
		//�����µ���Ƥ��
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(curPos.x, curPos.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		mEnd = curPos; //��¼����λ�ã���Ϊ�յ�
	}
	else
	{
	}
	return 0;
}
int CG2DLineSegmentCreateCommand::Cancel()
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 1) //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
	{
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(mEnd.x, mEnd.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
	}
	mStep = 0;
	mStart.x = mStart.y = mEnd.x = mEnd.y = 0;
	view->Prompt(_T("����")); //״̬����ʾ
	return 0;
}
