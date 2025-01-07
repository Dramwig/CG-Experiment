#pragma once
#include "afxdialogex.h"


// CInputLight �Ի���

class CInputLight : public CDialogEx
{
	DECLARE_DYNAMIC(CInputLight)

public:
	CInputLight(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CInputLight();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString mTitle;
	float Ar;
	float Ag;
	float Ab;
	float Dr;
	float Dg;
	float Db;
	float Sr;
	float Sg;
	float Sb;
	float Px;
	float Py;
	float Pz;
	float Dx;
	float Dy;
	float Dz;
	float At1;
	float At2;
	float At3;
	float SpotExp;
	float SpotCut;
};
