#include "stdafx.h" 
#include <string>  
#include <iostream>  
using namespace std;

#define gameHandle L"���ھ��"		//�滻Ϊ���ھ��

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

//��ȡ��Ϸ���ھ��
HWND getGameHWND(){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	return game_hwnd;
}

//�򿪽���Id
DWORD getGameProcessId(){
	HWND game_hwnd = getGameHWND();
	DWORD processid;
	::GetWindowThreadProcessId(game_hwnd, &processid);
	return processid;
}

//OpenProcess�򿪻�ý��̾��
HANDLE getGameProcessHandle(){
	DWORD processid = getGameProcessId();
	EnableDebugPriv();	//��������Ȩ�� VS2008�Ժ�İ汾����Ҫ
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	/*
	1.
	dwDesiredAccess��//��ӵ�еĸý��̷���Ȩ��
	PROCESS_ALL_ACCESS  //�����ܻ�õ�Ȩ��
	PROCESS_CREATE_PROCESS  //��Ҫ����һ������
	PROCESS_CREATE_THREAD   //��Ҫ����һ���߳�
	PROCESS_DUP_HANDLE      //�ظ�ʹ��DuplicateHandle���
	PROCESS_QUERY_INFORMATION   //��ý�����Ϣ��Ȩ�ޣ��������˳����롢���ȼ�
	PROCESS_QUERY_LIMITED_INFORMATION  *//*���ĳЩ��Ϣ��Ȩ�ޣ���������PROCESS_QUERY_INFORMATION��Ҳӵ��PROCESS_QUERY_LIMITED_INFORMATIONȨ��*//*
	PROCESS_SET_INFORMATION    //����ĳЩ��Ϣ��Ȩ�ޣ���������ȼ�
	PROCESS_SET_QUOTA          //�����ڴ����Ƶ�Ȩ�ޣ�ʹ��SetProcessWorkingSetSize
	PROCESS_SUSPEND_RESUME     //��ͣ��ָ����̵�Ȩ��
	PROCESS_TERMINATE          //��ֹһ�����̵�Ȩ�ޣ�ʹ��TerminateProcess
	PROCESS_VM_OPERATION       //���������ڴ�ռ��Ȩ��(����VirtualProtectEx��WriteProcessMemory) 
	PROCESS_VM_READ            //��ȡ�����ڴ�ռ��Ȩ�ޣ���ʹ��ReadProcessMemory
	PROCESS_VM_WRITE           //��ȡ�����ڴ�ռ��Ȩ�ޣ���ʹ��WriteProcessMemory
	SYNCHRONIZE                //�ȴ�������ֹ
	2.
	bInheritHandle����ʾ���õ��Ľ��̾���Ƿ���Ա��̳�
	3.
	dwProcessId�����򿪽��̵�PID
	*/
	//4.
	/*����ֵ��
		����������óɹ�������һ�����̾��ֵ�����򽫷���NULL*/
	return processH;
}

//ģ����
//��һ�����
//ֱ�ӵ� ĳ����
//ֱ���� p
//�ڶ������
//width ����������̵�XY����� ��Ҫ��
//height ����������̵�XY����� ��Ҫ��
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//���������
//offsetsX ����������̵�XY����� ����ƫ�� ��Ҫ��
//offsetsY ����������̵�XY����� ����ƫ�� ��Ҫ��
bool ClickPoint(POINT p, int width, int height, int offsetsX, int offsetsY)
{
	/*width = 31;
	height = 35;
	offsetsX = 21;
	offsetsY = 192;*/
	HWND hwnd = getGameHWND();
	int lparam;
	lparam = (p.y << 16) + p.x;
	if (width != NULL && height != NULL){
		lparam = ((p.y * height) << 16) + (p.x * width);
	}else if(width != NULL && height != NULL&&offsetsX != NULL&&offsetsY!=NULL){
		lparam = ((p.y * height + offsetsY) << 16) + (p.x * width + offsetsX);
	}
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//
	return true;
}

//strתLPCWSTR
LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

//��װMessageBox
//#define MB_OK                       0x00000000L
//#define MB_OKCANCEL                 0x00000001L
//#define MB_ABORTRETRYIGNORE         0x00000002L
//#define MB_YESNOCANCEL              0x00000003L
//#define MB_YESNO                    0x00000004L
//#define MB_RETRYCANCEL              0x00000005L
//#define MB_CANCELTRYCONTINUE        0x00000006L
void sendMessage(string str,int num){
	unsigned int pattern = 0x00000000L;
	if (num != NULL){
		switch (num)
		{
		case 0:
			pattern = MB_OK;
			break;
		case 1:
			pattern = MB_OKCANCEL;
			break;
		case 2:
			pattern = MB_ABORTRETRYIGNORE;
			break;
		case 3:
			pattern = MB_YESNOCANCEL;
			break;
		case 4:
			pattern = MB_YESNO;
			break;
		case 5:
			pattern = MB_RETRYCANCEL;
			break;
		case 6:
			pattern = MB_CANCELTRYCONTINUE;
			break;
		}
	}
	LPCWSTR str1 = stringToLPCWSTR(str);
	::MessageBox(0, str1, 0, pattern);
}


