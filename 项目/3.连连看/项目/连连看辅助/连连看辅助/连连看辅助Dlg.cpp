
// 连连看辅助Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "连连看辅助.h"
#include "连连看辅助Dlg.h"
#include "afxdialogex.h"
#include "GameProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C连连看辅助Dlg 对话框



C连连看辅助Dlg::C连连看辅助Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C连连看辅助Dlg::IDD, pParent)
	, m_edit_x(0)
	, m_edit_y(0)
	, m_edit_seat(0)
	, m_edit_chess_data(_T(""))
	, m_p1x(0)
	, m_p1y(0)
	, m_p2x(0)
	, m_p2y(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C连连看辅助Dlg::DoDataExchange(CDataExchange* pDX)
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
}

BEGIN_MESSAGE_MAP(C连连看辅助Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &C连连看辅助Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SEAT, &C连连看辅助Dlg::OnBnClickedButtonSeat)
	ON_BN_CLICKED(IDC_BUTTON_CHAT_DATA, &C连连看辅助Dlg::OnBnClickedButtonChatData)
	ON_BN_CLICKED(IDC_BUTTON_CLICK, &C连连看辅助Dlg::OnBnClickedButtonClick)
	ON_BN_CLICKED(IDC_BUTTON_SINGLE, &C连连看辅助Dlg::OnBnClickedButtonSingle)
END_MESSAGE_MAP()


// C连连看辅助Dlg 消息处理程序

BOOL C连连看辅助Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C连连看辅助Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C连连看辅助Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C连连看辅助Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//HWND gameh;
//RECT r1;
void C连连看辅助Dlg::OnBnClickedButtonStart()
{
	//// TODO: Add your control notification handler code here
	////获取游戏窗口句柄
	//gameh = ::FindWindow(NULL, L"QQ游戏 - 连连看角色版");
	//::GetWindowRect(gameh, &r1);
	//this->m_edit_x = r1.left; this->m_edit_y = r1.top;
	//UpdateData(false);
	////设置鼠标指针位置  取开局所在坐标:x=655;y=577 //lparam 0x0241028f
	//SetCursorPos(655 + r1.left, 577 + r1.top);
	startGame();
}

//const PCHAR gameCaption = "QQ游戏 - 连连看角色版";
void C连连看辅助Dlg::OnBnClickedButtonSeat()
{
	// 游戏窗口标题："QQ游戏 - 连连看角色版"
	// 1、FindWindow               //获取窗口句柄
	//2、GetWindowThreadProcessId //获取窗口进程ID
	//3、OpenProcess              //打开指定进程
	//4、ReadProcessMemory        //读指定进程 内存数据
	//获取窗口句柄
	HWND gameh = ::FindWindow(NULL, _T("QQ游戏 - 连连看角色版"));
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//打开指定进程
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//读指定进程 内存数据
	DWORD byread;
	LPCVOID pbase = (LPCVOID)0x00171618;		//座位
	LPVOID  nbuffer = (LPVOID)&m_edit_seat;
	::ReadProcessMemory(processH, pbase, nbuffer, 4, &byread);
	UpdateData(false); //更新变量的值到 编辑框
}

//byte chessdata[11][19];//a[y][x]
void C连连看辅助Dlg::OnBnClickedButtonChatData()
{
	// TODO: Add your control notification handler code here
	//获取窗口句柄
	HWND gameh = ::FindWindow(NULL, _T("QQ游戏 - 连连看角色版"));
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//打开指定进程
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//读指定进程 内存数据
	DWORD byread;
	LPCVOID pbase = (LPCVOID)0x00189F78; //棋盘数据基址
	LPVOID  nbuffer = (LPVOID)&chessdata;    //存放棋盘数据
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);
	///显示棋盘数据
	char buf[11];
	m_edit_chess_data = ""; //清空编辑
	for (int y = 0; y <= 10; y++)
	{
		for (int x = 0; x <= 18; x++) //读一行
		{
			_itoa_s(chessdata[y][x], buf, 16); //转换成字串
			m_edit_chess_data += buf;
			m_edit_chess_data += " ";
		}
		//换行
		m_edit_chess_data += "\r\n";
	}
	UpdateData(false);
}

void C连连看辅助Dlg::OnBnClickedButtonClick()
{

	int   x = 22, y = 187;
	HWND hwnd = ::FindWindow(NULL, _T("QQ游戏 - 连连看角色版"));
	int lparam;
	lparam = (y << 16) + x + 31 * 0;//表示指定格
	::SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	::SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);  //
}

void C连连看辅助Dlg::OnBnClickedButtonSingle()
{
	// TODO:  在此添加控件通知处理程序代码
	ClearPiar();
}

bool C连连看辅助Dlg::ClearPiar() //消除一对棋子
{
	//读出棋盘数据至chessdata 11,19
	updatdChess();
	//遍历整个棋盘 找出相同类型 一对棋子
	POINT p1, p2;
	int x1, y1, x2, y2;
	for (y1 = 0; y1<11; y1++)
	for (x1 = 0; x1<19; x1++)
	{
		for (y2 = y1; y2<11; y2++)
		for (x2 = 0; x2<19; x2++)
		if ((chessdata[y1][x1] == chessdata[y2][x2]) // 棋子1与棋子2 类型是否相同
			&& (!((x1 == x2) && (y1 == y2)))  //要求点1与点2 相等则假
			)
		{
			p1.x = x1; p1.y = y1;
			p2.x = x2; p2.y = y2;
			//检测 相同的2个棋子是否可消掉
			if (Check2p(p1, p2))//如果可消除 则返回真
			{
				//click2p 鼠标模拟 点击 p1，p2
				Click2p(p1, p2);
				m_p1x = x1;
				m_p1y = y1;
				m_p2x = x2;
				m_p2y = y2;
				UpdateData(false);//更新数据至窗口
				return true;

			}
		}
	}
	return false;
}

