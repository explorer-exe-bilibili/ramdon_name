#ifndef LOG_H
#define LOG_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#define INSIDEINT 1143221
// ������־����ö��

class Log {
private:
    std::ofstream logFile;
    static bool CreatedMultipleDirectory(const std::string& direct);
public:
    Log(const std::string& fileName, bool add);
    ~Log();

    Log& operator<<(const std::string& str);
    Log& operator<<(long double value);
    // ���Ը�����Ҫ���ظ����������͵�<<���������
    int nl();
    int pt();
private:
    void writeToLog(const std::string& message);
};
#endif // LOG_H