#ifndef MENU_H
#define MENU_H
#define displayWith 960
#define displayHeight 630
#include "game.h"
#include <iostream>

class menu{
    public:
        menu();
        ~menu();
        void showCredits();
        ALLEGRO_DISPLAY* display;
        ALLEGRO_MOUSE_STATE mouseState;
        int nativeMessageAwnser;
        ALLEGRO_BITMAP* unSelected;
        ALLEGRO_BITMAP* startSelected;
        ALLEGRO_BITMAP* creditsSelected;
        ALLEGRO_BITMAP* exitSlected;
        ALLEGRO_DISPLAY* creditsDisplay;
        ALLEGRO_BITMAP* creditsUnSelectedExit;
        ALLEGRO_BITMAP* creditsSelectedExit;
        game* newGame;
};

menu::menu(){
    display = al_create_display(displayWith, displayHeight);
    al_set_window_position(display,10,10);
    ALLEGRO_BITMAP *unSelected = al_load_bitmap("startMenu/unSelected.png");
    ALLEGRO_BITMAP *startSelected = al_load_bitmap("startMenu/start.png");
    ALLEGRO_BITMAP *creditsSelected = al_load_bitmap("startMenu/credits.png");
    ALLEGRO_BITMAP *exitSlected = al_load_bitmap("startMenu/exit.png");

    al_draw_bitmap(unSelected,0,0,0);
    al_flip_display();

    while(true){
    al_get_mouse_state(&mouseState);
        if(mouseState.x > 380 && mouseState.x < 560
          && mouseState.y > 240 && mouseState.y < 280){

            al_draw_bitmap(startSelected,-1,0,0);
            al_flip_display();
            if(mouseState.buttons & 1){
                std::cout << "psdfds" << std::endl;
                newGame = new game(display);
                al_resize_display(display, displayWith, displayHeight);
            }

        }else if(mouseState.x > 360 && mouseState.x < 585
                && mouseState.y > 340 && mouseState.y < 380){

            al_draw_bitmap(creditsSelected,0,-1,0);
            al_flip_display();
            if(mouseState.buttons & 1){
                showCredits();
            }

        }else if(mouseState.x > 405 && mouseState.x < 540
          && mouseState.y > 430 && mouseState.y < 470){

            al_draw_bitmap(exitSlected,-1,-1,0);
            al_flip_display();
            if(mouseState.buttons & 1){
               nativeMessageAwnser =  al_show_native_message_box(display, "Exiting game", "WARNING",
                 "Do you really wanna stop the fun?", NULL, ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

                 if(nativeMessageAwnser == 1){
                    exit(0);
                 }else{
                    continue;
                 }
            }

        }else{

            al_draw_bitmap(unSelected,0,1,0);
            al_flip_display();

        }
    }
}

void menu::showCredits(){
    ALLEGRO_DISPLAY* creditsDisplay;
    ALLEGRO_MOUSE_STATE mouseState;
    creditsDisplay = al_create_display(displayWith / 2, displayHeight / 2);
    ALLEGRO_BITMAP *creditsUnSelectedExit = al_load_bitmap("credits/unSelected.png");
    ALLEGRO_BITMAP *creditsSelectedExit = al_load_bitmap("credits/selected.png");

    al_draw_bitmap(creditsUnSelectedExit,-1,0,0);
    al_flip_display();

    while(true){
        al_get_mouse_state(&mouseState);
        if(mouseState.x > 180 && mouseState.x < 290
            && mouseState.y > 220 && mouseState.y < 290){

            al_draw_bitmap(creditsSelectedExit,0,0,0);
            al_flip_display();

            if(mouseState.buttons & 1){
                al_destroy_display(creditsDisplay);
            }

        }else{
            al_draw_bitmap(creditsUnSelectedExit,-1,0,0);
            al_flip_display();
        }
    }

}

menu::~menu(){
}

#endif
