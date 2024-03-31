#pragma once
#include"getname.h"
#include "directshow.h"
#include"mywindows.h"
#include <cstdio>
#include"setting.h"


#define BALL1 100
#define BALL10 101
#define MODE1 200 
#define EXIT 444
#define STAR L"E"
#define QI_YUAN L"r"
#define SETING L"'"

std::chrono::steady_clock::time_point start, end;
HANDLE random_handle;
DWORD random_;
HFONT text, icon, icon_star, text_big, text_mid, text_list, icon_mid;
LPCWSTR names[256], temp[10];
HINSTANCE hInstance = NULL;
UINT_PTR timerID;// ��ȫ�ַ�Χ�ڶ����ʱ��ID
int currentBitmap = 1;      // ��ǰ��ʾ�ı���ͼƬ
Log randomedlist("name.txt",1);
const char* video;
wchar_t signame[10],*tmp;
bool firsttime = 1, is5star = 0, is4star = 0, isball1 = 0, ing = 0, printing = 0, isball10 = 0, ball10ing = 0, clicked = 0, ft = 0, skipped = 0;
int number = 0,printnum,star_[10];
int mode = 1, step = 0,bottom1x,bottom1y;
int overlay1X, overlay2X, overlay3X, overlay4X, overlay1Y, overlayW, overlayH, button1x, button2x, button3x, button4x, buttony, overlayX, overlayY;
int ball10x, bally, ball1x, ball1end, ball10end, ballyend, skipbmx, skipbmy, skipbmxend, skipbmyend, settingx, settingy, settingxend, settingyend;
int ballW,ballH;
static int cx, cy, cxDib, cyDib;
int listx[11], listy = 0, listxend, listyend;

DWORD static WINAPI RandomNumberGenerator();
void destoryall();
void showname1();
void showname10();
void printstars(HDC hdc ,int number);
void printfirstmenu(HDC hdc, HDC hdcMem);
void printnames(HDC hdc, HDC hdcMem);
char Lstrtosingal(LPCWSTR in);
void creatbuttom(HDC hdc, HDC hdcMem, int x, int y, LPCWSTR text_out);
void out10name(HDC hdc, HDC hdcMem);
void out1name(HDC hdc, HDC hdcMem);
void menu(HDC hdc, HDC hdcMem);
void paintoverlay(HDC hdc, HDC hdcMem);


void out10name(HDC hdc, HDC hdcMem) {
    if (skipped) {
        menu(hdc, hdcMem);
        printing = !printing;
        ing = 0;
        isball10 = 0;
        ball10ing = 0;
        step = 0;
    }
    else if (printing) {
        printnames(hdc, hdcMem);
        printstars(hdc, star_[step]);
        if (step == 9) {
            menu(hdc, hdcMem);
            printing = !printing;
            ing = 0;
            isball10 = 0;
            ball10ing = 0;
            step = 0;
        }
    }
    step++;
}

