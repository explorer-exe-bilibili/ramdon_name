#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CONFIG "./config.txt"
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
        addConfigItem("namesfile", "D:\\YuanShenName\\names.txt");
        addConfigItem("language", "chinese");
        addConfigItem("Diamond", "10000");
        addConfigItem("buleball", "10000");
        addConfigItem("redball", "10000");
        addConfigItem("video_path", ".\\files\\background.avi");
        addConfigItem("first mode", "1");
        saveConfigFile();
        readConfigFile();
        printAllConfigItems();
    }
    else
    {
        fclose(file);
        readConfigFile();
        printAllConfigItems();
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
    return "null";
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
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    newNode->item = newItem;
    newNode->next = head;
    head = newNode;
}

// ��ȡ�����ļ����������������
void readConfigFile() {
    FILE* file = fopen(CONFIG, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
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
        }
    }

    fclose(file);
}

// ��������������ļ�
void saveConfigFile() {
    FILE* file = fopen(CONFIG, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
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
}
// �滻�����ļ��е�ָ��������
void replaceConfigOption(const char* option, const char* value) {
    FILE* file = fopen(CONFIG, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    const char* tempFilename = "temp_config.txt";
    FILE* tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file for writing");
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
    OutputDebugString(L" Configuration:\n");
    Node* current = head;
    while (current != NULL) {
        PrintfDebugString(L"%s: %s\n", current->item.name, current->item.value);
        current = current->next;
    }
}