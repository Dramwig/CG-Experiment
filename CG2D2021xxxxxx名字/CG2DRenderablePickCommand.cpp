#include "pch.h"
#include "CG2D2021xxxxxx����Doc.h" //����View֮ǰҪ����Doc
#include "CG2D2021xxxxxx����View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CG2DRenderablePickCommand.h"
CG2DRenderablePickCommand::CG2DRenderablePickCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview)
{
	mStep = 0;
}
int CG2DRenderablePickCommand::GetType() //��������
{
	return static_cast<int>(CommandType::cmd2dPickRenderable); //UIEventListener.h�ж��壬Ҫ���ݲ�ͬ�������������޸ģ��˴��ǻ���ֱ�߶�
}
//����¼�����������������ʰȡ��
int CG2DRenderablePickCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ
	if (mStep == 1)
	{
		Vec2d p = view->ViewPorttoWorld(Vec2i(pos.x, pos.y));
		if (nFlags & MK_CONTROL)  //Ctrl������
			view->AppendPicked(p, 5); //�ٶ�pick�뾶5����Ҫ��������
		else
			view->UpdatePicked(p, 5);
		mStep = 0;
	}
	return 0;
}
int CG2DRenderablePickCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		view->Prompt(_T("�����ͼ�ζ���"));
	}
	return 0;
}
//ȡ��Esc
int CG2DRenderablePickCommand::Cancel()
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
