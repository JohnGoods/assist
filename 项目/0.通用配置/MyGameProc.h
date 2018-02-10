#include "stdafx.h" 
#include <string>  
#include <iostream>  
using namespace std;

#define gameHandle L"窗口句柄"		//替换为窗口句柄

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

//获取游戏窗口句柄
HWND getGameHWND(){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	return game_hwnd;
}

//打开进程Id
DWORD getGameProcessId(){
	HWND game_hwnd = getGameHWND();
	DWORD processid;
	::GetWindowThreadProcessId(game_hwnd, &processid);
	return processid;
}

//OpenProcess打开获得进程句柄
HANDLE getGameProcessHandle(){
	DWORD processid = getGameProcessId();
	EnableDebugPriv();	//提升进程权限 VS2008以后的版本才需要
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	/*
	1.
	dwDesiredAccess：//想拥有的该进程访问权限
	PROCESS_ALL_ACCESS  //所有能获得的权限
	PROCESS_CREATE_PROCESS  //需要创建一个进程
	PROCESS_CREATE_THREAD   //需要创建一个线程
	PROCESS_DUP_HANDLE      //重复使用DuplicateHandle句柄
	PROCESS_QUERY_INFORMATION   //获得进程信息的权限，如它的退出代码、优先级
	PROCESS_QUERY_LIMITED_INFORMATION  *//*获得某些信息的权限，如果获得了PROCESS_QUERY_INFORMATION，也拥有PROCESS_QUERY_LIMITED_INFORMATION权限*//*
	PROCESS_SET_INFORMATION    //设置某些信息的权限，如进程优先级
	PROCESS_SET_QUOTA          //设置内存限制的权限，使用SetProcessWorkingSetSize
	PROCESS_SUSPEND_RESUME     //暂停或恢复进程的权限
	PROCESS_TERMINATE          //终止一个进程的权限，使用TerminateProcess
	PROCESS_VM_OPERATION       //操作进程内存空间的权限(可用VirtualProtectEx和WriteProcessMemory) 
	PROCESS_VM_READ            //读取进程内存空间的权限，可使用ReadProcessMemory
	PROCESS_VM_WRITE           //读取进程内存空间的权限，可使用WriteProcessMemory
	SYNCHRONIZE                //等待进程终止
	2.
	bInheritHandle：表示所得到的进程句柄是否可以被继承
	3.
	dwProcessId：被打开进程的PID
	*/
	//4.
	/*返回值：
		如果函数调用成功将返回一个进程句柄值，否则将返回NULL*/
	return processH;
}

//模拟点击
//第一种情况
//直接点 某个点
//直接填 p
//第二种情况
//width 如果根据棋盘的XY来点击 就要填
//height 如果根据棋盘的XY来点击 就要填
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxx
//第三种情况
//offsetsX 如果根据棋盘的XY来点击 且有偏移 就要填
//offsetsY 如果根据棋盘的XY来点击 且有偏移 就要填
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

//str转LPCWSTR
LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

//封装MessageBox
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


//根据HWND_ID获取状态设置 地址 是否修改数值
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
		//修改代码
		WriteProcessMemory(hp, site, a4, sizeof(a4), &bw);
	}
	else
	{
		//还原正常代码
		WriteProcessMemory(hp, site, b4, sizeof(a4), &bw);
	}
	CloseHandle(hp);
}


//----------------------打开内存数据 把内存数据 保存到某个值(模板)----------------------------
byte data[10];
void template_updateDate()
{
	//读指定进程 内存数据
	HANDLE processH = getGameProcessHandle();
	if (processH == NULL){
		string str = "进程没打开，程序退出，请检查窗口句柄是否设置正确";
		sendMessage(str, 0);
		exit(0);
	}
	DWORD byread;
	LPCVOID pbase = (LPCVOID)0x00000000;	//内存地址
	LPVOID  nbuffer = (LPVOID)&data;
	::ReadProcessMemory(processH, pbase, nbuffer, 0x10, &byread);
}
//----------------------打开内存数据 把内存数据 保存到某个值(模板)End----------------------------


//------------------------------注入代码模板---------------------------------------
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
	//游戏进程句柄
	HANDLE hp = getGameHWND();
	//在目标进程分配内存空间 以方便写入要执行的代码
	PVOID FarCall = VirtualAllocEx(hp, NULL, 0xFFFF, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	//LPVOID WINAPI VirtualAllocEx(
	//	__in      HANDLE hProcess,   //需要在其中分配空间的进程的句柄.
	//	__in_opt  LPVOID lpAddress,  //想要获取的地址区域..
	//	__in      SIZE_T dwSize,      //要分配的内存大小.
	//	__in      DWORD flAllocationType, //内存分配的类型
	//	__in      DWORD flProtect        //内存页保护.
	//	);
	PVOID CallArg = VirtualAllocEx(hp, NULL, sizeof(int) * 2, MEM_COMMIT, PAGE_READWRITE);
	//向目标进程的 目标地址写入我们要执行的代码 
	WriteProcessMemory(hp, FarCall, template_esp, 0xFFFF, &byWrite);
	//向目标进程 写入参数
	WriteProcessMemory(hp, CallArg, xy, sizeof(DWORD) * 3, &byWrite);
	//在目标进程 指定地址 执行代码
	//TRACE("\n addr=%x \n", FarCall);
	HANDLE th = CreateRemoteThread(hp, NULL, NULL, (LPTHREAD_START_ROUTINE)FarCall, CallArg, NULL, NULL);
	WaitForSingleObject(th, 0xFFFFFFF);//等待 ...
	VirtualFreeEx(hp, FarCall, 0xFFFF, MEM_DECOMMIT);
	CloseHandle(th);
	CloseHandle(hp);
}
//------------------------------注入代码模板End---------------------------------------