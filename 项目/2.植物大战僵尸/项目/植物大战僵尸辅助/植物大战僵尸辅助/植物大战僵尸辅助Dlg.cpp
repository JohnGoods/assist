
// ֲ���ս��ʬ����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ֲ���ս��ʬ����.h"
#include "ֲ���ս��ʬ����Dlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

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
//	ON_WM_TIMER()
ON_WM_TIMER()
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
	SetTimer(1, 500, NULL);
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
		::MessageBox(0, L"��Ϸδ��,�����˳�", 0, MB_OK);
		exit(0);
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
		::MessageBox(0, L"�򿪽��̳���,�����˳�", 0, MB_OK);
		exit(0);
		return NULL;
	}
	return hp;
}

void Cֲ���ս��ʬ����Dlg::OnBnClickedCheckCd()
{
	UpdateData(true);//���´���״̬������
}

void Cֲ���ս��ʬ����Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnTimer(nIDEvent);
	switch (nIDEvent)
	{
	case 1:     
		if (m_b_CD)	//��ѡȥ��CD
		{   //���õ���ȴʱ��
			for (int i = 0; i < 10; i++){
				HANDLE hp = GetGameProcessHandle();
				DWORD buf = 0, byread, bywrite;
				ReadProcessMemory(hp, (PVOID)0x755E0C, &buf, sizeof(buf), &byread);
				ReadProcessMemory(hp, (PVOID)(buf + 0x868), &buf, sizeof(buf), &byread);
				ReadProcessMemory(hp, (PVOID)(buf + 0x15C), &buf, sizeof(buf), &byread)      ;
				int tmp = 0x00000000;
				int deviation = 0;
				deviation = 0x50 + 0x50 * i;
				/*if (i == 0){
					deviation = 0x50;
				}
				else if (i == 1){
					deviation = 0xA0;
				}
				else if (i == 2){
					deviation = 0xF0;
				}
				else if (i == 3){
					deviation = 0x140;
				}
				else if (i == 4){
					deviation = 0x190;
				}
				else if (i == 5){
					deviation = 0x1E0;
				}
				else if (i == 6){
					deviation = 0x230;
				}
				else if (i == 7){
					deviation = 0x280;
				}
				else if (i == 8){
					deviation = 0x2D0;
				}
				else if (i == 9){
					deviation = 0x320;
				}*/
				WriteProcessMemory(hp, (PVOID)(buf + deviation), &tmp, sizeof(buf), &byread);
			}
		}
		break;
		case 2:

		break;
	}
}