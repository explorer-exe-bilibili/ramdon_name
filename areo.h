#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <vector>

// ����Direct2D��
#pragma comment(lib, "d2d1.lib")

// ȫ�ֱ���
ID2D1Factory1* pFactory = nullptr;
ID2D1Device* pDevice = nullptr;
ID2D1DeviceContext* pContext = nullptr;

// ��ȡ���ڲ�Ӧ�ø�˹ģ��
void CaptureAndBlurWindow(HWND hwnd) {
    // ��ʼ��Direct2D
    D2D1_FACTORY_OPTIONS options;
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    pFactory->CreateDevice(&pDevice);
    pDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &pContext);

    // ��ȡ����
    HBITMAP hBitmap = NULL;
    if (PrintWindow(hwnd, hBitmap, NULL)) {
        // ��HBITMAP����Direct2Dλͼ
        ID2D1Bitmap* pD2DBitmap = nullptr;
        pContext->CreateBitmapFromHbitmap(hBitmap, &D2D1::SizeU(0, 0), nullptr, &pD2DBitmap);

        // ������˹ģ��Ч��
        ID2D1Effect* pBlurEffect = nullptr;
        pContext->CreateEffect(CLSID_D2D1GaussianBlur, &pBlurEffect);
        pBlurEffect->SetInput(0, pD2DBitmap);
        pBlurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 3.0f);

        // ����ģ��Ч��
        pContext->BeginDraw();
        pContext->DrawImage(pBlurEffect);
        pContext->EndDraw();

        // �ͷ���Դ
        pD2DBitmap->Release();
        pBlurEffect->Release();
        DeleteObject(hBitmap);
    }
}

// ����Direct2D��Դ
void CleanupDirect2D() {
    if (pContext) pContext->Release();
    if (pDevice) pDevice->Release();
    if (pFactory) pFactory->Release();
}