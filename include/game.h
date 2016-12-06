#ifndef GAME_H
#define GAME_H

#define rows 7
#define column 7
#define widthPixels 1098
#define heightPixels 630
#define playerOne 1
#define playerTwo 2
#define endGame 3
#define pegWidth 90
#define pegHeight 90
#define plusInfinity 999999
#define lessInfinity -999999

#include <time.h>
#include <vector>
#include "boardStatus.h"

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
    void printBoard(boardStatus newBoardStatus);
    void updateBoard(int playerController);
    bool getActualColumn();
    bool checkWin();
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* playerOnePeg;
    ALLEGRO_BITMAP* playerTwoPeg;
    ALLEGRO_BITMAP* emptySpace;
    ALLEGRO_BITMAP* playerTurnSelected;
    ALLEGRO_BITMAP* playerTurnUnselected;
    ALLEGRO_BITMAP* computerTurnSelected;
    ALLEGRO_BITMAP* computerTurnUnselected;
    ALLEGRO_BITMAP* instructions;
    void printGraphicalBoard();
    void changeBackground();
    int computerMove();
    bool isDraw();
    bool invalidInput;
    std::vector<boardStatus> possibleMoves(boardStatus newBoardStatus, int playerController);
    int alphaBeta(boardStatus newBoardStatus, int alpha, int beta, bool player, int deep, boardStatus* toPlay);
};

game::game(){
    display = NULL;
}

game::game(ALLEGRO_DISPLAY* display){
    srand( time(0) );
    background = al_load_bitmap("gameGraphics/background.png");
    playerOnePeg = al_load_bitmap("gameGraphics/playerOne.png");
    playerTwoPeg = al_load_bitmap("gameGraphics/playerTwo.png");
    emptySpace = al_load_bitmap("gameGraphics/empy.png");
    computerTurnSelected = al_load_bitmap("gameGraphics/computerTurnSelected.png");
    computerTurnUnselected = al_load_bitmap("gameGraphics/computerTurnUnselected.png");
    playerTurnSelected = al_load_bitmap("gameGraphics/playerTurnSelected.png");
    playerTurnUnselected = al_load_bitmap("gameGraphics/playerTurnUnselected.png");
    instructions = al_load_bitmap("gameGraphics/instructions.png");
    invalidInput = false;
    this->display = display;
    startGame();
}

