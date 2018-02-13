
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
	, m_edit_chess_data(_T(""))
	, m_p1x(0)
	, m_p1y(0)
	, m_p2x(0)
	, m_p2y(0)
	, m_autoplay(FALSE)
	, m_autostart(FALSE)
	, m_sliderenable(FALSE)
	, m_gametop(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C����������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_x, m_edit_x);
	DDX_Text(pDX, IDC_EDIT_y, m_edit_y);
	DDX_Text(pDX, IDC_EDIT_SEAT, m_edit_seat);
	DDX_Text(pDX, IDC_EDIT_CHESS_DATA, m_edit_chess_data);
	DDX_Text(pDX, IDC_EDIT1, m_p1x);
	DDX_Text(pDX, IDC_EDIT2, m_p1y);
	DDX_Text(pDX, IDC_EDIT3, m_p2x);
	DDX_Text(pDX, IDC_EDIT4, m_p2y);
	DDX_Check(pDX, IDC_CHECK_CHECK_PLAY_GAME, m_autoplay);
	DDX_Check(pDX, IDC_CHECK_CHECK_START, m_autostart);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_ctl_slider);
	DDX_Control(pDX, IDC_CHECK_SPEED, m_ctl_check);
	DDX_Check(pDX, IDC_CHECK_SPEED, m_sliderenable);
	DDX_Check(pDX, IDC_CHECK_TOP, m_gametop);
}

BEGIN_MESSAGE_MAP(C����������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &C����������Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SEAT, &C����������Dlg::OnBnClickedButtonSeat)
	ON_BN_CLICKED(IDC_BUTTON_CHAT_DATA, &C����������Dlg::OnBnClickedButtonChatData)
	ON_BN_CLICKED(IDC_BUTTON_CLICK, &C����������Dlg::OnBnClickedButtonClick)
	ON_BN_CLICKED(IDC_BUTTON_SINGLE, &C����������Dlg::OnBnClickedButtonSingle)
	ON_BN_CLICKED(IDC_CHECK_CHECK_START, &C����������Dlg::OnBnClickedCheckCheckStart)
	ON_BN_CLICKED(IDC_CHECK_CHECK_PLAY_GAME, &C����������Dlg::OnBnClickedCheckCheckPlayGame)
	ON_BN_CLICKED(IDC_CHECK_SPEED, &C����������Dlg::OnBnClickedCheckSpeed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPEED, &C����������Dlg::OnNMCustomdrawSliderSpeed)
	ON_BN_CLICKED(IDC_CHECK_TOP, &C����������Dlg::OnBnClickedCheckTop)
	ON_BN_CLICKED(IDC_CHECK_TIME, &C����������Dlg::OnBnClickedCheckTime)
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
	MoveWindow(0, 0, 330, 200, true);
	this->m_ctl_slider.SetRange(50, 3000);
	this->m_ctl_slider.SetTicFreq(150);
	this->m_ctl_slider.SetPos(1000);
	this->m_ctl_check.SetCheck(true);

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

//const PCHAR gameCaption = "QQ��Ϸ - ��������ɫ��";
void C����������Dlg::OnBnClickedButtonSeat()
{
	// ��Ϸ���ڱ��⣺"QQ��Ϸ - ��������ɫ��"
	// 1��FindWindow               //��ȡ���ھ��
	//2��GetWindowThreadProcessId //��ȡ���ڽ���ID
	//3��OpenProcess              //��ָ������
	//4��ReadProcessMemory        //��ָ������ �ڴ�����
	//��ȡ���ھ��
	HWND gameh = ::FindWindow(NULL, gameHandle);
	//��ȡ���ڽ���ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//��ָ������
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//��ָ������ �ڴ�����
	DWORD byread;
	LPCVOID pbase = (LPCVOID)SEAT_ADDRESS;		//��λ
	LPVOID  nbuffer = (LPVOID)&m_edit_seat;
	::ReadProcessMemory(processH, pbase, nbuffer, 4, &byread);
	UpdateData(false); //���±�����ֵ�� �༭��
}

void C����������Dlg::OnBnClickedButtonChatData()
{
	// TODO: Add your control notification handler code here
	//��ȡ���ھ��
	HWND gameh = ::FindWindow(NULL, gameHandle);
	//��ȡ���ڽ���ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//��ָ������
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//��ָ������ �ڴ�����
	DWORD byread;
	LPCVOID pbase = (LPCVOID)CHESSBOARD_ADDRESS; //�������ݻ�ַ
	LPVOID  nbuffer = (LPVOID)&chessdata;    //�����������
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);
	///��ʾ��������
	char buf[11];
	m_edit_chess_data = ""; //��ձ༭
	for (int y = 0; y <= 10; y++)
	{
		for (int x = 0; x <= 18; x++) //��һ��
		{
			_itoa_s(chessdata[y][x], buf, 16); //ת�����ִ�
			m_edit_chess_data += buf;
			m_edit_chess_data += " ";
		}
		//����
		m_edit_chess_data += "\r\n";
	}
	UpdateData(false);
}

void C����������Dlg::OnBnClickedButtonClick()
{

	int   x = 22, y = 187;
	HWND hwnd = ::FindWindow(NULL, gameHandle);
	int lparam;
	lparam = (y << 16) + x + 31 * 0;//��ʾָ����
	::SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	::SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);  //
}

