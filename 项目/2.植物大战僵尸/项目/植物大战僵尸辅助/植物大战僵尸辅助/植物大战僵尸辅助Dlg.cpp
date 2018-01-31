
// 植物大战僵尸辅助Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "植物大战僵尸辅助.h"
#include "植物大战僵尸辅助Dlg.h"
#include "afxdialogex.h"
//#include <iostream>
using namespace std;

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


// C植物大战僵尸辅助Dlg 对话框



C植物大战僵尸辅助Dlg::C植物大战僵尸辅助Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C植物大战僵尸辅助Dlg::IDD, pParent)
	, m_b_CD(FALSE)
	, m_edit_money(0)
	, m_edit_sun(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C植物大战僵尸辅助Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CD, m_b_CD);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_edit_money);
	DDX_Text(pDX, IDC_EDIT_SUN, m_edit_sun);
}

BEGIN_MESSAGE_MAP(C植物大战僵尸辅助Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CD, &C植物大战僵尸辅助Dlg::OnBnClickedCheckCd)
//	ON_WM_TIMER()
ON_WM_TIMER()
ON_EN_CHANGE(IDC_EDIT_MONEY, &C植物大战僵尸辅助Dlg::OnEnChangeEditMoney)
ON_BN_CLICKED(IDC_BUTTON_MONEY, &C植物大战僵尸辅助Dlg::OnBnClickedButtonMoney)
ON_EN_CHANGE(IDC_EDIT_SUN, &C植物大战僵尸辅助Dlg::OnEnChangeEditSun)
ON_BN_CLICKED(IDC_BUTTON_SUN, &C植物大战僵尸辅助Dlg::OnBnClickedButtonSun)
ON_BN_CLICKED(IDC_BUTTON_PLAN, &C植物大战僵尸辅助Dlg::OnBnClickedButtonPlan)
ON_BN_CLICKED(IDC_BUTTON_OPENPLAN, &C植物大战僵尸辅助Dlg::OnBnClickedButtonOpenplan)
ON_BN_CLICKED(IDC_BUTTON_ClOSE_PLAN, &C植物大战僵尸辅助Dlg::OnBnClickedButtonClosePlan)
END_MESSAGE_MAP()


// C植物大战僵尸辅助Dlg 消息处理程序

BOOL C植物大战僵尸辅助Dlg::OnInitDialog()
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
	SetTimer(1, 500, NULL);
	SetTimer(2, 3000, NULL);
	SetTimer(3, 3000, NULL);
	CComboBox* pbox = (CComboBox*)GetDlgItem(IDC_COMBO_PLAN_ID);
	pbox->AddString(_T("000 = 豌豆射手"));
	pbox->AddString(_T("001 = 向日葵"));
	pbox->AddString(_T("002 = 樱桃炸弹"));
	pbox->AddString(_T("003 = 坚果"));
	pbox->AddString(_T("004 = 土拔鼠"));
	pbox->AddString(_T("005 = 寒冰豌豆射手"));
	pbox->AddString(_T("006 = 食人花"));
	pbox->AddString(_T("007 = 双重豌豆射手"));
	pbox->AddString(_T("008 = 小毒菇"));
	pbox->AddString(_T("009 = 小阳光菇"));
	pbox->AddString(_T("010 = 大毒菇"));
	pbox->AddString(_T("011 = 墓碑吞噬者"));
	pbox->AddString(_T("012 = 晕眩菇"));
	pbox->AddString(_T("013 = 长毒菇"));
	pbox->AddString(_T("014 = 寒冰菇"));
	pbox->AddString(_T("015 = 毁灭菇"));
	pbox->AddString(_T("016 = 莲蓬"));
	pbox->AddString(_T("017 = 瓜瓜"));
	pbox->AddString(_T("018 = 三碗射手"));
	pbox->AddString(_T("019 = 海藻"));
	pbox->AddString(_T("020 = 辣椒"));
	pbox->AddString(_T("021 = 地刺"));
	pbox->AddString(_T("022 = 火桩"));
	pbox->AddString(_T("023 = 高坚果"));
	pbox->AddString(_T("024 = 小海菇"));
	pbox->AddString(_T("025 = 夜灯"));
	pbox->AddString(_T("026 = 仙人掌"));
	pbox->AddString(_T("027 = 三叶草"));
	pbox->AddString(_T("028 = 左右豌豆射手"));
	pbox->AddString(_T("029 = 星星"));
	pbox->AddString(_T("030 = 南瓜"));
	pbox->AddString(_T("031 = 磁铁"));
	pbox->AddString(_T("032 = 菜投手"));
	pbox->AddString(_T("033 = 花盆"));
	pbox->AddString(_T("034 = 玉米投手"));
	pbox->AddString(_T("035 = 咖啡豆"));
	pbox->AddString(_T("036 = 大蒜"));
	pbox->AddString(_T("037 = 保护草"));
	pbox->AddString(_T("038 = 金银花"));
	pbox->AddString(_T("039 = 西瓜投手"));
	pbox->AddString(_T("040 = 多重豌豆射手"));
	pbox->AddString(_T("041 = 三向日葵"));
	pbox->AddString(_T("042 = 章鱼"));
	pbox->AddString(_T("043 = 陆陆猫"));
	pbox->AddString(_T("044 = 冰冻西瓜"));
	pbox->AddString(_T("045 = 吸金"));
	pbox->AddString(_T("046 = 地刺王"));
	pbox->AddString(_T("047 = 加农炮"));
	pbox->AddString(_T("048 = 克隆豆"));
	pbox->AddString(_T("049 = 红色坚果"));
	pbox->AddString(_T("050 = 巨大坚果"));
	pbox->AddString(_T("051 = 小草"));
	pbox->AddString(_T("052 = 反转射手?"));
	pbox->SetCurSel(2);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C植物大战僵尸辅助Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C植物大战僵尸辅助Dlg::OnPaint()
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
HCURSOR C植物大战僵尸辅助Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//提升进程访问权限   
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
		::MessageBox(0, L"游戏未打开,程序退出", 0, MB_OK);
		exit(0);
		return NULL;
	}
	//1005194
	DWORD pid, bywrite;
	GetWindowThreadProcessId(h, &pid);
	//GetWindowThreadProcessId
	//OpenProcss
	EnableDebugPriv();//提升进程权限 VS2008以后的版本才需要
	HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	//
	if (hp == NULL)
	{
		::MessageBox(0, L"打开进程出错,程序退出", 0, MB_OK);
		exit(0);
		return NULL;
	}
	return hp;
}

