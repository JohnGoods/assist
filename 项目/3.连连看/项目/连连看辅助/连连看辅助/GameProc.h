#include "stdafx.h" 
#include "ChessPoint.h"

//宏指令
#define gameHandle L"QQ游戏 - 连连看角色版"		//标题
#define SEAT_ADDRESS 0x00171618		//座位基址
#define CHESSBOARD_ADDRESS 0x00189F78		//标题

//游戏 功能函数
RECT r1;
POINT p;
byte chessdata[11][19];//a[y][x]
//获取游戏窗口句柄
HWND getGameHWND(){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	return game_hwnd;
}

//打开进程Id
DWORD getGameProcessId(){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	DWORD processid;
	::GetWindowThreadProcessId(game_hwnd, &processid);
	return processid;
}

//读指定进程 内存数据
HANDLE getGameProcessHandle(long address){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	DWORD processid;
	::GetWindowThreadProcessId(game_hwnd, &processid);
	HANDLE processH = ::OpenProcess(address, false, processid);
	return processH;
}


void startGame()
{
	//获取游戏窗口句柄
	HWND gameh = getGameHWND();
	//保存当前鼠标指针
	::GetWindowRect(gameh, &r1);
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


//更新棋盘数据至 chessdata
void updatdChess() 
{
	//读指定进程 内存数据
	HANDLE processH = getGameProcessHandle(PROCESS_ALL_ACCESS);	//传基址就可以获取到指定进程 内存数据了
	DWORD byread;
	LPCVOID pbase = (LPCVOID)CHESSBOARD_ADDRESS; //棋盘数据基址
	LPVOID  nbuffer = (LPVOID)&chessdata;    //存放棋盘数据
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);	
}

//检测2点间 是否连通（存在一条全为0的直线路径）
bool CheckLine(POINT p1, POINT p2)
{
	int x, y, t;   
	//同一线上的两点间 全为0 则返回真 
	//如果 p1 == p2 也返回真
	if ((p1.x == p2.x) && (p1.y == p2.y) && (chessdata[p1.y][p1.x] == 0) && (chessdata[p2.y][p2.x] == 0))  {
		return true;
	}
	else{
		//防止越界
		if ((p1.x < 0) || (p1.x>18) || (p1.y < 0) || (p1.y>10) ||
			(p2.x < 0) || (p2.x>18) || (p2.y < 0) || (p2.y>10))  {
			return false;
		}

		if (p1.x == p2.x){     //如果X轴相等则 比较
			//这种情况应该是左右邻居棋子
			if (p1.y > p2.y) {
				t = p1.y;
				p1.y = p2.y;
				p2.y = t;
			}
			//判断从上到下一条直线间 棋盘数据中 有没有其他棋子挡住
			for (y = p1.y; y <= p2.y; y++){
				if (chessdata[y][p1.x] != 0) {
					return false;
				}
			}
		}

		if (p1.y == p2.y){    //如果Y轴相等 则比较
			//这种情况应该是左右邻居棋子
			if (p1.x > p2.x){
				t = p1.x;
				p1.x = p2.x;
				p2.x = t;
			}
			//判断从左到右一条直线间 棋盘数据中 有没有其他棋子挡住
			for (x = p1.x; x <= p2.x; x++){
				if (chessdata[p1.y][x] != 0){
					return false;
				}
			}
		}
	}
	return  true;
}

//检测 p1,p2 2个棋子 是否可以消除
//bool check2p(POINT p1, POINT p2)
//{ 
//	ChessPoint pa(p1), pb(p2); //初始化棋子类
//	POINT p11, p22;
//	int x, y;
//	//检测 p1,p2 2个棋子 是否可以消除
//	// Y坐标相同的情况下 p1,p2 
//	if (p1.y == p2.y)
//	{
//
//		if (CheckLine(pa.down, pb.up)) return true;
//		//pa,pb ; pa,p_1;pb,p_2;
//		p11 = p1; p22 = p2;
//		for (y = 0; y<11; y++)
//		{
//			p11.y = p22.y = y;
//			if (CheckLine(p11, p22) && CheckLine(pa.up, p11) && CheckLine(pb.up, p22))
//				return true;
//		}
//
//	}
//	//X坐标相同的情况下 p1,p2
//	//LineNull(p1.down,p2.up)    //可消除
//	if (p1.x == p2.x)
//	{
//
//		if (CheckLine(pa.down, pb.up)) return true;
//		// //pa,pb ; pa,p_1;pb,p_2;
//	}
//	//X与Y坐标都不相情况下 p1,p2
//	//lineNull(p1.down,pa),LineNull(p2.down,pb),LineNull(pa,pb)//可消除
//	return true;
//}




