#pragma once
#include<Windows.h>

class init
{
public:
	static void font();
	static void resetxy();
	static void main(WNDPROC w1, WNDPROC w2, WNDPROC w3);
	static void MainWindow();
	static void regwindow(WNDPROC w1, WNDPROC w2, WNDPROC w3);
	static DWORD WINAPI Regwindows(); // �޸�����
	static DWORD WINAPI Upgrade();    // �޸�����
	static void music();
};
