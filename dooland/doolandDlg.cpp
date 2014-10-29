// doolandDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dooland.h"
#include "doolandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CdoolandDlg �Ի���




CdoolandDlg::CdoolandDlg(CWnd* pParent /*=NULL*/)
: CDialog(CdoolandDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdoolandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CdoolandDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CdoolandDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CdoolandDlg ��Ϣ�������

BOOL CdoolandDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	// ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	nTerminate=1;
	return TRUE; // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CdoolandDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
// �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
// �⽫�ɿ���Զ���ɡ�

void CdoolandDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CdoolandDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CdoolandDlg::StrcodeToStr(CString StrCode)
{
	CString ret="";
	while(StrCode.Find("\\u")>=0)
	{
		ret = ret + StrCode.Left(StrCode.Find("\\u"));
		CString uCode = StrCode.Mid( StrCode.Find("\\u")+2,4);
		StrCode =StrCode.Mid( StrCode.Find("\\u")+6,StrCode.GetLength()-6);
		 
		char *Vcodes=new char[4];
		strcpy(Vcodes,uCode);
		//79d1 31185  28672+2304+208+1
		for (int i=0;i<4;i++)
		{
			if (*(Vcodes+i)>='0'&&*(Vcodes+i)<='9')
				*(Vcodes+i)=*(Vcodes+i)-'0';
			if (*(Vcodes+i)>='a'&&*(Vcodes+i)<='f')
				*(Vcodes+i)=*(Vcodes+i)-'a'+10;
			if (*(Vcodes+i)>='A'&&*(Vcodes+i)<='F')
				*(Vcodes+i)=*(Vcodes+i)-'A'+10;
		}
		int iUcode=0;
		iUcode=iUcode+*(Vcodes)*4096;
		iUcode=iUcode+*(Vcodes+1)*256;
		iUcode=iUcode+*(Vcodes+2)*16;
		iUcode=iUcode+*(Vcodes+3);
		WCHAR Ucode=iUcode;
		char Acode[3]={'\n'}; 
		CString strUcode="";

		WideCharToMultiByte(CP_ACP, NULL, &Ucode, wcslen(&Ucode) + 1, Acode, 2, 0, 0);

		strUcode.Format("%s",Acode);
		ret=ret +strUcode;
	}
	return ret;
}
void CdoolandDlg::OnBnClickedButton1()
{
	for (int i=0;i<64;i++)
	{
		m_strKey[i]="";
		m_strString[i]="";
	}
	CString strBookID="";
	GetDlgItemText(IDC_EDIT1,strBookID);
	if (strBookID=="")
	{
		return;
	}
	CHttpClient conn; 
	CString _value;
	_value.Format("http://iphone.dooland.com/ipad/api2.php?act=getMagInfoById&id=%s&_udid=0c4ae220f9d1526d9b5a6f5914eb8434036ec667&_user_id=5754497&_user_md5=42ec6e7883858bdd069f7858c51335c0&_version=1.9&_currentmode_width=2048.000000&_appname=2048.000000&_mdcode=6f4ea",
				  strBookID); 
#ifdef RELEASEWL
	_value.Format("http://iphone.dooland.com/ipad/api2.php?act=getMagInfoById&id=%s&_udid=9f1ea9f852015c69253f96378a9f8d5e06fcd29d&_user_id=5754497&_user_md5=cafb9001e2ded6603ad16283a0f48e3d&_version=1.9&_currentmode_width=2048.000000&_appname=2048.000000&_mdcode=6f4ea",
		strBookID); 
#endif
	_value=conn.doGet(_value); 
	_value.Replace('{',' ');
	_value.Replace('}',' ');
	_value.Trim();
	int iGetStr=0;
	while(_value.Find(',')>=0||_value.Find(':')>=0)
	{
		CString StrBuffer="";
		if (_value.Find(',')>=0)
		{
			StrBuffer=_value.Left(_value.Find(',') );
			_value=_value.Mid(_value.Find(',')+1,_value.GetLength()-_value.Find(',')-1);
		}
		else
		{
			StrBuffer=_value;
			_value="";
		}
		m_strKey[iGetStr]=StrBuffer.Left(StrBuffer.Find(':'));
		m_strKey[iGetStr].Replace('\"',' ');
		m_strKey[iGetStr].Trim();
		m_strString[iGetStr]=StrBuffer.Mid(StrBuffer.Find(':')+1,StrBuffer.GetLength()-StrBuffer.Find(':')-1);
		m_strString[iGetStr].Replace('\"',' ');
		m_strString[iGetStr].Trim();
		iGetStr++;
	}

	if (iGetStr<10)
	{
		return;
	}

	CString strShow="";
	for (int i=0;i<iGetStr;i++)
	{
		if (m_strKey[i]=="")
		{
			break;
		}
		CString stradd;
		stradd.Format("%s = %s ",m_strKey[i],m_strString[i]);
		strShow=strShow+stradd+"\r\n";
	}
	SetDlgItemText(IDC_EDIT6,strShow);
	//////////////////////////////////////////////////////////////////////////
	//��������
	m_adfile_url=m_strString[findkey("adfile_url")];
	m_adfile_url.Replace("\\/","/");
	m_indexfile_url=m_strString[findkey("indexfile_url")];
	m_indexfile_url.Replace("\\/","/");
	m_s_pic=m_strString[findkey("s_pic")];
	m_s_pic.Replace("\\/","/");
	m_xfile_url=m_strString[findkey("xfile_url")];
	m_xfile_url.Replace("\\/","/");

	//�滻Key
	m_strKey[findkey("adfile_url")]="adfilename";
	m_strKey[findkey("indexfile_url")]="indexfilename";
	m_strKey[findkey("id")]="pk";
	m_strKey[findkey("xfile_url")]="xfilename";
	//�滻string
	int itemp=0;
	itemp=findkey("adfilename"); 
	m_strString[itemp]=m_strString[itemp].Mid(
		m_strString[itemp].ReverseFind('/')+1,
		m_strString[itemp].GetLength()-m_strString[itemp].ReverseFind('/')-1);

	itemp=findkey("indexfilename"); 
	m_strString[itemp]=m_strString[itemp].Mid(
		m_strString[itemp].ReverseFind('/')+1,
		m_strString[itemp].GetLength()-m_strString[itemp].ReverseFind('/')-1);

	itemp=findkey("s_pic"); 
	m_strString[itemp]=m_strString[itemp].Mid(
		m_strString[itemp].ReverseFind('/')+1,
		m_strString[itemp].GetLength()-m_strString[itemp].ReverseFind('/')-1);

	itemp=findkey("xfilename"); 
	m_strString[itemp]=m_strString[itemp].Mid(
		m_strString[itemp].ReverseFind('/')+1,
		m_strString[itemp].GetLength()-m_strString[itemp].ReverseFind('/')-1);

	itemp=findkey("sort_name");
	m_strString[itemp]=StrcodeToStr(m_strString[itemp]);

	itemp=findkey("title");
	m_strString[itemp]=StrcodeToStr(m_strString[itemp]);

	//����XML
	m_strXML=m_strXML+"	<dict>\r\n";
	m_strXML=m_strXML+"		<key>add_date</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("add_date")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>adfilename</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("adfilename")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>des</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("des")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>file_size</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("file_size")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>filename</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("filename")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>indexfile_size</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("indexfile_size")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>indexfilename</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("indexfilename")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>m_type</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("m_type")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>mp3_filepath</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("mp3_filepath")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>pic_size</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("pic_size")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>pk</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("pk")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>s_pic</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("s_pic")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>sort_id</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("sort_id")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>sort_name</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("sort_name")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>title</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("title")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>xfile_size</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("xfile_size")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>xfilename</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("xfilename")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>xflag</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("xflag")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>xmp3_filename</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("xmp3_filename")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>xmp3_size</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("xmp3_size")]+"</string>\r\n";
	m_strXML=m_strXML+"		<key>xtype</key>\r\n";
	m_strXML=m_strXML+"		<string>"+m_strString[findkey("xtype")]+"</string>\r\n";
	m_strXML=m_strXML+"	</dict>\r\n";

	//��ʾ��д��XML
	
	SetDlgItemText(IDC_EDIT2,m_strXML);
	CFile fDestFile; 
	CreateDirectory(".\\"+m_strString[findkey("title")],NULL);
 
	fDestFile.Open(".\\"+m_strString[findkey("title")]+"\\add_XML.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary); 
	fDestFile.Write(m_strXML, m_strXML.GetLength()); // ��ʵ������д���ļ� 
	fDestFile.Close();

	//��ʼ����
	nTerminate=0;
	h_downProc =(HANDLE ) _beginthreadex(NULL,0,DownloadFile,(LPVOID)this,0,NULL);
}
int CdoolandDlg::findkey(CString strKey)
{
	for (int i=0;i<63;i++)
	{
		if (m_strKey[i]==strKey)
		{
			return i;
		}
	}
	return 63;
}
//CFile file("C:\\Users\\Kay\\Desktop\\dooland\\bin\\test.swf",CFile::modeRead);
//char *pBuf;
//int iLen = file.GetLength();
//pBuf = new char [iLen+1];
//file.Read(pBuf,iLen);
//pBuf[iLen]=0;
//file.Close();
//char a,b,c;
//int ipage=0;
//for (int i=0;i<iLen-3;i++)
//{
//	a=pBuf[i];
//	b=pBuf[i+1];
//	c=pBuf[i+2];
//	if (a=='C'&&b=='W'&&c=='S')
//	{
//		CString str_name;
//		str_name.Format("C:\\Users\\Kay\\Desktop\\dooland\\bin\\%d.swf",++ipage);
//		CFile file(str_name,CFile::modeCreate | CFile::modeWrite);
//		file.Write( &pBuf[i],iLen-i);
//		file.Close();
//	}
//}

BOOL CdoolandDlg::InternetDownload(const CString &strURL, const CString &strFN) 
{
	CInternetSession internetSession(NULL,0); 
	//	CString myData; 
	BOOL bSucceed = TRUE; 
	try 
	{ 
		CStdioFile * pFile = internetSession.OpenURL(strURL); 
		if(pFile != NULL) 
		{ 
			CFile cf; 
			if(!cf.Open(strFN, CFile::modeCreate | CFile::modeWrite, NULL)) 
			{ 
				return FALSE; 
			} 
			BYTE *Buffer;
			Buffer = new BYTE [256*1024*1024];
			ZeroMemory(Buffer, sizeof(Buffer));	
			int nReadLen = 0; 
			while((nReadLen = pFile-> Read(Buffer, sizeof(Buffer))) > 0) 
			{ 
				cf.Write(Buffer, nReadLen); 
			} 
			cf.Close(); 
			pFile-> Close() ; 
			delete pFile; 
		} 
	} 
	catch (CInternetException& e) 
	{ 
		char szBuffer[128]; 
		ZeroMemory(szBuffer, sizeof(szBuffer)); 
		e.GetErrorMessage(szBuffer, sizeof(szBuffer), NULL); 
		TRACE( "InternetDownload, Exception: %s\n ",szBuffer); 
	} 
	catch(...) 
	{ 
		TRACE( "InternetDownload, Exception: ...\n "); 
	} 
	internetSession.Close() ; 
	if(!bSucceed) 
		DeleteFile(strFN); 
	return bSucceed; 
}


UINT WINAPI  CdoolandDlg::DownloadFile(LPVOID lpParameter) 
{
	CdoolandDlg* pwnd = (CdoolandDlg*)lpParameter; 

	pwnd->GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	pwnd->DownFile(pwnd->m_adfile_url,
		pwnd->m_strString[pwnd->findkey("adfilename")],
		pwnd->m_strString[pwnd->findkey("title")]);
	pwnd->DownFile(pwnd->m_indexfile_url,
		pwnd->m_strString[pwnd->findkey("indexfilename")],
		pwnd->m_strString[pwnd->findkey("title")]);
	pwnd->DownFile(pwnd->m_s_pic,
		pwnd->m_strString[pwnd->findkey("s_pic")],
		pwnd->m_strString[pwnd->findkey("title")]);
	pwnd->DownFile(pwnd->m_xfile_url,
		pwnd->m_strString[pwnd->findkey("xfilename")],
		pwnd->m_strString[pwnd->findkey("title")]);
	pwnd->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	pwnd->SetWindowText(pwnd->m_strString[pwnd->findkey("title")]+"|| �������"); 
	return 0; 
} 

void CdoolandDlg::DownFile(CString szFileURL,CString szFileName,CString BookName)
{ 
	CProgressCtrl* m_Prog =(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1); 
	CButton* bStart = (CButton*)GetDlgItem(IDC_BUTTON1); 
	char filebuf[512]; 
	int outfs=0; 
	CHttpFile* myHttpFile;
	CStdioFile *fTargFile; 
	CInternetSession netSession; 
	netSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);      // 5������ӳ�ʱ
	netSession.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 1000);           // 1��ķ��ͳ�ʱ
	netSession.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 7000);        // 7��Ľ��ճ�ʱ
	netSession.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 1000);     // 1��ķ��ͳ�ʱ
	netSession.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 7000);   // 7��Ľ��ճ�ʱ
	netSession.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);          // 1������

	CString szFile=szFileURL,FileSize="",KBin="",KBsec="",NewName=szFileName,Perc=""; 
	int nDownloaded=0;
	fTargFile=NULL;
	try 
	{   
		SetDlgItemText(IDC_EDIT7,BookName+"||"+szFileName+"||����У�����ص�ַ..."); 
		this->SetWindowText(BookName+"||"+szFileName+"||����У�����ص�ַ...");
		myHttpFile = (CHttpFile*)netSession.OpenURL(szFile,1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD); 

		CString queryinfo;
		myHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,queryinfo);
		int filesize = atoi(queryinfo);
		fTargFile  =myHttpFile; 
		COleDateTime dlStart = COleDateTime::GetCurrentTime(); 
		//fTargFile->SeekToBegin(); 
		outfs = filesize / 1024; // �����ļ���С��ǧ�ֽڣ� 
		FileSize.Format("%d",outfs); // ��KBΪ��λ��ʽ�ļ���С 

		// �ڵ�ǰĿ¼�����µ�Ŀ���ļ� 
		CFile fDestFile;
		CreateDirectory(".\\"+BookName,NULL);
		fDestFile.Open(".\\"+BookName+"\\"+szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary); 
		int byteswrite=0; // д���ļ����ֽ��� 
		int pos = 0; // ��ǰ��������λ�� 
		int nperc=0,kbrecv=0; // �������İٷֱ�,��ȡ�������ݴ�С��KbsΪ��λ�� 
		double secs=0,kbsec=0; // ��¼����, �ٶȣ�KB/�룩 

		// ����ļ���̫�������̴��ڵı��Ⲣ��״̬��ʾ 
		NewName = fTargFile->GetFileName(); // ��ȡ���ļ��� 

		if(fTargFile->GetFileName().GetLength() >= 10) 
		{ 
			NewName = fTargFile->GetFileName().Mid(0,7); // �ָ��ļ� 
			NewName = NewName + "..."; 
		} 

		SetDlgItemText(IDC_EDIT7,BookName+"||"+szFileName+"||��������..."); 
		this->SetWindowText(BookName+"||"+szFileName+"||��������...");
		m_Prog->SetRange32(0,filesize); 

		while (byteswrite = fTargFile->Read(filebuf, 512)) // ��ȡ�ļ� 
		{ 
			if(nTerminate == 1) // ������ȡ������ 
			{ 
				fDestFile.Close(); // �ر����ǵ�Ŀ���ļ� 
				fTargFile->Close(); // �ر�Զ���ļ� 
				delete fTargFile; // ɾ��CStdioFile�����Է�ֹй© 
				SetDlgItemText(IDC_EDIT7,BookName+":"+szFileName+"||����ʱ�ѱ��û�ȡ����"); // Set satus bar text
				this->SetWindowText(BookName+":"+szFileName+"||����ʱ�ѱ��û�ȡ����"); 
				AfxEndThread(0); // ���������߳� 
			} 

			// ���ݿ�ʼʱ���뵱ǰʱ��Ƚϣ���ȡ���� 
			COleDateTimeSpan dlElapsed = COleDateTime::GetCurrentTime() - dlStart; 
			secs = dlElapsed.GetTotalSeconds(); 
			pos += byteswrite; // �����µĽ�����λ�� 
			fDestFile.Write(filebuf, byteswrite); // ��ʵ������д���ļ� 
			m_Prog->SetPos(pos); 

			nperc =( pos * 100 )/ filesize ; // ���Ȱٷֱ� 
			kbrecv = pos / 1024; // ��ȡ�յ������� 
			kbsec = kbrecv / secs; // ��ȡÿ�����ض��٣�KB�� 

			//nperc=kbrecv/filesize;
			Perc.Format("%d",nperc); // ��ʽ�����Ȱٷֱ� 
			KBin.Format("%d",kbrecv); // ��ʽ�����������ݴ�С��KB�� 
			KBsec.Format("%d",(int)kbsec); // ��ʽ�������ٶȣ�KB/�룩 
 
			CString xpos = KBin + "/"+FileSize;
			SetDlgItemText(IDC_EDIT3,xpos + "KB"); // �����ش�С 
			SetDlgItemText(IDC_EDIT4,KBsec + "KB/��"); // �����ٶ� 
			SetDlgItemText(IDC_EDIT5,Perc + "%"); // ���Ȱٷֱ� 
		} 
		// ������ɣ��ر��ļ� 
		fDestFile.Close(); 
		SetDlgItemText(IDC_EDIT5,100 + "%"); // ���Ȱٷֱ� 
		nDownloaded = 1; 
	} 

	catch(CInternetException *IE) 
	{ 
		CString strerror; 
		TCHAR szerror[255]={0}; 

		IE->GetErrorMessage(szerror,255); // ��ȡ������Ϣ 
		strerror = szerror; 

		SetDlgItemText(IDC_EDIT7,strerror); 
		nDownloaded = 0; 
		IE->Delete(); // ɾ���쳣�����Է�ֹй© 
	} 
	delete fTargFile; 


	if(nDownloaded == 1) 
	{ 
		SetDlgItemText(IDC_EDIT7,"������ɣ�"); 
		bStart->EnableWindow(TRUE); 
	} 
	else
	{
		SetDlgItemText(IDC_EDIT7,"����ʧ�ܣ�"); 
	}
}