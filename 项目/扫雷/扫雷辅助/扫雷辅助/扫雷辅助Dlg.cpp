
// ɨ�׸���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ɨ�׸���.h"
#include "ɨ�׸���Dlg.h"
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


// Cɨ�׸���Dlg �Ի���



Cɨ�׸���Dlg::Cɨ�׸���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cɨ�׸���Dlg::IDD, pParent)
	, m_editBase(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cɨ�׸���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_editBase);
}

BEGIN_MESSAGE_MAP(Cɨ�׸���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHUJI_GAME, &Cɨ�׸���Dlg::OnBnClickedButtonChujiGame)
	ON_BN_CLICKED(IDC_BUTTON_ZHONGJI_GAME, &Cɨ�׸���Dlg::OnBnClickedButtonZhongjiGame)
	ON_BN_CLICKED(IDC_BUTTON_READ_FLAG, &Cɨ�׸���Dlg::OnBnClickedButtonReadFlag)
	ON_BN_CLICKED(IDC_BUTTON_GAOJI_GAME, &Cɨ�׸���Dlg::OnBnClickedButtonGaojiGame)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOM, &Cɨ�׸���Dlg::OnBnClickedButtonCustom)
	ON_BN_CLICKED(IDC_BUTTONC_CLICK, &Cɨ�׸���Dlg::OnBnClickedButtoncClick)
END_MESSAGE_MAP()


// Cɨ�׸���Dlg ��Ϣ�������

BOOL Cɨ�׸���Dlg::OnInitDialog()
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

void Cɨ�׸���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cɨ�׸���Dlg::OnPaint()
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
HCURSOR Cɨ�׸���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����һ��ͨ�õĴ�ID��������
void Cɨ�׸���Dlg::OnBaseOpenMenu(int ID)
{
	HWND h = ::FindWindow(NULL, L"ɨ��");
	if (h == 0){
		::MessageBox(0, L"ɨ��û��", 0, MB_OK);
		return;
	}
	::SendMessage(h, WM_COMMAND, ID, 0);
}

//���г�����Ϸ
void Cɨ�׸���Dlg::OnBnClickedButtonChujiGame()
{
	this->OnBaseOpenMenu(0x209);
}

//�����м���Ϸ
void Cɨ�׸���Dlg::OnBnClickedButtonZhongjiGame()
{
	this->OnBaseOpenMenu(0x20A);
}

//��ȡ����
void Cɨ�׸���Dlg::OnBnClickedButtonReadFlag()
{
	HWND h = ::FindWindow(NULL, L"ɨ��");
	if (h == 0){
		::MessageBox(0, L"ɨ��û��", 0, MB_OK);
		return;
	}
	DWORD pid;
	GetWindowThreadProcessId(h, &pid); //��ȡ����ID������
	HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, false, pid);	//��һ���Ѵ��ڵĽ��̶���
	if (hp == NULL)
	{
		::MessageBox(0, L"�򿪽��̳���", 0, MB_OK);
		return;
	}
	ReadProcessMemory(hp, (LPCVOID)0x1005194, &m_editBase, 4, &pid);	//���ݽ��̾������ý��̵�ĳ���ڴ�ռ�
	UpdateData(false);
}

//�߼���Ϸ
void Cɨ�׸���Dlg::OnBnClickedButtonGaojiGame()
{
	this->OnBaseOpenMenu(0x20B);
}

//�Զ���
void Cɨ�׸���Dlg::OnBnClickedButtonCustom()
{
	this->OnBaseOpenMenu(0x20C);
}

//ģ�ⵥ��
void Cɨ�׸���Dlg::OnBnClickedButtoncClick()
{
	WORD yx[2];
	HWND h = ::FindWindow(NULL, L"ɨ��");
	if (h == 0){
		::MessageBox(0, L"ɨ��û��", 0, MB_OK);
		return;
	}
	yx[0] = 21;
	yx[1] = 62;
	::SendMessage(h, WM_LBUTTONDOWN, 1, *(int*)yx);
	::SendMessage(h, WM_LBUTTONUP, 0, *(int*)yx);
}
