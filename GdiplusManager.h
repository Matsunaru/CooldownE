#pragma once
#include <Windows.h>
#include <gdiplus.h>

// Manages initialization and shutdown of GDI+ via RAII
class GdiPlusManager {
public:
    // Constructor: calls GdiplusStartup and stores the returned token
    GdiPlusManager();

    // Destructor: calls GdiplusShutdown using the stored token
    ~GdiPlusManager();

private:
    // Holds the token returned by GdiplusStartup for later shutdown
    ULONG_PTR gdiplusToken_;
};