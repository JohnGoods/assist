#include "stdafx.h" 
#include "ChessPoint.h"
//��Ϸ ���ܺ���
HWND gameh;
RECT r1;
POINT p;//x,y
void startGame()
{
	// TODO: Add your control notification handler code here
	//��ȡ��Ϸ���ھ��
	gameh = ::FindWindow(NULL, L"QQ��Ϸ - ��������ɫ��");
	::GetWindowRect(gameh, &r1);
	//���浱ǰ���ָ��
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


byte chessdata[11][19];//a[y][x]
//�������������� chessdata
void updatdChess() 
{
	// TODO: Add your control notification handler code here
	//��ȡ���ھ��
	HWND gameh = ::FindWindow(NULL, L"QQ��Ϸ - ��������ɫ��");
	//��ȡ���ڽ���ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//��ָ������
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//��ָ������ �ڴ�����
	DWORD byread;
	LPCVOID pbase = (LPCVOID)0x0012A508; //�������ݻ�ַ
	LPVOID  nbuffer = (LPVOID)&chessdata;    //�����������
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);
}

bool lineNull(POINT p1, POINT p2)
{
	return true;
}

//��� p1,p2 2������ �Ƿ��������
bool check2p(POINT p1, POINT p2)
{ 
	// Y������ͬ������� p1,p2 
	//lineNull(p1.right,p2.left) //������
	if (p1.y == p2.y)
	{
		ChessPoint pa(p1), pb(p2);

		if (lineNull(pa.down, pb.up)) return true;
	}
	//X������ͬ������� p1,p2
	//LineNull(p1.down,p2.up)    //������
	if (p1.x == p2.x)
	{
		ChessPoint pa(p1), pb(p2);

		if (lineNull(pa.down, pb.up)) return true;
	}

	//X��Y���궼��������� p1,p2
	//lineNull(p1.down,pa),LineNull(p2.down,pb),LineNull(pa,pb)
	//������
	return true;
}

//ģ��������
bool click2p(POINT p1, POINT p2)
{
	return true;
}

//����һ������
void ClearPiar()
{
	//��������������chessdata 11,19
	updatdChess();
	//������������ �ҳ���ͬ���� һ������
	POINT p1, p2;
	int x1, y1, x2, y2;
	for (y1 = 0; y1<11; y1++)
	for (x1 = 0; x1<19; x1++)
	{
		for (y2 = y1; y2<11; y2++)
		for (x2 = x1; x2<19; x2++)
		if ((chessdata[y1][x1] == chessdata[y2][x2]) // ����1������2 �����Ƿ���ͬ
			&& (!((x1 == x2) && (y1 == y2)))  //Ҫ���1���2 ������
			)
		{
			p1.x = x1; p1.y = y1;
			p2.x = x2; p2.y = y2;
			//��� ��ͬ��2�������Ƿ������
			if (check2p(p1, p2))//��������� �򷵻���
			{
				//click2p ���ģ�� ��� p1��p2
				click2p(p1, p2);

			}
		}
	}

}