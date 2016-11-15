#include <stdio.h>
#include <allegro.h>
#include <allegro_native_dialog.h>
#include <allegro_image.h>
#include <iostream>
#include "include/menu.h"

using namespace std;

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

    new menu();
    return 0;
}

