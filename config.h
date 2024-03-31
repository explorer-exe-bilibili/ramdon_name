#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CONFIG_ "\\files\\config.txt"
#define YUANSHI "Diamond"
#define NAMES "namesfile"
#define BLUE_BALL_COUNT "buleball"
#define PINK_BALL_COUNT "redball"
#define OFF_VIDEO "off video"
#define WINDOW_TITEL "title name"
#define MODE "first mode"
#define INWINDOW "window mode(not full screen)"
#define OVER4 "over4"
#define OVER3 "over3"
#define OVER2 "over2"
#define OVER1 "over1"
// ����������ṹ
typedef struct {
    char* name;
    char* value;
} ConfigItem;

// ��������ڵ�
typedef struct Node {
    ConfigItem item;
    struct Node* next;
} Node;

// ��������ͷ�ڵ�
Node* head = NULL;
const char* LogString;
std::string configpath;
const char* CONFIG;

void addConfigItem(const char* name, const char* value);
void readConfigFile();
void saveConfigFile();
void cleanupConfigList();
void deleteConfigItem(const char* name);
void replaceConfigOption(const char* option, const char* value);
void printAllConfigItems();
void initconfig();
const char* getConfigValue(const char* name);

void initconfig() {
    configpath = runpath;
    configpath += CONFIG_;
    CONFIG = configpath.c_str();
    FILE* file = fopen(CONFIG, "r");
    if (file == NULL) {
        addConfigItem(NAMES, ".\\names.txt");
        addConfigItem(YUANSHI, "10000");
        addConfigItem(BLUE_BALL_COUNT, "10000");
        addConfigItem(PINK_BALL_COUNT, "10000");
        addConfigItem(OFF_VIDEO, "0");
        addConfigItem(MODE, "1");
        addConfigItem(INWINDOW, "0");
        addConfigItem(WINDOW_TITEL, "ԭ��");
        addConfigItem(OVER4, ".\\files\\imgs\\over4.bmp");
        addConfigItem(OVER3, ".\\files\\imgs\\over3.bmp");
        addConfigItem(OVER2, ".\\files\\imgs\\over2.bmp");
        addConfigItem(OVER1, ".\\files\\imgs\\over1.bmp");
        saveConfigFile();
        readConfigFile();
        printAllConfigItems();
    }
    else
    {
        fclose(file);
        readConfigFile();
        const char* LogString = getConfigValue(MODE);
        if (strcmp(LogString, "err") == 0)addConfigItem(MODE, "1");
        LogString = getConfigValue(OFF_VIDEO);
        if (strcmp(LogString, "err") == 0)addConfigItem(OFF_VIDEO, "0");
        LogString = getConfigValue(WINDOW_TITEL);
        if (strcmp(LogString, "err") == 0)addConfigItem(WINDOW_TITEL, "ԭ��");
        LogString = getConfigValue(NAMES);
        if (strcmp(LogString, "err") == 0)addConfigItem(NAMES, ".\\names.txt");
        LogString = getConfigValue(BLUE_BALL_COUNT);
        if (strcmp(LogString, "err") == 0)addConfigItem(BLUE_BALL_COUNT, "10000");
        LogString = getConfigValue(PINK_BALL_COUNT);
        if (strcmp(LogString, "err") == 0)addConfigItem(PINK_BALL_COUNT, "10000");
        LogString = getConfigValue(YUANSHI);
        if (strcmp(LogString, "err") == 0)addConfigItem(YUANSHI, "10000");
        LogString = getConfigValue(INWINDOW);
        if (strcmp(LogString, "err") == 0)addConfigItem(INWINDOW, "0");
        LogString = getConfigValue(OVER1);
        if (strcmp(LogString, "err") == 0)addConfigItem(OVER1, ".\\files\\imgs\\over1.bmp");
        LogString = getConfigValue(OVER2);
        if (strcmp(LogString, "err") == 0)addConfigItem(OVER2, ".\\files\\imgs\\over2.bmp");
        LogString = getConfigValue(OVER3);
        if (strcmp(LogString, "err") == 0)addConfigItem(OVER3, ".\\files\\imgs\\over3.bmp");
        LogString = getConfigValue(OVER4);
        if (strcmp(LogString, "err") == 0)addConfigItem(OVER4, ".\\files\\imgs\\over4.bmp");
        printAllConfigItems();
        log("config init successfully");
    }
}
const char* getConfigValue(const char* name) {
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
void addConfigItem(const char* name, const char* value) {
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
    newItem.value = _strdup(value);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        errlog("Memory allocation error(addConfigItem)");
    }

    newNode->item = newItem;
    newNode->next = head;
    head = newNode;
    saveConfigFile();
}

// ��ȡ�����ļ����������������
void readConfigFile() {
    FILE* file = fopen(CONFIG, "r");
    if (file == NULL) {
        errlog("Error opening file for reading");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* trimLine = strtok(line, "\n");  // �Ƴ����з�
        char* currentOption = strtok(trimLine, "=");
        if (currentOption != NULL) {
            char* value = strtok(NULL, "=");
            // ������������
            addConfigItem(currentOption, value);
            log(trimLine);
        }
    }
    fclose(file);
}

// ��������������ļ�
void saveConfigFile() {
    FILE* file = fopen(CONFIG, "w");
    if (file == NULL) {
        errlog("Error opening file for writing");
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
void cleanupConfigList() {
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
    log("Free ConfigList complete");
}


// ɾ��������
void deleteConfigItem(const char* name) {
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
    log("del %s success", name);
}


void replaceConfigOption(const char* name, const char* value) {
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
    saveConfigFile();
}

void printAllConfigItems() {
    log(" Configuration:");
    Node* current = head;
    while (current != NULL) {
        log("%s: %s", current->item.name, current->item.value);
        current = current->next;
    }
}