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
int mywindows::windowWidth = screenWidth;
int mywindows::windowHeight = screenHeight;
int mywindows::windowTop;
int mywindows::windowLeft;
int mywindows::indices[10];
HWND mywindows::hWnd;
Log infolog(LOGPATH, 0), errlogf(ERR_LOGPATH, 0);

// �����༶Ŀ¼
bool mywindows::CreatedMultipleDirectory(const std::string& direct)
{
    std::string Directoryname = direct;
    if (Directoryname[Directoryname.length() - 1] != '\\')
    {
        Directoryname.append(1, '\\');
    }
    std::vector< std::string> vpath;
    std::string strtemp;
    BOOL  bSuccess = FALSE;
    for (int i = 0; i < Directoryname.length(); i++)
    {
        if (Directoryname[i] != '\\')
        {
            strtemp.append(1, Directoryname[i]);
        }
        else
        {
            vpath.push_back(strtemp);
            strtemp.append(1, '\\');
        }
    }
    std::vector< std::string>::iterator vIter = vpath.begin();
    for (; vIter != vpath.end(); vIter++)
    {
        bSuccess = CreateDirectoryA(vIter->c_str(), NULL) ? TRUE : FALSE;
    }
    return bSuccess;
}
//�Ƴ��ļ�·�����ļ���
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
void mywindows::removeFileNameFromPath(wchar_t* path) {
    // ��ȡ�ַ�������
    size_t len = wcslen(path);
    // �ҵ����һ��'\'��λ��
    wchar_t* lastSlash = wcsrchr(path, L'\\');
    // ����ҵ������һ��'\'�����������滹���ַ�
    if (lastSlash != NULL && lastSlash < path + len - 1) {
        // �����һ��'\'����������ַ����������Լ����滻Ϊ�ַ���������'\0'
        *lastSlash = '\0';
    }
}
void mywindows::removeFileNameFromPath(std::wstring& path) {
    // �ҵ����һ��'\\'��λ��
    std::size_t lastSlashPos = path.find_last_of(L'\\');

    // ����ҵ������һ��'\\'
    if (lastSlashPos != std::wstring::npos) {
        // �ض��ַ���,�����һ��'\\'����������ַ�ɾ��
        path.erase(lastSlashPos + 1);
    }
}
//INFO�����־
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
void mywindows::log(const wchar_t* format, ...) {
    if (format == NULL) errlog(L"meet a void string");

    va_list args;
    va_start(args, format);

    int length = _vscwprintf(format, args) + 1; // ��ȡ��ʽ���ַ�������
    std::wstring buffer;
    buffer.resize(length); // �����㹻���ڴ�

    int ret = vswprintf(&buffer[0], length, format, args); // ��ʽ���ַ���
    if (ret < 0) {
        errlog(L"Failed to format string");
        va_end(args);
        return;
    }

    infolog << infolog.pt() << L"[INFO]" << buffer << infolog.nl();
    va_end(args);
}
//ERROR�����־
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
void mywindows::errlog(const wchar_t* format, ...) {
    if (format == NULL)errlog(L"meet a void string");
    if (format == NULL)return;
    va_list args;
    va_start(args, format);
    int length = _vscwprintf(format, args) + 1;
    std::wstring buffer;
    buffer.resize(length); // �����㹻���ڴ�
    int ret = vswprintf(&buffer[0], length, format, args); // ��ʽ���ַ���
    if (ret < 0) {
        errlog(L"Failed to format string");
        va_end(args);
        return;
    }
    infolog << infolog.pt() << "[ERROR]" << buffer << infolog.nl();
    errlogf << errlogf.pt() << "[ERROR]" << buffer << errlogf.nl();
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