void C植物大战僵尸辅助Dlg::OnBnClickedCheckCd()
{
	UpdateData(true);//更新窗口状态至变量
}

void C植物大战僵尸辅助Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnTimer(nIDEvent);
	HANDLE hp = GetGameProcessHandle();
	DWORD buf = 0, byread, bywrite;
	switch (nIDEvent)
	{
	case 1:
		if (m_b_CD)	//勾选去了CD
		{   //禁用掉冷却时间
			for (int i = 0; i < 10; i++){
				/*HANDLE hp = GetGameProcessHandle();
				DWORD buf = 0, byread, bywrite;*/
				ReadProcessMemory(hp, (PVOID)0x755E0C, &buf, sizeof(buf), &byread);
				ReadProcessMemory(hp, (PVOID)(buf + 0x868), &buf, sizeof(buf), &byread);
				ReadProcessMemory(hp, (PVOID)(buf + 0x15C), &buf, sizeof(buf), &byread);
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
		ReadProcessMemory(hp, (PVOID)0x755E0C, &buf, sizeof(buf), &byread);
		ReadProcessMemory(hp, (PVOID)(buf + 0x950), &buf, sizeof(buf), &byread);
		ReadProcessMemory(hp, (PVOID)(buf + 0x50), &buf, sizeof(buf), &byread);
		m_edit_money = buf;
		UpdateData(false);
		//WriteProcessMemory(hp, (PVOID)(buf + 0x28), &num, sizeof(buf), &byread);
		break;
	case 3:
		/*HANDLE hp1 = GetGameProcessHandle();
		DWORD buf1 = 0, byread1, bywrite1;*/
		ReadProcessMemory(hp, (PVOID)0x755E0C, &buf, sizeof(buf), &byread);
		ReadProcessMemory(hp, (PVOID)(buf + 0x868), &buf, sizeof(buf), &byread);
		ReadProcessMemory(hp, (PVOID)(buf + 0x15C), &buf, sizeof(buf), &byread);
		ReadProcessMemory(hp, (PVOID)(buf + 0x2C), &buf, sizeof(buf), &byread);
		ReadProcessMemory(hp, (PVOID)(buf + 0x5578), &buf, sizeof(buf), &byread);
		m_edit_sun = buf;
		UpdateData(false);
		//WriteProcessMemory(hp, (PVOID)(buf + 0x28), &num, sizeof(buf), &byread);
		break;
	case 4:
		this->OnBnClickedButtonPlan();
		break;
	}
}

void C植物大战僵尸辅助Dlg::OnEnChangeEditMoney()
{
	KillTimer(2);
}


void C植物大战僵尸辅助Dlg::OnBnClickedButtonMoney()
{
	HANDLE hp = GetGameProcessHandle();
	DWORD buf = 0, byread, bywrite;
	ReadProcessMemory(hp, (PVOID)0x755E0C, &buf, sizeof(buf), &byread);
	ReadProcessMemory(hp, (PVOID)(buf + 0x950), &buf, sizeof(buf), &byread);
	UpdateData(true);
	WriteProcessMemory(hp, (PVOID)(buf + 0x50), &m_edit_money, sizeof(buf), &byread);
	SetTimer(2, 1000, NULL);
}


void C植物大战僵尸辅助Dlg::OnEnChangeEditSun()
{
	KillTimer(3);
}


void C植物大战僵尸辅助Dlg::OnBnClickedButtonSun()
{
	HANDLE hp = GetGameProcessHandle();
	DWORD buf = 0, byread, bywrite;
	ReadProcessMemory(hp, (PVOID)0x755E0C, &buf, sizeof(buf), &byread);
	ReadProcessMemory(hp, (PVOID)(buf + 0x868), &buf, sizeof(buf), &byread);
	ReadProcessMemory(hp, (PVOID)(buf + 0x15C), &buf, sizeof(buf), &byread);
	ReadProcessMemory(hp, (PVOID)(buf + 0x2C), &buf, sizeof(buf), &byread);
	UpdateData(true);
	WriteProcessMemory(hp, (PVOID)(buf + 0x5578), &m_edit_sun, sizeof(buf), &byread);
	SetTimer(3, 1000, NULL);
}

__declspec(naked) void plant1(DWORD *pxy)
{
	__asm
	{ //esp+4
		//mov edx, -1
		//	push edx	//push edx
		//	mov eax ,2
		//	push eax	//push eax
		//	mov eax,4	//y
		//	mov ecx, 8	//ecx
		//	push ecx	//x
		//	//push 26E9EC00
		//	mov edi, dword ptr ds : [0755E0C] //mov eax,0x6a9ec0
		//	mov edi, dword ptr ds : [edi + 0x868]
		//	push edi
		//	mov ebx, 0x00418D70
		//	call ebx
		//	ret
				
		mov ebx, [esp + 4] //xy
		mov ecx, [ebx]  //x
		mov edx, [ebx + 4] //y	
		mov eax, [ebx + 8]
			push -1
			push eax	//植物ID
			mov eax, edx
			push ecx
			mov edi, dword ptr ds : [0x755E0C] //mov eax,0x6a9ec0
			mov edi, dword ptr ds : [edi + 0x868]
			test edi, edi
			jz endl
			//mov edi, dword ptr ds : [0x255E0620]
			push edi
			mov ebx, 0x418D70
			call ebx
			ret
		endl :
			add esp, 0xc //3*sizeof(int)
			ret
			//mov ebx, [esp + 4] //xy
			//mov ecx, [ebx]  //x
			//mov edx, [ebx + 4] //y
			//push - 1
			//push 2
			//push ecx //X列
			//mov eax, dword ptr ds : [0x6a9ec0] //mov eax,0x6a9ec0
			//mov eax, dword ptr ds : [eax + 0x768]
			//push eax
			//mov eax, edx//Y行
			//mov edx, 0x0040D120
			//call edx
			//ret
	}
}

void plantOne(DWORD x, DWORD y, DWORD index)
{
	DWORD xy[3];
	xy[0] = x;//0..7
	xy[1] = y;// 0..4
	xy[2] = index;//植物ID
	DWORD byWrite;
	//游戏进程句柄
	HANDLE hp = GetGameProcessHandle();
	//在目标进程分配内存空间 以方便写入要执行的代码
	PVOID FarCall = VirtualAllocEx(hp, NULL, 0xFFFF, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	PVOID CallArg = VirtualAllocEx(hp, NULL, sizeof(int)* 2, MEM_COMMIT, PAGE_READWRITE);
	//向目标进程的 目标地址写入我们要执行的代码 
	WriteProcessMemory(hp, FarCall, plant1, 0xFFFF, &byWrite);
	//向目标进程 写入参数
	WriteProcessMemory(hp, CallArg, xy, sizeof(DWORD)* 3, &byWrite);
	//在目标进程 指定地址 执行代码
	TRACE("\n addr=%x \n", FarCall);
	HANDLE th = CreateRemoteThread(hp, NULL, NULL, (LPTHREAD_START_ROUTINE)FarCall, CallArg, NULL, NULL);
	WaitForSingleObject(th, 0xFFFFFFF);//等待 ...
	VirtualFreeEx(hp, FarCall, 0xFFFF, MEM_DECOMMIT);
	CloseHandle(th);
	CloseHandle(hp);
}

void C植物大战僵尸辅助Dlg::OnBnClickedButtonPlan()
{
	DWORD index = ((CComboBox*)GetDlgItem(IDC_COMBO_PLAN_ID))->GetCurSel();
	for (int x = 0; x <= 8; x++)
	{
		for (int y = 0; y <= 4; y++)
		{
			plantOne(x, y,index);
		}
	}
	// TODO: 在此添加控件通知处理程序代码
	//DWORD byWrite;
	////游戏进程句柄
	//HANDLE hp = GetGameProcessHandle();
	////在目标进程分配内存空间 以方便写入要执行的代码
	//PVOID FarCall = VirtualAllocEx(hp, NULL, 0xFFFF, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	////向目标进程的 目标地址写入我们要执行的代码 
	//WriteProcessMemory(hp, FarCall, plant1, 0xFFFF, &byWrite);
	////在目标进程 指定地址 执行代码
	//TRACE("\n addr=%x \n", FarCall);
	//CreateRemoteThread(hp, NULL, NULL, (LPTHREAD_START_ROUTINE)FarCall, NULL, NULL, NULL);

}


void C植物大战僵尸辅助Dlg::OnBnClickedButtonOpenplan()
{
	SetTimer(4, 2000, NULL);
}


void C植物大战僵尸辅助Dlg::OnBnClickedButtonClosePlan()
{
	KillTimer(4);
}
