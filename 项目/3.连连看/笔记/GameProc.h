#include "stdafx.h" 
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