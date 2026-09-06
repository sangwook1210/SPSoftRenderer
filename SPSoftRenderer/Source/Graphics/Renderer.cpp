#include "windows.h"
#include "Graphics//Renderer.h"

Renderer::Renderer(int width, int height)
	:width(width), height(height), frameBuffer(width, height) {}

void Renderer::Render(HWND hWnd)
{
    frameBuffer.Clear(0xFFFFFFFF);

    // 소프트웨어 렌더링

    /* test
    frameBuffer.SetPixel(511, 511, 0x00000000);
    frameBuffer.SetPixel(512, 511, 0x00000000);
    frameBuffer.SetPixel(513, 511, 0x00000000);
    frameBuffer.SetPixel(511, 512, 0x00000000);
    frameBuffer.SetPixel(512, 512, 0x00000000);
    frameBuffer.SetPixel(513, 512, 0x00000000);
    frameBuffer.SetPixel(511, 513, 0x00000000);
    frameBuffer.SetPixel(512, 513, 0x00000000);
    frameBuffer.SetPixel(513, 513, 0x00000000);
    */

    Present(hWnd);
}

void Renderer::Present(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);

    BITMAPINFO bitmapInfo = {};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = frameBuffer.GetWidth();
    bitmapInfo.bmiHeader.biHeight = -frameBuffer.GetHeight();   // top-down 데이터를 의미
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(
        hdc,
        0, 0,
        frameBuffer.GetWidth(),
        frameBuffer.GetHeight(),
        0, 0,
        frameBuffer.GetWidth(),
        frameBuffer.GetHeight(),
        frameBuffer.GetPixels(),
        &bitmapInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );

    ReleaseDC(hWnd, hdc);
}