void menu(HDC hdc, HDC hdcMem) {
    SelectObject(hdcMem, hbitmaps[listbg]);
    StretchBlt(hdc, 0, 0, windowWidth, windowHeight, hdcMem, 0, 0, listbm_.bmWidth, listbm_.bmHeight, SRCCOPY);
    LPCWSTR tmp_[10];
    int count, count1, count2, count3;
    int* itmp = find(star_, sizeof(star_) / sizeof(star[0]), 6, &count);
    if (itmp != NULL) for (int i = 0; i < count; ++i) tmp_[i] = temp[itmp[i]];
    itmp = find(star_, sizeof(star_) / sizeof(star[0]), 5, &count1);
    if (itmp != NULL) for (int i = 0; i < count1; ++i) tmp_[i + count] = temp[itmp[i]];
    itmp = find(star_, sizeof(star_) / sizeof(star[0]), 4, &count2);
    if (itmp != NULL) for (int i = 0; i < count2; ++i) tmp_[i + count + count1] = temp[itmp[i]];
    itmp = find(star_, sizeof(star_) / sizeof(star[0]), 3, &count3);
    if (itmp != NULL) for (int i = 0; i < count3; ++i) tmp_[i + count + count1 + count2] = temp[itmp[i]];
    SetTextColor(hdc, RGB(255, 255, 255));
    for (int i = 0; i < count; ++i) {
        Sleep(20);
        SelectObject(hdcMem, hbitmaps[list6]);
        StretchBlt(hdc, listx[i], listy, listxend,listyend, hdcMem, 0, 0,list6star_.bmWidth, list6star_.bmHeight, SRCCOPY);
        SelectObject(hdc, text_list);
        SetBkColor(hdc, RGB(223, 228, 158));
        wchar_t a[2];
        a[1] = '\0';
        switch (Lstrtosingal(tmp_[i])) {
        case 1:break;
        case 0:break;
        case 2:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.33, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.46, tmp);
            break;
        case 3:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.28, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.43, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.58, tmp);
            break;
        case 4:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.20, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.35, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.50, tmp);
            a[0] = signame[3];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.65, tmp);
            break;
        default:
            MessageBox(NULL, tmp_[i], L"������Ҳ̫����qwq", MB_SYSTEMMODAL | MB_ICONMASK);
            break;
        }
    }    
    for (int i = count; i < count+count1; ++i) {
        Sleep(20);
        SelectObject(hdcMem, hbitmaps[list5]);
        StretchBlt(hdc, listx[i], listy, listxend, listyend, hdcMem, 0, 0, list5star_.bmWidth, list5star_.bmHeight, SRCCOPY);
        SelectObject(hdc, text_list);
        SetBkColor(hdc, RGB(223, 228, 158));
        wchar_t a[2];
        a[1] = '\0';
        switch (Lstrtosingal(tmp_[i])) {
        case 1:break;
        case 0:break;
        case 2:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.33, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.46, tmp);
            break;
        case 3:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.28, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.43, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.58, tmp);
            break;
        case 4:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.20, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.35, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.50, tmp);
            a[0] = signame[3];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.65, tmp);
            break;
        default:
            MessageBox(NULL, tmp_[i], L"������Ҳ̫����qwq", MB_SYSTEMMODAL | MB_ICONMASK);
            break;
        }
    }
    for (int i = count + count1; i < count + count1 + count2; ++i) {
        Sleep(20);
        SelectObject(hdcMem, hbitmaps[list4]);
        StretchBlt(hdc, listx[i], listy, listxend, listyend, hdcMem, 0, 0, list4star_.bmWidth, list4star_.bmHeight, SRCCOPY);
        SelectObject(hdc, text_list);
        SetBkColor(hdc, RGB(154, 130, 220));
        wchar_t a[2];
        a[1] = '\0';
        switch (Lstrtosingal(tmp_[i])) {
        case 1:break;
        case 0:break;
        case 2:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.33, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.46, tmp);
            break;
        case 3:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.28, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.43, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.58, tmp);
            break;
        case 4:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.20, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.35, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.50, tmp);
            a[0] = signame[3];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.65, tmp);
            break;
        default:
            MessageBox(NULL, tmp_[i], L"������Ҳ̫����qwq", MB_SYSTEMMODAL | MB_ICONMASK);
            break;
        }
    }
    for (int i = count + count1+count2; i < count + count1 + count2+count3; ++i) {
        Sleep(20);
        SelectObject(hdcMem, hbitmaps[list3]);
        StretchBlt(hdc, listx[i], listy, listxend, listyend, hdcMem, 0, 0, list3star_.bmWidth, list3star_.bmHeight, SRCCOPY);
        SelectObject(hdc, text_list);
        SetBkColor(hdc, RGB(149, 157, 136));
        wchar_t a[2];
        a[1] = '\0';
        switch (Lstrtosingal(tmp_[i])) {
        case 1:break;
        case 0:break;
        case 2:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.33, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.46, tmp);
            break;
        case 3:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.28, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.43, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.58, tmp);
            break;
        case 4:
            a[0] = signame[0];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.20, tmp);
            a[0] = signame[1];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.35, tmp);
            a[0] = signame[2];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.50, tmp);
            a[0] = signame[3];
            tmp = &a[0];
            TextOut_(hdc, listx[i] + windowWidth * 0.01, listy + windowHeight * 0.65, tmp);
            break;
        default:
            MessageBox(NULL, tmp_[i], L"������Ҳ̫����qwq", MB_SYSTEMMODAL | MB_ICONMASK);
            break;
        }
    }
    skipped = 0;
    initing = 1;
}

