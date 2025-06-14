#include "OverlayWindow.h"
#include <gdiplus.h>
#include <codecvt>
#include <locale>

using namespace Gdiplus;

// Constructor: initializes overlay window at (x, y) with given size
OverlayWindow::OverlayWindow(int x, int y, int width, int height, HINSTANCE hInst)
    : hInst_(hInst)
{
    createWindow(x, y, width, height);
}

// Destructor: destroys the window if it exists
OverlayWindow::~OverlayWindow() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

// Helper that sets up a transparent, topmost layered window
void OverlayWindow::createWindow(int x, int y, int width, int height) {
    hwnd_ = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT,  // extended styles
        L"STATIC",    // predefined window class for static controls
        nullptr,        // no window title
        WS_POPUP,       // popup window style
        x, y, width, height,  // position and size
        nullptr, nullptr, hInst_, nullptr
    );
    if (!hwnd_) {
        // Show error message if window creation fails
        MessageBoxW(nullptr, L"Failed to create overlay window", L"Error", MB_ICONERROR);
        return;
    }
    // Make window transparent where the key color (pure green) appears
    SetLayeredWindowAttributes(hwnd_, RGB(0, 255, 0), 255, LWA_COLORKEY);
    ShowWindow(hwnd_, SW_SHOW);
    UpdateWindow(hwnd_);
}

// Renders the specified image and draws the countdown value
void OverlayWindow::update(int secondsLeft, const std::string& imagePath) {
    if (!hwnd_) return;

    // Convert UTF-8 path to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wPath = converter.from_bytes(imagePath);

    HDC hdc = GetDC(hwnd_);
    Graphics graphics(hdc);

    // Draw the image to fill the window
    Image img(wPath.c_str());
    graphics.DrawImage(&img, 0, 0, 105, 70);

    // Draw the countdown text on top of the image
    Font font(L"Arial", 24);
    SolidBrush brush(Color(255, 0, 0, 0));
    std::wstring wTime = std::to_wstring(secondsLeft);
    graphics.DrawString(wTime.c_str(), -1, &font, PointF(30, 40), &brush);

    // Release device context
    ReleaseDC(hwnd_, hdc);
}