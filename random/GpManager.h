#pragma once
#include"Gp.h"
class GpManager {
public:
    static Gp& getInstance() {
        static Gp instance;
        return instance;
    }

    static void reset() {
        Gp temp; // ����һ���µ� Gp ʵ��
        GpManager::instance = std::move(temp); // ʹ�� std::move ��ת������Ȩ
    }
private:
    static Gp instance;
};