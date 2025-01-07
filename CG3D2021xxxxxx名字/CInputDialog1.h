#pragma once
#include "afxdialogex.h"


// CInputDialog1 对话框

class CInputDialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog1)

public:
	CInputDialog1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInputDialog1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDC_INPUT_VALUE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mValue1;
	CString mValue2;
	CString mValue3;
	virtual BOOL OnInitDialog();
	CString mTitle;
	afx_msg void OnBnClickedOk();
};
