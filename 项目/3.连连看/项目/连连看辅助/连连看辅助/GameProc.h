#include "stdafx.h" 
#include "ChessPoint.h"
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


byte chessdata[11][19];//a[y][x]
//更新棋盘数据至 chessdata
void updatdChess() 
{
	// TODO: Add your control notification handler code here
	//获取窗口句柄
	HWND gameh = ::FindWindow(NULL, L"QQ游戏 - 连连看角色版");
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//打开指定进程
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//读指定进程 内存数据
	DWORD byread;
	LPCVOID pbase = (LPCVOID)0x0012A508; //棋盘数据基址
	LPVOID  nbuffer = (LPVOID)&chessdata;    //存放棋盘数据
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);
}

bool lineNull(POINT p1, POINT p2)
{
	return true;
}

//检测 p1,p2 2个棋子 是否可以消除
bool check2p(POINT p1, POINT p2)
{ 
	// Y坐标相同的情况下 p1,p2 
	//lineNull(p1.right,p2.left) //可消除
	if (p1.y == p2.y)
	{
		ChessPoint pa(p1), pb(p2);

		if (lineNull(pa.down, pb.up)) return true;
	}
	//X坐标相同的情况下 p1,p2
	//LineNull(p1.down,p2.up)    //可消除
	if (p1.x == p2.x)
	{
		ChessPoint pa(p1), pb(p2);

		if (lineNull(pa.down, pb.up)) return true;
	}

	//X与Y坐标都不相情况下 p1,p2
	//lineNull(p1.down,pa),LineNull(p2.down,pb),LineNull(pa,pb)
	//可消除
	return true;
}

//模拟点击两点
bool click2p(POINT p1, POINT p2)
{
	return true;
}

//消除一对棋子
void ClearPiar()
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
		for (x2 = x1; x2<19; x2++)
		if ((chessdata[y1][x1] == chessdata[y2][x2]) // 棋子1与棋子2 类型是否相同
			&& (!((x1 == x2) && (y1 == y2)))  //要求点1与点2 相等则假
			)
		{
			p1.x = x1; p1.y = y1;
			p2.x = x2; p2.y = y2;
			//检测 相同的2个棋子是否可消掉
			if (check2p(p1, p2))//如果可消除 则返回真
			{
				//click2p 鼠标模拟 点击 p1，p2
				click2p(p1, p2);

			}
		}
	}

}