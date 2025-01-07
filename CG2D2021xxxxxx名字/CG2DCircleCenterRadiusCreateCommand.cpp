#include "pch.h"
#include "CG2DCircleCenterRadiusCreateCommand.h"
#include "CG2D2021xxxxxx����Doc.h" //����View֮ǰҪ����Doc
#include "CG2D2021xxxxxx����View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CG2DLineSegment.h"
#include "CG2DCircle.h"
#include "CG2DPolygon.h"

CG2DCircleCenterRadiusCreateCommand::CG2DCircleCenterRadiusCreateCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview), mCenter(0, 0), mEdgePoint(0, 0)
{
	mStep = 0;
}
int CG2DCircleCenterRadiusCreateCommand::GetType() //��������
{
	return static_cast<int>(CommandType::cmd2dCircleCenterRadius); //UIEventListener.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���ֱ�߶�
}
int CG2DCircleCenterRadiusCreateCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ
	mEdgePoint = pos;
	if (mStep == 1) //��һ�ε�������������¼�����λ����Ϊ�������߶ε����
	{
		mCenter = pos;
		view->Prompt(_T("��ѡ��Բ�εİ뾶")); //ͨ�������¼���View��ʾ��״̬��
	}
	else if (mStep == 2) //�ڶ��ε�������������¼�����λ����Ϊ�������߶ε��յ�
	{
		if (pos == mCenter)
		{
			mStep = 1;
			view->Prompt(_T("��Բ���غϣ�������ѡ��뾶"));
			return -1;
		}
		//���������Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(mEdgePoint.x, mEdgePoint.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		
		//�������ڶ��ε�����ֱ�߶δ�������㡢�յ��ѻ�ȡ��
		//��������Ҫע������ת������������������Ӧ������
		//��ȡ��㡢�յ��Ӧ�ĳ����������ڴ���ֱ�߶ζ���

		int Radius = static_cast<int>(sqrt(pow(mCenter.x - mEdgePoint.x, 2) 
			+ pow(mCenter.y - mEdgePoint.y, 2)));
		CG2DPolygon* polygon = new CG2DPolygon();
		polygon->setPenColor(view->PenColor());
		polygon->setPenWidth(view->PenWidth());
		polygon->setPenStyle(view->PenStyle());
		for(double theta = 0; theta < 2*PI; theta += 2*PI  / 100) {
			Vec2d p = Vec2d(mCenter.x + Radius * cos(theta), mCenter.y + Radius * sin(theta));
			p = view->ViewPorttoWorld(Vec2d(p.x(), p.y()));
			polygon->addPoint(p);
		}
		view->addRenderable(polygon); //�����ɹ�����ӵ�����
		view->Invalidate(); //�ͻ�����Ҫ�ػ�
		view->UpdateWindow(); //�ͻ���ִ���ػ�
		mStep = 0; //��Ϊ0����д��ʼ�����߶ζ����õ����������ϵ��߶ΰ�ť
		mCenter.x = mCenter.y = mEdgePoint.x = mEdgePoint.y = 0;
		view->Prompt(_T("������Բ�ε�Բ��")); //״̬����ʾ
	}
	else
	{
	}
	return 0;
}

int CG2DCircleCenterRadiusCreateCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0) //��û�����һ���㣨��ȡ�߶���㣩
	{
		view->Prompt(_T("������Բ�ε�Բ��")); //״̬����ʾ
	}
	else if (mStep == 1) //�Ѿ����������󣬵�ǰ����ƶ���λ��������γ���Ƥ��
	{
		if (pos == mCenter)
		{
			return -1; //�����غϣ���������
		}
		CPoint prePos;
		prePos = mEdgePoint;
		//��������Ƥ��ʱ�Ȳ����ϴε���Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(prePos.x, prePos.y));
		int preRadius = static_cast<int>(sqrt(pow(prePos.x - mCenter.x, 2) + pow(prePos.y - mCenter.y, 2)));
		dc.Ellipse(mCenter.x - preRadius, mCenter.y - preRadius, mCenter.x + preRadius, mCenter.y + preRadius);
		//�����µ���Ƥ��
		int radius = static_cast<int>(sqrt(pow(pos.x - mCenter.x, 2) + pow(pos.y - mCenter.y, 2)));
		dc.Ellipse(mCenter.x - radius, mCenter.y - radius, mCenter.x + radius, mCenter.y + radius);
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(pos.x, pos.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		mEdgePoint = pos; //��¼����λ�ã���Ϊ�յ�
	}
	else
	{
	}
	return 0;
}
int CG2DCircleCenterRadiusCreateCommand::Cancel()
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
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(mEdgePoint.x, mEdgePoint.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
	}
	mStep = 0;
	mCenter.x = mCenter.y = mEdgePoint.x = mEdgePoint.y = 0;
	view->Prompt(_T("����")); //״̬����ʾ
	return 0;
}
