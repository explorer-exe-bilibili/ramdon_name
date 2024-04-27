#include "set-json.h"
#include"nlohmann/json.hpp"
#include"sth2sth.h"
#include"config.h"
#include "mywindows.h"
#include "bitmaps.h"
#include "directshow.h"
#include "ui.h"

#define BETWEENCOUNT 100
#define S_WINDOWTITLE 200
#define ISFILE 300
#define ISBITMAP 400
#define NOLIMIT 0

using json = nlohmann::json;
using namespace std;
Log setlog("set-json.log", 0);
extern HBITMAP hbitmaps[BitmapCounts];
extern BITMAP overlay1Bm, bm, ball, overlay2Bm, overlay3Bm, overlay4Bm, cardbg, exitinfo, goldenbg, listbm, liststar, buttom;

set2::set2() {
	{
		bitmaps[background] = &bm;
		bitmaps[blue10b] = &ball;
		bitmaps[blue10i] = &ball;
		bitmaps[blue1b] = &ball;
		bitmaps[blue1i] = &ball;
		bitmaps[Buttom] = &buttom;
		bitmaps[cardbackground] = &cardbg;
		bitmaps[exitb] = &exitinfo;
		bitmaps[exiti] = &exitinfo;
		bitmaps[goldencardbg] = &goldenbg;
		bitmaps[list3] = &liststar;
		bitmaps[list4] = &liststar;
		bitmaps[list5] = &liststar;
		bitmaps[list6] = &liststar;
		bitmaps[listbg] = &listbm;
		bitmaps[over1] = &overlay1Bm;
		bitmaps[over2] = &overlay2Bm;
		bitmaps[over3] = &overlay3Bm;
		bitmaps[over4] = &overlay4Bm;
		bitmaps[pink10b] = &ball;
		bitmaps[pink10i] = &ball;
		bitmaps[pink1b] = &ball;
		bitmaps[pink1i] = &ball;
		bitmaps[SetBM] = &setbm;
		bitmaps[setbutton] = &setbu;
	}
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
		pt.Title = sth2sth::str2wstr(page.value("Title", ""));
		for (const auto& sItem : page["item"]) {
			sitem t;
			t.IsFile = sItem.value("IsFile", 0);
			t.IsEditBox = sItem.value("IsEditBox", 0);
			t.IsSwitch = sItem.value("IsSwitch", 0);
			t.Limit = sItem.value("Limit", NOLIMIT);
			t.Number = sItem.value("Number", in);
			t.BitmapNumber = sItem.value("BitmapNumber", 0);
			t.Name = sth2sth::str2wstr(sItem.value("Name", ""));
			t.ConfigName = sth2sth::str2wstr(sItem.value("ConfigName", ""));
			t.FileChooseWindowName = sth2sth::str2wstr(sItem.value("FileChooseWindowName", ""));
			{
				string tmp = sItem.value("FileType", "All");
				if (tmp == "All" AND t.IsFile)
					t.FileType = L"�����ļ�\0 *.*\0\0";
				else if (tmp == "bmp")
					t.FileType = L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0\0";
				else if (tmp == "nameFile")
					t.FileType = L"�����ļ�(*.txt)\0 * .txt\0\0";
				else if (tmp == "video")
					t.FileType = L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0";
				else if (tmp == "picture")
					t.FileType = L"ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf)\0*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf\0\0";
				else t.FileType = L"";
			}
			if (t.Limit == BETWEENCOUNT) {
				t.max = sItem.value("max", 0);
				t.min = sItem.value("min", 0);
				t.OutOfLimitOutPut = sth2sth::str2wstr(sItem.value("OutOfLimit", ""));
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
set2::set2(std::string& jsonfile) {
	{

		bitmaps[background] = &bm;
		bitmaps[blue10b] = &ball;
		bitmaps[blue10i] = &ball;
		bitmaps[blue1b] = &ball;
		bitmaps[blue1i] = &ball;
		bitmaps[Buttom] = &buttom;
		bitmaps[cardbackground] = &cardbg;
		bitmaps[exitb] = &exitinfo;
		bitmaps[exiti] = &exitinfo;
		bitmaps[goldencardbg] = &goldenbg;
		bitmaps[list3] = &liststar;
		bitmaps[list4] = &liststar;
		bitmaps[list5] = &liststar;
		bitmaps[list6] = &liststar;
		bitmaps[listbg] = &listbm;
		bitmaps[over1] = &overlay1Bm;
		bitmaps[over2] = &overlay2Bm;
		bitmaps[over3] = &overlay3Bm;
		bitmaps[over4] = &overlay4Bm;
		bitmaps[pink10b] = &ball;
		bitmaps[pink10i] = &ball;
		bitmaps[pink1b] = &ball;
		bitmaps[pink1i] = &ball;
		bitmaps[SetBM] = &setbm;
		bitmaps[setbutton] = &setbu;
	}
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
		pt.Title = sth2sth::str2wstr(page.value("Title", ""));
		for (const auto& sItem : page["item"]) {
			sitem t;
			t.IsFile = sItem.value("IsFile", 0);
			t.IsEditBox = sItem.value("IsEditBox", 0);
			t.IsSwitch = sItem.value("IsSwitch", 0);
			t.Limit = sItem.value("Limit", NOLIMIT);
			t.Number = sItem.value("Number", in);
			t.BitmapNumber = sItem.value("BitmapNumber", 0);
			t.Name = sth2sth::str2wstr(sItem.value("Name", ""));
			t.ConfigName = sth2sth::str2wstr(sItem.value("ConfigName", ""));
			t.FileChooseWindowName = sth2sth::str2wstr(sItem.value("FileChooseWindowName", ""));
			{
				string tmp = sItem.value("FileType", "All");
				if (tmp == "All" AND t.IsFile)
					t.FileType = L"�����ļ�\0 *.*\0\0";
				else if (tmp == "bmp")
					t.FileType = L"bmpͼƬ�ļ�(*.bmp)\0 * .bmp\0\0";
				else if (tmp == "nameFile")
					t.FileType = L"�����ļ�(*.txt)\0 * .txt\0\0";
				else if (tmp == "video")
					t.FileType = L"��Ƶ�ļ�(*.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v)\0 *.avi; *.mpg; *.mpeg; *.m2v; *.vob; *.mp4; *.m4v; *.mp4v; *.3gp; *.3gp2; *.wmv; *.asf; *.mov; *.qt; *.rm; *.rmvb; *.flv; *.f4v\0\0";
				else if (tmp == "picture")
					t.FileType = L"ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf)\0*.jpg;*.jpeg;*.bmp;*.png;*.tif;*.tiff;*.gif;*.wmf;*.emf\0\0";
				else t.FileType = L"";
			}
			if (t.Limit == BETWEENCOUNT) {
				t.max = sItem.value("max", 0);
				t.min = sItem.value("min", 0);
				t.OutOfLimitOutPut = sth2sth::str2wstr(sItem.value("OutOfLimit", ""));
			}
			else if (t.Limit == ISFILE || t.Limit == ISBITMAP) {
				t.IsEditBox = 1;
				t.IsFile = 1;
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
		SelectObject(hdcMem, hbitmaps[SetBM]);
		StretchBlt(hdc, 0, 0, mywindows::windowWidth, mywindows::windowHeight, hdcMem, 0, 0, setbm.bmWidth, setbm.bmHeight, SRCCOPY);
		firstpaint = 0;
	}
	SelectObject(hdc, ui::text_mid);
	wstring title = pages[settingpage].Title;
	int titlex, titley;
	int stringWidth = 0.0272 * mywindows::windowWidth * title.length();
	titlex= (mywindows::windowWidth - stringWidth) / 2;
	titley = mywindows::windowHeight * 0.09;
	TextOut_(hdc, titlex, titley, title.c_str());
	SelectObject(hdcMem, hbitmaps[exitb]);
	StretchBlt(hdc, ui::exitx, ui::exity, ui::exitxend - ui::exitx, ui::exityend - ui::exity, hdcMem, 0, 0, exitinfo.bmWidth, exitinfo.bmHeight, SRCAND);
	SelectObject(hdcMem, hbitmaps[exiti]);
	StretchBlt(hdc, ui::exitx, ui::exity, ui::exitxend - ui::exitx, ui::exityend - ui::exity, hdcMem, 0, 0, exitinfo.bmWidth, exitinfo.bmHeight, SRCPAINT);
	for (const auto& item : pages[settingpage].items) {
		showitem(item, hdc, hdcMem);
	}
	unsigned int totalp = static_cast<int>(pages.size());
	wstring t = to_wstring(settingpage) + L"/" + to_wstring(totalp);
	SelectObject(hdc, ui::icon_mid);
	TextOut_(hdc, nextbmx, nextbmy, L"b");
	TextOut_(hdc, lastbmx, lastbmy, L"c");
	SelectObject(hdc, ui::text_mid);
	TextOut_(hdc, mywindows::windowWidth * 0.765, mywindows::windowHeight * 0.91, t.c_str());

}
void set2::rollback(string jsonpath) {
	json data;
	data = {
		{"Title","ͼƬ",
		{"item",{
			"Name","����1ͼƬ",
			"ConfigName","over1",
			"FileChooseWindowName","ѡ�񿨳�1ͼƬ",
			"FileType","bmp",
			"Limit",ISBITMAP,
			"Number",1,
			"BitmapNumber",0
			},{
			"Name","����2ͼƬ",
			"ConfigName","over2",
			"FileChooseWindowName","ѡ�񿨳�2ͼƬ",
			"FileType","bmp",
			"Limit",ISBITMAP,
			"Number",2,
			"BitmapNumber",1
			},{
			"Name","����3ͼƬ",
			"ConfigName","over3",
			"FileChooseWindowName","ѡ�񿨳�3ͼƬ",
			"FileType","bmp",
			"Limit",ISBITMAP,
			"Number",3,
			"BitmapNumber",2
			},{
			"Name","����4ͼƬ",
			"ConfigName","over4",
			"FileChooseWindowName","ѡ�񿨳�4ͼƬ",
			"FileType","bmp",
			"Limit",ISBITMAP,
			"Number",4,
			"BitmapNumber",3
			},{
			"Name","�ر�����",
			"ConfigName","off music",
			"IsSwitch",1,
			"Number",11
			},{
			"Name","�ر���Ƶ",
			"ConfigName","off video",
			"IsSwitch",1,
			"Number",12
			}
		}},
		{"Title","�����뿨��",
		{"item",{
			"Name","����1����",
			"ConfigName","namesfile1",
			"FileChooseWindowName","ѡ�񿨳�1����",
			"FileType","nameFile",
			"Limit",ISFILE,
			"Number",1
			},{
			"Name","����2����",
			"ConfigName","namesfile2",
			"FileChooseWindowName","ѡ�񿨳�2����",
			"FileType","nameFile",
			"Limit",ISFILE,
			"Number",2
			},{
			"Name","����3����",
			"ConfigName","namesfile3",
			"FileChooseWindowName","ѡ�񿨳�3����",
			"FileType","nameFile",
			"Limit",ISFILE,
			"Number",3
			},{
			"Name","����4����",
			"ConfigName","namesfile4",
			"FileChooseWindowName","ѡ�񿨳�4����",
			"FileType","nameFile",
			"Limit",ISFILE,
			"Number",4
			},{
			"Name","�鱳����",
			"ConfigName","special",
			"IsEditBox",1,
			"Limit",BETWEENCOUNT,
			"max",4,
			"min",0,
			"OutOfLimitOutPut","����һ��0-4֮������֣�0��ʾ���ã�",
			"Number",11
			},{
			"Name","�ر�����",
			"ConfigName","off music",
			"IsSwitch",1,
			"Number",12
			},{
			"Name","�ر���Ƶ",
			"ConfigName","off video",
			"IsSwitch",1,
			"Number",13
			}
		}},
		{"Title","��Ƶ",
		"item",{{
			"Name","����3����Ƶ",
			"ConfigName","signal 3star video",
			"FileChooseWindowName","ѡ�񵥷�3����Ƶ",
			"FileType","video",
			"Limit",ISFILE,
			"Number",1
			},{
			"Name","����4����Ƶ",
			"ConfigName","signal 4star video",
			"FileChooseWindowName","ѡ�񵥷�4����Ƶ",
			"FileType","video",
			"Limit",ISFILE,
			"Number",2
			},{
			"Name","����5����Ƶ",
			"ConfigName","signal 5star video",
			"FileChooseWindowName","ѡ�񵥷�5����Ƶ",
			"FileType","video",
			"Limit",ISFILE,
			"Number",3
			},{
			"Name","ʮ��4����Ƶ",
			"ConfigName","group 4star video",
			"FileChooseWindowName","ѡ��ʮ��4����Ƶ",
			"FileType","video",
			"Limit",ISFILE,
			"Number",5
			},{
			"Name","ʮ��5����Ƶ",
			"ConfigName","group 5star video",
			"FileChooseWindowName","ѡ��ʮ��5����Ƶ",
			"FileType","video",
			"Limit",ISFILE,
			"Number",6
			},{
			"Name","�ر�����",
			"ConfigName","off music",
			"IsSwitch",1,
			"Number",11
			},{
			"Name","�ر���Ƶ",
			"ConfigName","off video",
			"IsSwitch",1,
			"Number",12
			}
		}},
		{"Title","����",
		{"item",{{
			"Name","����ģʽ",
			"ConfigName","window mode(not full screen)",
			"IsSwitch",1,
			"Number",1,
			},{
			"Name","����",
			"ConfigName","title name",
			"IsEditBox",1,
			"Number",2
			},{
			"Name","�ر�����",
			"ConfigName","off music",
			"IsSwitch",1,
			"Number",11
			},{
			"Name","�ر���Ƶ",
			"ConfigName","off video",
			"IsSwitch",1,
			"Number",12
			}
		}}
}
	};
	// д��JSON�ļ�
	std::ofstream file("files\\setting.json");
	if (file.is_open()) {
		file << data.dump(4); // ��JSON����д���ļ���4��ʾ����4���ո�
		file.close();
		setlog<<setlog.pt()<<"[INFO]" << "JSON data written to 'files\\setting.json'" << std::endl;
	}
	else {
		setlog << setlog.pt() << "[ERROR]" << "Failed to open file for writing" << std::endl;
	}
}
void set2::clicked(int x, int y)
{
	int totalp = pages.size();
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
	else {
		sNode* current = shead;
		while (current != NULL) {
			if (x >= current->x AND x <= current->xend AND y >= current->y AND y <= current->yend) {
				number = current->number;
				break;
			}
			current = current->next;
		}
	}
	if (number != -1) {
		directshow::music(CLICK);
		if (number > 0) {
			for (const auto& item : pages[settingpage - 1].items) {
				if (number = item.Number) {
					if (item.IsSwitch)
						config::turnUpSideDown(item.ConfigName);
					else if (item.IsFile) {
						ChooseFile(mywindows::hWnd, item);
						if (item.Limit == ISBITMAP) {
							reloadbmp(item);
						}
					}
				}
			}
		}
	}
}
void set2::reloadbmp(sitem item)
{
	DeleteObject(hbitmaps[item.BitmapNumber]);
	hbitmaps[item.BitmapNumber] =
		(HBITMAP)LoadImage(NULL, config::get(item.ConfigName).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hbitmaps[item.BitmapNumber], sizeof(BITMAP), bitmaps[item.BitmapNumber]);
}
void set2::rereadconfig() {
	offmusic = config::getint(OFFMUSIC);
	fullscreen = !config::getint(INWINDOW);
}
void set2::changepage()
{
	char n = 0;
	while (textboxhwnd[n] != 0) {
		DestroyWindow(textboxhwnd[n]);
		n++;
	}
	for (n = 0; n < 40; n++)isused[n] = 0;
	firstpaint = 1;
}
void set2::showitem(sitem item, HDC hdc, HDC hdcMem) {
	if (item.IsSwitch) {
		switchbm(item, hdc, hdcMem);
	}
	else if (item.IsEditBox) {
		textbox(item, hdc, hdcMem);
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
				if (item.Number == numberoftextbox) editboxeditor(item,tmp);
				else continue;
			}
		}
	}
}
void set2::textbox(sitem item, HDC hdc, HDC hdcMem)
{
	SelectObject(hdc, ui::text_mid);
	SetBkColor(hdc, RGB(236, 229, 216));
	SelectObject(hdcMem, hbitmaps[setbutton]);
	TextOut_(hdc, sxy[item.Number].x, sxy[item.Number].y + mywindows::windowHeight * 0.01, item.Name.c_str());
	int number = item.Number;
	std::wstring wst = config::get(item.ConfigName).c_str();
	if (isused[number] == 0) {
		textboxhwnd[number] = CreateEditBox(mywindows::hWnd, number, sxy[number].bmx, sxy[number].bmy, sxy[number].bmw, sxy[number].bmh, wst.c_str());
	}
	if (item.IsFile) {
		if (!isused[number + 20]) {
			StretchBlt(hdc, sxy[number].bmxend, sxy[number].bmy, sxy[number].bmw, sxy[number].bmh, hdcMem, 0, 0, setbu.bmWidth, setbu.bmHeight, SRCCOPY);
			TextOut_(hdc, sxy[number].bmxend + mywindows::windowWidth * 0.02, sxy[number].y + mywindows::windowHeight * 0.01, L"ѡ���ļ�");

			int x = sxy[number].bmxend, y = sxy[number].bmy, xend = sxy[number].bmxend + sxy[number].bmw, yend = sxy[number].bmh + sxy[number].bmy;
			if (!isused[number]) {
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
	isused[number] = 1;
}
void set2::editboxeditor(sitem item, wstring tmp)
{
	switch (item.Limit)
	{
	case S_WINDOWTITLE:
		SetWindowTextW(mywindows::hWnd, tmp.c_str());
		break;
	case BETWEENCOUNT: {
		int value = std::stoi(tmp);
		if (value < item.min || value > item.max) {
			MessageBoxW(NULL, item.OutOfLimitOutPut.c_str(), L"����", MB_ICONERROR);
			return;
		}
	}break;
	case ISFILE:
	case ISBITMAP:
		if (!std::filesystem::exists(tmp))return;
		break;
	default:
		break;
	}
	config::replace(item.ConfigName, tmp);
	return;
}
set2::~set2() {
	return;
}
void set2::switchbm(sitem item, HDC hdc, HDC hdcMem) {
	SelectObject(hdc, ui::text_mid);
	SetBkColor(hdc, RGB(236, 229, 216));
	SelectObject(hdcMem, hbitmaps[setbutton]);
	StretchBlt(hdc, sxy[item.Number].bmx, sxy[item.Number].bmy, sxy[item.Number].bmw, sxy[item.Number].bmh, hdcMem, 0, 0, setbu.bmWidth, setbu.bmHeight, SRCCOPY);
	TextOut_(hdc, sxy[item.Number].x, sxy[item.Number].y + mywindows::windowHeight * 0.01, item.Name.c_str());
	if (std::stoi(config::get(item.ConfigName)) == 1)
		TextOut_(hdc, sxy[item.Number].bmx + mywindows::windowWidth * 0.04, sxy[item.Number].bmy + mywindows::windowHeight * 0.01, L"��");
	else
		TextOut_(hdc, sxy[item.Number].bmx + mywindows::windowWidth * 0.04, sxy[item.Number].bmy + mywindows::windowHeight * 0.01, L"��");
	int x = sxy[item.Number].bmx, y = sxy[item.Number].bmy, xend = sxy[item.Number].bmxend, yend = sxy[item.Number].bmh + sxy[item.Number].bmy;
	sNode* newnode = new sNode;
	if (newnode == NULL) {
		mywindows::errlog("Memory allocation error(textbox)");
	};
	newnode->x = x;
	newnode->xend = xend;
	newnode->y = y;
	newnode->yend = yend;
	newnode->next = shead;
	newnode->number = item.Number;
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
void set2::ChooseFile(HWND hwnd, sitem item)
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
		Edit_SetText(textboxhwnd[item.Number], filename.c_str());
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
	ui::ScreenModeChanged = 1;
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