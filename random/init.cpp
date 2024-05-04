#include "init.h"
#include "ui.h"
#include<Windows.h>
#include"paintname.h"
#include"mywindows.h"
#include"set-json.h"
#include"config.h"
#include<filesystem>
#include <functional>

#include"resource.h"
#include"log.h"
#include<thread>

extern set2 setscreen;
extern HBITMAP hbitmaps[BitmapCounts];
extern BITMAP overlay1Bm, bm, ball, overlay2Bm, overlay3Bm, overlay4Bm, cardbg, exitinfo, goldenbg, listbm, liststar, buttom;
WNDPROC w2_, w3_;

void init::picture()
{
	// ������������ͼƬ
	DWORD threadId;
	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoadIMG, NULL, 0, &threadId);
	hbitmaps[BackGround] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\wish-background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[over1] = (HBITMAP)LoadImage(NULL, config::getpath(OVER1).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[over2] = (HBITMAP)LoadImage(NULL, config::getpath(OVER2).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[over3] = (HBITMAP)LoadImage(NULL, config::getpath(OVER3).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[over4] = (HBITMAP)LoadImage(NULL, config::getpath(OVER4).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[pink1b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1pinkb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[pink1i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1pinki.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[pink10i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10pinki.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[pink10b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10pinkb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[blue1b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1blueb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[blue1i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1bluei.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[exiti] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\exiti.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[exitb] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\exitb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[Buttom] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\buttom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[blue10i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10bluei.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[blue10b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10blueb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hbitmaps[BackGround], sizeof(BITMAP), &bm);
	GetObject(hbitmaps[Buttom], sizeof(BITMAP), &buttom);
	GetObject(hbitmaps[exitb], sizeof(BITMAP), &exitinfo);
	GetObject(hbitmaps[over1], sizeof(BITMAP), &overlay1Bm);
	GetObject(hbitmaps[over2], sizeof(BITMAP), &overlay2Bm);
	GetObject(hbitmaps[over3], sizeof(BITMAP), &overlay3Bm);
	GetObject(hbitmaps[over4], sizeof(BITMAP), &overlay4Bm);
	GetObject(hbitmaps[pink1b], sizeof(BITMAP), &ball);
}
void init::font()
{
	int desiredPixelHeight = mywindows::windowWidth * 0.17;
	// ��ȡ�豸�����ĵ� DPI
	HDC hdc = GetDC(NULL); // ��ȡ�����豸������
	int dpi = GetDeviceCaps(hdc, LOGPIXELSY);
	// �����߼���λ�߶�
	int logicalHeight = MulDiv(desiredPixelHeight, 72, dpi);
	int logicalweidth = logicalHeight * 0.77;
	paintname::icon_star = CreateFontW(logicalHeight * 0.0862, logicalweidth * 0.1127, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
	ui::icon_mid = CreateFontW(logicalHeight * 0.16, logicalweidth * 0.22, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
	ui::icon = CreateFontW(logicalHeight * 0.2299, logicalweidth * 0.3008, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
	ui::text = CreateFontW(logicalHeight * 0.1149, logicalweidth * 0.1127, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
	ui::text_mid = CreateFontW(logicalHeight * 0.1724, logicalweidth * 0.1729, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
	ui::text_big = CreateFontW(logicalHeight, logicalweidth, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
	ui::text_list = CreateFontW(logicalHeight * 0.7, logicalweidth * 0.7, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
	ReleaseDC(NULL, hdc);
	if (ui::text == NULL)mywindows::errlog("text font load error");
	if (ui::icon == NULL)mywindows::errlog("icon font load error");
	if (ui::text_big == NULL)mywindows::errlog("icon font load error");
}
void init::resetxy()
{
	RECT rect;
	GetClientRect(mywindows::main_hwnd, &rect);
	// ���㴰�ڵĿ�Ⱥ͸߶�
	mywindows::windowTop = rect.left;
	mywindows::windowLeft = rect.top;
	int tempint = rect.right - rect.left;
	if (tempint != mywindows::windowWidth)ui::ScreenModeChanged = 1;
	mywindows::windowWidth = tempint;
	tempint = rect.bottom - rect.top;
	if (tempint != mywindows::windowHeight)ui::ScreenModeChanged = 1;
	mywindows::windowHeight = tempint;
	if (ui::ScreenModeChanged) {
		ui::ballW = 0.18 * mywindows::windowWidth;
		ui::ballH = 0.075 * mywindows::windowHeight;
		ui::ball10x = mywindows::windowWidth - ui::ballW * 1.3;
		ui::bally = mywindows::windowHeight - ui::ballH * 2;
		ui::ball1x = mywindows::windowWidth - ui::ballW * 2.4;
		ui::ball1end = ui::ball1x + ui::ballW;
		ui::ball10end = ui::ball10x + ui::ballW;
		ui::ballyend = ui::bally + ui::ballH;
		ui::overlay1X = mywindows::windowWidth * 3 / 9 - mywindows::windowWidth / 17;
		ui::overlay2X = mywindows::windowWidth * 4 / 9 - mywindows::windowWidth / 17;
		ui::overlay3X = mywindows::windowWidth * 5 / 9 - mywindows::windowWidth / 17;
		ui::overlay4X = mywindows::windowWidth * 6 / 9 - mywindows::windowWidth / 17;
		ui::overlay1Y = mywindows::windowHeight * 3 / 40;
		ui::overlayW = mywindows::windowWidth * 3 / 40;
		ui::overlayH = mywindows::windowHeight * 3 / 40;
		ui::button1x = ui::overlay1X + ui::overlayW;
		ui::button2x = ui::overlay2X + ui::overlayW;
		ui::button3x = ui::overlay3X + ui::overlayW;
		ui::button4x = ui::overlay4X + ui::overlayW;
		ui::buttony = ui::overlay1Y + ui::overlayH;
		ui::overX = mywindows::windowWidth / 10 * 2;
		ui::overlayY = mywindows::windowHeight / 10 * 2;
		ui::bottom1x = mywindows::windowWidth * 0.1;
		ui::bottom1y = mywindows::windowHeight * 0.85;
		ui::listyend = mywindows::windowHeight;
		paintname::skipbmx = mywindows::windowWidth * 0.8;
		paintname::skipbmy = mywindows::windowHeight * 0.045;
		paintname::skipbmxend = paintname::skipbmx + mywindows::windowWidth * 0.1;
		paintname::skipbmyend = paintname::skipbmy + 100;
		ui::settingx = mywindows::windowWidth * 0.05;
		ui::settingy = mywindows::windowHeight * 0.85;
		ui::settingxend = ui::settingx + mywindows::windowWidth * 0.023;
		ui::settingyend = ui::settingy + mywindows::windowHeight * 0.036;
		ui::exitx = mywindows::windowWidth * 0.9;
		ui::exitxend = mywindows::windowWidth * 0.93;
		ui::exity = mywindows::windowHeight * 0.045;
		ui::exityend = mywindows::windowHeight * 0.045 + mywindows::windowWidth * 0.03;
		ui::listx[0] = mywindows::windowWidth * 0.107;
		ui::listxend = mywindows::windowWidth * 0.078;
		ui::addnamex = mywindows::windowWidth * 0.4;
		ui::addnameendx = ui::addnamex + mywindows::windowWidth * 0.12;
		ui::addnamey = mywindows::windowHeight * 0.8;
		ui::addnameendy = ui::addnamey + mywindows::windowHeight * 0.036;
		setscreen.resetplace();
		for (char i = 0; i <= 9; i++) {
			ui::listx[i + 1] = ui::listx[i] + ui::listxend;
		}
		DeleteObject(paintname::icon_star);
		DeleteObject(ui::text_mid);
		DeleteObject(ui::text_big);
		DeleteObject(ui::text);
		DeleteObject(ui::text_list);
		DeleteObject(ui::icon_mid);
		DeleteObject(ui::icon);
		font();
	}
}
void init::resetpicture()
{
	if (setscreen.changebitmap[0]) {
		hbitmaps[over1] = (HBITMAP)LoadImage(NULL, config::getpath(OVER1).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(hbitmaps[over1], sizeof(BITMAP), &overlay1Bm);
		setscreen.changebitmap[0] = 0;
	}
	if (setscreen.changebitmap[1]) {
		hbitmaps[over2] = (HBITMAP)LoadImage(NULL, config::getpath(OVER2).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(hbitmaps[over2], sizeof(BITMAP), &overlay2Bm);
		setscreen.changebitmap[1] = 0;
	}
	if (setscreen.changebitmap[2]) {
		hbitmaps[over3] = (HBITMAP)LoadImage(NULL, config::getpath(OVER3).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(hbitmaps[over3], sizeof(BITMAP), &overlay3Bm);
		setscreen.changebitmap[2] = 0;
	}
	if (setscreen.changebitmap[3]) {
		hbitmaps[over4] = (HBITMAP)LoadImage(NULL, config::getpath(OVER4).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(hbitmaps[over4], sizeof(BITMAP), &overlay4Bm);
		setscreen.changebitmap[3] = 0;
	}
}
void init::main(WNDPROC w1, WNDPROC w2, WNDPROC w3)
{
	std::thread loading(std::bind(&init::regwindow, w1, w2, w3));
	loading.detach();
	SetConsoleOutputCP(65001); // ����ΪUTF-8����
	CHAR run[260] = { 0 };
	GetModuleFileNameA(NULL, run, MAX_PATH);
	int len = MultiByteToWideChar(CP_ACP, 0, run, -1, NULL, 0);
	wchar_t* run_ = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, run, -1, run_, len);
	Log::wrunpath = run_;
	mywindows::log("getting run path \n%s", run);
	mywindows::log(L"getting run path \n%s", run_);
	mywindows::removeFileNameFromPath(run);
	Log::wrunpath = run_;
	mywindows::removeFileNameFromPath(Log::wrunpath);
	Log::runpath = run;
	mywindows::log("initiating run path(string) %s", Log::runpath.c_str());
	mywindows::log(L"initiating run path(wstring) %ws", Log::wrunpath.c_str());
	config::init();
	setscreen.offmusic = config::getint(OFFMUSIC);
	setscreen.FloatWindow = config::getint(FLOATWINDOW);
	DWORD threadId;
	// �����߳�
	mywindows::log("start thread");
	paintname::random_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)paintname::RandomNumberGenerator, NULL, 0,&threadId);
	setscreen.offvideo = config::getint(OFF_VIDEO);
	ui::mode = config::getint(MODE);
	setscreen.offmusic = config::getint(OFFMUSIC);
	DWORD threadId2;
	// �����߳�
	mywindows::log("start thread");
	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Upgrade, NULL, 0, &threadId2);
	mciSendString(L"open .\\files\\mp3\\backsound.mp3 alias bgm", NULL, 0, NULL); // �� MP3 �ļ�������һ������ 'bgm'
}
void init::music()
{
	static bool once = 1;
	if (once) {
		std::wstring str = L"open \"";
		str += Log::wrunpath;
		str += L"\\files\\mp3\\backsound.mp3\" alias bgm";
		mywindows::log(L"load bgm,command is :%ws", str.c_str());
		mciSendString(str.c_str(), 0, 0, 0);
		once = 0;
	}// �򿪲����ű�������
	if (!setscreen.offmusic)
		mciSendString(L"play bgm repeat", NULL, 0, NULL); // ʹ�ñ��� 'bgm' �������֣�������Ϊѭ������
}
void init::MainWindow()
{
	setscreen.fullscreen = !config::getint(INWINDOW);
	if (setscreen.fullscreen)mywindows::main_hwnd = CreateWindowW(L"main", config::get(WINDOW_TITEL).c_str(), WS_POPUP | WS_CLIPSIBLINGS | WS_OVERLAPPED | WS_CLIPCHILDREN,
		0, 0, mywindows::windowWidth, mywindows::windowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	else {
		mywindows::windowWidth = mywindows::screenWidth * 0.6;
		mywindows::windowHeight = mywindows::screenHeight * 0.6;
		mywindows::main_hwnd = CreateWindowW(L"main", config::get(WINDOW_TITEL).c_str(), WS_CLIPSIBLINGS | WS_OVERLAPPED | WS_CLIPCHILDREN | WS_THICKFRAME,
			0, 0, mywindows::windowWidth, mywindows::windowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	}
	ShowWindow(mywindows::main_hwnd, SW_SHOWNORMAL);//�Ѵ�����ʾ����
}
void init::regwindow(WNDPROC w1,WNDPROC w2,WNDPROC w3)
{
	w2_ = w2; w3_ = w3;
	WNDCLASS wndcls{}; //����һ��������
	wndcls.cbClsExtra = 0;//��Ķ����ڴ棬Ĭ��Ϊ0����
	wndcls.cbWndExtra = 0;//���ڵĶ����ڴ棬Ĭ��Ϊ0����
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
	wndcls.hCursor = LoadCursorW(NULL, IDC_ARROW);//���ù��
	wndcls.hIcon = LoadIconW(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));//���ô������Ͻǵ�ͼ��
	wndcls.hInstance = GetModuleHandle(NULL);;//���ô���������Ӧ�ó���ʵ��
	wndcls.lpfnWndProc = w1;//WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
	wndcls.lpszClassName = L"main";//���ô��������
	wndcls.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
	wndcls.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
	RegisterClass(&wndcls);//�����ϵͳע�ᴰ��
	DWORD threadId;
	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Regwindows, NULL, 0, &threadId);
}
DWORD WINAPI init::Regwindows() {
	WNDCLASS Fwndcls{}; //����һ��������
	Fwndcls.cbClsExtra = 0;//��Ķ����ڴ棬Ĭ��Ϊ0����
	Fwndcls.cbWndExtra = 0;//���ڵĶ����ڴ棬Ĭ��Ϊ0����
	Fwndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
	Fwndcls.hCursor = LoadCursorW(NULL, IDC_ARROW);//���ù��
	Fwndcls.hIcon = LoadIconW(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));//���ô������Ͻǵ�ͼ��
	Fwndcls.hInstance = GetModuleHandle(NULL);;//���ô���������Ӧ�ó���ʵ��
	Fwndcls.lpfnWndProc = w2_;//WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
	Fwndcls.lpszClassName = L"FLOAT";//���ô��������
	Fwndcls.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
	Fwndcls.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
	RegisterClass(&Fwndcls);//�����ϵͳע�ᴰ��
	WNDCLASS Qwndcls{}; //����һ��������
	Fwndcls.cbClsExtra = 0;//��Ķ����ڴ棬Ĭ��Ϊ0����
	Fwndcls.cbWndExtra = 0;//���ڵĶ����ڴ棬Ĭ��Ϊ0����
	Fwndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
	Fwndcls.hCursor = LoadCursorW(NULL, IDC_ARROW);//���ù��
	Fwndcls.hIcon = LoadIconW(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));//���ô������Ͻǵ�ͼ��
	Fwndcls.hInstance = GetModuleHandle(NULL);;//���ô���������Ӧ�ó���ʵ��
	Fwndcls.lpfnWndProc = w3_;//WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
	Fwndcls.lpszClassName = L"QUIT";//���ô��������
	Fwndcls.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
	Fwndcls.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
	RegisterClass(&Fwndcls);//�����ϵͳע�ᴰ��
	return 0;
}
DWORD WINAPI init::LoadIMG() {
	hbitmaps[goldencardbg] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\goldenbg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[listbg] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[list3] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\3list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[list4] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\4list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[list5] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\5list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[list6] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\fulllist.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[SetBM] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\setting.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[setbutton] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\settingbuttom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbitmaps[cardbackground] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\cardbg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(hbitmaps[SetBM], sizeof(BITMAP), &setscreen.setbm);
	GetObject(hbitmaps[setbutton], sizeof(BITMAP), &setscreen.setbu);
	GetObject(hbitmaps[goldencardbg], sizeof(BITMAP), &goldenbg);
	GetObject(hbitmaps[list3], sizeof(BITMAP), &liststar);
	GetObject(hbitmaps[listbg], sizeof(BITMAP), &listbm);
	GetObject(hbitmaps[cardbackground], sizeof(BITMAP), &cardbg);
	return 0;
}
DWORD WINAPI init::Upgrade(){
	mywindows::log("writes version");
	FILE* t;
	fopen_s(&t, ".\\version", "w");
	if (t != 0) {
		fprintf(t, "1.0.0");
		fclose(t);
		t = 0;
	}
	if (std::filesystem::exists("upgrade_temp.exe"))
	{
		std::filesystem::remove("upgrade.exe");
		std::filesystem::rename("upgrade_temp.exe", "upgrade.exe");
	}
	ShellExecute(NULL, L"open", L"upgrade.exe", NULL, NULL, SW_SHOWNORMAL);
	return 0;
}