void out1name(HDC hdc,HDC hdcMem){
    if (printing) {
        printnames(hdc,hdcMem);
        printstars(hdc, star_[0]);
        printing = !printing;
    }
}

void printnames(HDC hdc, HDC hdcMem) {
    if (star_[step] < 5) {
        SelectObject(hdcMem, hbitmaps[cardbackground]);
        StretchBlt(hdc, 0, 0, windowWidth, windowHeight, hdcMem, 0, 0, cardbg_.bmWidth, cardbg_.bmHeight, SRCCOPY);
        SetTextColor(hdc, RGB(240, 240, 240));
        SetBkColor(hdc, RGB(21, 26, 38));
    }
    else {
        SelectObject(hdcMem, hbitmaps[goldencardbg]);
        StretchBlt(hdc, 0, 0, windowWidth, windowHeight, hdcMem, 0, 0, goldenbg.bmWidth, goldenbg.bmHeight, SRCCOPY);
        SetTextColor(hdc, RGB(240, 240, 240));
        SetBkColor(hdc, RGB(69, 47, 29));
    }
    SelectObject(hdc, text_mid);
    TextOut_(hdc, windowWidth * 0.175, windowHeight * 8 / 13, temp[step]);
    SelectObject(hdc, text_big);
    wchar_t a[2];
    a[1] = '\0';
    switch (Lstrtosingal(temp[step])) {
    case 1:break;
    case 0:break;
    case 2:
        a[0] = signame[0];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.44, windowHeight * 0.26, tmp);
        a[0] = signame[1];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.44, windowHeight * 0.50, tmp);
        break;
    case 3:
        a[0] = signame[0];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.40, windowHeight * 0.26, tmp);
        a[0] = signame[1];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.50, windowHeight * 0.36, tmp);
        a[0] = signame[2];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.40, windowHeight * 0.46, tmp);
        break;
    case 4:
        a[0] = signame[0];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.40, windowHeight * 0.26, tmp);
        a[0] = signame[1];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.50, windowHeight * 0.26, tmp);
        a[0] = signame[2];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.40, windowHeight * 0.46, tmp);
        a[0] = signame[3];
        tmp = &a[0];
        TextOut_(hdc, windowWidth * 0.50, windowHeight * 0.46, tmp);
        break;
    default:
        TextOut_(hdc, windowWidth * 0.30, windowHeight * 0.36, temp[step]);
        break;
    }
    if (ball10ing) {
        SelectObject(hdc, text_mid);
        SetTextColor(hdc, RGB(255, 255, 255));
        TextOut_(hdc, skipbmx, skipbmy, L"���� ��");
    }
}

void destoryall() {
    // �ͷ���Դ���˳�����
    for (char i = BitmapCounts-1; i >= 0; i--)DeleteObject(hbitmaps[i]);
    mciSendString(L"close bgm", NULL, 0, NULL); // �ر������ļ�
    mciSendString(L"close star3", NULL, 0, NULL); // �ر������ļ�
    mciSendString(L"close star4", NULL, 0, NULL); // �ر������ļ�
    mciSendString(L"close star5", NULL, 0, NULL); // �ر������ļ�
    mciSendString(L"close starfull", NULL, 0, NULL); // �ر������ļ�
    mciSendString(L"close listbgm", NULL, 0, NULL); // �ر������ļ�
    cleanupConfigList();
    //relase_ferrtype();
    log("destory objects successfully");
}

