#ifndef GAME_H
#define GAME_H

#define rows 7
#define column 7
#define widthPixels 630
#define heightPixels 630
#define playerOne 1
#define playerTwo 2
#define endGame 3
#define empty 0

class game{
    public:
    game();
    game(ALLEGRO_DISPLAY* display);
    void startGame();
    ~game();
    int board[rows][column];
    int playerController;
    int actualColumn;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_MOUSE_STATE mouseState;
    void clearBoard();
    void printBoard();
    void updateBoard(int actualColumn, int playerController);
    void getActualColumn();
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
    this->clearBoard();
    playerController = playerOne;
    while(playerController != endGame){

        getActualColumn();
        std::cout << "actual column: "<< actualColumn << std::endl;
        this->updateBoard(actualColumn, playerController);
        this->printBoard();
        if(playerController == playerOne){
            playerController = playerTwo;
        }else{
            playerController = playerOne;
        }
    }

}

void game::clearBoard(){
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < column; j ++){
            board[i][j] = 0;
        }
    }

}

void game::printBoard(){
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < column; j ++){
            std::cout << board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void game::updateBoard(int actualColumn, int playerController){
    int row = 0;
    while(row < rows && board[row + 1][actualColumn] != playerOne && board[row + 1][actualColumn] != playerTwo){
        row ++;
    }

    board[row][actualColumn] = playerController;

}

void game::getActualColumn(){
    ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
    ALLEGRO_EVENT event;
    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        al_get_next_event(eventQueue, &event);
    }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_get_mouse_state(&mouseState);
                if(mouseState.x > 0 && mouseState.x < 90){
                    actualColumn = 0;
                }else if(mouseState.x > 90 && mouseState.x < 180){
                    actualColumn = 1;
                }else if(mouseState.x > 180 && mouseState.x < 270){
                    actualColumn = 2;
                }else if(mouseState.x > 270 && mouseState.x < 360){
                    actualColumn = 3;
                }else if(mouseState.x > 360 && mouseState.x < 450){
                    actualColumn = 4;
                }else if(mouseState.x > 450 && mouseState.x < 540){
                    actualColumn = 5;
                }
                else if(mouseState.x > 540 && mouseState.x < 630){
                    actualColumn = 6;
                }
        }


}

#endif
