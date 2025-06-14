#include "CountdownHandler.h"
#include <Windows.h>
#include <gdiplus.h>

// Constructor: initializes key codes, target window, and countdown length
CountdownHandler::CountdownHandler(int keyCode1, int keyCode2, OverlayWindow* window, int startSeconds)
    : key1_(keyCode1)
    , key2_(keyCode2)
    , window_(window)
    , startSec_(startSeconds)
    , comboActive_(false)
{
    // No additional initialization required here
}

// Main listening loop runs in a background thread
void CountdownHandler::listen() {
    // Initially render the background state (zero seconds)
    window_->update(0, "TLO.png");

    while (true) {
        if (key2_ < 0) {
            // Single-key mode: trigger countdown immediately on key1 press
            if (GetAsyncKeyState(key1_) & 0x8000) {
                for (int i = startSec_; i >= 0; --i) {
                    // Choose image based on countdown length
                    window_->update(i,
                        (startSec_ == 60) ? "TITLE2.png" : "TITLE1.png");
                    Sleep(1000);
                }
                // After countdown, reset to background state
                window_->update(0, "TLO.png");
                // Wait for key1 release to avoid retriggering
                while (GetAsyncKeyState(key1_) & 0x8000) Sleep(30);
            }
        }
        else {
            // Combo mode: first arm on key1 + key2
            if (!comboActive_) {
                bool k1 = (GetAsyncKeyState(key1_) & 0x8000);
                bool k2 = (GetAsyncKeyState(key2_) & 0x8000);
                if (k1 && k2) {
                    comboActive_ = true;
                    // Debounce: wait until both keys are released
                    while ((GetAsyncKeyState(key1_) & 0x8000) ||
                        (GetAsyncKeyState(key2_) & 0x8000))
                    {
                        Sleep(30);
                    }
                }
            }
            else {
                // Armed: wait for 'C' press to start countdown
                if (GetAsyncKeyState('C') & 0x8000) {
                    for (int i = startSec_; i >= 0; --i) {
                        window_->update(i, "TITLE1.png");
                        Sleep(1000);
                    }
                    // Reset armed state and return to background
                    comboActive_ = false;
                    window_->update(0, "TLO.png");
                    // Debounce 'C' key to prevent immediate retrigger
                    while (GetAsyncKeyState('C') & 0x8000)
                        Sleep(30);
                }
            }
        }

        // Small sleep to reduce CPU usage
        Sleep(50);
    }
}
