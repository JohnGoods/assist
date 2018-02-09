#include "stdafx.h" 
#include "ChessPoint.h"

//��ָ��
#define gameHandle L"QQ��Ϸ - ��������ɫ��"		//����
#define SEAT_ADDRESS 0x00171618		//��λ��ַ
#define CHESSBOARD_ADDRESS 0x00189F78		//����

//��Ϸ ���ܺ���
RECT r1;
POINT p;
byte chessdata[11][19];//a[y][x]
//��ȡ��Ϸ���ھ��
HWND getGameHWND(){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	return game_hwnd;
}

//�򿪽���Id
DWORD getGameProcessId(){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	DWORD processid;
	::GetWindowThreadProcessId(game_hwnd, &processid);
	return processid;
}

//��ָ������ �ڴ�����
HANDLE getGameProcessHandle(long address){
	HWND game_hwnd = ::FindWindow(NULL, gameHandle);
	DWORD processid;
	::GetWindowThreadProcessId(game_hwnd, &processid);
	HANDLE processH = ::OpenProcess(address, false, processid);
	return processH;
}


void startGame()
{
	//��ȡ��Ϸ���ھ��
	HWND gameh = getGameHWND();
	//���浱ǰ���ָ��
	::GetWindowRect(gameh, &r1);
	//ȡ�õ�ǰ���λ��
	GetCursorPos(&p);
	//�������ָ��λ��  ȡ������������:x=655;y=577 //lparam 0x0241028f
	SetCursorPos(655 + r1.left, 577 + r1.top);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	//����ڵ�ǰλ��̧��
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	//��ԭ���λ��
	Sleep(100);//��һ��ʱ�� ��ִ�к�ߵĴ���
	SetCursorPos(p.x, p.y);
}


//�������������� chessdata
void updatdChess() 
{
	//��ָ������ �ڴ�����
	HANDLE processH = getGameProcessHandle(PROCESS_ALL_ACCESS);	//����ַ�Ϳ��Ի�ȡ��ָ������ �ڴ�������
	DWORD byread;
	LPCVOID pbase = (LPCVOID)CHESSBOARD_ADDRESS; //�������ݻ�ַ
	LPVOID  nbuffer = (LPVOID)&chessdata;    //�����������
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);	
}

//���2��� �Ƿ���ͨ������һ��ȫΪ0��ֱ��·����
bool CheckLine(POINT p1, POINT p2)
{
	int x, y, t;   
	//ͬһ���ϵ������ ȫΪ0 �򷵻��� 
	//��� p1 == p2 Ҳ������
	if ((p1.x == p2.x) && (p1.y == p2.y) && (chessdata[p1.y][p1.x] == 0) && (chessdata[p2.y][p2.x] == 0))  {
		return true;
	}
	else{
		//��ֹԽ��
		if ((p1.x < 0) || (p1.x>18) || (p1.y < 0) || (p1.y>10) ||
			(p2.x < 0) || (p2.x>18) || (p2.y < 0) || (p2.y>10))  {
			return false;
		}

		if (p1.x == p2.x){     //���X������� �Ƚ�
			//�������Ӧ���������ھ�����
			if (p1.y > p2.y) {
				t = p1.y;
				p1.y = p2.y;
				p2.y = t;
			}
			//�жϴ��ϵ���һ��ֱ�߼� ���������� ��û���������ӵ�ס
			for (y = p1.y; y <= p2.y; y++){
				if (chessdata[y][p1.x] != 0) {
					return false;
				}
			}
		}

		if (p1.y == p2.y){    //���Y����� ��Ƚ�
			//�������Ӧ���������ھ�����
			if (p1.x > p2.x){
				t = p1.x;
				p1.x = p2.x;
				p2.x = t;
			}
			//�жϴ�����һ��ֱ�߼� ���������� ��û���������ӵ�ס
			for (x = p1.x; x <= p2.x; x++){
				if (chessdata[p1.y][x] != 0){
					return false;
				}
			}
		}
	}
	return  true;
}