void showname10() {
    printing = 1;
    ing = 1;
    ft = 1;
    randomedlist << randomedlist.pt()<<"{" << randomedlist.nl();
    for (int tmp = number + 10; number < tmp; number++) {
        temp[10-(tmp - number)] = names[number];
        star_[10-(tmp - number)] = star[number];
        if (star[number] >= 5)is5star = 1;
        log("10balling number=%d,tmp=%d,star=%d", number, tmp,star_[10-(tmp-number)]);
        randomedlist << "[" << star_[10 - (tmp - number)] << "��]" << "[" << LWStostr(temp[10 - (tmp - number)]) << "]"<<randomedlist.nl();
    }
    randomedlist << "}"<<randomedlist.nl();
    mciSendString(L"stop bgm", NULL, 0, NULL); // ֹͣ����
    if (!offvideo) {
        if (is5star == 1)
            play("\\files\\video\\5star-multi.mp4");
        else if (is5star == 0)
            play("\\files\\video\\4star-multi.mp4");
    }
    else
        mciSendString(L"stop bgm", NULL, 0, NULL); // ֹͣ����
    is5star = 0;
    is4star = 0;
    screenmode = SHOW_NAMES_ING;
    isball1 = 0;
    isball10 = 1;
    ball10ing = 1;
    InvalidateRect(hWnd, NULL, FALSE);
    log("finish ball 10,number is %d", number);
}