//检测 a,b 2个棋子 是否可以消除
bool Check2p(POINT a, POINT b)
{
	ChessPoint p1(a), p2(b);
	POINT pa, pb;//转角点
	int x, y;

	/*先常规的检测*/
	//如果两点为同一点 则返回false
	if ((a.x == b.x) && (a.y == b.y))  { 
		return false;
	}
	//如果两点有一点数据为0 or 两点的不是相同的棋子 则返回false
	else{
		if ((chessdata[a.y][a.x] == 0) || (chessdata[b.y][b.x] == 0))
		{
			return false;
		}
		else{
			if (chessdata[a.y][a.x] != chessdata[b.y][b.x])
			{
				return false;
			}
		}
	}

	/*判断两点可否消除*/

	pa = a; pb = b;	 //pa pb赋值

	//----------- 第一种情况(两只棋子在横向一条线上 y坐标 相同) -----------
	if (a.y == b.y){
		//两个棋子是邻居...
		if ((p1.right.x == p2.p.x) || (p1.left.x == p2.p.x)){	
			return true;
		}

		//先检测 这条线是否有一条路径相通
		if (CheckLine(p1.right, p2.left)){
			return true;
		}

		//检测 上下

		//先判断上
		/* 从上面找三个点
		 ___________
		|			|
		P1			p2
		*/
		//pa = a; pb = b;
		//如果在最顶层是不能有路径去消除的 所以首先判断Y轴是不是在最顶层
		if ((p1.up.y >= 0) && (p1.up.y <= 10)){
			for (y = 0; y <= p1.up.y; y++)
			{
				pa.y = y; pb.y = y;
				//检查棋盘中 有三条直线没数据 那就是可以消除的
				if (CheckLine(pa, p1.up) && CheckLine(pb, p2.up) && CheckLine(pa, pb))
				{
					return true;
				}
			}
		}

		//判断下
		/* 从下面找三个点
		P1			p2
		|			|
		-------------
		*/
		//pa = a; pb = b;
		//如果在最底层是不能有路径去消除的 所以首先判断Y轴是不是在最底层
		if ((p1.down.y >= 0) && (p1.down.y <= 10)){
			//检查棋盘中 有三条直线没数据 那就是可以消除的
			for (y = p1.down.y; y <= 10; y++)
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pa, p1.down) && CheckLine(pb, p2.down) && CheckLine(pa, pb))  {
					return true; 
				}
			}

		}
		//因为 y轴相等,所以不存在左右路径
	}
	//----------- 第二种情况(纵向一条线  x 坐标 相同) -----------
	else if (a.x == b.x){
		//x下上 相邻不
		if ((p1.down.y == p2.p.y) || (p1.up.y == p2.p.y))   {
			return true;
		}
		//检测 这条线是否有一条路径相通
		if (CheckLine(p1.down, p2.up))  { 
			return true;
		}

		//检测 左右
		//x左
		//pa = a; pb = b;
		for (x = 0; x <= p1.left.x; x++)
		{
			pa.x = x;
			pb.x = x;
			if (CheckLine(pa, p1.left) && CheckLine(pb, p2.left) && CheckLine(pa, pb))  { return true; }
		}

		//x右
		//pa = a; pb = b;
		for (x = p1.right.x; x <= 18; x++)
		{
			pa.x = x;
			pb.x = x;
			if (CheckLine(pa, p1.right) && CheckLine(pb, p2.right) && CheckLine(pa, pb))  { return true; }
		}

		//因为 y轴相等,所以不存在上下路径
	}
	////----------- 第三种情况(xy 坐标 都不相同) -----------
	else{
		//pa = a; pb = b;
		if (a.x > b.x)  {   // p2点 在 左 left
			////////////////xxxxxxxxxxxxxxxxx  找x轴路径
			for (x = 0; x <= p2.left.x; x++)
			{
				pa.x = x; pb.x = x;
				if (CheckLine(pa, p1.left) && CheckLine(pa, pb) && CheckLine(pb, p2.left))
				{
					return true;
				}
			} // end for
			for (x = p2.right.x; x <= p1.left.x; x++)
			{
				pa.x = x; pb.x = x;
				if (CheckLine(p2.right, pb) && CheckLine(pa, pb) && CheckLine(pa, p1.left))  {
					return true;
				}

			}
			for (x = p2.right.x; x <= 18; x++)
			{
				pa.x = x; pb.x = x;
				if (CheckLine(p1.right, pa) && CheckLine(p2.right, pb) && CheckLine(pa, pb))  {
					return true;
				}
			}
			/////////////////yyyyyyyyyyyyyyyyyyyy 找y轴路径 由于是从上向下 搜索 所以p1.y>p2.y
			pa.x = a.x;   pb.x = b.x; //初始化坐标 y軕渐变
			for (y = 0; y <= p1.up.y; y++)    //1段
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pb, pa) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))      {
					return true;
				}
			}
			////////////////////////
			for (y = p1.down.y; y <= p2.up.y; y++)//2段
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pb, pa) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))   {
					return true;
				}
			}
			///////////////////////
			for (y = p2.down.y; y <= 10; y++) //3段
			{
				///////////////////////////////
				pa.y = y; pb.y = y;
				if (CheckLine(pb, pa) && CheckLine(p1.down, pa) && CheckLine(p2.down, pb))   { return true; }
			}

		}
		else{////////////p2点  在 右 right a.x>b.x
			pa.y = a.y;   pb.y = b.y; //初始化坐标
			for (x = 0; x <= p1.left.x; x++);
			{
				pa.x = x; pb.x = x;
				if (CheckLine(pa, pb) && CheckLine(pa, p1.left) && CheckLine(pb, p2.left))  {
					return true;
				}
			}
			/////////////////////

			for (x = p1.right.x; x <= p2.left.x; x++)
			{
				pa.x = x; pb.x = x;
				if (CheckLine(pa, pb) && CheckLine(p1.right, pa) && CheckLine(pb, p2.left))  {
					return true;
				}
			}
			///////////////////////

			for (x = p2.right.x; x <= 18; x++)
			{
				pa.x = 0; pb.x = x;
				if (CheckLine(pa, pb) && CheckLine(p1.right, pa) && CheckLine(p2.right, pb)) {
					return true;
				}
			}
			///////////////////////yyyyyyyyyyyyyyyyyy   y轴渐变
			pa.x = a.x;   pb.x = b.x; //初始化坐标
			if ((p1.up.y >= 0) && (p1.up.y <= 10))
			{
				for (y = 0; y <= p1.up.y; y++)    //1段
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pa, pb) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))  {
						return true;
					}
				}
			}
			//////
			pa.x = a.x;   pb.x = b.x; //初始化坐标
			if ((p1.down.y <= 10) && (p2.up.y >= 0))
			{
				for (y = p1.down.y; y <= p2.up.y; y++)  //2段
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pa, pb) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))  {
						return true;
					}
				}
			}
			////
			pa.x = a.x;   pb.x = b.x; //初始化坐标
			if (p2.down.y <= 10)
			{
				for (y = p2.down.y; y <= 10; y++)           //3段
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pa, pb) && CheckLine(p1.down, pa) && CheckLine(p2.down, pb))  { return true; }

				}
			}
		}
	}
	//xy 坐标 都不相同 }}}}}}}}}
	return false;
}

