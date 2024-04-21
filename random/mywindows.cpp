#include "mywindows.h"
#include <mmsystem.h>
#include<time.h>
#include <cstdarg>
#include <filesystem>
#include<commctrl.h>
#include"sth2sth.h"

#pragma comment(lib, "winmm.lib") // ���ӵ� Winmm.lib

std::mutex mywindows::logMutex, mywindows::randomlock;
int mywindows::screenHeight = GetSystemMetrics(SM_CYSCREEN);
int mywindows::screenWidth = GetSystemMetrics(SM_CXSCREEN);
int mywindows::mywindows::windowWidth = screenWidth;
int mywindows::mywindows::windowHeight = screenHeight;
int mywindows::windowTop;
int mywindows::windowLeft;
int mywindows::indices[10];
bool mywindows::fullscreen, mywindows::offmusic = 0;
HWND mywindows::hWnd;
FILE* mywindows::logfile_main, * mywindows::logfile_err;
Log infolog(LOGPATH, 0), errlogf(ERR_LOGPATH, 0);


void mywindows::removeFileNameFromPath(char* path) {
    // ��ȡ�ַ�������
    size_t len = strlen(path);
    // �ҵ����һ��'\'��λ��
    char* lastSlash = strrchr(path, '\\');
    // ����ҵ������һ��'\'�����������滹���ַ�
    if (lastSlash != NULL && lastSlash < path + len - 1) {
        // �����һ��'\'����������ַ����������Լ����滻Ϊ�ַ���������'\0'
        *lastSlash = '\0';
    }
}

void mywindows::IntMessageBox(int intValue) {
    char tmp[3];
    Itoa(intValue, tmp);
    MessageBox(NULL, sth2sth::UTF8To16(tmp), L"��ʾ", MB_OK);
}
HWND mywindows::CreateButton(const char* classname, const char* title, int x, int y, int width, int height, HWND hWnd, int numberofbutton, const char* path, bool mode) {
    HWND hwndbutton = CreateWindow(sth2sth::UTF8To16(classname), sth2sth::UTF8To16(title), WS_VISIBLE | WS_CHILD | BS_BITMAP | BS_PUSHBUTTON, x, y, width, height, hWnd, (HMENU)numberofbutton, GetModuleHandle(NULL), NULL);
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, sth2sth::UTF8To16(path), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(hwndbutton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    return hwndbutton;
}
void mywindows::PrintfDebugString(const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);

    int length = _vscwprintf(format, args) + 1; // ��ȡ��ʽ���ַ����ĳ���
    wchar_t* buffer = new wchar_t[length];

    vswprintf_s(buffer, length, format, args);

    OutputDebugStringW(buffer);

    delete[] buffer;
    va_end(args);
}
void mywindows::log(const char* format, ...) {
    if (format == NULL)errlog("meet a void string");
    va_list args;
    va_start(args, format);
    int length = vsnprintf(0, 0, format, args) + 1;
    char* buffer = new char[length];
    if (buffer == NULL) {
        // ����ڴ����ʧ�ܣ����������Ϣ
        errlog("memory error(log)");
        va_end(args);
        return;
    }
    vsnprintf_s(buffer, length, _TRUNCATE, format, args);
    infolog << infolog.pt() << "[INFO]" << buffer << infolog.nl();
    delete[] buffer;
    va_end(args);
}
void mywindows::errlog(const char* format, ...) {
    if (format == NULL)errlog("meet a void string");
    if (format == NULL)return;
    va_list args;
    va_start(args, format);
    int length = _vscprintf(format, args) + 1;
    char* buffer = new char[length];
    vsnprintf_s(buffer, length, _TRUNCATE, format, args);
    infolog << infolog.pt() << "[ERROR]" << buffer << infolog.nl();
    errlogf << errlogf.pt() << "[ERROR]" << buffer << errlogf.nl();
    delete[] buffer;
    va_end(args);
}

// �������ڲ����������ض�ֵ������λ��
int* mywindows::find(int* array, int size, int valueToFind, int* count) {
    // ����һ����̬�������洢�ҵ�������
    if (indices == NULL) {
        // ����ڴ����ʧ�ܣ����� NULL
        return NULL;
    }
    int indexCount = 0; // ���ڼ�¼�ҵ�����������

    // �������飬���ÿ��Ԫ���Ƿ��� valueToFind ���
    for (int i = 0; i < size; ++i) {
        if (array[i] == valueToFind) {
            indices[indexCount++] = i; // ����ҵ�ƥ���ֵ������������ӵ�������
        }
    }

    // ���� count ��������ʾ�ҵ�����������
    *count = indexCount;

    // ���û���ҵ��κ�ƥ���ֵ���ͷŷ�����ڴ沢���� NULL
    if (indexCount == 0) {
        return NULL;
    }

    return indices; // ���ذ�������ƥ������������
}

void mywindows::errend() {
    MessageBox(NULL, L"����������鿴log���ύissue", L"����", MB_ICONERROR);
    PostQuitMessage(-1);
}


HWND mywindows::CreateEditBox(HWND hWndParent, int NUMBER, int x, int y, int w, int h, const char* words) {
    // ����EDIT�ؼ�����ʽ
    DWORD editStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL;
    // ����EDIT�ؼ��ĸ�����ʽ����ѡ��
    DWORD editExStyle = WS_EX_CLIENTEDGE;

    // �����ı���
    HWND hEdit = CreateWindowExA(editExStyle, "EDIT", words, editStyle, x, y, w, h, hWndParent, (HMENU)NUMBER, NULL, NULL);

    // �����ı�����
    return hEdit;
}
