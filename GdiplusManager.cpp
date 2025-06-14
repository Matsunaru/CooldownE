#include "GdiPlusManager.h"
using namespace Gdiplus;

// Constructor: initializes GDI+ by calling GdiplusStartup
GdiPlusManager::GdiPlusManager() {
    GdiplusStartupInput gdiplusStartupInput;  // Input parameters for GDI+ startup
    GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput, nullptr); // Store token for shutdown
}

// Destructor: shuts down GDI+ by calling GdiplusShutdown with the stored token
GdiPlusManager::~GdiPlusManager() {
    GdiplusShutdown(gdiplusToken_); // Clean up all GDI+ resources
}