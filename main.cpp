#include <stdio.h>
#include <allegro.h>
#include <allegro_native_dialog.h>
#include <allegro_image.h>
#include <iostream>

#define displayWith 960
#define displayHeight 630
using namespace std;


void showCredits();

int main(int argc, char **argv){

    if(!al_init()){
        cout << "allegro won't work" << endl;
        return -1;
    }
    if(!al_init_image_addon()){
        cout << "image addon not working" << endl;
    }
    if(!al_install_mouse()){
        cout << "mouse driver bad" << endl;
    }

    ALLEGRO_DISPLAY* display;
    ALLEGRO_MOUSE_STATE mouseState;
    int nativeMessageAwnser;

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
    return 0;
}

void showCredits(){
    ALLEGRO_DISPLAY* creditsDisplay;
    ALLEGRO_MOUSE_STATE mouseState;
    creditsDisplay = al_create_display(displayWith / 2, displayHeight / 2);
    ALLEGRO_BITMAP *unSelectedExit = al_load_bitmap("credits/unSelected.png");
    ALLEGRO_BITMAP *selectedExit = al_load_bitmap("credits/selected.png");

    al_draw_bitmap(unSelectedExit,-1,0,0);
    al_flip_display();

    while(true){
        al_get_mouse_state(&mouseState);
        if(mouseState.x > 180 && mouseState.x < 290
            && mouseState.y > 220 && mouseState.y < 290){

            al_draw_bitmap(selectedExit,0,0,0);
            al_flip_display();

            if(mouseState.buttons & 1){
                al_destroy_display(creditsDisplay);
            }

        }else{
            al_draw_bitmap(unSelectedExit,-1,0,0);
            al_flip_display();
        }
    }

}