//��� p1,p2 2������ �Ƿ��������
//bool check2p(POINT p1, POINT p2)
//{ 
//	ChessPoint pa(p1), pb(p2); //��ʼ��������
//	POINT p11, p22;
//	int x, y;
//	//��� p1,p2 2������ �Ƿ��������
//	// Y������ͬ������� p1,p2 
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
//	//X������ͬ������� p1,p2
//	//LineNull(p1.down,p2.up)    //������
//	if (p1.x == p2.x)
//	{
//
//		if (CheckLine(pa.down, pb.up)) return true;
//		// //pa,pb ; pa,p_1;pb,p_2;
//	}
//	//X��Y���궼��������� p1,p2
//	//lineNull(p1.down,pa),LineNull(p2.down,pb),LineNull(pa,pb)//������
//	return true;
//}




//��� a,b 2������ �Ƿ��������
bool Check2p(POINT a, POINT b)
{
	ChessPoint p1(a), p2(b);
	POINT pa, pb;//ת�ǵ�
	int x, y;

	/*�ȳ���ļ��*/
	//�������Ϊͬһ�� �򷵻�false
	if ((a.x == b.x) && (a.y == b.y))  { 
		return false;
	}
	//���������һ������Ϊ0 or ����Ĳ�����ͬ������ �򷵻�false
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

	/*�ж�����ɷ�����*/

	pa = a; pb = b;	 //pa pb��ֵ

	//----------- ��һ�����(��ֻ�����ں���һ������ y���� ��ͬ) -----------
	if (a.y == b.y){
		//�����������ھ�...
		if ((p1.right.x == p2.p.x) || (p1.left.x == p2.p.x)){	
			return true;
		}

		//�ȼ�� �������Ƿ���һ��·����ͨ
		if (CheckLine(p1.right, p2.left)){
			return true;
		}

		//��� ����

		//���ж���
		/* ��������������
		 ___________
		|			|
		P1			p2
		*/
		//pa = a; pb = b;
		//���������ǲ�����·��ȥ������ ���������ж�Y���ǲ��������
		if ((p1.up.y >= 0) && (p1.up.y <= 10)){
			for (y = 0; y <= p1.up.y; y++)
			{
				pa.y = y; pb.y = y;
				//��������� ������ֱ��û���� �Ǿ��ǿ���������
				if (CheckLine(pa, p1.up) && CheckLine(pb, p2.up) && CheckLine(pa, pb))
				{
					return true;
				}
			}
		}

		//�ж���
		/* ��������������
		P1			p2
		|			|
		-------------
		*/
		//pa = a; pb = b;
		//�������ײ��ǲ�����·��ȥ������ ���������ж�Y���ǲ�������ײ�
		if ((p1.down.y >= 0) && (p1.down.y <= 10)){
			//��������� ������ֱ��û���� �Ǿ��ǿ���������
			for (y = p1.down.y; y <= 10; y++)
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pa, p1.down) && CheckLine(pb, p2.down) && CheckLine(pa, pb))  {
					return true; 
				}
			}

		}
		//��Ϊ y�����,���Բ���������·��
	}
	//----------- �ڶ������(����һ����  x ���� ��ͬ) -----------
	else if (a.x == b.x){
		//x���� ���ڲ�
		if ((p1.down.y == p2.p.y) || (p1.up.y == p2.p.y))   {
			return true;
		}
		//��� �������Ƿ���һ��·����ͨ
		if (CheckLine(p1.down, p2.up))  { 
			return true;
		}

		//��� ����
		//x��
		//pa = a; pb = b;
		for (x = 0; x <= p1.left.x; x++)
		{
			pa.x = x;
			pb.x = x;
			if (CheckLine(pa, p1.left) && CheckLine(pb, p2.left) && CheckLine(pa, pb))  { return true; }
		}

		//x��
		//pa = a; pb = b;
		for (x = p1.right.x; x <= 18; x++)
		{
			pa.x = x;
			pb.x = x;
			if (CheckLine(pa, p1.right) && CheckLine(pb, p2.right) && CheckLine(pa, pb))  { return true; }
		}

		//��Ϊ y�����,���Բ���������·��
	}
	////----------- ���������(xy ���� ������ͬ) -----------
	else{
		//pa = a; pb = b;
		if (a.x > b.x)  {   // p2�� �� �� left
			////////////////xxxxxxxxxxxxxxxxx  ��x��·��
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
			/////////////////yyyyyyyyyyyyyyyyyyyy ��y��·�� �����Ǵ������� ���� ����p1.y>p2.y
			pa.x = a.x;   pb.x = b.x; //��ʼ������ yܑ����
			for (y = 0; y <= p1.up.y; y++)    //1��
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pb, pa) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))      {
					return true;
				}
			}
			////////////////////////
			for (y = p1.down.y; y <= p2.up.y; y++)//2��
			{
				pa.y = y; pb.y = y;
				if (CheckLine(pb, pa) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))   {
					return true;
				}
			}
			///////////////////////
			for (y = p2.down.y; y <= 10; y++) //3��
			{
				///////////////////////////////
				pa.y = y; pb.y = y;
				if (CheckLine(pb, pa) && CheckLine(p1.down, pa) && CheckLine(p2.down, pb))   { return true; }
			}

		}
		else{////////////p2��  �� �� right a.x>b.x
			pa.y = a.y;   pb.y = b.y; //��ʼ������
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
			///////////////////////yyyyyyyyyyyyyyyyyy   y�ὥ��
			pa.x = a.x;   pb.x = b.x; //��ʼ������
			if ((p1.up.y >= 0) && (p1.up.y <= 10))
			{
				for (y = 0; y <= p1.up.y; y++)    //1��
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pa, pb) && CheckLine(pa, p1.up) && CheckLine(pb, p2.up))  {
						return true;
					}
				}
			}
			//////
			pa.x = a.x;   pb.x = b.x; //��ʼ������
			if ((p1.down.y <= 10) && (p2.up.y >= 0))
			{
				for (y = p1.down.y; y <= p2.up.y; y++)  //2��
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pa, pb) && CheckLine(p1.down, pa) && CheckLine(pb, p2.up))  {
						return true;
					}
				}
			}
			////
			pa.x = a.x;   pb.x = b.x; //��ʼ������
			if (p2.down.y <= 10)
			{
				for (y = p2.down.y; y <= 10; y++)           //3��
				{
					pa.y = y; pb.y = y;
					if (CheckLine(pa, pb) && CheckLine(p1.down, pa) && CheckLine(p2.down, pb))  { return true; }

				}
			}
		}
	}
	//xy ���� ������ͬ }}}}}}}}}
	return false;
}