//����HWND_ID��ȡ״̬���� ��ַ �Ƿ��޸���ֵ
void baseWriteProcessMemory(HWND id, PVOID site, UCHAR a4[], UCHAR b4[])
{
	//UCHAR a4[4] = { 0x90, 0x90, 0x90, 0x90 };
	//UCHAR b4[4] = { 0x83, 0x46, 0x40, 0xfc };
	//site = (PVOID)0x0054BA6A;
	int nWnd_Id;
	nWnd_Id = (int)id;

	DWORD bw;

	CButton* pbtn = (CButton*)GetDlgItem(NULL, nWnd_Id);
	HANDLE hp = getGameHWND();
	if (pbtn->GetCheck())
	{
		//�޸Ĵ���
		WriteProcessMemory(hp, site, a4, sizeof(a4), &bw);
	}
	else
	{
		//��ԭ��������
		WriteProcessMemory(hp, site, b4, sizeof(a4), &bw);
	}
	CloseHandle(hp);
}


//----------------------���ڴ����� ���ڴ����� ���浽ĳ��ֵ(ģ��)----------------------------
byte data[10];
void template_updateDate()
{
	//��ָ������ �ڴ�����
	HANDLE processH = getGameProcessHandle();
	if (processH == NULL){
		string str = "����û�򿪣������˳������鴰�ھ���Ƿ�������ȷ";
		sendMessage(str, 0);
		exit(0);
	}
	DWORD byread;
	LPCVOID pbase = (LPCVOID)0x00000000;	//�ڴ��ַ
	LPVOID  nbuffer = (LPVOID)&data;
	::ReadProcessMemory(processH, pbase, nbuffer, 0x10, &byread);
}
//----------------------���ڴ����� ���ڴ����� ���浽ĳ��ֵ(ģ��)End----------------------------


//------------------------------ע�����ģ��---------------------------------------
__declspec(naked) void template_esp(DWORD *pxy)
{
	__asm
	{ 
		mov ebx, [esp + 4] //pxy
			mov ecx, [ebx]  //x
			mov edx, [ebx + 4] //y	
			mov eax, [ebx + 8] //index
	}
}

void template_VirtualFreeEx(DWORD x, DWORD y, DWORD index)
{
	DWORD xy[3];
	xy[0] = x;
	xy[1] = y;
	xy[2] = index;
	DWORD byWrite;
	//��Ϸ���̾��
	HANDLE hp = getGameHWND();
	//��Ŀ����̷����ڴ�ռ� �Է���д��Ҫִ�еĴ���
	PVOID FarCall = VirtualAllocEx(hp, NULL, 0xFFFF, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	//LPVOID WINAPI VirtualAllocEx(
	//	__in      HANDLE hProcess,   //��Ҫ�����з���ռ�Ľ��̵ľ��.
	//	__in_opt  LPVOID lpAddress,  //��Ҫ��ȡ�ĵ�ַ����..
	//	__in      SIZE_T dwSize,      //Ҫ������ڴ��С.
	//	__in      DWORD flAllocationType, //�ڴ���������
	//	__in      DWORD flProtect        //�ڴ�ҳ����.
	//	);
	PVOID CallArg = VirtualAllocEx(hp, NULL, sizeof(int) * 2, MEM_COMMIT, PAGE_READWRITE);
	//��Ŀ����̵� Ŀ���ַд������Ҫִ�еĴ��� 
	WriteProcessMemory(hp, FarCall, template_esp, 0xFFFF, &byWrite);
	//��Ŀ����� д�����
	WriteProcessMemory(hp, CallArg, xy, sizeof(DWORD) * 3, &byWrite);
	//��Ŀ����� ָ����ַ ִ�д���
	//TRACE("\n addr=%x \n", FarCall);
	HANDLE th = CreateRemoteThread(hp, NULL, NULL, (LPTHREAD_START_ROUTINE)FarCall, CallArg, NULL, NULL);
	WaitForSingleObject(th, 0xFFFFFFF);//�ȴ� ...
	VirtualFreeEx(hp, FarCall, 0xFFFF, MEM_DECOMMIT);
	CloseHandle(th);
	CloseHandle(hp);
}
//------------------------------ע�����ģ��End---------------------------------------