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
#define pegWidth 90
#define pegHeight 90

class game{
    public:
    game();
    game(ALLEGRO_DISPLAY* display);
    void startGame();
    ~game();
    int board[rows][column];
    int playerController;
    int actualColumn;
    int actualRow;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_MOUSE_STATE mouseState;
    void clearBoard();
    void printBoard();
    void updateBoard(int playerController);
    void getActualColumn();
    bool checkWin();
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* playerOnePeg;
    ALLEGRO_BITMAP* playerTwoPeg;
    ALLEGRO_BITMAP* emptySpace;
    void printGraphicalBoard();
    void changeBackground();
    bool isDraw();
};

game::game(){
    display = NULL;
}

game::game(ALLEGRO_DISPLAY* display){
    background = al_load_bitmap("gameGraphics/background.png");
    playerOnePeg = al_load_bitmap("gameGraphics/playerOne.png");
    playerTwoPeg = al_load_bitmap("gameGraphics/playerTwo.png");
    emptySpace = al_load_bitmap("gameGraphics/empy.png");
    this->display = display;
    startGame();
}

void game::startGame(){
    if(! al_resize_display(display, widthPixels, heightPixels)){
        std::cout << "can't resize" << std::endl;
    }

    this->changeBackground();

    int actualRow;
    this->clearBoard();
    playerController = playerOne;
    while(playerController != endGame){

        getActualColumn();
        std::cout << "actual column: "<< actualColumn << std::endl;
        this->updateBoard(playerController);
        this->printBoard();
        if(this->checkWin()){
            break;
        }
        if(this->isDraw()){
            break;
        }
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

void game::updateBoard(int playerController){
    int row = 1;
    while(row < rows - 1 && board[row + 1][actualColumn] != playerOne && board[row + 1][actualColumn] != playerTwo){
        board[row - 1][actualColumn] = empty;
        board[row][actualColumn] = playerController;
        this->printGraphicalBoard();
        al_rest(.15);
        row ++;
    }
    actualRow = row;
}

void game::getActualColumn(){
    ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
    ALLEGRO_EVENT event;
    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        al_get_next_event(eventQueue, &event);
    }
    al_destroy_event_queue(eventQueue);

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
                }else if(mouseState.x > 540 && mouseState.x < 630){
                    actualColumn = 6;
                }
        }


}

bool game::checkWin(){
    int horizontal = 1;
    int vertical = 1;
    int diagonal = 1;
    int auxColumn = actualColumn;
    int auxRow = actualRow;

    while(board[actualRow][auxColumn + 1] == playerController && auxColumn < column -1){
        auxColumn++;
        horizontal++;
    }
    auxColumn = actualColumn;
    while(board[actualRow][auxColumn - 1] == playerController && auxColumn > 0){
        auxColumn--;
        horizontal++;
    }
    if(horizontal >= 4){
        al_show_native_message_box(display, "Exiting game", "WARNING", "pleyer won", NULL,
         ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);
        return true;
    }

    while(board[auxRow + 1][actualColumn] == playerController && auxRow < rows - 1){
        auxRow ++;
        vertical ++;
    }

    auxRow = auxColumn;

    while(board[auxRow - 1][actualColumn] == playerController && auxRow > 0){
        auxRow --;
        vertical ++;
    }
    if(vertical >= 4){
        al_show_native_message_box(display, "Exiting game", "WARNING", "player won", NULL,
         ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);
        return true;
    }

    auxColumn = actualColumn;
    auxRow = actualRow;

    while(auxColumn < column - 1 && auxRow < rows - 1 && board[auxRow + 1][auxColumn + 1] == playerController){
        auxColumn++;
        auxRow++;
        diagonal++;
    }

    auxColumn = actualColumn;
    auxRow = actualRow;

    while(auxColumn > 0 && auxRow > 0 && board[auxRow - 1][auxColumn - 1] == playerController){
        auxColumn--;
        auxRow--;
        diagonal++;
    }

    if(diagonal >= 4){
        al_show_native_message_box(display, "Exiting game", "WARNING", "player won", NULL,
         ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);
        return true;
    }

    diagonal = 1;
    auxColumn = actualColumn;
    auxRow = auxRow;
    while(auxColumn < column - 1 && auxRow >0 && board[auxRow - 1][auxColumn + 1] == playerController){
        auxColumn++;
        auxRow--;
        diagonal++;
    }

    auxColumn = actualColumn;
    auxRow = actualRow;

    while(auxColumn > 0 && auxRow < rows - 1 && board[auxRow + 1][auxColumn - 1] == playerController){
        auxColumn--;
        auxRow++;
        diagonal++;
    }

    if(diagonal >= 4){
        al_show_native_message_box(display, "Exiting game", "WARNING", "player won", NULL,
         ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);
        return true;
    }

    return false;

}

void game::changeBackground(){
    al_draw_bitmap(background,0,0,0);
    al_flip_display();
}

void game::printGraphicalBoard(){
    int x,y;
    for (x = 0; x < rows; x++){
        for (y = 1; y < column; y++){

            if(board[y][x] == playerOne){
                al_draw_bitmap_region(playerOnePeg, 0, 0, pegWidth, pegHeight, x * pegWidth, y * pegHeight, NULL);
            }else if(board[y][x] == playerTwo){
                al_draw_bitmap_region(playerTwoPeg, 0, 0, pegWidth, pegHeight, x * pegWidth, y * pegHeight, NULL);
            }else{
                al_draw_bitmap_region(emptySpace, 0, 0, pegWidth, pegHeight, x * pegWidth, y * pegHeight, NULL);
            }

        }

    }
    al_flip_display();
}

bool game::isDraw(){
    int x,y;
    for(x = 1; x < rows; x++){
        for(y = 0; y < column; y++){
            if(board[x][y] == empty){
                return false;
            }
        }
    }
    al_show_native_message_box(display, "WARNING", "DRAW", "No one wins this game", NULL, ALLEGRO_MESSAGEBOX_WARN);
    return true;
}

#endif
