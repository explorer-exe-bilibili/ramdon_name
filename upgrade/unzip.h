#ifndef UNZIP_H
#define UNZIP_H
#pragma once
#include "Log.h"
#include <string>
class unzip
{
public:
    static std::string upgraderfile;
    // ���ַ����ڵ�old_value�滻��new_value
    static std::string& replace_all(std::string& str, const std::string& old_value, const std::string& new_value);
    // �����༶Ŀ¼
    static bool CreatedMultipleDirectory(const std::string& direct);
    /*
    * �������� : �ݹ��ѹ�ļ�Ŀ¼
    * ��    ע : strFilePath ѹ����·��
    *      strTempPath ��ѹ��
    */
    static void UnzipFile(const std::string& strFilePath, const std::string& strTempPath);
};

#endif // !UNZIP_H