//模拟点击两个棋子
bool Click2p(POINT p1, POINT p2)
{
	//点击p1
	HWND hwnd = getGameHWND();
	int lparam;
	lparam = ((p1.y * 35 + 192) << 16) + (p1.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//
	//点击p2
	lparam = ((p2.y * 35 + 192) << 16) + (p2.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//
	return true;
}

//消除一对棋子
bool ClearPiar()
{
	//读出棋盘数据至chessdata
	updatdChess();

	//int xMax = 19;	//棋盘X坐标最大数据
	//int yMax = 11;	//棋盘Y坐标最大数据

	//遍历整个棋盘 找出相同类型 一对棋子
	POINT p1, p2;
	int x1, y1, x2, y2;
	for (y1 = 0; y1 < 11; y1++){
		for (x1 = 0; x1 < 19; x1++){		//遍历棋盘

			for (y2 = y1; y2 < 11; y2++){
				for (x2 = 0; x2 < 19; x2++){	//第二次遍历棋盘
					if ((chessdata[y1][x1] == chessdata[y2][x2]) // 棋子1与棋子2 类型是否相同
						&& (!((x1 == x2) && (y1 == y2)))  //要求点1与点2 相等则假
						){
						p1.x = x1; p1.y = y1;
						p2.x = x2; p2.y = y2;
						//检测 相同的2个棋子是否可消掉
						if (Check2p(p1, p2)){//如果可消除 则返回真
							//click2p 鼠标模拟 点击 p1，p2
							Click2p(p1, p2);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}