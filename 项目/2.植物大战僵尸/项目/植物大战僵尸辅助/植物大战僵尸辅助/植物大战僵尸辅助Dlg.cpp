
// ֲ���ս��ʬ����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ֲ���ս��ʬ����.h"
#include "ֲ���ս��ʬ����Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cֲ���ս��ʬ����Dlg �Ի���



Cֲ���ս��ʬ����Dlg::Cֲ���ս��ʬ����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cֲ���ս��ʬ����Dlg::IDD, pParent)
	, m_b_CD(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cֲ���ս��ʬ����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CD, m_b_CD);
}

BEGIN_MESSAGE_MAP(Cֲ���ս��ʬ����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CD, &Cֲ���ս��ʬ����Dlg::OnBnClickedCheckCd)
END_MESSAGE_MAP()


// Cֲ���ս��ʬ����Dlg ��Ϣ�������

BOOL Cֲ���ս��ʬ����Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cֲ���ս��ʬ����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cֲ���ս��ʬ����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cֲ���ս��ʬ����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�������̷���Ȩ��   
bool EnableDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return false;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		CloseHandle(hToken);
		return false;
	}
	return true;
}

HANDLE GetGameProcessHandle(){
	HWND h = ::FindWindow(NULL, L"Plants vs. Zombies");
	if (h == 0)
	{
		::MessageBox(0, L"��Ϸδ��", 0, MB_OK);
		return NULL;
	}
	//1005194
	DWORD pid, bywrite;
	GetWindowThreadProcessId(h, &pid);
	//GetWindowThreadProcessId
	//OpenProcss
	EnableDebugPriv();//��������Ȩ�� VS2008�Ժ�İ汾����Ҫ
	HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	//
	if (hp == NULL)
	{
		::MessageBox(0, L"�򿪽��̳���", 0, MB_OK);
		return NULL;
	}
	return hp;
}

void Cֲ���ս��ʬ����Dlg::OnBnClickedCheckCd()
{
	UpdateData(true);//���´���״̬������
	UCHAR buf[2];
	
	HANDLE hp = GetGameProcessHandle();
	//��ȡ���� 
	DWORD  bywrite;
	if (m_b_CD)
	{   //���õ���ȴʱ��
		//0x0049DDE6 - 75 4
		//	90 90
		buf[0] = 0x90;
		buf[1] = 0x90;
	}
	else
	{   //������ȴʱ��
		//0x0049DDE6 - 75 4  
		buf[0] = 0x75;
		buf[1] = 0x4;
		//0x4
	}
	//��buf������д�� 0x0487296
	WriteProcessMemory(hp, (LPVOID)0x0049DDE6, buf, sizeof(buf), &bywrite);
	//WriteProcessMemory(hp, (LPVOID)0x0049DDE6, buf, sizeof(buf), &bywrite);
}
