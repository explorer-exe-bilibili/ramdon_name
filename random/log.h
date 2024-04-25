#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#define INSIDEINT 1143221
// ������־����ö��

class Log {
private:
    std::ofstream logFile;
    static bool CreatedMultipleDirectory(const std::string& direct);
public:
    static std::wstring wrunpath;
    static std::string runpath;
    Log(const std::string& fileName, bool add);
    ~Log();

    Log& operator<<(const std::string& str);
    Log& operator<<(const std::wstring& str);
    Log& operator<<(long double value);
    // ���Ը�����Ҫ���ظ����������͵�<<���������
    int nl();
    int pt();
private:
    void writeToLog(const std::string& message);
};