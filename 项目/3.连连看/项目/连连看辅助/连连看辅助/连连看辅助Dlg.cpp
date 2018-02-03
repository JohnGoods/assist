
// ����������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����������.h"
#include "����������Dlg.h"
#include "afxdialogex.h"
#include "GameProc.h"

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


// C����������Dlg �Ի���



C����������Dlg::C����������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C����������Dlg::IDD, pParent)
	, m_edit_x(0)
	, m_edit_y(0)
	, m_edit_seat(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C����������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_x, m_edit_x);
	DDX_Text(pDX, IDC_EDIT_y, m_edit_y);
	DDX_Text(pDX, IDC_EDIT_SEAT, m_edit_seat);
}

BEGIN_MESSAGE_MAP(C����������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &C����������Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SEAT, &C����������Dlg::OnBnClickedButtonSeat)
END_MESSAGE_MAP()


// C����������Dlg ��Ϣ�������

BOOL C����������Dlg::OnInitDialog()
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

void C����������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C����������Dlg::OnPaint()
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
HCURSOR C����������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//HWND gameh;
//RECT r1;
void C����������Dlg::OnBnClickedButtonStart()
{
	//// TODO: Add your control notification handler code here
	////��ȡ��Ϸ���ھ��
	//gameh = ::FindWindow(NULL, L"QQ��Ϸ - ��������ɫ��");
	//::GetWindowRect(gameh, &r1);
	//this->m_edit_x = r1.left; this->m_edit_y = r1.top;
	//UpdateData(false);
	////�������ָ��λ��  ȡ������������:x=655;y=577 //lparam 0x0241028f
	//SetCursorPos(655 + r1.left, 577 + r1.top);
	startGame();
}

//const PCHAR gameCaption = L("QQ��Ϸ - ��������ɫ��");
void C����������Dlg::OnBnClickedButtonSeat()
{
	// ��Ϸ���ڱ��⣺"QQ��Ϸ - ��������ɫ��"
	// 1��FindWindow               //��ȡ���ھ��
	//2��GetWindowThreadProcessId //��ȡ���ڽ���ID
	//3��OpenProcess              //��ָ������
	//4��ReadProcessMemory        //��ָ������ �ڴ�����
	//��ȡ���ھ��
	HWND gameh = ::FindWindow(NULL, L"QQ��Ϸ - ��������ɫ��");
	//��ȡ���ڽ���ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//��ָ������
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//��ָ������ �ڴ�����
	DWORD byread;
	LPCVOID pbase = (LPCVOID)0x00171618;
	LPVOID  nbuffer = (LPVOID)&m_edit_seat;
	::ReadProcessMemory(processH, pbase, nbuffer, 4, &byread);
	UpdateData(false); //���±�����ֵ�� �༭��
}