void printfirstmenu(HDC hdc,HDC hdcMem) {
    // ������ʾͼƬ
    if (initing) {
        initing = 0;
        SelectObject(hdcMem, hbitmaps[background]);
        StretchBlt(hdc, 0, 0, windowWidth, windowHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        if (offvideo)
            creatbuttom(hdc, hdcMem, bottom1x, bottom1y, L"������Ƶ:��");
        if (!offvideo)
            creatbuttom(hdc, hdcMem, bottom1x, bottom1y, L"������Ƶ:��");
    }SelectObject(hdcMem, hbitmaps[over1]);
    StretchBlt(hdc, overlay1X, overlay1Y, overlayW, overlayH, hdcMem, 0, 0, overlay1Bm.bmWidth, overlay1Bm.bmHeight, SRCCOPY);
    SelectObject(hdcMem, hbitmaps[over2]);
    StretchBlt(hdc, overlay2X, overlay1Y, overlayW, overlayH, hdcMem, 0, 0, overlay2Bm.bmWidth, overlay2Bm.bmHeight, SRCCOPY);
    SelectObject(hdcMem, hbitmaps[over3]);
    StretchBlt(hdc, overlay3X, overlay1Y, overlayW, overlayH, hdcMem, 0, 0, overlay3Bm.bmWidth, overlay3Bm.bmHeight, SRCCOPY);
    SelectObject(hdcMem, hbitmaps[over4]);
    StretchBlt(hdc, overlay4X, overlay1Y, overlayW, overlayH, hdcMem, 0, 0, overlay4Bm.bmWidth, overlay4Bm.bmHeight, SRCCOPY);
    SelectObject(hdcMem, hbitmaps[exitb]);
    StretchBlt(hdc, exitx, exity, exitxend - exitx, exityend - exity, hdcMem, 0, 0, exitbm.bmWidth, exitbm.bmHeight, SRCAND);
    SelectObject(hdcMem, hbitmaps[exiti]);
    StretchBlt(hdc, exitx, exity, exitxend - exitx, exityend - exity, hdcMem, 0, 0, exitbm.bmWidth, exitbm.bmHeight, SRCPAINT);
    SelectObject(hdc, icon);
    SetBkColor(hdc, RGB(255, 255, 255));
    SetTextColor(hdc, RGB(211, 188, 142));
    TextOut_(hdc, windowWidth * 0.045, windowHeight * 0.04, QI_YUAN);
    SelectObject(hdc, text);
    SetTextColor(hdc, RGB(0, 0, 0));
    TextOut_(hdc, windowWidth * 0.075, windowHeight * 0.05, L"��Ը");
    SelectObject(hdc, icon_mid);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkColor(hdc, RGB(225, 222, 213));
    TextOut_(hdc, settingx,settingy, SETING);
    paintoverlay(hdc,hdcMem);
    firsttime = !firsttime;
}

char Lstrtosingal(LPCWSTR in) {
    // ����һ����������ָ���ַ����Ŀ�ʼ
    LPCWSTR it = in;
    int i = 0;
    for (LPCWSTR it = in; *it != L'\0'; it++) { 
        if (*it != 65279)signame[i] = *it;
        else i--;
        i++;
    }
    return i;
}

void creatbuttom(HDC hdc, HDC hdcMem, int x, int y, LPCWSTR text_out) {
    SelectObject(hdcMem, hbitmaps[buttom]);
    StretchBlt(hdc, x, y, windowWidth*0.073, windowHeight*0.039, hdcMem, 0, 0, buttom_.bmWidth, buttom_.bmHeight, SRCCOPY);
    SelectObject(hdc, text);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkColor(hdc, RGB(225, 222, 213));
    TextOut_(hdc, x+windowWidth*0.0073 , y+windowHeight*0.0065, text_out);
}

void printstars(HDC hdc, int number) {
    musicplayed = 1;
    if (number <= 4) {
        SetBkColor(hdc, RGB(21, 26, 38));
        SelectObject(hdc, icon_star);
        SetTextColor(hdc, RGB(220, 184, 14));
    }
    else {
        SetBkColor(hdc, RGB(53, 35, 27));
        SelectObject(hdc, icon_star);
        SetTextColor(hdc, RGB(220, 184, 14));
    }
    switch (number)
    {
    case 3: {
        openmusic(_1_3, "star3");
        Sleep(2000);
        TextOut_(hdc, windowWidth * 0.177, windowHeight * 31 / 52, STAR);
        Sleep(200);
        TextOut_(hdc, windowWidth * 0.187, windowHeight * 31 / 52, STAR);
        Sleep(200);
        TextOut_(hdc, windowWidth * 0.197, windowHeight * 31 / 52, STAR);
    }break;
    case 4: {
        openmusic(_1_4, "star4");
        Sleep(2100);
        TextOut_(hdc, windowWidth * 0.177, windowHeight * 31 / 52, STAR);
        Sleep(200);
        TextOut_(hdc, windowWidth * 0.187, windowHeight * 31 / 52, STAR);
        Sleep(200);
        TextOut_(hdc, windowWidth * 0.197, windowHeight * 31 / 52, STAR);
        Sleep(130);
        TextOut_(hdc, windowWidth * 0.207, windowHeight * 31 / 52, STAR);
    }break;
    case 5: {
        openmusic(_1_5, "star5");
        Sleep(2150);
        TextOut_(hdc, windowWidth * 0.177, windowHeight * 31 / 52, STAR);
        Sleep(110);
        TextOut_(hdc, windowWidth * 0.187, windowHeight * 31 / 52, STAR);
        Sleep(170);
        TextOut_(hdc, windowWidth * 0.197, windowHeight * 31 / 52, STAR);
        Sleep(160);
        TextOut_(hdc, windowWidth * 0.207, windowHeight * 31 / 52, STAR);
        Sleep(145);
        TextOut_(hdc, windowWidth * 0.217, windowHeight * 31 / 52, STAR);
    }break;
    case 6: {
        openmusic(_1_6, "starfull");
        Sleep(2150);
        int x, y;
        for (int i = 500; i > 0; i--) {
            x = randomIntegerBetween(0, windowWidth * 0.99);
            y = randomIntegerBetween(0, windowHeight * 0.99);
            TextOut_(hdc, x, y, STAR);
            Sleep(5);
        }
    }break;
    default:
        break;
    }
}

void showname1() {
    printing = 1;
    ing = 1;
    temp[0] = names[number];
    star_[0] = star[number];
    randomedlist << randomedlist.pt() << "[" << star_[0] << "��]" << "[" << LWStostr(temp[0]) << "]" << randomedlist.nl();
    printnum = 1;
    if (star_[0] >= 5)is5star = 1;
    if (star_[0] == 4)is4star = 1;
    if (!offvideo) {
        if (is4star == 0 AND is5star == 0)
            play("\\files\\video\\3star-single.mp4");
        if (is4star == 1 AND is5star == 0)
            play("\\files\\video\\4star-single.mp4");
        if (is5star == 1)
            play("\\files\\video\\5star-single.mp4");
    }
    else
        mciSendString(L"stop bgm", NULL, 0, NULL); // ֹͣ����
    screenmode = SHOW_NAMES_ING;
    isball1 = 1;
    isball10 = 0;
    InvalidateRect(hWnd, NULL, FALSE);
    is4star = 0;
    is5star = 0;
    step = 0;
    number++;
    log("finish ball 1,number is %d", number);
}

DWORD static WINAPI RandomNumberGenerator() {
    fileerr = 0;
    for (unsigned int i = 0; i <= 255; i++) {
        names[i] = random(i);
        if (fileerr) { MessageBoxA(NULL, "�����ļ���ʧ�ܣ�������������ѡ��", "����", MB_SYSTEMMODAL | MB_ICONERROR); return -1; }
    }
    log("random finish");
    return 0;
}

void paintoverlay(HDC hdc, HDC hdcMem) {
    if (mode == 1) {
        SelectObject(hdcMem, hbitmaps[over1]);
        StretchBlt(hdc, overlayX, overlayY, (windowWidth * 0.6), (windowHeight * 0.6), hdcMem, 0, 0, overlay1Bm.bmWidth, overlay1Bm.bmHeight, SRCCOPY);
        SelectObject(hdcMem, hbitmaps[pink1b]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[pink1i]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        SelectObject(hdcMem, hbitmaps[pink10b]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[pink10i]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        log("set mode1 successfully");
    }
    else if (mode == 2) {
        SelectObject(hdcMem, hbitmaps[over2]);
        StretchBlt(hdc, overlayX, overlayY, (windowWidth * 0.6), (windowHeight * 0.6), hdcMem, 0, 0, overlay2Bm.bmWidth, overlay2Bm.bmHeight, SRCCOPY);
        SelectObject(hdcMem, hbitmaps[pink1b]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[pink1i]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        SelectObject(hdcMem, hbitmaps[pink10b]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[pink10i]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        log("set mode2 successfully");
    }
    else if (mode == 3) {
        SelectObject(hdcMem, hbitmaps[over3]);
        StretchBlt(hdc, overlayX, overlayY, (windowWidth * 0.6), (windowHeight * 0.6), hdcMem, 0, 0, overlay3Bm.bmWidth, overlay3Bm.bmHeight, SRCCOPY);
        SelectObject(hdcMem, hbitmaps[pink1b]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[pink1i]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        SelectObject(hdcMem, hbitmaps[pink10b]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[pink10i]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        log("set mode3 successfully");
    }
    else if (mode == 4) {
        SelectObject(hdcMem, hbitmaps[over4]);
        StretchBlt(hdc, overlayX, overlayY, (windowWidth * 0.6), (windowHeight * 0.6), hdcMem, 0, 0, overlay4Bm.bmWidth, overlay4Bm.bmHeight, SRCCOPY);
        SelectObject(hdcMem, hbitmaps[blue1b]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[blue1i]);
        StretchBlt(hdc, ball1x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        SelectObject(hdcMem, hbitmaps[blue10b]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCAND);
        SelectObject(hdcMem, hbitmaps[blue10i]);
        StretchBlt(hdc, ball10x, bally, ball.bmWidth, ball.bmHeight, hdcMem, 0, 0, ball.bmWidth, ball.bmHeight, SRCPAINT);
        log("set mode4 successfully");
    }
    log("paint overlay bitmap");
}

void rerandom() {
    for (int i = 0; i <= 256; i++)names[i] = 0;
    random_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RandomNumberGenerator, NULL, 0, NULL);
    reran = 0;
}