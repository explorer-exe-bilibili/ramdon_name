#include"genthen-impact.h"

LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    HDC hdc =GetDC(NULL);
    hWnd = hwnd;
    switch (uMsg) {//ͨ���ж���Ϣ������Ϣ��Ӧ
    case WM_CREATE: {
        // ������������ͼƬ
        hbitmaps[background] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\wish-background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[over1] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[over2] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[over3] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[over4] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\over4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[cardbackground] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\hbitmaps[cardbackground].bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[pink1b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1pinkb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[pink1i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1pinki.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[pink10i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10pinki.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[pink10b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10pinkb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[blue1b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1blueb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[blue1i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\1bluei.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[exiti] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\exiti.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[exitb] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\exitb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[buttom] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\buttom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[blue10i] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10bluei.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[blue10b] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\10blueb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[goldencardbg] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\goldenbg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[listbg] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[list3] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\3list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[list4] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\4list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[list5] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\5list.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[list6] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\fulllist.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[setbm] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\setting.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbitmaps[setbutton] = (HBITMAP)LoadImage(NULL, L".\\files\\imgs\\settingbuttom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        
        int desiredPixelHeight = windowWidth*0.17;
        // ��ȡ�豸�����ĵ� DPI
        HDC hdc = GetDC(NULL); // ��ȡ�����豸������
        int dpi = GetDeviceCaps(hdc, LOGPIXELSY);
        // �����߼���λ�߶�
        int logicalHeight = MulDiv(desiredPixelHeight, 72, dpi);
        int logicalweidth = logicalHeight * 0.77;
        icon_star = CreateFontW(logicalHeight * 0.0862, logicalweidth * 0.1127, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
        icon_mid = CreateFontW(logicalHeight*0.16, logicalweidth*0.22, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
        icon = CreateFontW(logicalHeight*0.2299, logicalweidth*0.3008, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"genshin-icon");
        text = CreateFontW(logicalHeight*0.1149, logicalweidth*0.1127, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        text_mid = CreateFontW(logicalHeight*0.1724, logicalweidth*0.1729, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        text_big = CreateFontW(logicalHeight, logicalweidth, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        text_list = CreateFontW(logicalHeight*0.7, logicalweidth*0.7, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"SDK_SC_Web");
        ReleaseDC(NULL, hdc);
        if (text == NULL)errlog("text font load error");
        if (icon == NULL)errlog("icon font load error");
        if (text_big == NULL)errlog("icon font load error");
        if (icon_star == NULL)errlog("star load error");
        // ��ȡͼ��λͼ��Ϣ
        GetObject(hbitmaps[background], sizeof(BITMAP), &bm);
        GetObject(hbitmaps[setbutton], sizeof(BITMAP), &setbu);
        GetObject(hbitmaps[cardbackground], sizeof(BITMAP), &cardbg_);
        GetObject(hbitmaps[listbg], sizeof(BITMAP), &listbm_);
        GetObject(hbitmaps[exitb], sizeof(BITMAP), &exitbm);
        GetObject(hbitmaps[goldencardbg], sizeof(BITMAP), &goldenbg);
        GetObject(hbitmaps[pink1b], sizeof(BITMAP), &ball);
        GetObject(hbitmaps[list3], sizeof(BITMAP), &list3star_);
        GetObject(hbitmaps[list4], sizeof(BITMAP), &list4star_);
        GetObject(hbitmaps[list5], sizeof(BITMAP), &list5star_);
        GetObject(hbitmaps[list6], sizeof(BITMAP), &list6star_);
        GetObject(hbitmaps[over1], sizeof(BITMAP), &overlay1Bm);
        GetObject(hbitmaps[over2], sizeof(BITMAP), &overlay2Bm);
        GetObject(hbitmaps[over3], sizeof(BITMAP), &overlay3Bm);
        GetObject(hbitmaps[buttom], sizeof(BITMAP), &buttom_);
        GetObject(hbitmaps[over4], sizeof(BITMAP), &overlay4Bm);
        GetObject(hbitmaps[setbm], sizeof(BITMAP), &setbm_);
        // �򿪲����ű�������
        mciSendString(L"open .\\files\\mp3\\backsound.mp3 alias bgm", NULL, 0, NULL); // �� MP3 �ļ�������һ������ 'bgm'
        mciSendString(L"open .\\files\\mp3\\result-list.mp3 alias listbgm", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-3star.mp3 alias star3", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-4star.mp3 alias star4", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-5star.mp3 alias star5", NULL, 0, NULL);
        mciSendString(L"open .\\files\\mp3\\reveal-fullstar.mp3 alias starfull", NULL, 0, NULL);
        mciSendString(L"play bgm repeat", NULL, 0, NULL); // ʹ�ñ��� 'bgm' �������֣�������Ϊѭ������
        SetWindowPos(hWnd, HWND_TOP, 0, 0, windowWidth, windowHeight, SWP_NOZORDER | SWP_FRAMECHANGED);
        ReleaseDC(0, hdc);
        break;
    }
    case WM_PAINT: {
        RECT rect;
        GetClientRect(hwnd, &rect);
        // ���㴰�ڵĿ�Ⱥ͸߶�
        windowTop = rect.left;
        windowLeft = rect.top;
        int tempint = rect.right - rect.left;
        if (tempint != windowWidth)initing = 1;
        windowWidth = tempint;
        tempint = rect.bottom - rect.top;
        if (tempint != windowHeight)initing = 1;
        windowHeight = tempint;
        if (initing) {
            ball10x = windowWidth - ball.bmWidth * 1.3;
            bally = windowHeight - ball.bmHeight * 2;
            ball1x = windowWidth - ball.bmWidth * 2.4;
            ball1end = ball1x + ball.bmWidth;
            ball10end = ball10x + ball.bmWidth;
            ballyend = bally + ball.bmHeight;
            overlay1X = windowWidth * 3 / 9 - windowWidth / 17;
            overlay2X = windowWidth * 4 / 9 - windowWidth / 17;
            overlay3X = windowWidth * 5 / 9 - windowWidth / 17;
            overlay4X = windowWidth * 6 / 9 - windowWidth / 17;
            overlay1Y = windowHeight * 3 / 40;
            overlayW = windowWidth * 3 / 40;
            overlayH = windowHeight * 3 / 40;
            button1x = overlay1X + overlayW;
            button2x = overlay2X + overlayW;
            button3x = overlay3X + overlayW;
            button4x = overlay4X + overlayW;
            buttony = overlay1Y + overlayH;
            overlayX = windowWidth / 10 * 2;
            overlayY = windowHeight / 10 * 2;
            ballW = 0.152 * windowWidth;
            ballH = 0.0625 * windowHeight;
            bottom1x = windowWidth * 0.1;
            bottom1y = windowHeight * 0.85;
            listyend = windowHeight;
            skipbmx = windowWidth * 0.8;
            skipbmy = windowHeight * 0.045;
            skipbmxend = skipbmx + windowWidth * 0.1;
            skipbmyend = skipbmy + 100;
            settingx = windowWidth * 0.05;
            settingy = windowHeight * 0.85;
            settingxend =settingx+ windowWidth * 0.023;
            settingyend =settingy+ windowHeight * 0.036;
            exitx = windowWidth * 0.9;
            exitxend = windowWidth * 0.93;
            exity = windowHeight * 0.045;
            exityend = windowHeight * 0.045 + windowWidth * 0.03;
            listx[0] = windowWidth * 0.107;
            listxend = windowWidth * 0.078;
            initsetting();
            for (char i = 0; i <= 9; i++) {
                listx[i + 1] = listx[i] + listxend;
            }
        }
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);
        SetStretchBltMode(hdc, HALFTONE);
        switch (screenmode)
        {
        case FIRST_MENU: {
            if (initing)printfirstmenu(hdc, hdcMem);
            else if (!(initing AND firsttime)) {
                if (offvideo)
                    creatbuttom(hdc, hdcMem, bottom1x, bottom1y, L"������Ƶ:��");
                if (!offvideo)
                    creatbuttom(hdc, hdcMem, bottom1x, bottom1y, L"������Ƶ:��");
                paintoverlay(hdc, hdcMem);
                log("set mode %d", mode);
            }
            else if (firsttime)if (clicked) printfirstmenu(hdc, hdcMem);
        }break;
        case SHOW_NAMES_ING: {
            if (printing) {

                if (isball1) {
                    out1name(hdc, hdcMem);
                    ing = 0;
                    initing = 1;
                }
                if (isball10) {
                    if (ft) { if (!skipped)out10name(hdc, hdcMem); ft = 0; }
                    else if (clicked)
                        out10name(hdc, hdcMem);
                    ing = 0;
                }
            }
        }break;
        case SETTING: {
            paintsettingpage(hdc, hdcMem, text_mid);
        }break;
        default:
            break;
        }
        log("paint successfully");
        DeleteDC(hdcMem);
        EndPaint(hWnd, &ps);
    }break;
    case WM_LBUTTONDOWN: {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (x >= exitx AND x <= exitxend AND y >= exity AND y <= exityend)PostQuitMessage(0);
        if (!ing) {
            switch (screenmode)
            {
            case FIRST_MENU: {
                // ��ȡ���λ��
                SetStretchBltMode(hdc, HALFTONE);
                if (x >= overlay1X AND x <= button1x AND y >= overlay1Y AND y <= buttony) mode = 1;
                if (x >= overlay2X AND x <= button2x AND y >= overlay1Y AND y <= buttony) mode = 2;
                if (x >= overlay3X AND x <= button3x AND y >= overlay1Y AND y <= buttony) mode = 3;
                if (x >= overlay4X AND x <= button4x AND y >= overlay1Y AND y <= buttony) mode = 4;
                if (x >= bottom1x AND x <= bottom1x + 123 AND y >= bottom1y AND y <= bottom1y + 31) { offvideo = !offvideo; InvalidateRect(hWnd, NULL, FALSE); }
                if (x >= ball10x AND x <= ball10end AND y >= bally AND y <= ballyend)showname10();
                if (x >= ball1x AND x <= ball1end AND y >= bally AND y <= ballyend)showname1();
                if (x >= settingx AND x <= settingxend AND y >= settingy AND y <= settingyend)screenmode = SETTING;
            }break;
            case SHOW_NAMES_ING: {
                if (ball10ing) {
                    if (x >= skipbmx AND x <= skipbmxend AND y >= skipbmy AND y <= skipbmyend)skipped = 1;
                    clicked = 1;
                    InvalidateRect(hWnd, NULL, FALSE);
                }
                else {
                    screenmode = FIRST_MENU;
                    firsttime = 1;
                    mciSendString(L"play bgm repeat", NULL, 0, NULL); // ʹ�ñ��� 'bgm' �������֣�������Ϊѭ������
                }
            }break;
            case SETTING: {
                
            }
            default:
                break;
            }
            InvalidateRect(hWnd, NULL, FALSE);
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
    case WM_COMMAND:
        switch (HIWORD(wParam)) {
        case EN_CHANGE: {
            // ��ȡ�ı���ľ����ȷ��������Ч��
            HWND editBoxHwnd = (HWND)LOWORD(lParam);
            if (editBoxHwnd != NULL) {
                // ���仺������С����������ı����е��ı����ᳬ��256���ַ�
                // ��ȡ�ı����е��ı�
                GetWindowTextW(editBoxHwnd, buffer, 256);
                // ��ʾ�ı����е��ı�
                MessageBoxW(NULL, buffer, L"Text Changed", MB_OK);
                delete[] buffer; // �ͷŷ�����ڴ�
            }
            break;
        }
        default:
            break;
        }
        break;
    case WM_DESTROY: {
        PostQuitMessage(0);
    }break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);//�Բ�����Ȥ����Ϣ����ȱʡ���������иô��룬�������������
	}
	return 0;
}

//main
int WINAPI WinMain(HINSTANCE hInstance_, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    initlogs();
    initconfig();
    SetConsoleOutputCP(65001); // ����ΪUTF-8����
    WNDCLASS wndcls; //����һ��������
    wndcls.cbClsExtra = 0;//��Ķ����ڴ棬Ĭ��Ϊ0����
    wndcls.cbWndExtra = 0;//���ڵĶ����ڴ棬Ĭ��Ϊ0����
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
    wndcls.hCursor = LoadCursorW(NULL, IDC_ARROW);//���ù��
    wndcls.hIcon = LoadIconW(NULL, IDI_ERROR);//���ô������Ͻǵ�ͼ��
    wndcls.hInstance = hInstance;//���ô���������Ӧ�ó���ʵ��
    wndcls.lpfnWndProc = WinSunProc;//���ô���Ļص���������ʱûд��������ΪNULL�����油��
    wndcls.lpszClassName = L"main";//���ô��������
    wndcls.lpszMenuName = NULL;//���ô���Ĳ˵�,û�У���NULL
    wndcls.style = CS_HREDRAW | CS_VREDRAW;//���ô�����Ϊˮƽ�ػ��ʹ�ֱ�ػ�
    RegisterClass(&wndcls);//�����ϵͳע�ᴰ��
    hInstance = hInstance_;
    fullscreen = !std::stoi(getConfigValue(INWINDOW));
    if(fullscreen)hWnd = CreateWindowA("main", getConfigValue(WINDOW_TITEL), WS_POPUP | WS_CLIPSIBLINGS | WS_OVERLAPPED | WS_CLIPCHILDREN, 0, 0, windowWidth, windowHeight, NULL, NULL, hInstance_, NULL);
    else {
        windowWidth = screenWidth * 0.6;
        windowHeight = screenHeight * 0.6;
        hWnd = CreateWindowA("main", getConfigValue(WINDOW_TITEL), WS_CLIPSIBLINGS | WS_OVERLAPPED | WS_CLIPCHILDREN| WS_THICKFRAME, 0, 0, windowWidth, windowHeight, NULL, NULL, hInstance_, NULL);
    }
    DWORD threadId;
    // �����߳�
    random_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RandomNumberGenerator, NULL, 0, &threadId);
    offvideo = std::stoi(getConfigValue(OFF_VIDEO));
    mode = std::stoi(getConfigValue(MODE));
	ShowWindow(hWnd, SW_SHOWNORMAL);//�Ѵ�����ʾ����
    FILE *temppppppp;
    fopen_s(&temppppppp, ".\\version", "w");
    fprintf(temppppppp,"0.3.1");
    fclose(temppppppp);
    log("INIT COMPETLLY SUCCESSFULLY");
	MSG msg;
	while (GetMessageW(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
    }
    destoryall();
    log("bye!");
}

