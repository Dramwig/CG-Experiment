// CInputLight.cpp: 实现文件
//

#include "pch.h"
#include "CG3D2021xxxxxx名字.h"
#include "afxdialogex.h"
#include "CInputLight.h"


// CInputLight 对话框

IMPLEMENT_DYNAMIC(CInputLight, CDialogEx)

CInputLight::CInputLight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_LIGHT, pParent)
	, Ar(0)
	, Ag(0)
	, Ab(0)
	, Dr(200)
	, Dg(200)
	, Db(200)
	, Sr(250)
	, Sg(150)
	, Sb(150)
	, Px(0)
	, Py(5)
	, Pz(0)
	, Dx(0)
	, Dy(-1)
	, Dz(0)
	, At1(0.5)
	, At2(0)
	, At3(0)
	, SpotExp(10)
	, SpotCut(180)
{

}

CInputLight::~CInputLight()
{
}

void CInputLight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Ar, Ar);
	DDX_Text(pDX, IDC_Ag, Ag);
	DDX_Text(pDX, IDC_Ab, Ab);
	DDX_Text(pDX, IDC_Dr, Dr);
	DDX_Text(pDX, IDC_Dg, Dg);
	DDX_Text(pDX, IDC_Db, Db);
	DDX_Text(pDX, IDC_Sr, Sr);
	DDX_Text(pDX, IDC_Sg, Sg);
	DDX_Text(pDX, IDC_Sb, Sb);
	DDX_Text(pDX, IDC_Px, Px);
	DDX_Text(pDX, IDC_Py, Py);
	DDX_Text(pDX, IDC_Pz, Pz);
	DDX_Text(pDX, IDC_Dx, Dx);
	DDX_Text(pDX, IDC_Dy, Dy);
	DDX_Text(pDX, IDC_Dz, Dz);
	DDX_Text(pDX, IDC_At1, At1);
	DDX_Text(pDX, IDC_At2, At2);
	DDX_Text(pDX, IDC_At3, At3);
	DDX_Text(pDX, IDC_SpotExp, SpotExp);
	DDX_Text(pDX, IDC_SpotCutoff, SpotCut);
}


BEGIN_MESSAGE_MAP(CInputLight, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputLight::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputLight 消息处理程序


void CInputLight::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true); //取回输入框中数据到成员变量 
	CDialogEx::OnOK();
}


BOOL CInputLight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (mTitle.GetLength() > 1)
		this->SetWindowText(mTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
