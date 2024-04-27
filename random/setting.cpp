#include "setting.h"
#pragma once
#include <Shlobj.h>
#include <tchar.h>
#include <Commctrl.h>
#include<filesystem>
#include"mywindows.h"
#include "config.h"
#include"directshow.h"
#include "sth2sth.h"
#include "bitmaps.h"
#include"ui.h"
using namespace std;

namespace fs = std::filesystem;
#pragma comment(lib, "comctl32.lib")

extern HBITMAP hbitmaps[BitmapCounts];
extern BITMAP overlay1Bm, bm, ball, overlay2Bm, overlay3Bm, overlay4Bm, cardbg, exitinfo, goldenbg, listbm;

bool setting::fullscreen, setting::offmusic = 0;
setting::sNode* setting::shead = NULL;
int setting::settingpage = 1;
BITMAP setting::setbm, setting::setbu;
bool setting::offvideo = 0, setting::reran = 0;
HWND setting::textboxhwnd[TEXTBOXHWNDNUMBER] = { NULL };
int setting::textboxnumber = 0;
bool setting::isused[TEXTBOXHWNDNUMBER + BOTTONNUMBER] = { 0 }, setting::changebitmap[4] = { 0 };
setting::settingxy setting::sxy[20];
static bool firstpaint = 1;
int nextbmx, nextbmy, nextxend, nextyend;
int lastbmx, lastbmy, lastxend, lastyend;
int totalp = 3;
void setting::paintsettingpage(HDC hdc, HDC hdcMem) {
	if (firstpaint) {
		SelectObject(hdcMem, hbitmaps[SetBM]);
		StretchBlt(hdc, 0, 0, mywindows::windowWidth, mywindows::windowHeight, hdcMem, 0, 0, setbm.bmWidth, setbm.bmHeight, SRCCOPY);
		firstpaint = 0;
	}
	SelectObject(hdcMem, hbitmaps[exitb]);
	StretchBlt(hdc, ui::exitx, ui::exity, ui::exitxend - ui::exitx, ui::exityend - ui::exity, hdcMem, 0, 0, exitinfo.bmWidth, exitinfo.bmHeight, SRCAND);
	SelectObject(hdcMem, hbitmaps[exiti]);
	StretchBlt(hdc, ui::exitx, ui::exity, ui::exitxend - ui::exitx, ui::exityend - ui::exity, hdcMem, 0, 0, exitinfo.bmWidth, exitinfo.bmHeight, SRCPAINT);
	switch (settingpage)
	{
	case 1: {
		switchbm(fullscreen, L"ȫ��ģʽ", 1, hdc, hdcMem);
		switchbm(OFF_VIDEO, L"�ر���Ƶ", 2, hdc, hdcMem);
		switchbm(offmusic, L"�ر�����", 3, hdc, hdcMem);
		textbox(1, 4, WINDOW_TITEL, L"��������", hdc, hdcMem, 0);
		textbox(0, 5, SPECIAL, L"�鱳����", hdc, hdcMem, 0);
		textbox(2, 6, OVER1, L"����1ͼƬ", hdc, hdcMem, 1);
		textbox(3, 7, OVER2, L"����2ͼƬ", hdc, hdcMem, 1);
		textbox(4, 8, OVER3, L"����3ͼƬ", hdc, hdcMem, 1);
		textbox(5, 9, OVER4, L"����4ͼƬ", hdc, hdcMem, 1);
		textbox(6, 10, NAMES1, L"�����ļ�1", hdc, hdcMem, 1);
		textbox(7, 11, NAMES2, L"�����ļ�2", hdc, hdcMem, 1);
		textbox(8, 12, NAMES3, L"�����ļ�3", hdc, hdcMem, 1);
		textbox(9, 13, NAMES4, L"�����ļ�4", hdc, hdcMem, 1);
		textbox(10, 14, SIGNALSTAR3, L"����3����Ƶ", hdc, hdcMem, 1);
		textbox(11, 15, SIGNALSTAR4, L"����4����Ƶ", hdc, hdcMem, 1);
		textbox(12, 16, SIGNALSTAR5, L"����5����Ƶ", hdc, hdcMem, 1);
		textbox(13, 17, GROUPSTAR4, L"ʮ��4����Ƶ", hdc, hdcMem, 1);
		textbox(14, 18, GROUPSTAR5, L"ʮ��5����Ƶ", hdc, hdcMem, 1);
	}break;
	}
	wstring t = to_wstring(settingpage) + L"/" + to_wstring(totalp);
	SelectObject(hdc, ui::icon_mid);
	TextOut_(hdc, nextbmx , nextbmy , L"b");
	TextOut_(hdc, lastbmx, lastbmy, L"c");
	SelectObject(hdc, ui::text_mid);
	TextOut_(hdc, mywindows::windowWidth * 0.765, mywindows::windowHeight * 0.91, t.c_str());
}
void setting::switchbm(const wchar_t* configname, const wchar_t* name, int number, HDC hdc, HDC hdcMem) {
	SelectObject(hdc, ui::text_mid);
	SetBkColor(hdc, RGB(236, 229, 216));
	SelectObject(hdcMem, hbitmaps[setbutton]);
	StretchBlt(hdc, sxy[number].bmx, sxy[number].bmy, sxy[number].bmw, sxy[number].bmh, hdcMem, 0, 0, setbu.bmWidth, setbu.bmHeight, SRCCOPY);
	TextOut_(hdc, sxy[number].x, sxy[number].y + mywindows::windowHeight * 0.01, name);
	if (std::stoi(config::get(configname)) == 1)TextOut_(hdc, sxy[number].bmx + mywindows::windowWidth * 0.04, sxy[number].bmy + mywindows::windowHeight * 0.01, L"��");
	else TextOut_(hdc, sxy[number].bmx + mywindows::windowWidth * 0.04, sxy[number].bmy + mywindows::windowHeight * 0.01, L"��");
	int x = sxy[number].bmx, y = sxy[number].bmy, xend = sxy[number].bmxend, yend = sxy[number].bmh + sxy[number].bmy;
	sNode* newnode = new sNode;
	if (newnode == NULL) {
		mywindows::errlog("Memory allocation error(textbox)");
	};
	newnode->x = x;
	newnode->xend = xend;
	newnode->y = y;
	newnode->yend = yend;
	newnode->next = shead;
	newnode->number = number;
	shead = newnode;
}
void setting::changepage()
{
	char n = 0;
	while (textboxhwnd[n] != 0) {
		DestroyWindow(textboxhwnd[n]);
		n++;
	}
	for (n = 0; n < TEXTBOXHWNDNUMBER + BOTTONNUMBER; n++)isused[n] = 0;
	firstpaint = 1;
}
void setting::switchbm(bool OnOrOff, const wchar_t* name, int number, HDC hdc, HDC hdcMem) {
	SelectObject(hdc, ui::text_mid);
	SetBkColor(hdc, RGB(236, 229, 216));
	SelectObject(hdcMem, hbitmaps[setbutton]);
	StretchBlt(hdc, sxy[number].bmx, sxy[number].bmy, sxy[number].bmw, sxy[number].bmh, hdcMem, 0, 0, setbu.bmWidth, setbu.bmHeight, SRCCOPY);
	TextOut_(hdc, sxy[number].x, sxy[number].y + mywindows::windowHeight * 0.01, name);
	if (OnOrOff == 1)TextOut_(hdc, sxy[number].bmx + mywindows::windowWidth * 0.04, sxy[number].bmy + mywindows::windowHeight * 0.01, L"��");
	else TextOut_(hdc, sxy[number].bmx + mywindows::windowWidth * 0.04, sxy[number].bmy + mywindows::windowHeight * 0.01, L"��");
	int x = sxy[number].bmx, y = sxy[number].bmy, xend = sxy[number].bmxend, yend = sxy[number].bmh + sxy[number].bmy;
	sNode* newnode = new sNode;
	if (newnode == NULL) {
		mywindows::errlog("Memory allocation error(textbox)");
	};
	newnode->x = x;
	newnode->xend = xend;
	newnode->y = y;
	newnode->yend = yend;
	newnode->next = shead;
	newnode->number = number;
	shead = newnode;
}
void setting::textbox(int ebnumber, int number, std::wstring configname, LPCWSTR name, HDC hdc, HDC hdcMem, bool getfile) {
	SelectObject(hdc, ui::text_mid);
	SetBkColor(hdc, RGB(236, 229, 216));
	SelectObject(hdcMem, hbitmaps[setbutton]);
	TextOut_(hdc, sxy[number].x, sxy[number].y + mywindows::windowHeight * 0.01, name);
	std::wstring wst = config::get(configname).c_str();
	if (isused[ebnumber] == 0) {
		textboxhwnd[ebnumber] = CreateEditBox(mywindows::hWnd, ebnumber, sxy[number].bmx, sxy[number].bmy, sxy[number].bmw, sxy[number].bmh, wst.c_str());
	}
	if (getfile) {
		if (!isused[ebnumber + TEXTBOXHWNDNUMBER]) {
			StretchBlt(hdc, sxy[number].bmxend, sxy[number].bmy, sxy[number].bmw, sxy[number].bmh, hdcMem, 0, 0, setbu.bmWidth, setbu.bmHeight, SRCCOPY);
			TextOut_(hdc, sxy[number].bmxend + mywindows::windowWidth * 0.02, sxy[number].y + mywindows::windowHeight * 0.01, L"ѡ���ļ�");

			int x = sxy[number].bmxend, y = sxy[number].bmy, xend = sxy[number].bmxend + sxy[number].bmw, yend = sxy[number].bmh + sxy[number].bmy;
			if (!isused[ebnumber]) {
				sNode* newnode = new sNode;
				if (newnode == nullptr) {
					mywindows::errlog(L"Memory allocation error(textbox)");
				}
				newnode->x = x;
				newnode->xend = xend;
				newnode->y = y;
				newnode->yend = yend;
				newnode->next = shead;
				newnode->number = number;
				shead = newnode;
			}
		}
	}
	isused[ebnumber] = 1;
}
void  setting::settingkicked(int x, int y) {
	sNode* current = shead;
	int number = -1;
	if (x >= ui::exitx AND x <= ui::exitxend AND y >= ui::exity AND y <= ui::exityend)quit();
	else if (x >= nextbmx AND x <= nextxend AND y >= nextbmy AND y <= nextyend) {
		number = 0;
		settingpage--;
		if (settingpage < 1) {
			settingpage = totalp;
		}
		changepage();
	}
	else if (x >= lastbmx AND x <= lastxend AND y >= lastbmy AND y <= lastyend) {
		number = 0;
		settingpage++;
		if (settingpage > totalp) {
			settingpage = 1;
		}
		changepage();
	}
	else 
		while (current != NULL) {
			if (x >= current->x AND x <= current->xend AND y >= current->y AND y <= current->yend) {
				number = current->number;
				break;
			}
			current = current->next;
		}
	if (number != -1) {
		directshow::music(CLICK);
		switch (number)
		{
		case 1: {
			fullscreen = !fullscreen;
			if (fullscreen) config::replace(INWINDOW, L"0");
			else config::replace(INWINDOW, L"1");
		}break;
		case 2:
			offvideo = !offvideo;
			if (offvideo)
				config::replace(OFF_VIDEO, L"1");
			else config::replace(OFF_VIDEO, L"0");
			break;
		case 3:
			offmusic = !offmusic;
			if (offmusic) {
				mciSendString(L"stop bgm", NULL, 0, NULL);
				config::replace(OFFMUSIC, L"1");
			}
			else
			{
				mciSendString(L"play bgm repeat", NULL, 0, NULL);
				config::replace(OFFMUSIC, L"0");
			}break;
		case 6:
			OnButtonClick(mywindows::hWnd, L"ѡ��1����ͼƬ�ļ�", L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0", 2, OVER1);
			hbitmaps[over1] = (HBITMAP)LoadImage(NULL, config::get(OVER1).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			GetObject(hbitmaps[over1], sizeof(BITMAP), &overlay1Bm);
			break;
		case 7:
			OnButtonClick(mywindows::hWnd, L"ѡ��2����ͼƬ�ļ�", L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0", 3, OVER2);
			hbitmaps[over2] = (HBITMAP)LoadImage(NULL, config::get(OVER2).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			GetObject(hbitmaps[over2], sizeof(BITMAP), &overlay2Bm);
			break;
		case 8:
			OnButtonClick(mywindows::hWnd, L"ѡ��3����ͼƬ�ļ�", L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0", 4, OVER3);
			hbitmaps[over3] = (HBITMAP)LoadImage(NULL, config::get(OVER3).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			GetObject(hbitmaps[over3], sizeof(BITMAP), &overlay3Bm);
			break;
		case 9:
			OnButtonClick(mywindows::hWnd, L"ѡ��4����ͼƬ�ļ�", L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0", 5, OVER4);
			hbitmaps[over4] = (HBITMAP)LoadImage(NULL, config::get(OVER4).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			GetObject(hbitmaps[over4], sizeof(BITMAP), &overlay4Bm);
			break;
		case 10:
			OnButtonClick(mywindows::hWnd, L"ѡ�������ļ�", L"�����ļ�(*.txt)\0 * .txt\0", 6, NAMES1);
			reran = 1;
			break;
		case 11:
			OnButtonClick(mywindows::hWnd, L"ѡ�������ļ�", L"�����ļ�(*.txt)\0 * .txt\0", 7, NAMES2);
			reran = 1;
			break;
		case 12:
			OnButtonClick(mywindows::hWnd, L"ѡ�������ļ�", L"�����ļ�(*.txt)\0 * .txt\0", 8, NAMES3);
			reran = 1;
			break;
		case 13:
			OnButtonClick(mywindows::hWnd, L"ѡ�������ļ�", L"�����ļ�(*.txt)\0 * .txt\0", 9, NAMES4);
			reran = 1;
			break;
		case 14:
			OnButtonClick(mywindows::hWnd, L"ѡ�񵥷�3����Ƶ", L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0", 10, SIGNALSTAR3);
			break;
		case 15:
			OnButtonClick(mywindows::hWnd, L"ѡ�񵥷�4����Ƶ", L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0", 11, SIGNALSTAR4);
			break;
		case 16:
			OnButtonClick(mywindows::hWnd, L"ѡ�񵥷�5����Ƶ", L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0", 12, SIGNALSTAR5);
			break;
		case 17:
			OnButtonClick(mywindows::hWnd, L"ѡ��ʮ��4����Ƶ", L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0", 13, GROUPSTAR4);
			break;
		case 18:
			OnButtonClick(mywindows::hWnd, L"ѡ��ʮ��5����Ƶ", L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0", 14, GROUPSTAR5);
			break;
		}
	}
}
void setting::seteditbox(LPARAM lParam, WPARAM wParam) {
	// ��ȡ�ı���ľ��,ȷ��������Ч��
	HWND editBoxHwnd = (HWND)(lParam);
	int numberoftextbox = LOWORD(wParam);
	if (editBoxHwnd != NULL) {
		// ���仺������С,��������ı����е��ı����ᳬ��256���ַ�
		wchar_t sz[256];
		Edit_GetText(editBoxHwnd, sz, 256);
		// ��ʾ�ı����е��ı�
		if (wcslen(sz) != 0) {
			std::wstring tmp(sz);
			switch (numberoftextbox)
			{
			case 0:
				if (!tmp.empty()) {
					int value = std::stoi(tmp);
					if (value < 0 || value > 4) {
						MessageBoxW(NULL, L"����һ��0-4֮������֣�0��ʾ���ã�", L"����", MB_ICONERROR);
						return;
					}
					else config::replace(SPECIAL, tmp);
				}
				break;
			case 1:
				config::replace(WINDOW_TITEL, tmp);
				SetWindowTextW(mywindows::hWnd, tmp.c_str());
				break;
			case 2:
				if (fs::exists(tmp)) {
					config::replace(OVER1, tmp);
					changebitmap[0] = 1;
				}
				break;
			case 3:
				if (fs::exists(tmp)) {
					config::replace(OVER2, tmp);
					changebitmap[1] = 1;
				}
				break;
			case 4:
				if (fs::exists(tmp)) {
					config::replace(OVER3, tmp);
					changebitmap[2] = 1;
				}break;
			case 5:
				if (fs::exists(tmp)) {
					config::replace(OVER4, tmp);
					changebitmap[3] = 1;
				}break;
			case 6:
				if (fs::exists(tmp)) {
					config::replace(NAMES1, tmp);
				}break;
			case 7:
				if (fs::exists(tmp)) {
					config::replace(NAMES2, tmp);
				}break;
			case 8:
				if (fs::exists(tmp)) {
					config::replace(NAMES3, tmp);
				}break;
			case 9:
				if (fs::exists(tmp)) {
					config::replace(NAMES4, tmp);
				}break;
			case 10:
				if (fs::exists(tmp)) {
					config::replace(SIGNALSTAR3, tmp);
				}break;
			case 11:
				if (fs::exists(tmp)) {
					config::replace(SIGNALSTAR4, tmp);
				}break;
			case 12:
				if (fs::exists(tmp)) {
					config::replace(SIGNALSTAR5, tmp);
				}break;
			case 13:
				if (fs::exists(tmp)) {
					config::replace(GROUPSTAR4, tmp);
				}break;
			case 14:
				if (fs::exists(tmp)) {
					config::replace(GROUPSTAR5, tmp);
				}break;
			default:
				break;
			}
		}
	}
	ui::ScreenModeChanged = 1;
}
//����һ���ı���
HWND setting::CreateEditBox(HWND hWndParent, int NUMBER, int x, int y, int w, int h, const wchar_t* words) {
	// ����EDIT�ؼ�����ʽ
	DWORD editStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL;

	// ����EDIT�ؼ��ĸ�����ʽ����ѡ��
	DWORD editExStyle = WS_EX_CLIENTEDGE;

	// �����ı���
	HWND hEdit = CreateWindowExW(editExStyle, L"EDIT", words, editStyle, x, y, w, h, hWndParent, (HMENU)NUMBER, NULL, NULL);

	// �����ı�����
	return hEdit;
}
void setting::init() {
	mywindows::log(L"Free Setting List complete");
	for (char i = 1; i <= 10; i++) {
		sxy[i].x = mywindows::windowWidth * 0.05;
		sxy[i].y = mywindows::windowHeight * (i) * 0.09;
		sxy[i].bmx = mywindows::windowWidth * 0.25;
		sxy[i].bmxend = mywindows::windowWidth * 0.35;
		sxy[i].bmy = sxy[i].y;
		sxy[i].bmyend = sxy[i].y + mywindows::windowHeight * 0.07;
		sxy[i].bmw = mywindows::windowWidth * 0.1;
		sxy[i].bmh = mywindows::windowWidth * 0.03;
	}
	for (char i = 11; i <= 19; i++) {
		sxy[i].x = mywindows::windowWidth * 0.55;
		sxy[i].y = mywindows::windowHeight * (i - 9) * 0.09;
		sxy[i].bmx = mywindows::windowWidth * 0.75;
		sxy[i].bmxend = mywindows::windowWidth * 0.85;
		sxy[i].bmy = sxy[i].y;
		sxy[i].bmyend = sxy[i].y + mywindows::windowHeight * 0.07;
		sxy[i].bmw = mywindows::windowWidth * 0.1;
		sxy[i].bmh = mywindows::windowWidth * 0.03;
	}

	nextbmx = mywindows::windowWidth * 0.73;
	nextbmy = mywindows::windowHeight * 0.91;
	nextxend = mywindows::windowWidth * 0.752;
	nextyend = mywindows::windowHeight * 0.95;
	lastbmx = mywindows::windowWidth * 0.8;
	lastbmy = mywindows::windowHeight * 0.91;
	lastxend = mywindows::windowWidth * 0.822;
	lastyend = mywindows::windowHeight * 0.95;
}
// ����������һ���¼��������У����簴ť����¼�
void setting::OnButtonClick(HWND hwnd, LPCWSTR title, LPCWSTR filter, int number, const wchar_t* configname)
{
loop:
	OPENFILENAMEW ofn = { 0 };
	wchar_t strFilename[MAX_PATH] = { 0 }; // ���ڽ����ļ���

	ofn.lStructSize = sizeof(OPENFILENAMEW); // �ṹ���С
	ofn.hwndOwner = mywindows::hWnd; // ӵ���ߴ��ھ��,ΪNULL��ʾ�Ի����Ƿ�ģ̬��,ʵ��Ӧ����һ�㶼Ҫ��������
	ofn.lpstrFilter = filter; // ���ù���
	ofn.nFilterIndex = 1; // ����������
	ofn.lpstrFile = strFilename; // ���շ��ص��ļ���,ע���һ���ַ���ҪΪNULL
	ofn.nMaxFile = sizeof(strFilename); // ����������
	ofn.lpstrInitialDir = NULL; // ��ʼĿ¼ΪĬ��
	ofn.lpstrTitle = title; // ʹ��ϵͳĬ�ϱ������ռ���
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; // �ļ���Ŀ¼�������,����ֻ��ѡ��

	if (GetOpenFileNameW(&ofn))
	{
		std::wstring filename(strFilename);
		config::replace(configname, filename);
		Edit_SetText(textboxhwnd[number], filename.c_str());
	}
	else
	{
		MessageBoxW(NULL, L"��ѡ��һ���ļ�", NULL, MB_ICONERROR);
		goto loop;
	}
}
void  setting::quit() {
	directshow::music(ENTER);
	char n = 0;
	while (textboxhwnd[n] != 0) {
		DestroyWindow(textboxhwnd[n]);
		n++;
	}
	ui::screenmode = FIRST_MENU;
	ui::ScreenModeChanged = 1;
	for (n = 0; n < TEXTBOXHWNDNUMBER + BOTTONNUMBER; n++)isused[n] = 0;
	firstpaint = 1;
}
void setting::repaint()
{
	firstpaint = 1;
	InvalidateRect(mywindows::hWnd, NULL, FALSE);
}