//bool C����������Dlg::ClearPiar() //�ѵ����������µ�������
//{
//	//��������������chessdata 11,19
//	updatdChess();
//	//������������ �ҳ���ͬ���� һ������
//	POINT p1, p2;
//	int x1, y1, x2, y2;
//	for (y1 = 0; y1<11; y1++)
//	for (x1 = 0; x1<19; x1++)
//	{
//		for (y2 = y1; y2<11; y2++)
//		for (x2 = 0; x2<19; x2++)
//		if ((chessdata[y1][x1] == chessdata[y2][x2]) // ����1������2 �����Ƿ���ͬ
//			&& (!((x1 == x2) && (y1 == y2)))  //Ҫ���1���2 ������
//			)
//		{
//			p1.x = x1; p1.y = y1;
//			p2.x = x2; p2.y = y2;
//			//��� ��ͬ��2�������Ƿ������
//			if (Check2p(p1, p2))//��������� �򷵻���
//			{
//				//click2p ���ģ�� ��� p1��p2
//				Click2p(p1, p2);
//				m_p1x = x1;
//				m_p1y = y1;
//				m_p2x = x2;
//				m_p2y = y2;
//				UpdateData(false);//��������������
//				return true;
//
//			}
//		}
//	}
//	return false;
//}


//������ť
void C����������Dlg::OnBnClickedButtonSingle()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ClearPiar();
}


//�Զ���Ϸ
VOID CALLBACK playproc(
	HWND hwnd,     // handle of window for timer messages
	UINT uMsg,     // WM_TIMER message
	UINT idEvent,  // timer identifier
	DWORD dwTime   // current system time
	)
{
	ClearPiar();
}

//�Զ�׼��
VOID CALLBACK strartproc(
	HWND hwnd,     // handle of window for timer messages
	UINT uMsg,     // WM_TIMER message
	UINT idEvent,  // timer identifier
	DWORD dwTime   // current system time
	)
{
	HWND gameh = ::FindWindow(NULL, gameHandle);
	if (gameh == 0) { return; } //û���ҵ���Ϸ����

	if (gametop)
	{
		SetWindowPos(gameh, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
	else
	{
		SetWindowPos(gameh, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	}

	//SetWindowPos(gameh, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	startGame(); //�Զ�����
}

VOID CALLBACK topproc(
	HWND hwnd,     // handle of window for timer messages
	UINT uMsg,     // WM_TIMER message
	UINT idEvent,  // timer identifier
	DWORD dwTime   // current system time
	)
{
	/*if (gametop && BST_CHECKED == IsDlgButtonChecked(NULL, IDC_CHECK_TOP)){
		return;
	}*/
	gametop = false;
	if (BST_CHECKED == IsDlgButtonChecked(NULL,IDC_CHECK_TOP))
	{
		gametop = true;
	}

	if (gametop)
	{
		HWND gameh = ::FindWindow(NULL, gameHandle);
		if (gameh == 0) { return; } //û���ҵ���Ϸ����
		//����Ϸ�����ö�
		::SetWindowPos(gameh, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}//�����ö�
	else
	{
		HWND gameh = ::FindWindow(NULL, gameHandle);
		if (gameh == 0) { return; } //û���ҵ���Ϸ����
		//����Ϸ�����ö�
		::SetWindowPos(gameh, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}//�����ö�
}

const int PLAYID = 111;
const int STARTID = 112;
const int TOP = 113;

//�Զ�����
void C����������Dlg::OnBnClickedCheckCheckStart()
{
	UpdateData(true);//���´�������������
	if (m_autostart)
	{
		SetTimer(STARTID, 3 * 1000, &strartproc);
	}
	else
	{
		KillTimer(STARTID);
	}
}

//�Զ���Ϸ
void C����������Dlg::OnBnClickedCheckCheckPlayGame()
{
	UpdateData(true);//���´�������������
	if (m_autoplay)
	{
		SetTimer(PLAYID, this->m_ctl_slider.GetPos(), &playproc);
	}
	else
	{
		KillTimer(PLAYID);
	}
}

//���ڶ���
void C����������Dlg::OnBnClickedCheckTop()
{
	//���´�������������
	UpdateData(true);
	if (m_gametop)
	{
		SetTimer(TOP, 1000, &topproc);
	}
	else
	{
		KillTimer(TOP);
	}

	//gametop = m_gametop;
	//if (m_gametop)
	//{
	//	HWND gameh = ::FindWindow(NULL, gameHandle);
	//	if (gameh == 0) { return; } //û���ҵ���Ϸ����
	//	//����Ϸ�����ö�
	//	::SetWindowPos(gameh, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	//}//�����ö�
	//else
	//{
	//	HWND gameh = ::FindWindow(NULL, gameHandle);
	//	if (gameh == 0) { return; } //û���ҵ���Ϸ����
	//	//����Ϸ�����ö�
	//	::SetWindowPos(gameh, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	//}//�����ö�
}

void CheckTop(){
	//IDC_CHECK_TOP
	HWND m_gametop = GetDlgItem(NULL,IDC_CHECK_TOP);
	gametop = m_gametop;
	if (m_gametop)
	{
		HWND gameh = ::FindWindow(NULL, gameHandle);
		if (gameh == 0) { return; } //û���ҵ���Ϸ����
		//����Ϸ�����ö�
		::SetWindowPos(gameh, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}//�����ö�
	else
	{
		HWND gameh = ::FindWindow(NULL, gameHandle);
		if (gameh == 0) { return; } //û���ҵ���Ϸ����
		//����Ϸ�����ö�
		::SetWindowPos(gameh, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}//�����ö�
}

void C����������Dlg::OnBnClickedCheckSpeed()
{
	UpdateData(true);
	::EnableWindow(m_ctl_slider.m_hWnd, m_sliderenable);
}


void C����������Dlg::OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
	//�϶����������°�
	OnBnClickedCheckCheckPlayGame();
}

void C����������Dlg::OnBnClickedCheckTime()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
