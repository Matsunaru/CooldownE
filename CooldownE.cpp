#pragma comment(lib, "Gdiplus.lib")
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

#include <Windows.h>
#include <gdiplus.h>
#include "GdiPlusManager.h"
#include "OverlayWindow.h"
#include "CountdownHandler.h"

// Entry point for Windows GUI applications
int WINAPI wWinMain(
    _In_ HINSTANCE hInst,          // Handle to the current instance
    _In_opt_ HINSTANCE hPrevInst,  // Handle to the previous instance (unused)
    _In_ PWSTR    lpCmdLine,       // Command line arguments as Unicode string
    _In_ int      nShowCmd        // Controls how the window is to be shown
) {
    // Initialize GDI+ for graphics operations
    GdiPlusManager gdiManager;

    // Create two overlay windows for countdown displays
    OverlayWindow window1(700, 700, 104, 69, hInst);
    OverlayWindow window2(900, 700, 104, 69, hInst);

    // Set up countdown handlers:
    // handler1: single-key mode, triggered by '6', counts down from 60 seconds
    CountdownHandler handler1(0x36, -1, &window1, 60);
    // handler2: combo mode, triggered by INSERT + DOWN, then 'C', counts from 25 seconds
    CountdownHandler handler2(VK_INSERT, VK_DOWN, &window2, 25);

    // Start the key listeners in background threads
    handler1.start();
    handler2.start();

    // Enter the message loop to keep the application running
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}