/*

SpaceInputs - A library that fits to all of your input needings.

Copyright (c) 2021 - SpaceCraft

Distributed under the terms of MIT licence.

*/
#pragma once
#include "spaceinclude/spaceinputs_definitions.hpp" //Contains preprocessor definitions and directives.
namespace SpaceInputs{

    #if defined(__unix__)
            #ifdef XLIB_EXISTS
            class Keyboard{ 
                    SpaceKeyStroke temp;
                    Display *dpy;
                    XEvent event;
                    Window win;
                    uint32_t keyboard_evt_capture_flags = SpaceKeyboardKeyPress;
                public:
                    Keyboard(Window &window);
                    Keyboard(Display* display, Window &window);
                    Keyboard(Display* display, Window &window, uint32_t captured_events);
                    SpaceKeyStroke get_keybind();
                    void change_keyboard_lights(); //Works for Caps-Lock etc. lights XkbLockModifiers.
                    void keyboard_control_status(bool is_controlled_by_program = false); //Not recommended to use because it might yield with unexpected results.
                    ~Keyboard();
                private:
                    void prepare_environment(Window &window, Display *display_, uint32_t evt_);
            };
            #endif //Xlib checker
        
            class TerminalKeyboard{

            };
        
    #endif //UNIX checker

    #if defined(__unix__)
            #ifdef XLIB_EXISTS
        class Mouse{
                    XEvent event;
                    Display *dpy;
                    Window win;
                    SpaceMouseEvents latest_mouse_evt;
                    SpaceCursorPosition latest_cursor_location;
                    uint32_t mouse_evt_capture_flags;
                public:
                    Mouse(Window &window);
                    Mouse(Display* display, Window &window);
                    Mouse(Display* display, Window &window, uint32_t captured_events);
                    SpaceMouseEvents get_mouse_events();
                    void mouse_control_status(bool is_controlled_by_program = false); //Not recommended to use because it might yield with unexpected results.
                    ~Mouse();
                private:
                    void prepare_environment(Window &window, Display *display_, uint32_t evt_);
        };
            #endif //Xlib checker
    #endif //UNIX checker
};
