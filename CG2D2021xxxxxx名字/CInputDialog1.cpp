// CInputDialog1.cpp: ʵ���ļ�
//

#include "pch.h"
#include "CG2D2021xxxxxx����.h"
#include "afxdialogex.h"
#include "CInputDialog1.h"


// CInputDialog1 �Ի���

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


// CInputDialog1 ��Ϣ�������


void CInputDialog1::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true); //ȡ������������ݵ���Ա���� 
	CDialogEx::OnOK();
}


BOOL CInputDialog1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (mTitle.GetLength() > 1)
		this->SetWindowText(mTitle);
	return TRUE;  // return TRUE unless you set the focus to a control 
	// �쳣: OCX ����ҳӦ���� FALSE
}
