// doolandDlg.h : ͷ�ļ�
//

#pragma once
#include <afxinet.h>
#include "HttpClient.h"
#include <process.h>

// CdoolandDlg �Ի���
class CdoolandDlg : public CDialog
{
// ����
public:
	CdoolandDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DOOLAND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
