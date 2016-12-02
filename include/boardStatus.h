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
        void print();
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
void boardStatus::print(){
    int i,j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < column; j++){
            this->board[i][j] = board[i][j];
            std::cout<<board[i][j]<<" ";
        }
        std::cout<<std::endl;
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
    int cont=0,score=0;
    //vertical
    for(int i=1;i<=3;i++){
        if(board[x+i][j]!=player && board[x+i][j]!=0 || board[x-1][j]!=player && board[x-1][j]!=0) break;
        if(board[x+i][j]==player && x+i<= rows-1){
            cont++;
        }
    }
    if(cont==3){
        score+=100;
    }
    if(cont==2){
        score+=50;
    }
    cont=0;
    //Horizontal derecha
    for(int i=1;i<=3;i++){
        if(board[x][j+i]!=player && board[x][j+i]!=0) break;
        if(board[x][j+i]==player && j+i<= column-1){
            cont++;
        }
    }
    if(cont==3){
        score+=100;
    }
    if(cont==2){
        score+=50;
    }
    cont=0;
    //Horizontal izquierda
    for(int i=1;i<=3;i++){
        if(board[x][j-i]!=player && board[x][j-i]!=0) break;
        if(board[x][j-i]==player && j-i >=0){
            cont++;
        }
    }
    if(cont==3){
        score+=100;
    }
    if(cont==2){
        score+=50;
    }
    cont=0;
    //Diagonal arriba derecha
    for(int i=1;i<=3;i++){
        if(board[x-i][j+i]!=player && board[x-i][j+i]!=0) break;
        if(board[x-i][j+i]==player && x-i>=0 && j+i<=column-1){
            cont++;
        }
    }
    if(cont==3){
        score+=100;
    }
    if(cont==2){
        score+=50;
    }
    cont=0;
    //Diagonal arriba izquierda
    for(int i=1;i<=3;i++){
        if(board[x-i][j-i]!=player && board[x-i][j-i]!=0) break;
        if(board[x-i][j-i]==player && x-i>=0 && j-i>=0){
            cont++;
        }
    }
    if(cont==3){
        score+=100;
    }
    if(cont==2){
        score+=50;
    }
    cont=0;        cont=0;
    //Diagonal abajo izquierda
    for(int i=1;i<=3;i++){
        if(board[x+i][j-i]!=player && board[x+i][j-i]!=0) break;
        if(board[x+i][j-i]==player && x+i<=rows-1 && j-i>=0){
            cont++;
        }
    }
    if(cont==3){
        score+=100;
    }
    if(cont==2){
        score+=50;
    }
    cont=0;
    //Diagonal abajo derecha
    for(int i=1;i<=3;i++){
        if(board[x+i][j+i]!=player && board[x+i][j+i]!=0) break;
        if(board[x+i][j+i]==player && x+i<=rows-1 && j+i<=column-1){
            cont++;
        }
    }
    if(cont==3){
        score+=100;
    }
    if(cont==2){
        score+=50;
    }
    cont=0;
    print();
    std::cout<< x <<" , "<< j <<" = "<< score <<std::endl;
    std::cin.get();
    return score;
}
#endif
