#pragma once
#include <thread>
#include "OverlayWindow.h"

// Abstract base class for key event listeners
class KeyListener {
public:
    // Virtual destructor for safe cleanup in derived classes
    virtual ~KeyListener() = default;

    // Blocking method that starts listening for key events; must be implemented by subclasses
    virtual void listen() = 0;

    // Launches the listen() method in a detached background thread
    void start() {
        std::thread(&KeyListener::listen, this).detach();
    }
};

