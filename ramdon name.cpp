#include"genthen-impact.h"

LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    HDC hdc =GetDC(NULL);
    hWnd = hwnd;
    switch (uMsg) {//ͨ���ж���Ϣ������Ϣ��Ӧ
    case WM_CREATE: {
        // ������������ͼƬ
        hBitmap1 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\wish-background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hOverlayBitmap1 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hOverlayBitmap2 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hOverlayBitmap3 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hOverlayBitmap4 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        cardbg = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\cardbg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        pink1 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1pink.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        pink10 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10pink.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        blue1 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1blue.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        buttom = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\buttom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        blue10 = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10blue.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        goldencardbg = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\goldenbg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        listbm = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        list3star = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\3list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        list4star = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\4list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        list5star = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\5list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        list6star = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\fulllist.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        exitbuttom_ = (HICON)LoadImageW(NULL, L".\\files\\icos\\exit.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

        int desiredPixelHeight = screenWidth*0.17;
        // ��ȡ�豸�����ĵ� DPI
        HDC hdc = GetDC(NULL); // ��ȡ�����豸������
        int dpi = GetDeviceCaps(hdc, LOGPIXELSY);
        // �����߼���λ�߶�
        int logicalHeight = MulDiv(desiredPixelHeight, 72, dpi);
        int logicalweidth = logicalHeight * 0.77;
        icon_star = CreateFontW(15, 15, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
        icon = CreateFontW(40, 40, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
        text = CreateFontW(20, 15, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        text_mid = CreateFontW(30, 23, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        text_big = CreateFontW(logicalHeight, logicalweidth, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        text_list = CreateFontW(logicalHeight*0.7, logicalweidth*0.7, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        ReleaseDC(NULL, hdc);
        if (text == NULL)errlog("text font load error");
        if (icon == NULL)errlog("icon font load error");
        if (text_big == NULL)errlog("icon font load error");
        if (icon_star == NULL)errlog("star load error");
        //��ȡͼƬ�Ŀ��
        GetIconInfo(exitbuttom_, &exitinfo);
        // ��ȡͼ��λͼ��Ϣ
        GetObject(hBitmap1, sizeof(BITMAP), &bm);
        GetObject(cardbg, sizeof(BITMAP), &cardbg_);
        GetObject(listbm, sizeof(BITMAP), &listbm_);
        GetObject(exitinfo.hbmColor, sizeof(BITMAP), &exitinfo_);
        GetObject(goldencardbg, sizeof(BITMAP), &goldenbg);
        GetObject(pink1, sizeof(BITMAP), &ball);
        GetObject(list3star, sizeof(BITMAP), &list3star_);
        GetObject(list4star, sizeof(BITMAP), &list4star_);
        GetObject(list5star, sizeof(BITMAP), &list5star_);
        GetObject(list6star, sizeof(BITMAP), &list6star_);
        GetObject(hOverlayBitmap1, sizeof(BITMAP), &overlay1Bm);
        GetObject(hOverlayBitmap2, sizeof(BITMAP), &overlay2Bm);
        GetObject(hOverlayBitmap3, sizeof(BITMAP), &overlay3Bm);
        GetObject(hOverlayBitmap4, sizeof(BITMAP), &overlay4Bm);
        const int ball10x_ = screenWidth - ball.bmWidth * 1.3;
        ball10x = ball10x_;
        bally = screenHeight - ball.bmHeight * 2;
        ball1x = screenWidth - ball.bmWidth * 2.4;
        ball1end = ball1x + ball.bmWidth;
        ball10end = ball10x + ball.bmWidth;
        ballyend = bally + ball.bmHeight;
        exitbotton = CreateWindow(L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_ICON | SS_NOTIFY, screenWidth*0.9,screenHeight*0.045, exitinfo_.bmWidth-1, 
        exitinfo_.bmHeight-1, hWnd, (HMENU)EXIT, hInstance, NULL);
        if (exitbuttom_ == NULL)MessageBox(NULL, L"load exitbotton error", L"", NULL);
        // �򿪲����ű�������
        mciSendString(L"open .\\files\\mp3\\backsound.mp3 alias bgm", NULL, 0, NULL); // �� MP3 �ļ�������һ������ 'bgm'
        mciSendString(L"open .\\files\\mp3\\result-list.mp3 alias listbgm", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-3star.mp3 alias star3", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-4star.mp3 alias star4", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-5star.mp3 alias star5", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-fullstar.mp3 alias starfull", NULL, 0, NULL);
        listx[0] = screenWidth * 0.107;
        listxend = screenWidth * 0.078;
        for (char i = 0; i <= 9; i++) {
            listx[i + 1] = listx[i]+listxend;
        }
        mciSendString(L"play bgm repeat", NULL, 0, NULL); // ʹ�ñ��� 'bgm' �������֣�������Ϊѭ������
        SetWindowPos(hWnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_NOZORDER | SWP_FRAMECHANGED);
        SendMessage(exitbotton, STM_SETICON, (WPARAM)exitbuttom_, 0);
        ReleaseDC(0, hdc);
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);
        SetStretchBltMode(hdc, HALFTONE);
        if (firstmenu) {
            if (initing)printfirstmenu(hdc, hdcMem);
            else if (firsttime AND clicked) printfirstmenu(hdc, hdcMem);
            else {
                if (mode == 1) {
                    SelectObject(hdcMem, hOverlayBitmap1);
                    StretchBlt(hdc, overlayX, overlayY, (screenWidth * 0.6), (screenHeight * 0.6), hdcMem, 0, 0, overlay1Bm.bmWidth, overlay1Bm.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, pink1);
                    StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, pink10);
                    StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    log("set mode1 successfully");
                }
                else if (mode == 2) {
                    SelectObject(hdcMem, hOverlayBitmap2);
                    StretchBlt(hdc, overlayX, overlayY, (screenWidth * 0.6), (screenHeight * 0.6), hdcMem, 0, 0, overlay2Bm.bmWidth, overlay2Bm.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, pink1);
                    StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, pink10);
                    StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    log("set mode2 successfully");
                }
                else if (mode == 3) {
                    SelectObject(hdcMem, hOverlayBitmap3);
                    StretchBlt(hdc, overlayX, overlayY, (screenWidth * 0.6), (screenHeight * 0.6), hdcMem, 0, 0, overlay3Bm.bmWidth, overlay3Bm.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, pink1);
                    StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, pink10);
                    StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    log("set mode3 successfully");
                }
                else if (mode == 4) {
                    SelectObject(hdcMem, hOverlayBitmap4);
                    StretchBlt(hdc, overlayX, overlayY, (screenWidth * 0.6), (screenHeight * 0.6), hdcMem, 0, 0, overlay4Bm.bmWidth, overlay4Bm.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, blue1);
                    StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    SelectObject(hdcMem, blue10);
                    StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCCOPY);
                    log("set mode4 successfully");
                }
            }
            if (offvideo)
                creatbuttom(hdc, hdcMem, screenWidth * 0.1, screenHeight * 0.9, L"������Ƶ:��");
            if (!offvideo)
                creatbuttom(hdc, hdcMem, screenWidth * 0.1, screenHeight * 0.9, L"������Ƶ:��");
            log("set mode %d", mode);
        }
        else {
            if (printing) {

                if (isball1) {
                    out1name(hdc,hdcMem);
                    ing = 0;
                }
                if(isball10) {
                    if (ft) { out10name(hdc, hdcMem); ft = 0; }
                    else if(clicked)
                    out10name(hdc,hdcMem);
                    ing = 0;
                }
            }
        }
        log("paint successfully");
        DeleteDC(hdcMem);
        EndPaint(hWnd, &ps);
    }break;
    case WM_LBUTTONDOWN: {
        if (!ing) {
            if (firstmenu) {
                // ��ȡ���λ��
                int x = LOWORD(lParam);
                int y = HIWORD(lParam);
                SetStretchBltMode(hdc, HALFTONE);
                if (x >= overlay1X AND x <= button1x AND y >= overlay1Y AND y <= buttony) mode = 1;
                if (x >= overlay2X AND x <= button2x AND y >= overlay1Y AND y <= buttony) mode = 2;
                if (x >= overlay3X AND x <= button3x AND y >= overlay1Y AND y <= buttony) mode = 3;
                if (x >= overlay4X AND x <= button4x AND y >= overlay1Y AND y <= buttony) mode = 4;
                if (x >= screenWidth * 0.1 AND x <= screenWidth * 0.1 + 123 AND y >= screenHeight * 0.9 AND y <= screenHeight * 0.9 + 31) {
                    offvideo = !offvideo;
                    InvalidateRect(hWnd, NULL, FALSE);
                }
                if (x >= ball10x AND x <= ball10end AND y >= bally AND y <= ballyend)showname10();
                if (x >= ball1x AND x <= ball1end AND y >= bally AND y <= ballyend)showname1();
            }
            else {
                if (ball10ing) {
                    clicked = 1;
                    InvalidateRect(hWnd, NULL, FALSE);
                }
                else {
                    firstmenu = 1;
                    firsttime = 1;
                    mciSendString(L"play bgm repeat", NULL, 0, NULL); // ʹ�ñ��� 'bgm' �������֣�������Ϊѭ������
                }
            }
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else {

        }
    }break;
    case WM_KEYDOWN: switch (wParam) {
    case VK_ESCAPE: {
        PostQuitMessage(0);
        break;
    }
    default:
        break;
    }break;
    case WM_COMMAND: switch (LOWORD(wParam)){
        case EXIT: {
            PostQuitMessage(0);
            break;
        }
        default:
            break;
    }break;    
    case WM_DESTROY: {
        PostQuitMessage(0);
        break; }
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);//�Բ�����Ȥ����Ϣ����ȱʡ���������иô��룬�������������
	}
	return 0;
}

//main
int WINAPI WinMain(HINSTANCE hInstance_, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    initlogs();
    {
        WNDCLASS wndcls; //����һ��������
        wndcls.cbClsExtra = 0;//��Ķ����ڴ棬Ĭ��Ϊ0����
        wndcls.cbWndExtra = 0;//���ڵĶ����ڴ棬Ĭ��Ϊ0����
        wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
        wndcls.hCursor = LoadCursorW(NULL, IDC_ARROW);//���ù��
        wndcls.hIcon = LoadIconW(NULL, IDI_ERROR);//���ô������Ͻǵ�ͼ��
        wndcls.hInstance = hInstance;//���ô���������Ӧ�ó���ʵ��
        wndcls.lpfnWndProc = WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
        wndcls.lpszClassName = L"test";//���ô��������
        wndcls.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
        wndcls.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
        RegisterClass(&wndcls);//�����ϵͳע�ᴰ��
    }
    hInstance = hInstance_;
    initconfig();
    //inittype();
    const char* tmp = getConfigValue("first mode");
    if (strcmp(tmp, "err")==0)addConfigItem("first mode", "1");
    mode = std::stoi(tmp);
    const char *tmp1 = getConfigValue("off video");
    if (strcmp(tmp1, "err")==0)addConfigItem("off video", "0");
    if (std::stoi(getConfigValue("off video"))==0)offvideo = 0;
    else offvideo = 1;
	hWnd = CreateWindowW(L"test", L"ԭ��", WS_POPUP| WS_VISIBLE| WS_CLIPSIBLINGS| WS_OVERLAPPED| WS_CLIPCHILDREN, 0, 0, screenWidth, screenHeight, NULL, NULL, hInstance_, NULL);
    DWORD threadId;
    // �����߳�
    random_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RandomNumberGenerator, NULL, 0, &threadId);
	ShowWindow(hWnd, SW_SHOWNORMAL);//�Ѵ�����ʾ����
    log("INIT COMPETLLY SUCCESSFULLY");
	MSG msg;
	while (GetMessageW(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
    }
    destoryall();
    log("bye!");
}

