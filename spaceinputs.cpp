/*

SpaceInputs - An input library that fits to all of your input needings.

Copyright (c) 2021 - SpaceCraft

Distributed under the terms of MIT licence.

*/ 
#include "spaceinputs.hpp"

//We can load the mouse functions under these preprocessor command cycle too.
    #if defined(__unix__)
        
            #ifdef XLIB_EXISTS
                void SpaceInputs::Keyboard::prepare_environment(Window &window, Display *display_ = XOpenDisplay(nullptr), uint32_t evt_ = SpaceKeyboardKeyPress){
                        this->win = window;
                        this->dpy = display_;
                        this->keyboard_evt_capture_flags = evt_;
                        XSelectInput(this->dpy,this->win,this->keyboard_evt_capture_flags);
                        XMapRaised(this->dpy,win);
                }
                SpaceInputs::Keyboard::Keyboard(Window &window){
                    this->prepare_environment(window);
                }
                SpaceInputs::Keyboard::Keyboard(Display* display, Window &window){
                    this->prepare_environment(window,display);
                }
                SpaceInputs::Keyboard::Keyboard(Display* display, Window &window, uint32_t captured_events){
                    this->prepare_environment(window,display,captured_events);
                }
                SpaceKeyStroke SpaceInputs::Keyboard::get_keybind(){
                    
                    XNextEvent(this->dpy,&this->event);
                    switch(event.type){ //Don't worry about unwanted events, X Server will do the thing for us with not capturing the events except we've passed into constructor(s).
                        case KeyPress:
                            temp.keycode = event.xkey.keycode;
                            temp.key_name = XKeysymToString(XKeycodeToKeysym(this->dpy,temp.keycode,0));
                            temp.event_type = 1;
                        break;
                        case KeyRelease:
                            temp.keycode = event.xkey.keycode;
                            temp.key_name = XKeysymToString(XKeycodeToKeysym(this->dpy,temp.keycode,0));
                            temp.event_type = 0;
                        break;
                        default:
                            break;
                    }
                    return temp;
                }
                SpaceInputs::Keyboard::~Keyboard(){
                    XDestroyWindow(this->dpy,this->win);
                    XCloseDisplay(this->dpy);
                }
            #endif //Xlib checker
        //TODO: Terminal Stuff.
       
    #endif //UNIX checker

#if (defined(__unix__) && defined(XLIB_EXISTS))
            void SpaceInputs::Mouse::prepare_environment(Window &window, Display *display_ = XOpenDisplay(NULL), uint32_t evt_ = SpaceMouseButtonEvents){
                    this->win = window;
                    this->dpy = display_;
                    this->mouse_evt_capture_flags = evt_;
                    XSelectInput(this->dpy,this->win,this->mouse_evt_capture_flags);
                    XMapRaised(this->dpy,win);
            }                
            SpaceInputs::Mouse::Mouse(Window &window){
                this->prepare_environment(window);
            }
            SpaceInputs::Mouse::Mouse(Display* display, Window &window){
                this->prepare_environment(window,display);
            }
            SpaceInputs::Mouse::Mouse(Display* display, Window &window, uint32_t captured_events){
                   this->prepare_environment(window,display,captured_events);
            }
            SpaceMouseEvents SpaceInputs::Mouse::get_mouse_events(){
                this->latest_mouse_evt.clicked_button =
                XNextEvent(this->dpy,&this->event);
                switch(this->event.type){
                    case ButtonPress:
                    
                       this->latest_mouse_evt.clicked_button = this->event.xbutton.button;
                    break;
                    case MotionNotify:
                        this->latest_mouse_evt.cursor_location.x = this->event.xmotion.x;
                        this->latest_mouse_evt.cursor_location.y = this->event.xmotion.y;
                    break;
                    case EnterNotify:
				        this->latest_mouse_evt.is_cursor_outside_window = false;
			        break;
			        case LeaveNotify:
				        this->latest_mouse_evt.is_cursor_outside_window = true;
			        break;
                    default:
                        break;
                }
                return this->latest_mouse_evt;
            }
            SpaceInputs::Mouse::~Mouse(){
                XDestroyWindow(this->dpy,this->win);
                XCloseDisplay(this->dpy); 
            }
#endif