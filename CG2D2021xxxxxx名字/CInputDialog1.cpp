// CInputDialog1.cpp: 实现文件
//

#include "pch.h"
#include "CG2D2021xxxxxx名字.h"
#include "afxdialogex.h"
#include "CInputDialog1.h"


// CInputDialog1 对话框

IMPLEMENT_DYNAMIC(CInputDialog1, CDialogEx)

CInputDialog1::CInputDialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_DIALOG1, pParent)
	, mValue1(_T(""))
{

}

CInputDialog1::~CInputDialog1()
{
}

void CInputDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_VALUE1, mValue1);
}


BEGIN_MESSAGE_MAP(CInputDialog1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputDialog1::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputDialog1 消息处理程序


void CInputDialog1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true); //取回输入框中数据到成员变量 
	CDialogEx::OnOK();
}


BOOL CInputDialog1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (mTitle.GetLength() > 1)
		this->SetWindowText(mTitle);
	return TRUE;  // return TRUE unless you set the focus to a control 
	// 异常: OCX 属性页应返回 FALSE
}
