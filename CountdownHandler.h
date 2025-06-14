#pragma once
#include "KeyListener.h"
#include "OverlayWindow.h"
#include <atomic>

// Handles countdown logic triggered by key events
// Inherits from KeyListener to run in a background thread
class CountdownHandler : public KeyListener {
public:
    // Constructor parameters:
    // keyCode1: primary key or first part of a key combo
    // keyCode2: secondary key (combo) or -1 if single-key mode
    // window: target overlay window for rendering countdown
    // startSeconds: initial countdown value in seconds
    CountdownHandler(int keyCode1, int keyCode2, OverlayWindow* window, int startSeconds);

    // Implements the listening loop that watches for key events and triggers the countdown
    void listen() override;
    void start() {
        running_ = true;
        thread_ = std::thread(&CountdownHandler::listen, this);
    }
    void stop() {
        running_ = false;
        if (thread_.joinable()) thread_.join();
    }

private:
    std::atomic<bool> running_{ false };
    std::thread      thread_;
    int key1_;           // Virtual-key code for primary key
    int key2_;           // Virtual-key code for secondary key (or -1 if unused)
    OverlayWindow* window_; // Overlay window instance for drawing
    int startSec_;       // Starting value for countdown
    bool comboActive_;   // Tracks if key combo has been armed
};
