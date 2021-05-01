/*

SpaceInputs - A library that fits to all of your input needings, whether GUI is present or not.

Copyright (c) 2021 - SpaceCraft

Distributed under terms of the MIT licence.

*/
#pragma once

#define SpaceLogToFile 1<<1
#define SpaceLogToTerminal 1<<2

#if __has_include("spacelogs.hpp") //C++17 stuff here: Checks if the SpaceLogs is available or not.  
    #include "spacelogs.hpp"
#else
    #include "lib/spacelogs.hpp"
    #warning "Don't forget to run install.sh after compilation, otherwise SpaceInputs won't work."
#endif
#include <cstdint>
#include <cstring>

#ifdef __unix__
            #if __has_include("X11/Xlib.h") 
                #include <X11/Xlib.h>
                #define XLIB_EXISTS

                /*Keyboard events to be handled.*/
                #define SpaceKeyboardKeyPress KeyPressMask
                #define SpaceKeyboardKeyRelease KeyReleaseMask

                /*Keyboard light codes.*/
                #define SpaceKeyboardLightNumLock 16
                #define SpaceKeyboardLightScrollLock 1
                #define SpaceKeyboardLightCapsLock 2
            #else
                #include <termios.h>
                #define XLIB_DOES_NOT_EXIST
            #endif
    #else
        #ifdef _WIN32
            #error "SpaceInputs cannot be compiled under Windows (for now)!"
        #endif
    #endif


typedef struct{
    char* key_name;
    uint32_t keycode;
    uint8_t event_type; //1: the key is being pressed, 0: the key has been released.
} SpaceKeyStroke;
#if (defined(XLIB_EXISTS))
    
    /*Mouse events to be captured.*/
    #define SpaceMouseButtonEvents (ButtonPressMask | ButtonReleaseMask) //Button press and release events.
    #define SpaceCursorWindowEvents (EnterWindowMask | LeaveWindowMask) //Covers the pointer-window entry and exit events.
    #define SpaceCursorMovementEvents (PointerMotionMask) //Covers the pointer movements.
    
    /*Mouse buttons. Can be used with SpaceMouseEvents struct.*/
    #define SpaceCursorLeftButton 1
    #define SpaceCursorMiddleButton 2
    #define SpaceCursorRightButton 3
    #define SpaceCursorScrollUp 4
    #define SpaceCursorScrollDown 5

    /*Cursor position as X and Y.*/
    typedef struct{
        int32_t x,y;
    } SpaceCursorPosition;
    
    /*Covers every single mouse event.*/
    typedef struct{
        SpaceCursorPosition cursor_location; //X and Y coordinates of the cursor location.
        uint32_t clicked_button;
        bool is_cursor_outside_window;
    } SpaceMouseEvents;

#endif
    SpaceLogs g_log_evt;
    uint8_t g_log_level = 0;
    void log_err(std::string log);