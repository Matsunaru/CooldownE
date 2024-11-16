#include <iostream>
#include <windows.h>
#include <thread>
#include <gdiplus.h>
#include <string>
#include <codecvt>
#include <locale>
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
        x, y, 100, 100, // x,y Position, size
        NULL, NULL, hInstance, NULL //Parent, Menu, Instance handle, Parameters
    );

    if (!hwnd) {
        MessageBox(NULL, L"can't open win", L"Error", MB_ICONERROR);
        return NULL;
    }

    SetLayeredWindowAttributes(hwnd, RGB(0,255,0), 255, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    return hwnd;
}

void aktuwin(HWND hwnd,int i,string opn)
{
    if (!hwnd) return;

    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    wstring w_opn = converter.from_bytes(opn);

    HDC hdc = GetDC(hwnd);
    Graphics graphics(hdc);

    //graphics.Clear(Color(255, 255, 255, 255));//clean win

    // loading image
    Image image(w_opn.c_str());
    graphics.DrawImage(&image, 0, 0, 102, 102); // Drawing a picture

    // Countdown display
    Font font(L"Arial", 24);
    SolidBrush brush(Color(255, 0, 0, 0));
    std::wstring currentTime = to_wstring(i);
    graphics.DrawString(currentTime.c_str(), -1, &font, PointF(30, 70), &brush);

    // clean
    ReleaseDC(hwnd, hdc);
}


void klawisz()//first Key graber
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    InitializeGDIPlus();
    HWND hwnd = Ekran(700, 700, hInstance);
    aktuwin(hwnd, 0, "TLO.png");
    while (true)
    {
        if (GetAsyncKeyState(0x36) & 0x8000)//grabing "6"
        {

            for (int i = 60; i >= 0; i--)
            {
                aktuwin(hwnd, i,"TITLE2O.png");
                Sleep(1000);
            }
            aktuwin(hwnd, 0, "TITLE2.png");
        }
    }
}

void klawisz2()//2nd key graber
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    InitializeGDIPlus();
    HWND hwnd = Ekran(900, 700, hInstance);
    aktuwin(hwnd, 0, "TLO.png");
    while (true)
    {
        if ((GetAsyncKeyState(0x2D) & 0x8000) && (GetAsyncKeyState(0x28) & 0x8000)) //checking if ins and arrow down is press if yes, then 'true'
        {
            insAndDownPressed = true;
        }
        {
            if ((insAndDownPressed == true) && (GetAsyncKeyState(0x43) & 0x8000))//checking if down&ins is true, and if 'c' was press
            {

                for (int i = 25; i >= 0; i--)
                {
                    aktuwin(hwnd, i,"TITLE1O.png");
                    Sleep(1000);
                }
                insAndDownPressed = false;// returing ins&down on false
                aktuwin(hwnd,0, "TITLE1.png");
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

