#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CONFIG ".\\files\\config.txt"
#define YUANSHI "Diamond"
#define NAMES "namesfile"
#define BLUE_BALL_COUNT "buleball"
#define PINK_BALL_COUNT "redball"
#define OFF_VIDEO "off video"
#define WINDOW_TITEL "title name"
#define MODE "first mode"
#define INWINDOW "window mode(not full screen)"
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
// �滻�����ļ��е�ָ��������
void replaceConfigOption(const char* option, const char* value) {
    FILE* file = fopen(CONFIG, "r");
    if (file == NULL) {
        errlog("Error opening file for reading");
        return;
    }

    const char* tempFilename = "temp_config.txt";
    FILE* tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        errlog("Error opening temporary file for writing");
        fclose(file);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* trimLine = strtok(line, "\n");  // �Ƴ����з�
        char* currentOption = strtok(trimLine, "=");
        if (currentOption != NULL && strcmp(currentOption, option) == 0) {
            // �滻����������
            fprintf(tempFile, "%s=%s\n", option, value);
        }
        else {
            // ��������������
            fprintf(tempFile, "%s\n", trimLine);
        }
    }
    fclose(file);
    fclose(tempFile);
    // �滻ԭʼ�ļ�
    remove(CONFIG);
    rename(tempFilename, CONFIG);
}

void printAllConfigItems() {
    log(" Configuration:");
    Node* current = head;
    while (current != NULL) {
        log("%s: %s", current->item.name, current->item.value);
        current = current->next;
    }
}