#ifndef GAME_H
#define GAME_H

#define rows 7
#define column 7
#define widthPixels 630
#define heightPixels 630
class game{
    public:
    game();
    game(ALLEGRO_DISPLAY* display);
    void startGame();
    ~game();
    int board[rows][column];
    ALLEGRO_DISPLAY* display;
    ALLEGRO_MOUSE_STATE mouseState;
};

game::game(){
    display = NULL;
}

game::game(ALLEGRO_DISPLAY* display){
    this->display = display;
    startGame();
}

void game::startGame(){
    if(! al_resize_display(display, widthPixels, heightPixels)){
        std::cout << "can't resize" << std::endl;
    }
    int actualColumn;
    while(true){
        if(mouseState.buttons & 1){
            std::cout << "this is the actual column"<< actualColumn << std::endl;
            break;
        }
        al_get_mouse_state(&mouseState);
        if(mouseState.x > 0 && mouseState.x < 90){
            actualColumn = 0;
            std::cout << actualColumn << std::endl;
        }else if(mouseState.x > 90 && mouseState.x < 180){
            actualColumn = 1;
            std::cout << actualColumn << std::endl;
        }else if(mouseState.x > 180 && mouseState.x < 270){
            actualColumn = 2;
            std::cout << actualColumn << std::endl;
        }else if(mouseState.x > 270 && mouseState.x < 360){
            actualColumn = 3;
            std::cout << actualColumn << std::endl;
        }else if(mouseState.x > 360 && mouseState.x < 450){
            actualColumn = 4;
            std::cout << actualColumn << std::endl;
        }else if(mouseState.x > 450 && mouseState.x < 540){
            actualColumn = 5;
            std::cout << actualColumn << std::endl;
        }
        else if(mouseState.x > 540 && mouseState.x < 630){
            actualColumn = 6;
            std::cout << actualColumn << std::endl;
        }
    }

}

#endif
