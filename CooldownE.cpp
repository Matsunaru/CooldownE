#include <iostream>
#include <windows.h>
#include <thread>
#include <gdiplus.h>
#include <string>
#pragma comment (lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;

bool insAndDownPressed = false;


void InitializeGDIPlus() {
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}
//Initialization GDI

HWND Ekran(int x, int y,HINSTANCE hInstance)
{
    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT,//always on, Trasparation
        L"STATIC", //class name
        NULL, //window name
        WS_POPUP,//style
        x, y, 400, 300, // x,y Position, size
        NULL, NULL, hInstance, NULL //Parent, Menu, Instance handle, Parameters
    );

    if (!hwnd) {
        MessageBox(NULL, L"can't open win", L"Error", MB_ICONERROR);
        return NULL;
    }

    SetLayeredWindowAttributes(hwnd, 0, 128, LWA_ALPHA);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    return hwnd;
}

void aktuwin(HWND hwnd,int i)
{
    if (!hwnd) return;

    HDC hdc = GetDC(hwnd);
    Graphics graphics(hdc);

    graphics.Clear(Color(255, 255, 255, 255));//clean win

    // loading image
    Image image(L"path_to_image.jpg");
    graphics.DrawImage(&image, 0, 0, 400, 300); // Drawing a picture

    // Countdown display
    Font font(L"Arial", 24);
    SolidBrush brush(Color(255, 0, 0, 0));
    std::wstring currentTime = to_wstring(i);
    graphics.DrawString(currentTime.c_str(), -1, &font, PointF(10, 10), &brush);

    // clean
    ReleaseDC(hwnd, hdc);
}


void klawisz()//first Key graber
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    InitializeGDIPlus();
    HWND hwnd = Ekran(100, 10, hInstance);
    while (true)
    {
        if (GetAsyncKeyState(0x36) & 0x8000)//grabing "6"
        {

            for (int i = 60; i >= 0; i--)
            {
                aktuwin(hwnd, i);
                Sleep(1000);
            }
        }
    }
}

void klawisz2()//2nd key graber
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    InitializeGDIPlus();
    HWND hwnd = Ekran(200, 200, hInstance);
    while (true)
    {
        if ((GetAsyncKeyState(0x2D) & 0x8000) && (GetAsyncKeyState(0x28) & 0x8000)) //checking if ins and arrow down is press if yes, then 'true'
        {
            insAndDownPressed = true;
        }
        {
            if ((insAndDownPressed == true) && (GetAsyncKeyState(0x43) & 0x8000))//checking if down&ins is true, and if 'c' was press
            {

                for (int i = 60; i >= 0; i--)
                {
                    aktuwin(hwnd, i);
                    Sleep(1000);
                }
                insAndDownPressed = false;// returing ins&down on false
            }
        }
    }
}

int main()
{
    thread t1(klawisz);//atach key graber on thread t1
    thread t2(klawisz2);//atach 2nd key graber on thread t2

    t1.detach();//detach t1 from main program
    t2.detach();//detach t2 from main program

    while (true)//it make program stay always on
    {
        Sleep(1000);
    }
    return 0;
}

