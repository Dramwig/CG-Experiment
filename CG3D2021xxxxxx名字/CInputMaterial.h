#pragma once
#include "afxdialogex.h"


// CInputMaterial 对话框

class CInputMaterial : public CDialogEx
{
	DECLARE_DYNAMIC(CInputMaterial)

public:
	CInputMaterial(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInputMaterial();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_MATERIAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString mTitle;
	int Ab;
	int Ag;
	int Ar;
	int Db;
	int Dr;
	int Dg;
	int Eb;
	int Eg;
	int Er;
	int Sr;
	int Sg;
	int Sb;
	float Shin;
	virtual BOOL OnInitDialog();
};
