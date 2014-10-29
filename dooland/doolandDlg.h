// doolandDlg.h : 头文件
//

#pragma once
#include <afxinet.h>
#include "HttpClient.h"
#include <process.h>

// CdoolandDlg 对话框
class CdoolandDlg : public CDialog
{
// 构造
public:
	CdoolandDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DOOLAND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	BOOL InternetDownload(const CString &strURL, const CString &strFN) ;
	
	void ValueToChars(void *_strKey,void *_strVale,CString _value);
	CString StrcodeToStr(CString StrCode);

	CString m_strKey[64];
	CString m_strString[64];
	CString m_strXML;
	int findkey(CString strKey);
	CString m_adfile_url;
	CString m_indexfile_url;
	CString m_s_pic;
	CString m_xfile_url;
	static UINT  WINAPI DownloadFile(LPVOID lpParameter);
	void DownFile(CString szFileURL,CString szFileName,CString BookName);
	HANDLE h_downProc;
	int nTerminate;
};
