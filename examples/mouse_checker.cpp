/*

SpaceInputs - An input library that fits to all of your input needings.

Copyright (c) 2021 - SpaceCraft

Distributed under the terms of MIT licence.

*/
#define SPACEINPUTS_GUI_MODE
#include "../spaceinputs.hpp"
#include <string.h>
int main(){
    Display *display = XOpenDisplay(NULL);
    Screen* screen = DefaultScreenOfDisplay(display);
	int screenId = DefaultScreen(display);
    Window win = XCreateSimpleWindow(display, screen->root, 0, 0, 320, 200, 1, BlackPixel(display, screenId), WhitePixel(display, screenId));
    SpaceMouseEvents evt;
    SpaceInputs::Mouse mouse(&(*display),win,SpaceCursorMovementEvents | SpaceMouseButtonEvents);
    char* buttons[6] = {"","LMB","Middle MB", "RMB", "Scroll up", "Scroll dn"};
    while(1){
        evt = mouse.get_mouse_events();
        if(evt.clicked_button > 0 && evt.clicked_button < 6){
            std::cout<<"Mouse x,y : "<<evt.cursor_location.x<<","<<evt.cursor_location.y<<"\n"<<"Clicked button: "<<buttons[evt.clicked_button]<<"\n";
        }
        else{
            std::cout<<"Mouse x,y : "<<evt.cursor_location.x<<","<<evt.cursor_location.y<<"\n";
        }
        
    }    
    return 0;
}