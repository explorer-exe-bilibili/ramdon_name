#include "floatwindow.h"
#include<Windows.h>
#include "mywindows.h"
#include "resource.h"
#include "set-json.h"

extern set2 setscreen;
bool showfloatwindow = 1,showQuitwindow=1;
WNDPROC floatwindow::g_OrigFloatWndProc = NULL;
bool floatwindow::is_mouse_dragging;
POINT floatwindow::p, floatwindow::p1;
POINT floatwindow::last_mouse_pos;
bool showing = 0;
HBITMAP floatwindow::bitmap;
int floatwindow::icon_w, floatwindow::icon_h;
HBITMAP black;

void floatwindow::open()
{
	if (showfloatwindow) {
		showfloatwindow = 0;
		createWindow();
	}

}

void floatwindow::stop()
{
	ShowWindow(mywindows::float_hWnd, SW_HIDE);
}

void floatwindow::paint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mywindows::float_hWnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	RECT rect;
	GetWindowRect(mywindows::float_hWnd, &rect);
	int w = rect.right - rect.left, h = rect.bottom - rect.top;
	SelectObject(hdcMem, black);
	StretchBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, icon_w, icon_h, SRCCOPY);
	SelectObject(hdcMem, bitmap);
	SetBkColor(hdc, RGB(0, 0, 0));
	StretchBlt(hdc, 0, 0, w, h, hdcMem, 0, 0,icon_w , icon_h, SRCCOPY);
	DeleteDC(hdcMem);
	DeleteDC(hdc);
	EndPaint(mywindows::float_hWnd, &ps);
}

void floatwindow::createWindow() {
	// �����������ڵ�λ�úʹ�С
	const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	constexpr int floatWndWidth = 50;
	constexpr int floatWndHeight = 50;
	const int floatWndX = screenWidth - floatWndWidth - 10;
	const int floatWndY = screenHeight - floatWndHeight - 10;

	// ������������
	mywindows::float_hWnd = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST| WS_EX_TOOLWINDOW,
		L"FLOAT",L"Float Window", WS_POPUPWINDOW,
		floatWndX, floatWndY, floatWndWidth, floatWndHeight,
		NULL, NULL, mywindows::hinstance, NULL);

	// �����������ڵĳ�ʼ͸����
	SetLayeredWindowAttributes(mywindows::float_hWnd, 0, 128, LWA_ALPHA);
	// ��ʾ��������
	ShowWindow(mywindows::float_hWnd, SW_SHOWNOACTIVATE);
	UpdateWindow(mywindows::float_hWnd);
	int x, y, w, h;
	x = 0; y = 0; w = mywindows::screenWidth; h = mywindows::screenHeight * 0.3;
	mywindows::Quit_hwnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TOPMOST|WS_EX_TOOLWINDOW,
		L"QUIT", L"", WS_VISIBLE | WS_POPUP, x, y, w, h, NULL, NULL, mywindows::hinstance, 0);
	SetLayeredWindowAttributes(mywindows::Quit_hwnd, 0, 200, LWA_ALPHA);
	ShowWindow(mywindows::Quit_hwnd, SW_HIDE);
}

void floatwindow::showQuitWindow()
{
	if (!showing) {
		showing = 1;
		ShowWindow(mywindows::Quit_hwnd, SW_SHOWNOACTIVATE);
	}
}

