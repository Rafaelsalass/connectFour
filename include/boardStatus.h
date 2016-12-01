#ifndef BOARDSTATUS_H
#define BOARDSTATUS_H
#define rows 7
#define column 7

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
};

boardStatus::boardStatus(){
}

boardStatus::boardStatus(int board[rows][column]){
    int i,j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < column; j++){
            this->board[i][j] = board[i][j];
        }
    }
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
#endif