void game::startGame(){
    this->changeBackground();
    this->clearBoard();

    playerController = rand() % 1 + 1;

    while(playerController < endGame){

        if(playerController == playerOne){

            if(this->getActualColumn()){
                this->updateBoard(playerController);
            }

        }else if(playerController == playerTwo){
            actualColumn = this->computerMove();
            this->updateBoard(playerController);
        }
        std::cout << "actual column: "<< actualColumn << std::endl;
        if(!invalidInput){
            if(this->checkWin()){
                break;
            }
            if(this->isDraw()){
                break;
            }
            (playerController == playerOne)? playerController = playerTwo : playerController = playerOne;
        }
        invalidInput = false;

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

void game::printBoard(boardStatus newBoardStatus){
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < column; j ++){
            std::cout << newBoardStatus.board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void game::updateBoard(int playerController){
    int row = 1;
    if(board[row][actualColumn] != 0){
        al_show_native_message_box(display, "Invalid input", "WARNING", "column is already full", NULL,
         ALLEGRO_MESSAGEBOX_WARN);
         invalidInput = true;
    }
    while(row < rows && board[row][actualColumn] == 0){
        board[row - 1][actualColumn] = 0;
        board[row][actualColumn] = playerController;
        this->printGraphicalBoard();
        al_rest(.05);
        row ++;
    }
    actualRow = --row;
    //std::cout << "[" << row << "," << actualColumn << "]" << std::endl;
}

bool game::getActualColumn(){
    ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
    ALLEGRO_EVENT event;
    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        al_get_next_event(eventQueue, &event);
    }
    al_destroy_event_queue(eventQueue);

                al_get_mouse_state(&mouseState);
                if(mouseState.x > 0 && mouseState.x < 90){
                    actualColumn = 0;
                }else if(mouseState.x > 90 && mouseState.x < 180){
                    actualColumn = 1;
                    return true;
                }else if(mouseState.x > 180 && mouseState.x < 270){
                    actualColumn = 2;
                    return true;
                }else if(mouseState.x > 270 && mouseState.x < 360){
                    actualColumn = 3;
                    return true;
                }else if(mouseState.x > 360 && mouseState.x < 450){
                    actualColumn = 4;
                    return true;
                }else if(mouseState.x > 450 && mouseState.x < 540){
                    actualColumn = 5;
                    return true;
                }else if(mouseState.x > 540 && mouseState.x < 630){
                    actualColumn = 6;
                    return true;
                }else if(mouseState.x > 630){
                    if(mouseState.x > 780 && mouseState.x < 935 && mouseState.y > 355 && mouseState.y < 400){
                        al_show_native_message_box(display, "Exiting game", "WARNING",
                        "exiting current game", NULL, ALLEGRO_MESSAGEBOX_WARN);
                        invalidInput = true;
                        playerController = endGame;
                        return false;
                    }
                    al_show_native_message_box(display, "Invalid input", "WARNING", "click on the board", NULL,
                     ALLEGRO_MESSAGEBOX_WARN);
                    invalidInput = true;
                    return false;
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
        this->printGraphicalBoard();
        al_show_native_message_box(display, "Exiting game", "WARNING", "horizontal win", NULL,
         ALLEGRO_MESSAGEBOX_WARN);
        return true;
    }

    while(board[auxRow + 1][actualColumn] == playerController && auxRow < rows - 1){
        auxRow ++;
        vertical ++;
    }

    auxRow = actualRow;

    while(board[auxRow - 1][actualColumn] == playerController && auxRow > 0){
        auxRow --;
        vertical ++;
    }
    if(vertical >= 4){
        this->printGraphicalBoard();
        al_show_native_message_box(display, "Exiting game", "WARNING", "vertical win", NULL,
         ALLEGRO_MESSAGEBOX_WARN);
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
        this->printGraphicalBoard();
        al_show_native_message_box(display, "Exiting game", "WARNING", "diagonal win", NULL,
         ALLEGRO_MESSAGEBOX_WARN);
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
    diagonal = 1;

    while(auxColumn > 0 && auxRow < rows - 1 && board[auxRow + 1][auxColumn - 1] == playerController){
        auxColumn--;
        auxRow++;
        diagonal++;
    }

    if(diagonal >= 4){
        this->printGraphicalBoard();
        al_show_native_message_box(display, "Exiting game", "WARNING", "diagonal win", NULL,
         ALLEGRO_MESSAGEBOX_WARN);
        return true;
    }

    return false;

}

void game::changeBackground(){
    al_rest(.15);
    al_draw_bitmap(instructions, -85, 0, 0);
    al_flip_display();
    al_rest(1);
    if(! al_resize_display(display, widthPixels, heightPixels)){
        std::cout << "can't resize" << std::endl;
    }
    al_rest(.01);
    al_draw_bitmap(background,0,0,0);
    if(playerController == playerOne){
        al_draw_bitmap(computerTurnUnselected,631,0,0);
    }else{
        al_draw_bitmap(playerTurnUnselected,631,0,0);
    }
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
    if(playerController == playerOne){
        al_draw_bitmap(computerTurnUnselected,631,2,0);
    }else{
        al_draw_bitmap(playerTurnUnselected,631,0,0);
    }
    al_flip_display();
}

bool game::isDraw(){
    int x,y;
    for(x = 1; x < rows; x++){
        for(y = 0; y < column; y++){
            if(board[x][y] == 0){
                return false;
            }
        }
    }
    al_show_native_message_box(display, "WARNING", "DRAW", "No one wins this game", NULL, ALLEGRO_MESSAGEBOX_WARN);
    return true;
}

int game::computerMove(){
    std::vector<boardStatus> moves;
    boardStatus toPlay;
    toPlay.playedColumn = -1;
    int score = 0;
    boardStatus newBoardStatus;
    system("clear");
    newBoardStatus.setBoard(board);
    moves = this->possibleMoves(newBoardStatus, playerTwo);

    score = this->alphaBeta(newBoardStatus, lessInfinity, plusInfinity, true, 4, &toPlay);
    std::cout << score << std::endl;
    std::cout << "tiPlay playedColumn: "<< toPlay.playedColumn << std::endl;
    return toPlay.playedColumn;
}


std::vector<boardStatus> game::possibleMoves(boardStatus newBoardStatus, int player){
    std::vector<boardStatus> moves;
    boardStatus aux;
    aux = newBoardStatus;
    int j = rows - 1;
    for(int i = 0; i < column; i++){
        while(aux.board[j][i] != 0 && j > 0){
            j--;
        }
        if(j != 0){
            aux.board[j][i] = player;
            aux.playedColumn = i;
            moves.push_back(aux);
        }
        aux = newBoardStatus;
        j = rows - 1;
    }

    return moves;

}

int game::alphaBeta(boardStatus newBoardStatus, int alpha, int beta, bool maxPlayer, int deep, boardStatus* toPlay){
    std::vector<boardStatus> newMoves;
    newMoves = this->possibleMoves(newBoardStatus, playerOne);
    int bestValue;
    int childValue;

    if(newMoves.size() == 0 || deep <= 0){
        //std::cout << "newMoves.size() :" << newMoves.size()<<" alpha: "<<alpha<<" beta: "<<beta<<" bestValue: "<<bestValue<<" deep: "<<deep<<std::endl;
        //std::cin.get();
        newBoardStatus.calculatedScore();
        bestValue = newBoardStatus.score;

    }else {
        //std::cout << "maxPlayer: " << maxPlayer<<" deep: "<<deep<<std::endl;
        //std::cin.get();
        if(maxPlayer){
            newMoves.clear();
            newMoves = this->possibleMoves(newBoardStatus, playerOne);
            bestValue = alpha;
            for (int i = 0; i < newMoves.size(); i ++){
                //std::cout << "i: " << i<<" alpha: "<<alpha<<" beta: "<<beta<<" bestValue: "<<bestValue<<" deep: "<<deep<<" maxPlayer:"<<maxPlayer<<std::endl;
                //newMoves[i].print();
                //std::cin.get();
                childValue = alphaBeta(newMoves[i], bestValue, beta, false, --deep, toPlay);
                //std::cout << "childValue: " << childValue<<" bestValue-alpha: "<<bestValue<<std::endl;
                if(childValue > bestValue){
                    //std::cout << "ENTRO"<<std::endl;
                    bestValue = childValue;
                    toPlay->playedColumn = newMoves[i].playedColumn;
                    //std::cout << "childValue: " << childValue<<" bestValue-alpha: "<<bestValue<<std::endl;
                }
                if(beta <= bestValue){
                    //std::cout << "bestValue: "<<bestValue<<" beta: "<<beta<<std::endl;
                    break;
                }
            }
        }else{
            newMoves.clear();
            newMoves = this->possibleMoves(newBoardStatus, playerTwo);
            bestValue = beta;
            for (int j = 0; j < newMoves.size(); j++){
                //std::cout << "j: " << j<<" alpha: "<<alpha<<" beta: "<<beta<<" bestValue: "<<bestValue<<" deep: "<<deep<<" maxPlayer:"<<maxPlayer<<std::endl;
                //newMoves[j].print();
                //std::cin.get();
                childValue = alphaBeta(newMoves[j], alpha, bestValue, true, --deep, toPlay);
                //std::cout << "childValue: " << childValue<<" bestValue-beta: "<<bestValue<<std::endl;
                if(childValue < bestValue){
                    //std::cout << "ENTRO"<<std::endl;
                    bestValue = childValue;

                    //std::cout << "childValue: " << childValue<<" bestValue-beta: "<<bestValue<<std::endl;
                }
                if(bestValue <= alpha){
                    //std::cout << "bestValue: "<<bestValue<<" alpha: "<<alpha<<std::endl;
                    break;
                }
            }
        }
    }
    return bestValue;
}
#endif