void floatwindow::create()
{
	BITMAP bmp;
	bitmap= (HBITMAP)LoadImage(NULL, L"files\\imgs\\OIP-C.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(bitmap, sizeof(BITMAP), &bmp);
	icon_w = bmp.bmWidth; icon_h = bmp.bmHeight;
}

void floatwindow::hideQuitWindow()
{
	if (showing) {
		ShowWindow(mywindows::Quit_hwnd, SW_HIDE);
		showing = 0;
	}
}

BOOL floatwindow::IsEntirelyCovered(HWND hWnd)
{
	RECT rectWnd, rectDesktop;
	HRGN hRgnWindow, hRgnDesktop;

	// ��ȡ���ھ�������
	GetWindowRect(hWnd, &rectWnd);

	// ��ȡ���洰�ھ��
	HWND hDesktopWnd = GetDesktopWindow();

	// ��ȡ���洰�ھ�������
	GetWindowRect(hDesktopWnd, &rectDesktop);

	// ������������
	hRgnWindow = CreateRectRgnIndirect(&rectWnd);

	// ������������
	hRgnDesktop = CreateRectRgnIndirect(&rectDesktop);

	// �����������������������
	CombineRgn(hRgnDesktop, hRgnDesktop, hRgnWindow, RGN_DIFF);

	// ����ʣ�������еĴ���
	HWND hWndCover = NULL;
	while ((hWndCover = GetWindow(mywindows::main_hwnd, GW_HWNDNEXT)) != NULL)
	{
		if (IsWindowVisible(hWndCover) && hWndCover != hWnd && hWndCover != hDesktopWnd)
		{
			HRGN hRgnCover{};
			GetWindowRgn(hWndCover, hRgnCover);

			// �����Ǵ�����������������м�ȥ
			CombineRgn(hRgnDesktop, hRgnDesktop, hRgnCover, RGN_DIFF);
			DeleteObject(hRgnCover);
		}
	}

	// ���ʣ������Ϊ��,˵�����ڱ���ȫ�ڵ�
	const BOOL bCovered = (GetRgnBox(hRgnDesktop, &rectDesktop) == NULLREGION);

	DeleteObject(hRgnWindow);
	DeleteObject(hRgnDesktop);

	return bCovered;
}

BOOL floatwindow::IsFullScreen(HWND hWnd)
{
	RECT rectWnd, rectDesktop;

	// ��ȡ���ھ�������
	GetWindowRect(hWnd, &rectWnd);

	// ��ȡ���洰�ھ�������
	HWND hDesktopWnd = GetDesktopWindow();
	GetWindowRect(hDesktopWnd, &rectDesktop);

	// �����������������������ȫ�غ�,����Ϊ��ȫ��
	return (EqualRect(&rectWnd, &rectDesktop));
}

LRESULT floatwindow::nchittest(WPARAM wParam)
{
	if (wParam == HTLEFT)
	{
		SetCapture(mywindows::float_hWnd);
		return HTCAPTION;
	}
	return HTCLIENT;
}

void floatwindow::lbuttondown(WPARAM wParam)
{
	if (wParam == HTCLIENT)
	{
		showQuitWindow();
		GetCursorPos(&p); //��ȡ���λ��
		is_mouse_dragging = true;
		GetCursorPos(&last_mouse_pos);
		SetCapture(mywindows::float_hWnd);
	}
}

void floatwindow::mousemove()
{
	if (is_mouse_dragging)
	{
		POINT currentMousePos;
		GetCursorPos(&currentMousePos);

		RECT rect;
		GetWindowRect(mywindows::float_hWnd, &rect);

		int dx = currentMousePos.x - last_mouse_pos.x;
		int dy = currentMousePos.y - last_mouse_pos.y;

		MoveWindow(mywindows::float_hWnd, rect.left + dx, rect.top + dy, rect.right - rect.left, rect.bottom - rect.top, TRUE);

		last_mouse_pos = currentMousePos;
	}
}

void floatwindow::lbuttonup()
{
	if (is_mouse_dragging)
	{
		hideQuitWindow();
		GetCursorPos(&p1); //��ȡ���λ��
		is_mouse_dragging = false;
		ReleaseCapture();
		if (-3 <= (p.x - p1.x)AND(p.x - p1.x) <= 3 AND - 3 <= (p.y - p1.y)AND(p.y - p1.y) <= 3)
		{
			ShowWindow(mywindows::main_hwnd, SW_SHOW);
			ShowWindow(mywindows::float_hWnd, SW_HIDE);
		}
	}
	POINT currentMousePos;
	GetCursorPos(&currentMousePos);
	if (currentMousePos.y <= mywindows::screenHeight * 0.3) {
		PostQuitMessage(0);
	}
}

void floatwindow::lbuttonclick(WPARAM wParam)
{
	if (wParam == HTCLIENT)
	{
		// ˫�������ڲ�����ʱ�Ĳ�����������ʾ/����������
		ShowWindow(mywindows::main_hwnd, SW_SHOW);
		ShowWindow(mywindows::float_hWnd, SW_HIDE);
	}
}