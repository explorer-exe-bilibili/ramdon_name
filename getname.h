#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <stdbool.h>
#include"mywindows.h"
#include"config.h"
#include <iostream>
#include <iostream>

std::string RandomLineFromFile(const std::string& filename);
std::string removeAfterDash(const std::string& input);
int getstar(const std::string& input);
LPCWSTR random(int i);
int randomIntegerBetween(int min, int max);

int seed = 2434,seed2=32435;
int star[256];
bool fileerr = 0;

LPCWSTR random(int i) {
    std::string tmp1;
    LPCWSTR tmp3;
    const char* path = getConfigValue("namesfile");
    tmp1 = RandomLineFromFile(path);
    if (strcmp(tmp1.c_str(), "FOF") == 0)fileerr = 1;
    star[i] = getstar(tmp1);
    tmp1 = removeAfterDash(tmp1);
    tmp3 = UTF8To16(tmp1.c_str());
    return tmp3;
}

int getstar(const std::string& input) {
    // �ҵ���һ�� "-"
    std::cerr << input << "\n";
    size_t dashPos = input.find("-");
    std::cerr << input << "\n";
    if (dashPos != std::string::npos) {
        // ����ҵ��� "-", ��ȡ "-" ���������
        std::string numberStr = input.substr(dashPos + 1);
        // �������ַ���ת��Ϊ����
        int result = std::stoi(numberStr);
        if (result > 6)result = 6;
        if (result < 3)result = 3;
        return result;
    }
    // ���δ�ҵ� "-" ��ת��ʧ�ܣ�����Ĭ��ֵ�����Ը�����Ҫ�޸ģ�
    return 3;
}

std::string removeAfterDash(const std::string& input) {
    // �ҵ���һ�� "-"
    size_t dashPos = input.find("-");
    if (dashPos != std::string::npos) {
        // ����ҵ��� "-", ���е� "-" ���������
        return input.substr(0, dashPos);
    }
    else {
        // ���δ�ҵ� "-", ֱ�ӷ���ԭ�ַ���
        return input;
    }
}

std::string RandomLineFromFile(const std::string& filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (!file)
    {
        errlog("�ļ�������");
        return "FOF";
    }
    std::string line="���ţ������-3";
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    if (lines.empty())
    {
        errlog("file is empty");
        return "File is empty";
    }
    // ���ѡ��һ��
    std::srand(static_cast<unsigned int>(std::time(nullptr))*seed);
    int temp = rand();
    std::srand(((static_cast<unsigned int>(std::time(nullptr))) * seed + temp) * rand());
    int randomIndex = std::rand() % lines.size();
    seed++;
    return lines[randomIndex];
}
int randomIntegerBetween(int min, int max) {
    // ��ʼ�������������
    srand(static_cast<unsigned int>(time(0))+seed2);
    // ����������ķ�Χ��������һ���������Χ�ڵ������
    int range = max - min + 1;
    int randomNum = rand();
    srand(static_cast<unsigned int>(time(0)) + seed2 + randomNum);
    randomNum = min + rand() % range;
    seed2+=randomNum;
    return randomNum;
}