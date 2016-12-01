#ifndef BOARDSTATUS_H
#define BOARDSTATUS_H
#define rows 7
#define column 7
#define playerOne 1
#define playerTwo 2

class boardStatus
{
    public:
        boardStatus();
        boardStatus(int board[rows][column]);
        virtual ~boardStatus();
        int board[rows][column];
        int score;
        int playedColumn;
        void setBoard(int board[rows][column]);
        void calculatedScore();
        int evaluatePlayer(int x, int y, int player);
        int checkSurroundings(int x, int y, int player);
};

boardStatus::boardStatus(){
}

boardStatus::boardStatus(int board[rows][column]){
    this->setBoard(board);
}

boardStatus::~boardStatus(){
}

void boardStatus::setBoard(int board[rows][column]){
    int i,j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < column; j++){
            this->board[i][j] = board[i][j];
        }
    }
}


void boardStatus::calculatedScore(){
    int i,j, winPossibility, losePossibility, auxScore;
    winPossibility = losePossibility = 0;
    for(i = 0; i < rows; i++){
        for(j = 0; j < column; j++){
            if(board[i][j] == 0){
                continue;
            }else if(board[i][j] == playerOne){
                losePossibility += checkSurroundings(i, j, playerOne);
            }else if(board[i][j] == playerTwo){
                winPossibility += checkSurroundings(i, j, playerTwo);
            }
        }
    }
}

int boardStatus::checkSurroundings(int x, int j, int player){

}
#endif
