#pragma once
#include <mmsystem.h>
#include<time.h>
#include <wchar.h>
#include <stdio.h>
#include <cstdarg>
#include <filesystem>
#include"bitmaps.h"
#include"log.h"
#include<commctrl.h>

#pragma comment(lib, "winmm.lib") // ���ӵ� Winmm.lib

#define TextOut_(hdc,x,y,string) TextOutW(hdc,x,y,string,wcslen(string)) 
#define Itoa(number,goal) _itoa(number,(char*)goal,10)
#define OR ||
#define AND &&
#define LOGPATH ".\\files\\log\\main.log"
#define ERR_LOGPATH ".\\files\\log\\err.log"

std::mutex logMutex,randomlock;
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int windowWidth = screenWidth;
int windowHeight = screenHeight;
int windowTop, windowLeft;
int indices[10];
bool fullscreen,offmusic = 0;
HWND hWnd;
FILE *logfile_main,*logfile_err;
Log infolog(LOGPATH, 0),errlogf(ERR_LOGPATH,0);

HWND CreateButton(const char* classname, const char* title, int x, int y, int width, int height, HWND hWnd, int numberofbutton, const char* path,bool mode);
LPCWSTR UTF8To16(const char* utf8String);
void PrintfDebugString(const wchar_t* format, ...);
void IntMessageBox(int intValue);
void log(const char* logstring,...);
void errlog(const char* format, ...);
HWND CreateEditBox(HWND hWndParent, int NUMBER, int x, int y, int w, int h, const char* words);
std::string UTF_82ASCII(std::string& strUtf8Code);
void removeFileNameFromPath(char* path);
std::string WideByte2Acsi(std::wstring& wstrcode);
std::string LWStostr(LPCWSTR lpcwszStr);
std::wstring Utf82Unicode(const std::string& utf8string);
HWND CreateEditBox(HWND hWndParent, int NUMBER, int x, int y, int w, int h, const char* words);
int* find(int* array, int size, int valueToFind, int* count);
char* const_char_ptr_to_char_ptr(const char* const_char_ptr);


void removeFileNameFromPath(char* path) {
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

void IntMessageBox(int intValue) {
    char tmp[3];
    Itoa(intValue,tmp);
    MessageBox(NULL, UTF8To16(tmp), L"��ʾ", MB_OK);
}
HWND CreateButton(const char* classname,const char* title,int x,int y,int width,int height,HWND hWnd,int numberofbutton, const char* path,bool mode){
    HWND hwndbutton = CreateWindow(UTF8To16(classname), UTF8To16(title), WS_VISIBLE | WS_CHILD | BS_BITMAP | BS_PUSHBUTTON, x, y, width, height, hWnd, (HMENU)numberofbutton, GetModuleHandle(NULL), NULL);
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,UTF8To16(path), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SendMessage(hwndbutton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    return hwndbutton;
}
LPCWSTR UTF8To16(const char* utf8String)
{
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, nullptr, 0);
    wchar_t* wideString = new wchar_t[bufferSize];

    MultiByteToWideChar(CP_UTF8, 0, utf8String, -1, wideString, bufferSize);
    
    return wideString;
}
void PrintfDebugString(const wchar_t* format, ...)
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
void log(const char* format,...) {
    if (format == NULL)errlog("meet a void string");
    va_list args;
    va_start(args, format);
    int length = vsnprintf(0,0,format, args) + 1;
    char* buffer = new char[length];
    if (buffer == NULL) {
        // ����ڴ����ʧ�ܣ����������Ϣ
        errlog("memory error(log)");
        va_end(args);
        return;
    }
    vsnprintf_s(buffer, length, _TRUNCATE, format, args);
    infolog << infolog.pt() << "[INFO]" << buffer<<infolog.nl();
    delete[] buffer;
    va_end(args);
}
void errlog(const char* format, ...) {
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


std::string LWStostr(LPCWSTR lpcwszStr)
{
    std::string str;
    DWORD dwMinSize = 0;
    LPSTR lpszStr = NULL;
    dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
    if (0 == dwMinSize)
    {
        return FALSE;
    }
    lpszStr = new char[dwMinSize];
    WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwMinSize, NULL, FALSE);
    str = lpszStr;
    delete[] lpszStr;
    return str;
}


// �������ڲ����������ض�ֵ������λ��
int* find(int* array, int size, int valueToFind, int* count) {
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

void errend() {
    MessageBox(NULL, L"����������鿴log���ύissue", L"����", MB_ICONERROR);
    PostQuitMessage(-1);
}


HWND CreateEditBox(HWND hWndParent,int NUMBER,int x,int y,int w,int h,const char *words) {
    // ����EDIT�ؼ�����ʽ
    DWORD editStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL;
    // ����EDIT�ؼ��ĸ�����ʽ����ѡ��
    DWORD editExStyle = WS_EX_CLIENTEDGE;

    // �����ı���
    HWND hEdit = CreateWindowExA(editExStyle, "EDIT", words, editStyle, x, y, w, h, hWndParent, (HMENU)NUMBER, NULL, NULL);

    // �����ı�����
    return hEdit;
}

std::wstring Utf82Unicode(const std::string& utf8string)
{
    int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw std::exception("Error in conversion.");
    }

    std::vector<wchar_t> resultstring(widesize);

    int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);

    if (convresult != widesize)
    {
        throw std::exception("La falla!");
    }

    return std::wstring(&resultstring[0]);
}


//unicode תΪ ascii  


std::string WideByte2Acsi(std::wstring& wstrcode)
{
    int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw std::exception("Invalid UTF-8 sequence.");
    }
    if (asciisize == 0)
    {
        throw std::exception("Error in conversion.");
    }
    std::vector<char> resultstring(asciisize);
    int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);

    if (convresult != asciisize)
    {
        throw std::exception("La falla!");
    }

    return std::string(&resultstring[0]);
}
//utf-8 ת ascii  


std::string UTF_82ASCII(std::string& strUtf8Code)
{
    std::string strRet("");
    //�Ȱ� utf8 תΪ unicode  
    std::wstring wstr = Utf82Unicode(strUtf8Code);
    //���� unicode תΪ ascii  
    strRet = WideByte2Acsi(wstr);
    return strRet;
}

char* const_char_ptr_to_char_ptr(const char* const_char_ptr) {
    return const_cast<char*>(const_char_ptr);
}