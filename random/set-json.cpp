#include "set-json.h"
#include"nlohmann/json.hpp"
#include"sth2sth.h"
#include"config.h"
#include "mywindows.h"
#include "bitmaps.h"
#include "directshow.h"
#include "ui.h"

#define BETWEENCOUNT 100
#define WINDOWTITLE 200
#define ISFILE 300
#define NOLIMIT 0

using json = nlohmann::json;
using namespace std;
Log setlog("set-json.log", 0);
extern HBITMAP hbitmaps[BitmapCounts];
extern BITMAP overlay1Bm, bm, ball, overlay2Bm, overlay3Bm, overlay4Bm, cardbg_, exitinfo_, goldenbg, listbm_, list4star_, list5star_, list6star_, list3star_, buttom_;

set2::set2() {
	initing = 1;
	offmusic = config::getint(OFFMUSIC);
	fullscreen = config::getint(INWINDOW);
	// ��ȡJSON�ļ�
	string jsonpath = "files\\setting.json";
	std::ifstream fileStream(jsonpath);
	if (!fileStream.is_open()) {
		setlog << "Failed to open file" << std::endl;
		if (!std::filesystem::exists(jsonpath))
			rollback(jsonpath);
		return;
	}
	// ���ļ����ݽ���ΪJSON����
	json data{};
	try {
		fileStream >> data;
	}
	catch (const std::exception& e) {
		setlog << "Failed to parse JSON: " << e.what() << std::endl;
		return;
	}
	int sp = 0;//settingpage
	int in = 0;//ItemNumber
	for (const auto& page : data["pages"]) {
		in = 0;
		spage pt;
		for (const auto& sItem : page["item"]) {
			sitem t;
			t.HaveChooseFileBM = sItem.value("IsFile", 0);
			t.IsEditBox = sItem.value("IsEditBox", 0);
			t.IsSwitchBM = sItem.value("IsSwitch", 0);
			t.number = sItem.value("Number", in);
			t.Name = sth2sth::str2wstr(sItem.value("Name", "unknow"));
			t.ConfigName = sth2sth::str2wstr(sItem.value("ConfigName", "unknow"));
			t.FileChooseWindowName = sth2sth::str2wstr(sItem.value("WindowName", "unknow"));
			{
				string tmp = sItem.value("FileType", "All");
				if (tmp == "All" AND t.HaveChooseFileBM)
					t.FileType = L"�����ļ�\0 *.*\0\0";
				else if (tmp == "bmp")
					t.FileType = L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0\0";
				else if (tmp == "nameFile")
					t.FileType = L"�����ļ�(*.txt)\0 * .txt\0\0";
				else if (tmp == "video")
					t.FileType = L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0";
				else if (tmp == "picture")
					t.FileType = L"ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf)\0*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf\0\0";
			}
			pt.items.push_back(t);
			in++;
		}
		pages.push_back(pt);
		sp++;
	}
	return;
}
set2::set2(std::string& jsonfile) {
	initing = 1;
	offmusic = config::getint(OFFMUSIC);
	fullscreen = config::getint(INWINDOW);
	// ��ȡJSON�ļ�
	std::ifstream fileStream(jsonfile);
	if (!fileStream.is_open()) {
		setlog << "Failed to open file" << std::endl;
		if (!std::filesystem::exists(jsonfile))
			rollback(jsonfile);
		return;
	}
	// ���ļ����ݽ���ΪJSON����
	json data{};
	try {
		fileStream >> data;
	}
	catch (const std::exception& e) {
		setlog << "Failed to parse JSON: " << e.what() << std::endl;
		return;
	}
	int sp = 0;//settingpage
	int in = 0;//ItemNumber
	for (const auto& page : data["pages"]) {
		in = 0;
		spage pt;
		for (const auto& sItem : page["item"]) {
			sitem t;
			t.HaveChooseFileBM = sItem.value("IsFile", 0);
			t.IsEditBox = sItem.value("IsEditBox", 0);
			t.IsSwitchBM = sItem.value("IsSwitch", 0);
			t.number = sItem.value("Number", in);
			t.Name = sth2sth::str2wstr(sItem.value("Name", "unknow"));
			t.ConfigName = sth2sth::str2wstr(sItem.value("ConfigName", "unknow"));
			t.FileChooseWindowName = sth2sth::str2wstr(sItem.value("WindowName", "unknow"));
			{
				string tmp = sItem.value("FileType", "All");
				if (tmp == "All" AND t.HaveChooseFileBM)
					t.FileType = L"�����ļ�\0 *.*\0\0";
				else if (tmp == "bmp")
					t.FileType = L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0\0";
				else if (tmp == "nameFile")
					t.FileType = L"�����ļ�(*.txt)\0 * .txt\0\0";
				else if (tmp == "video")
					t.FileType = L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0";
				else if (tmp == "picture")
					t.FileType = L"ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf)\0*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf\0\0";
			}
			t.limit = sItem.value("Limit", NOLIMIT);
			if (t.limit == BETWEENCOUNT) {
				t.max = sItem.value("max", 0);
				t.min = sItem.value("min", 0);
				t.OutOfLimitOutPut = sth2sth::str2wstr(sItem.value("OutOfLimit", "NULL"));
			}
			pt.items.push_back(t);
			in++;
		}
		pt.itemcount = in;
		pages.push_back(pt);
		sp++;
	}
	return;
}
void set2::paint(HDC hdc, HDC hdcMem) {
	if (firstpaint) {
		SelectObject(hdcMem, hbitmaps[setbm]);
		StretchBlt(hdc, 0, 0, mywindows::windowWidth, mywindows::windowHeight, hdcMem, 0, 0, setbm_.bmWidth, setbm_.bmHeight, SRCCOPY);
		firstpaint = 0;
	}
}
void set2::seteditbox(LPARAM lParam, WPARAM wParam)
{
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
			for (const auto& item : pages[settingpage].items) {
				if (item.number == numberoftextbox) editboxeditor(item,tmp);
				else continue;
			}
		}
	}
}
void set2::textbox(sitem item, HDC hdc, HDC hdcMem)
{
}
void set2::editboxeditor(sitem item, wstring tmp)
{
	switch (item.limit)
	{
	case WINDOWTITLE:
		SetWindowTextW(mywindows::hWnd, tmp.c_str());
		break;
	case BETWEENCOUNT:
		int value = std::stoi(tmp);
		if (value < item.min || value > item.max) {
			MessageBoxW(NULL, item.OutOfLimitOutPut.c_str(), L"����", MB_ICONERROR);
			return;
		}
		break;
	case ISFILE:
		if (!std::filesystem::exists(tmp))return;
	default:
		break;
	}
	if (item.limit == WINDOWTITLE) {
	}
	else if (item.limit == BETWEENCOUNT)
	{

	}
	else if(item.limit)
	config::replace(item.ConfigName, tmp);
	return;
}