//ģ������������
bool Click2p(POINT p1, POINT p2)
{
	//���p1
	HWND hwnd = getGameHWND();
	int lparam;
	lparam = ((p1.y * 35 + 192) << 16) + (p1.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//
	//���p2
	lparam = ((p2.y * 35 + 192) << 16) + (p2.x * 31 + 21);
	SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//
	return true;
}

//����һ������
bool ClearPiar()
{
	//��������������chessdata
	updatdChess();

	//int xMax = 19;	//����X�����������
	//int yMax = 11;	//����Y�����������

	//������������ �ҳ���ͬ���� һ������
	POINT p1, p2;
	int x1, y1, x2, y2;
	for (y1 = 0; y1 < 11; y1++){
		for (x1 = 0; x1 < 19; x1++){		//��������

			for (y2 = y1; y2 < 11; y2++){
				for (x2 = 0; x2 < 19; x2++){	//�ڶ��α�������
					if ((chessdata[y1][x1] == chessdata[y2][x2]) // ����1������2 �����Ƿ���ͬ
						&& (!((x1 == x2) && (y1 == y2)))  //Ҫ���1���2 ������
						){
						p1.x = x1; p1.y = y1;
						p2.x = x2; p2.y = y2;
						//��� ��ͬ��2�������Ƿ������
						if (Check2p(p1, p2)){//��������� �򷵻���
							//click2p ���ģ�� ��� p1��p2
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