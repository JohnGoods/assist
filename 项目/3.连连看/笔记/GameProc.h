#include "stdafx.h" 
//游戏 功能函数
HWND gameh;
RECT r1;
POINT p;//x,y
void startGame()
{
	// TODO: Add your control notification handler code here
	//获取游戏窗口句柄
	gameh = ::FindWindow(NULL, L"QQ游戏 - 连连看角色版");
	::GetWindowRect(gameh, &r1);
	//保存当前鼠标指针
	//取得当前鼠标位置
	GetCursorPos(&p);
	//设置鼠标指针位置  取开局所在坐标:x=655;y=577 //lparam 0x0241028f
	SetCursorPos(655 + r1.left, 577 + r1.top);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	//鼠标在当前位置抬起
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	//还原鼠标位置
	Sleep(100);//过一段时间 再执行后边的代码
	SetCursorPos(p.x, p.y);
}