set2::~set2() {
	return;
}
void set2::textbox(sitem item, HDC hdc, HDC hdcMem) {
	SelectObject(hdc, ui::text_mid);
	SetBkColor(hdc, RGB(236, 229, 216));
	SelectObject(hdcMem, hbitmaps[setbutton]);
	TextOut_(hdc, sxy[item.number].x, sxy[item.number].y + mywindows::windowHeight * 0.01, item.Name.c_str());
	std::wstring wst = config::get(item.ConfigName).c_str();
	if (isused[item.number] == 0) {
		textboxhwnd[item.number] = CreateEditBox(mywindows::hWnd, item.number, sxy[item.number].bmx, sxy[item.number].bmy, sxy[item.number].bmw, sxy[item.number].bmh, wst.c_str());
	}
	if (item.HaveChooseFileBM) {
		if (!isused[item.number + 20]) {
			StretchBlt(hdc, sxy[item.number].bmxend, sxy[item.number].bmy, sxy[item.number].bmw, sxy[item.number].bmh, hdcMem, 0, 0, setbu.bmWidth, setbu.bmHeight, SRCCOPY);
			TextOut_(hdc, sxy[item.number].bmxend + mywindows::windowWidth * 0.02, sxy[item.number].y + mywindows::windowHeight * 0.01, L"ѡ���ļ�");

			int x = sxy[item.number].bmxend, y = sxy[item.number].bmy, xend = sxy[item.number].bmxend + sxy[item.number].bmw, yend = sxy[item.number].bmh + sxy[item.number].bmy;
			if (!isused[item.number]) {
				sNode* newnode = new sNode;
				if (newnode == nullptr) {
					mywindows::errlog(L"Memory allocation error(textbox)");
				}
				newnode->x = x;
				newnode->xend = xend;
				newnode->y = y;
				newnode->yend = yend;
				newnode->next = shead;
				newnode->number = item.number;
				shead = newnode;
			}
		}
	}
	isused[item.number] = 1;
}
void set2::switchbm(sitem item, HDC hdc, HDC hdcMem) {
	SelectObject(hdc, ui::text_mid);
	SetBkColor(hdc, RGB(236, 229, 216));
	SelectObject(hdcMem, hbitmaps[setbutton]);
	StretchBlt(hdc, sxy[item.number].bmx, sxy[item.number].bmy, sxy[item.number].bmw, sxy[item.number].bmh, hdcMem, 0, 0, setbu.bmWidth, setbu.bmHeight, SRCCOPY);
	TextOut_(hdc, sxy[item.number].x, sxy[item.number].y + mywindows::windowHeight * 0.01, item.Name.c_str());
	if (std::stoi(config::get(item.ConfigName)) == 1)
		TextOut_(hdc, sxy[item.number].bmx + mywindows::windowWidth * 0.04, sxy[item.number].bmy + mywindows::windowHeight * 0.01, L"��");
	else
		TextOut_(hdc, sxy[item.number].bmx + mywindows::windowWidth * 0.04, sxy[item.number].bmy + mywindows::windowHeight * 0.01, L"��");
	int x = sxy[item.number].bmx, y = sxy[item.number].bmy, xend = sxy[item.number].bmxend, yend = sxy[item.number].bmh + sxy[item.number].bmy;
	sNode* newnode = new sNode;
	if (newnode == NULL) {
		mywindows::errlog("Memory allocation error(textbox)");
	};
	newnode->x = x;
	newnode->xend = xend;
	newnode->y = y;
	newnode->yend = yend;
	newnode->next = shead;
	newnode->number = item.number;
	shead = newnode;
}
void set2::resetplace() {
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
}
void set2::OnButtonClick(HWND hwnd, sitem item)
{
loop:
	OPENFILENAMEW ofn = { 0 };
	wchar_t strFilename[MAX_PATH] = { 0 }; // ���ڽ����ļ���

	ofn.lStructSize = sizeof(OPENFILENAMEW); // �ṹ���С
	ofn.hwndOwner = mywindows::hWnd; // ӵ���ߴ��ھ��,ΪNULL��ʾ�Ի����Ƿ�ģ̬��,ʵ��Ӧ����һ�㶼Ҫ��������
	ofn.lpstrFilter = item.FileType.c_str(); // ���ù���
	ofn.nFilterIndex = 1; // ����������
	ofn.lpstrFile = strFilename; // ���շ��ص��ļ���,ע���һ���ַ���ҪΪNULL
	ofn.nMaxFile = sizeof(strFilename); // ����������
	ofn.lpstrInitialDir = NULL; // ��ʼĿ¼ΪĬ��
	ofn.lpstrTitle = item.FileChooseWindowName.c_str(); // ʹ��ϵͳĬ�ϱ������ռ���
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; // �ļ���Ŀ¼�������,����ֻ��ѡ��

	if (GetOpenFileNameW(&ofn))
	{
		std::wstring filename(strFilename);
		config::replace(item.ConfigName, filename);
		Edit_SetText(textboxhwnd[item.number], filename.c_str());
	}
	else
	{
		MessageBoxW(NULL, L"��ѡ��һ���ļ�", NULL, MB_ICONERROR);
		goto loop;
	}
}
void set2::quit() {
	directshow::music(ENTER);
	char n = 0;
	while (n <= 0) {
		if (textboxhwnd[n] != NULL)
			DestroyWindow(textboxhwnd[n]);
		n++;
	}
	ui::screenmode = FIRST_MENU;
	initing = 1;
	for (n = 0; n < 40; n++)isused[n] = 0;
	firstpaint = 1;
}
void set2::repaint()
{
	firstpaint = 1;
	InvalidateRect(mywindows::hWnd, NULL, FALSE);
}
HWND set2::CreateEditBox(HWND hWndParent, int NUMBER, int x, int y, int w, int h, const wchar_t* words) {
	// ����EDIT�ؼ�����ʽ
	DWORD editStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL;

	// ����EDIT�ؼ��ĸ�����ʽ����ѡ��
	DWORD editExStyle = WS_EX_CLIENTEDGE;

	// �����ı���
	HWND hEdit = CreateWindowExW(editExStyle, L"EDIT", words, editStyle, x, y, w, h, hWndParent, (HMENU)NUMBER, NULL, NULL);

	// �����ı�����
	return hEdit;
}