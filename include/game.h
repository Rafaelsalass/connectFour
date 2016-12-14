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
    bool checkWin(int newRow, int newColumn, int playerController, boardStatus newBoardStatus);
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
    bool terminalState(boardStatus newBoardState, boardStatus* toPlay, int playerController);
};

game::game(){
    display = NULL;
}

/**
* Loads all the images that the game needs to look properly,
* and calls the funtion starGame()
*/
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

/**
* controls the flow of the game and manage the players turns
* it calls the funtions that generate input to the game
*/
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

/**
* Clears the board by putting 0 in every space of the game board.
*/
void game::clearBoard(){
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < column; j ++){
            board[i][j] = 0;
        }
    }

}

/**
* Prints the board with the std output.
*/
void game::printBoard(boardStatus newBoardStatus){
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < column; j ++){
            std::cout << newBoardStatus.board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

/**
* controls the animation of the circles falling down it updates the board
* with the input of the player or the computer.
*/
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

/**
* Gets the input from the mouse of the human player base on the position of the mouse when
* the user perform a click action.
*/
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

/**
* Base on the current board it looks if there is four circles of the same player
* in a line wich means that one player won the match
*/
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
    auxRow = actualRow;
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
        this->printGraphicalBoard();
        al_show_native_message_box(display, "Exiting game", "WARNING", "diagonal win", NULL,
         ALLEGRO_MESSAGEBOX_WARN);
        return true;
    }

    return false;

}

 
/**
* Base on the parameters it looks if there is four circles of the same player
* in a line wich means that one player won the match
*/

bool game::checkWin(int newRow, int newColumn, int player, boardStatus newBoardStatus){
    int horizontal = 1;
    int vertical = 1;
    int diagonal = 1;
    int auxColumn = newColumn;
    int auxRow = newRow;

    while(newBoardStatus.board[newRow][auxColumn + 1] == player && auxColumn < column -1){
        auxColumn++;
        horizontal++;
    }

    auxColumn = newColumn;

    while(newBoardStatus.board[newRow][auxColumn - 1] == player && auxColumn > 0){
        auxColumn--;
        horizontal++;
    }
    if(horizontal >= 4){
        return true;
    }

    while(newBoardStatus.board[auxRow + 1][newColumn] == player && auxRow < rows - 1){
        auxRow ++;
        vertical ++;
    }

    auxRow = newRow;

    while(newBoardStatus.board[auxRow - 1][newColumn] == player && auxRow > 0){
        auxRow --;
        vertical ++;
    }
    if(vertical >= 4){
        return true;
    }

    auxColumn = newColumn;
    auxRow = newRow;

    while(auxColumn < column - 1 && auxRow < rows - 1 && newBoardStatus.board[auxRow + 1][auxColumn + 1] == player){
        auxColumn++;
        auxRow++;
        diagonal++;
    }

    auxColumn = newColumn;
    auxRow = newRow;

    while(auxColumn > 0 && auxRow > 0 && newBoardStatus.board[auxRow - 1][auxColumn - 1] == player){
        auxColumn--;
        auxRow--;
        diagonal++;
    }

    if(diagonal >= 4){
        return true;
    }

    diagonal = 1;
    auxColumn = newColumn;
    auxRow = newRow;
    while(auxColumn < column - 1 && auxRow >0 && newBoardStatus.board[auxRow - 1][auxColumn + 1] == player){
        auxColumn++;
        auxRow--;
        diagonal++;
    }

    auxColumn = newColumn;
    auxRow = newRow;

    while(auxColumn > 0 && auxRow < rows - 1 && newBoardStatus.board[auxRow + 1][auxColumn - 1] == player){
        auxColumn--;
        auxRow++;
        diagonal++;
    }

    if(diagonal >= 4){
        return true;
    }

    return false;
}

/**
* Displays the instructions an after a moment displays the graphical 
* layout of the game.
*/
void game::changeBackground(){
    al_rest(.15);
    al_draw_bitmap(instructions, -85, 0, 0);
    al_flip_display();
    al_rest(5);
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

/**
* repaint the grphical interface of the game base on the
* current state of it.
*/
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

/**
* controls the input from the computer AI to the startGame() funtion
* displays with the standart output the existence of a terminal situation
* in the game or the use of the alpha beta algorythm.
*/
int game::computerMove(){
    std::vector<boardStatus> moves;
    boardStatus toPlay;
    toPlay.playedColumn = -1;
    int score = 0;
    boardStatus newBoardStatus;
    newBoardStatus.setBoard(board);

    if(this->terminalState(newBoardStatus, &toPlay, playerTwo)){
        std::cout << "Terminal move for computer" << std::endl;
        std::cout << "toPlay playedColumn: "<< toPlay.playedColumn << std::endl;
        std::cout << std::endl << std::endl;
        return toPlay.playedColumn;
    }else if(this->terminalState(newBoardStatus, &toPlay, playerOne)){
        std::cout << "Terminal move for human" << std::endl;
        std::cout << "toPlay playedColumn: "<< toPlay.playedColumn << std::endl;
        std::cout << std::endl << std::endl;
        return toPlay.playedColumn;
    }else{
        std::cout << "aplying alphaBeta" << std::endl;
        score = this->alphaBeta(newBoardStatus, lessInfinity, plusInfinity, true, 4, &toPlay);
        std::cout << score << std::endl;
        std::cout << "toPlay playedColumn: "<< toPlay.playedColumn << std::endl;
        std::cout << std::endl << std::endl;
        return toPlay.playedColumn;
    }
}

/**
* return a std::vector with all the posible moves where the given
* player can place a circle.
*/
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
            aux.playedRow = j;
            moves.push_back(aux);
        }
        aux = newBoardStatus;
        j = rows - 1;
    }

    return moves;

}

/**
* returns the best possible game move for the computer.
*/
int game::alphaBeta(boardStatus newBoardStatus, int alpha, int beta, bool maxPlayer, int deep, boardStatus* toPlay){
    std::vector<boardStatus> newMoves;
    newMoves = this->possibleMoves(newBoardStatus, playerOne);
    int bestValue;
    int childValue;

    if(newMoves.size() == 0 || deep <= 0){
        bestValue = newBoardStatus.score;

    }else {
        if(maxPlayer){
            newMoves.clear();
            newMoves = this->possibleMoves(newBoardStatus, playerOne);
            bestValue = alpha;
            for (int i = 0; i < newMoves.size(); i ++){
                if(childValue > bestValue){
                    bestValue = childValue;
                    toPlay->playedColumn = newMoves[i].playedColumn;
                }
                if(beta <= bestValue){
                    break;
                }
            }
        }else{
            newMoves.clear();
            newMoves = this->possibleMoves(newBoardStatus, playerTwo);
            bestValue = beta;
            for (int j = 0; j < newMoves.size(); j++){
                if(childValue < bestValue){
                    bestValue = childValue;
                }
                if(bestValue <= alpha){
                    break;
                }
            }
        }
    }
    return bestValue;
}

/**
* look for a terminal state when a player have
* a possible move that can lead to the end of the match.
*/
bool game::terminalState(boardStatus newBoardStatus, boardStatus* toplay, int player){
    std::vector<boardStatus> moves;
    moves = this->possibleMoves(newBoardStatus, playerController);

    for(int x = 0; x < moves.size(); x++){
        if(this->checkWin(moves[x].playedRow, moves[x].playedColumn, player, moves[x])){
            toplay->playedColumn = moves[x].playedColumn;
            return true;
        }
    }

    return false;

}
#endif
