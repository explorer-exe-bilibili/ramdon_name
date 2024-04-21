#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<string>
#include"mywindows.h"
// ����������ṹ

typedef struct ConfigItem {
    char* name;
    char value[260];
} ConfigItem;

// ��������ڵ�
typedef struct Node {
    ConfigItem item;
    struct Node* next;
} Node;

// ��������ͷ�ڵ�
Node* config::head = NULL;
const char* config::LogString;
std::string config::configpath;
const char* config::CONFIG;

void config::init() {
    configpath = Log::runpath;
    configpath += CONFIG_;
    CONFIG = configpath.c_str();
    FILE* file = fopen(CONFIG, "r");
    if (file == NULL) {
        add(NAMES, ".\\names.txt");
        add(NAMES1, ".\\names1.txt");
        add(NAMES2, ".\\names2.txt");
        add(NAMES3, ".\\names3.txt");
        add(NAMES4, ".\\names4.txt");
        add(YUANSHI, "10000");
        add(BLUE_BALL_COUNT, "10000");
        add(PINK_BALL_COUNT, "10000");
        add(OFF_VIDEO, "0");
        add(SPECIAL, "0");
        add(MODE, "1");
        add(INWINDOW, "0");
        add(OFFMUSIC, "0");
        add(WINDOW_TITEL, "ԭ��");
        add(OVER4, ".\\files\\imgs\\over4.bmp");
        add(OVER3, ".\\files\\imgs\\over3.bmp");
        add(OVER2, ".\\files\\imgs\\over2.bmp");
        add(OVER1, ".\\files\\imgs\\over1.bmp");
        saveFile();
        readFile();
        printAllConfigItems();
    }
    else
    {
        fclose(file);
        readFile();
        const char* LogString = get(MODE);
        if (strcmp(LogString, "err") == 0)add(MODE, "1");
        LogString = get(OFF_VIDEO);
        if (strcmp(LogString, "err") == 0)add(OFF_VIDEO, "0");
        LogString = get(WINDOW_TITEL);
        if (strcmp(LogString, "err") == 0)add(WINDOW_TITEL, "ԭ��");
        LogString = get(NAMES);
        if (strcmp(LogString, "err") == 0)add(NAMES, ".\\names.txt");
        LogString = get(NAMES1);
        if (strcmp(LogString, "err") == 0)add(NAMES1, ".\\names1.txt");
        LogString = get(NAMES2);
        if (strcmp(LogString, "err") == 0)add(NAMES2, ".\\names2.txt");
        LogString = get(NAMES3);
        if (strcmp(LogString, "err") == 0)add(NAMES3, ".\\names3.txt");
        LogString = get(NAMES4);
        if (strcmp(LogString, "err") == 0)add(NAMES4, ".\\names4.txt");
        LogString = get(BLUE_BALL_COUNT);
        if (strcmp(LogString, "err") == 0)add(BLUE_BALL_COUNT, "10000");
        LogString = get(PINK_BALL_COUNT);
        if (strcmp(LogString, "err") == 0)add(PINK_BALL_COUNT, "10000");
        LogString = get(YUANSHI);
        if (strcmp(LogString, "err") == 0)add(YUANSHI, "10000");
        LogString = get(SPECIAL);
        if (strcmp(LogString, "err") == 0)add(SPECIAL, "0");
        LogString = get(OFFMUSIC);
        if (strcmp(LogString, "err") == 0)add(OFFMUSIC, "0");
        LogString = get(INWINDOW);
        if (strcmp(LogString, "err") == 0)add(INWINDOW, "0");
        LogString = get(OVER1);
        if (strcmp(LogString, "err") == 0)add(OVER1, ".\\files\\imgs\\over1.bmp");
        LogString = get(OVER2);
        if (strcmp(LogString, "err") == 0)add(OVER2, ".\\files\\imgs\\over2.bmp");
        LogString = get(OVER3);
        if (strcmp(LogString, "err") == 0)add(OVER3, ".\\files\\imgs\\over3.bmp");
        LogString = get(OVER4);
        if (strcmp(LogString, "err") == 0)add(OVER4, ".\\files\\imgs\\over4.bmp");
        printAllConfigItems();
        mywindows::log("config init successfully");
    }
}

const char* config::get(const char* name) {
    Node* current = head;

    // �����������ƥ���������
    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            // �ҵ�ƥ�����������������ֵ
            return current->item.value;
        }
        current = current->next;
    }

    // ���û���ҵ�ƥ�����������ؿ��ַ������ʵ���Ĭ��ֵ
    return "err";
}
// ������������
void config::add(const char* name, const char* value) {
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            strcpy(current->item.value, value);
            return;
        }
        prev = current;
        current = current->next;
    }
    ConfigItem newItem;
    newItem.name = _strdup(name);
    strcpy(newItem.value, value);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        mywindows::errlog("Memory allocation error(add)");
    }

    newNode->item = newItem;
    newNode->next = head;
    head = newNode;
    saveFile();
}
// ��ȡ�����ļ����������������
void config::readFile() {
    FILE* file = fopen(CONFIG, "r");
    if (file == NULL) {
        mywindows::errlog("Error opening file for reading");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* trimLine = strtok(line, "\n");  // �Ƴ����з�
        char* currentOption = strtok(trimLine, "=");
        if (currentOption != NULL) {
            char* value = strtok(NULL, "=");
            // ������������
            add(currentOption, value);
            mywindows::log(trimLine);
        }
    }
    fclose(file);
}
// ��������������ļ�
void config::saveFile() {
    FILE* file = fopen(CONFIG, "w");
    if (file == NULL) {
        mywindows::errlog("Error opening file for writing");
        return;
    }
    Node* current = head;
    while (current != NULL) {
        fprintf(file, "%s=%s\n", current->item.name, current->item.value);
        current = current->next;
    }
    fclose(file);
}
// �ͷ�����ڵ���ڴ�
void config::cleanup() {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current->item.name);
        free(current->item.value);
        free(current);
        current = next;
    }
    head = NULL;
    mywindows::log("Free ConfigList complete");
}
// ɾ��������
void config::deleteItem(const char* name) {
    Node* prev = NULL;
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            // �ҵ�ƥ��������ɾ����
            if (prev != NULL) {
                prev->next = current->next;
            }
            else {
                head = current->next;
            }
            free(current->item.name);
            free(current->item.value);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    mywindows::log("del %s success", name);
}

void config::replace(const char* name, const char* value) {
    Node* prev = NULL;
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            strcpy(current->item.value, value);
        }
        prev = current;
        current = current->next;
    }
    free(current);
    saveFile();
}

void config::printAllConfigItems() {
    mywindows::log(" Configuration:");
    Node* current = head;
    while (current != NULL) {
        mywindows::log("%s: %s", current->item.name, current->item.value);
        current = current->next;
    }
}