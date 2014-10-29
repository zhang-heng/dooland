// doolandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dooland.h"
#include "doolandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

	// 实现
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


// CdoolandDlg 对话框




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


// CdoolandDlg 消息处理程序

BOOL CdoolandDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	// 执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	nTerminate=1;
	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
// 来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
// 这将由框架自动完成。

void CdoolandDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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
	//下载链接
	m_adfile_url=m_strString[findkey("adfile_url")];
	m_adfile_url.Replace("\\/","/");
	m_indexfile_url=m_strString[findkey("indexfile_url")];
	m_indexfile_url.Replace("\\/","/");
	m_s_pic=m_strString[findkey("s_pic")];
	m_s_pic.Replace("\\/","/");
	m_xfile_url=m_strString[findkey("xfile_url")];
	m_xfile_url.Replace("\\/","/");

	//替换Key
	m_strKey[findkey("adfile_url")]="adfilename";
	m_strKey[findkey("indexfile_url")]="indexfilename";
	m_strKey[findkey("id")]="pk";
	m_strKey[findkey("xfile_url")]="xfilename";
	//替换string
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

	//处理XML
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

	//显示并写入XML
	
	SetDlgItemText(IDC_EDIT2,m_strXML);
	CFile fDestFile; 
	CreateDirectory(".\\"+m_strString[findkey("title")],NULL);
 
	fDestFile.Open(".\\"+m_strString[findkey("title")]+"\\add_XML.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary); 
	fDestFile.Write(m_strXML, m_strXML.GetLength()); // 将实际数据写入文件 
	fDestFile.Close();

	//开始下载
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
	pwnd->SetWindowText(pwnd->m_strString[pwnd->findkey("title")]+"|| 下载完成"); 
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
	netSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);      // 5秒的连接超时
	netSession.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 1000);           // 1秒的发送超时
	netSession.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 7000);        // 7秒的接收超时
	netSession.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 1000);     // 1秒的发送超时
	netSession.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 7000);   // 7秒的接收超时
	netSession.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);          // 1次重试

	CString szFile=szFileURL,FileSize="",KBin="",KBsec="",NewName=szFileName,Perc=""; 
	int nDownloaded=0;
	fTargFile=NULL;
	try 
	{   
		SetDlgItemText(IDC_EDIT7,BookName+"||"+szFileName+"||正在校验下载地址..."); 
		this->SetWindowText(BookName+"||"+szFileName+"||正在校验下载地址...");
		myHttpFile = (CHttpFile*)netSession.OpenURL(szFile,1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD); 

		CString queryinfo;
		myHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,queryinfo);
		int filesize = atoi(queryinfo);
		fTargFile  =myHttpFile; 
		COleDateTime dlStart = COleDateTime::GetCurrentTime(); 
		//fTargFile->SeekToBegin(); 
		outfs = filesize / 1024; // 计算文件大小（千字节） 
		FileSize.Format("%d",outfs); // 以KB为单位格式文件大小 

		// 在当前目录创建新的目标文件 
		CFile fDestFile;
		CreateDirectory(".\\"+BookName,NULL);
		fDestFile.Open(".\\"+BookName+"\\"+szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary); 
		int byteswrite=0; // 写入文件的字节数 
		int pos = 0; // 当前进度条的位置 
		int nperc=0,kbrecv=0; // 进度条的百分比,获取到的数据大小（Kbs为单位） 
		double secs=0,kbsec=0; // 记录秒数, 速度（KB/秒） 

		// 如果文件名太长，缩短窗口的标题并在状态显示 
		NewName = fTargFile->GetFileName(); // 获取新文件名 

		if(fTargFile->GetFileName().GetLength() >= 10) 
		{ 
			NewName = fTargFile->GetFileName().Mid(0,7); // 分割文件 
			NewName = NewName + "..."; 
		} 

		SetDlgItemText(IDC_EDIT7,BookName+"||"+szFileName+"||正在下载..."); 
		this->SetWindowText(BookName+"||"+szFileName+"||正在下载...");
		m_Prog->SetRange32(0,filesize); 

		while (byteswrite = fTargFile->Read(filebuf, 512)) // 读取文件 
		{ 
			if(nTerminate == 1) // 如果点击取消下载 
			{ 
				fDestFile.Close(); // 关闭我们的目标文件 
				fTargFile->Close(); // 关闭远程文件 
				delete fTargFile; // 删除CStdioFile对象，以防止泄漏 
				SetDlgItemText(IDC_EDIT7,BookName+":"+szFileName+"||下载时已被用户取消！"); // Set satus bar text
				this->SetWindowText(BookName+":"+szFileName+"||下载时已被用户取消！"); 
				AfxEndThread(0); // 结束下载线程 
			} 

			// 根据开始时间与当前时间比较，获取秒数 
			COleDateTimeSpan dlElapsed = COleDateTime::GetCurrentTime() - dlStart; 
			secs = dlElapsed.GetTotalSeconds(); 
			pos += byteswrite; // 设置新的进度条位置 
			fDestFile.Write(filebuf, byteswrite); // 将实际数据写入文件 
			m_Prog->SetPos(pos); 

			nperc =( pos * 100 )/ filesize ; // 进度百分比 
			kbrecv = pos / 1024; // 获取收到的数据 
			kbsec = kbrecv / secs; // 获取每秒下载多少（KB） 

			//nperc=kbrecv/filesize;
			Perc.Format("%d",nperc); // 格式化进度百分比 
			KBin.Format("%d",kbrecv); // 格式化已下载数据大小（KB） 
			KBsec.Format("%d",(int)kbsec); // 格式化下载速度（KB/秒） 
 
			CString xpos = KBin + "/"+FileSize;
			SetDlgItemText(IDC_EDIT3,xpos + "KB"); // 已下载大小 
			SetDlgItemText(IDC_EDIT4,KBsec + "KB/秒"); // 下载速度 
			SetDlgItemText(IDC_EDIT5,Perc + "%"); // 进度百分比 
		} 
		// 下载完成，关闭文件 
		fDestFile.Close(); 
		SetDlgItemText(IDC_EDIT5,100 + "%"); // 进度百分比 
		nDownloaded = 1; 
	} 

	catch(CInternetException *IE) 
	{ 
		CString strerror; 
		TCHAR szerror[255]={0}; 

		IE->GetErrorMessage(szerror,255); // 获取错误消息 
		strerror = szerror; 

		SetDlgItemText(IDC_EDIT7,strerror); 
		nDownloaded = 0; 
		IE->Delete(); // 删除异常对象，以防止泄漏 
	} 
	delete fTargFile; 


	if(nDownloaded == 1) 
	{ 
		SetDlgItemText(IDC_EDIT7,"下载完成！"); 
		bStart->EnableWindow(TRUE); 
	} 
	else
	{
		SetDlgItemText(IDC_EDIT7,"下载失败！"); 
	}
}