#pragma once
#include <Windows.h>
#include <string>
#include <gdiplus.h>

// Class that creates and manages a transparent overlay window for drawing images and countdowns
class OverlayWindow {
public:
    // Constructs the overlay at position (x,y) with given size and application instance handle
    OverlayWindow(int x, int y, int width, int height, HINSTANCE hInst);

    // Destroys the overlay window upon object destruction
    ~OverlayWindow();

    // Renders the specified image and draws the countdown value (secondsLeft) onto the window
    void update(int secondsLeft, const std::string& imagePath);

private:
    HWND hwnd_;         // Handle to the Win32 window
    HINSTANCE hInst_;   // Application instance handle

    // Internal helper to create the layered, transparent window
    void createWindow(int x, int y, int width, int height);
};
