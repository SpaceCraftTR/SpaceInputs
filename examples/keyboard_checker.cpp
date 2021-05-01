/*

SpaceInputs - An input library that fits to all of your input needings.

Copyright (c) 2021 - SpaceCraft

Distributed under the terms of MIT licence.

*/
#define SPACEINPUTS_GUI_MODE
#include "../spaceinputs.hpp"
#include <cstring>
int main(){
    Display *display = XOpenDisplay(NULL);
    Screen* screen = DefaultScreenOfDisplay(display);
	int screenId = DefaultScreen(display);
    Window win = XCreateSimpleWindow(display, RootWindowOfScreen(screen), 0, 0, 320, 200, 1, BlackPixel(display, screenId), WhitePixel(display, screenId));

    SpaceInputs::Keyboard kbd(display,win, SpaceKeyboardKeyPress | SpaceKeyboardKeyRelease); //Or just pass the window into constructor.
    SpaceKeyStroke key_things;
    while(1){ //An example event loop. You can connect this library with your choice of game engine if you want to.
        key_things = kbd.get_keybind();
        std::cout<<"Keycode : "<<key_things.keycode<<"\nKeycode-to-string : "<<key_things.key_name<<"\nEvent type : "<<((key_things.event_type == 0)?("Key press"):("Key release"))<<"\n";
        if(key_things.keycode == 9){ //or !strcmp with key_things.keyname...
            std::cout<<"Exiting...\n";
            break;
        }
    }
    kbd.~Keyboard();
    return 0;
}