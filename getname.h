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

bool IsFontInstalled(LPCWSTR fontName);
std::string RandomLineFromFile(const std::string& filename);
std::string removeAfterDash(const std::string& input);
int getstar(const std::string& input);
LPCWSTR random(int i);

int seed = 2434;
int star[256];

LPCWSTR random(int i) {
    std::string tmp1;
    LPCWSTR tmp3;
    const char* path = getConfigValue("namesfile");
    tmp1 = RandomLineFromFile(path);
    tmp3 = UTF8To16(tmp1.c_str());
    if (lstrcmpW(tmp3, L"FOF")==0||lstrcmpW(tmp3,L"FAIL TO READ") == 0) {
        MessageBox(NULL, L"FALL", L"", NULL);
        PostQuitMessage(0);
        return L"FALL";
    }
    else {
        star[i] = getstar(tmp1);
        tmp1 = removeAfterDash(tmp1);
        return tmp3;
    }
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
        MessageBox(NULL, L"���ļ�ʧ�ܣ���ȷ���ļ�����", L"�����Ҳ����ļ�����", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
        return "FOF";
    }

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    if (lines.empty())
    {
        return "File is empty";
    }
    // ���ѡ��һ��
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex = std::rand() % lines.size();
    return lines[randomIndex];
}

bool IsFontInstalled(LPCWSTR fontName) {// ��������������Ƿ����
    LOGFONTW lf;
    memset(&lf, 0, sizeof(LOGFONTW));
    lf.lfCharSet = DEFAULT_CHARSET;
    wcscpy(lf.lfFaceName, fontName);

    BOOL fontExists = FALSE;
    EnumFontFamiliesExW(GetDC(NULL), &lf, [](const LOGFONTW* lpelfe, const TEXTMETRICW* lpntme, DWORD FontType, LPARAM lParam) -> int {
        BOOL* fontExists = (BOOL*)lParam;
        *fontExists = TRUE;
        return 0; // ֹͣö��
        }, (LPARAM)&fontExists, 0);

    return fontExists;
}