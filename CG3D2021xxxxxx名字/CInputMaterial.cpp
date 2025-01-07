// CInputMaterial.cpp: 实现文件
//

#include "pch.h"
#include "CG3D2021xxxxxx名字.h"
#include "afxdialogex.h"
#include "CInputMaterial.h"


// CInputMaterial 对话框

IMPLEMENT_DYNAMIC(CInputMaterial, CDialogEx)

CInputMaterial::CInputMaterial(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_MATERIAL, pParent)
	, Ar(255)
	, Ag(0)
	, Ab(0)
	, Dr(0)
	, Dg(255)
	, Db(0)
	, Sr(0)
	, Sg(0)
	, Sb(255)
	, Eb(10)
	, Eg(10)
	, Er(10)
	, Shin(32)
	
{

}

CInputMaterial::~CInputMaterial()
{
}

void CInputMaterial::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Ab, Ab);
	DDX_Text(pDX, IDC_Ag, Ag);
	DDX_Text(pDX, IDC_Ar, Ar);
	DDX_Text(pDX, IDC_Db, Db);
	DDX_Text(pDX, IDC_Dr, Dr);
	DDX_Text(pDX, IDC_Dg, Dg);
	DDX_Text(pDX, IDC_Eb, Eb);
	DDX_Text(pDX, IDC_Eg, Eg);
	DDX_Text(pDX, IDC_Er, Er);
	DDX_Text(pDX, IDC_Sb, Sb);
	DDX_Text(pDX, IDC_Sg, Sg);
	DDX_Text(pDX, IDC_Shin, Shin);
	DDX_Text(pDX, IDC_Sr, Sr);
}


BEGIN_MESSAGE_MAP(CInputMaterial, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputMaterial::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputMaterial 消息处理程序


void CInputMaterial::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true); //取回输入框中数据到成员变量
	CDialogEx::OnOK();
}


BOOL CInputMaterial::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (mTitle.GetLength() > 1)
		this->SetWindowText(mTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
