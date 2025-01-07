// CInputDialog1.cpp: 实现文件
//

#include "pch.h"
#include "CG3D2021xxxxxx名字.h"
#include "afxdialogex.h"
#include "CInputDialog1.h"


// CInputDialog1 对话框

IMPLEMENT_DYNAMIC(CInputDialog1, CDialogEx)

CInputDialog1::CInputDialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDC_INPUT_VALUE1, pParent)
	, mValue1(_T(""))
	, mValue2(_T(""))
	, mValue3(_T(""))
{

}

CInputDialog1::~CInputDialog1()
{
}

void CInputDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mValue1);
	DDX_Text(pDX, IDC_EDIT2, mValue2);
	DDX_Text(pDX, IDC_EDIT3, mValue3);
}


BEGIN_MESSAGE_MAP(CInputDialog1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputDialog1::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputDialog1 消息处理程序


BOOL CInputDialog1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (mTitle.GetLength() > 1)
	{
		SetWindowText(mTitle);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CInputDialog1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true); //取回输入框中数据到成员变量 
	CDialogEx::OnOK();
}
