
// ֲ���ս��ʬ����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ֲ���ս��ʬ����.h"
#include "ֲ���ս��ʬ����Dlg.h"
#include "afxdialogex.h"
//#include <iostream>
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
	, m_edit_money(0)
	, m_edit_sun(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cֲ���ս��ʬ����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CD, m_b_CD);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_edit_money);
	DDX_Text(pDX, IDC_EDIT_SUN, m_edit_sun);
}

BEGIN_MESSAGE_MAP(Cֲ���ս��ʬ����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CD, &Cֲ���ս��ʬ����Dlg::OnBnClickedCheckCd)
//	ON_WM_TIMER()
ON_WM_TIMER()
ON_EN_CHANGE(IDC_EDIT_MONEY, &Cֲ���ս��ʬ����Dlg::OnEnChangeEditMoney)
ON_BN_CLICKED(IDC_BUTTON_MONEY, &Cֲ���ս��ʬ����Dlg::OnBnClickedButtonMoney)
ON_EN_CHANGE(IDC_EDIT_SUN, &Cֲ���ս��ʬ����Dlg::OnEnChangeEditSun)
ON_BN_CLICKED(IDC_BUTTON_SUN, &Cֲ���ս��ʬ����Dlg::OnBnClickedButtonSun)
ON_BN_CLICKED(IDC_BUTTON_PLAN, &Cֲ���ս��ʬ����Dlg::OnBnClickedButtonPlan)
ON_BN_CLICKED(IDC_BUTTON_OPENPLAN, &Cֲ���ս��ʬ����Dlg::OnBnClickedButtonOpenplan)
ON_BN_CLICKED(IDC_BUTTON_ClOSE_PLAN, &Cֲ���ս��ʬ����Dlg::OnBnClickedButtonClosePlan)
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
	SetTimer(2, 3000, NULL);
	SetTimer(3, 3000, NULL);
	CComboBox* pbox = (CComboBox*)GetDlgItem(IDC_COMBO_PLAN_ID);
	pbox->AddString(_T("000 = �㶹����"));
	pbox->AddString(_T("001 = ���տ�"));
	pbox->AddString(_T("002 = ӣ��ը��"));
	pbox->AddString(_T("003 = ���"));
	pbox->AddString(_T("004 = ������"));
	pbox->AddString(_T("005 = �����㶹����"));
	pbox->AddString(_T("006 = ʳ�˻�"));
	pbox->AddString(_T("007 = ˫���㶹����"));
	pbox->AddString(_T("008 = С����"));
	pbox->AddString(_T("009 = С���⹽"));
	pbox->AddString(_T("010 = �󶾹�"));
	pbox->AddString(_T("011 = Ĺ��������"));
	pbox->AddString(_T("012 = ��ѣ��"));
	pbox->AddString(_T("013 = ������"));
	pbox->AddString(_T("014 = ������"));
	pbox->AddString(_T("015 = ����"));
	pbox->AddString(_T("016 = ����"));
	pbox->AddString(_T("017 = �Ϲ�"));
	pbox->AddString(_T("018 = ��������"));
	pbox->AddString(_T("019 = ����"));
	pbox->AddString(_T("020 = ����"));
	pbox->AddString(_T("021 = �ش�"));
	pbox->AddString(_T("022 = ��׮"));
	pbox->AddString(_T("023 = �߼��"));
	pbox->AddString(_T("024 = С����"));
	pbox->AddString(_T("025 = ҹ��"));
	pbox->AddString(_T("026 = ������"));
	pbox->AddString(_T("027 = ��Ҷ��"));
	pbox->AddString(_T("028 = �����㶹����"));
	pbox->AddString(_T("029 = ����"));
	pbox->AddString(_T("030 = �Ϲ�"));
	pbox->AddString(_T("031 = ����"));
	pbox->AddString(_T("032 = ��Ͷ��"));
	pbox->AddString(_T("033 = ����"));
	pbox->AddString(_T("034 = ����Ͷ��"));
	pbox->AddString(_T("035 = ���ȶ�"));
	pbox->AddString(_T("036 = ����"));
	pbox->AddString(_T("037 = ������"));
	pbox->AddString(_T("038 = ������"));
	pbox->AddString(_T("039 = ����Ͷ��"));
	pbox->AddString(_T("040 = �����㶹����"));
	pbox->AddString(_T("041 = �����տ�"));
	pbox->AddString(_T("042 = ����"));
	pbox->AddString(_T("043 = ½½è"));
	pbox->AddString(_T("044 = ��������"));
	pbox->AddString(_T("045 = ����"));
	pbox->AddString(_T("046 = �ش���"));
	pbox->AddString(_T("047 = ��ũ��"));
	pbox->AddString(_T("048 = ��¡��"));
	pbox->AddString(_T("049 = ��ɫ���"));
	pbox->AddString(_T("050 = �޴���"));
	pbox->AddString(_T("051 = С��"));
	pbox->AddString(_T("052 = ��ת����?"));
	pbox->SetCurSel(2);
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
	HANDLE hp = GetGameProcessHandle();
	DWORD buf = 0, byread, bywrite;
	switch (nIDEvent)
	{
	case 1:
		if (m_b_CD)	//��ѡȥ��CD
		{   //���õ���ȴʱ��
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

void Cֲ���ս��ʬ����Dlg::OnEnChangeEditMoney()
{
	KillTimer(2);
}


void Cֲ���ս��ʬ����Dlg::OnBnClickedButtonMoney()
{
	HANDLE hp = GetGameProcessHandle();
	DWORD buf = 0, byread, bywrite;
	ReadProcessMemory(hp, (PVOID)0x755E0C, &buf, sizeof(buf), &byread);
	ReadProcessMemory(hp, (PVOID)(buf + 0x950), &buf, sizeof(buf), &byread);
	UpdateData(true);
	WriteProcessMemory(hp, (PVOID)(buf + 0x50), &m_edit_money, sizeof(buf), &byread);
	SetTimer(2, 1000, NULL);
}


void Cֲ���ս��ʬ����Dlg::OnEnChangeEditSun()
{
	KillTimer(3);
}


void Cֲ���ս��ʬ����Dlg::OnBnClickedButtonSun()
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
			push eax	//ֲ��ID
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
			//push ecx //X��
			//mov eax, dword ptr ds : [0x6a9ec0] //mov eax,0x6a9ec0
			//mov eax, dword ptr ds : [eax + 0x768]
			//push eax
			//mov eax, edx//Y��
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
	xy[2] = index;//ֲ��ID
	DWORD byWrite;
	//��Ϸ���̾��
	HANDLE hp = GetGameProcessHandle();
	//��Ŀ����̷����ڴ�ռ� �Է���д��Ҫִ�еĴ���
	PVOID FarCall = VirtualAllocEx(hp, NULL, 0xFFFF, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	PVOID CallArg = VirtualAllocEx(hp, NULL, sizeof(int)* 2, MEM_COMMIT, PAGE_READWRITE);
	//��Ŀ����̵� Ŀ���ַд������Ҫִ�еĴ��� 
	WriteProcessMemory(hp, FarCall, plant1, 0xFFFF, &byWrite);
	//��Ŀ����� д�����
	WriteProcessMemory(hp, CallArg, xy, sizeof(DWORD)* 3, &byWrite);
	//��Ŀ����� ָ����ַ ִ�д���
	TRACE("\n addr=%x \n", FarCall);
	HANDLE th = CreateRemoteThread(hp, NULL, NULL, (LPTHREAD_START_ROUTINE)FarCall, CallArg, NULL, NULL);
	WaitForSingleObject(th, 0xFFFFFFF);//�ȴ� ...
	VirtualFreeEx(hp, FarCall, 0xFFFF, MEM_DECOMMIT);
	CloseHandle(th);
	CloseHandle(hp);
}

void Cֲ���ս��ʬ����Dlg::OnBnClickedButtonPlan()
{
	DWORD index = ((CComboBox*)GetDlgItem(IDC_COMBO_PLAN_ID))->GetCurSel();
	for (int x = 0; x <= 8; x++)
	{
		for (int y = 0; y <= 4; y++)
		{
			plantOne(x, y,index);
		}
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//DWORD byWrite;
	////��Ϸ���̾��
	//HANDLE hp = GetGameProcessHandle();
	////��Ŀ����̷����ڴ�ռ� �Է���д��Ҫִ�еĴ���
	//PVOID FarCall = VirtualAllocEx(hp, NULL, 0xFFFF, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	////��Ŀ����̵� Ŀ���ַд������Ҫִ�еĴ��� 
	//WriteProcessMemory(hp, FarCall, plant1, 0xFFFF, &byWrite);
	////��Ŀ����� ָ����ַ ִ�д���
	//TRACE("\n addr=%x \n", FarCall);
	//CreateRemoteThread(hp, NULL, NULL, (LPTHREAD_START_ROUTINE)FarCall, NULL, NULL, NULL);

}


void Cֲ���ս��ʬ����Dlg::OnBnClickedButtonOpenplan()
{
	SetTimer(4, 2000, NULL);
}


void Cֲ���ս��ʬ����Dlg::OnBnClickedButtonClosePlan()
{
	KillTimer(4);
}
