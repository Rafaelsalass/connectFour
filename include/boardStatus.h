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
        int playedRow;
        void setBoard(int board[rows][column]);
        void calculatedScore();
        void print();
        int evaluatePlayer(int x, int y, int player);
        int checkSurroundings(int x, int y, int player);
};

boardStatus::boardStatus(){
}

/**
* Overloaded constructor.
*/
boardStatus::boardStatus(int board[rows][column]){
    this->setBoard(board);
    this->score = 0;
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

/**
* prints the current status of the board in the object.
*/
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

/**
* Look for playerOne and playerTwo int the board and
* adds to the socore the return value of th funtion chechSurroundings
*/
void boardStatus::calculatedScore(){
    int i,j, winPossibility, losePossibility;
    winPossibility = losePossibility = 0;
    for(i = 0; i < rows; i++){
        for(j = 0; j < column; j++){

	    if(board[i][j] == playerOne){
                losePossibility += checkSurroundings(i, j, playerOne);
            }else if(board[i][j] == playerTwo){
                winPossibility += checkSurroundings(i, j, playerTwo);
            }
        }
    }
    this->score = losePossibility*2 - winPossibility;

}


/**
* Looks for the possible moves that can lead to a win situation and generates and score out
* of that possible moves
*/
int boardStatus::checkSurroundings(int x, int j, int player){
    int cont=0,score=0,b=0;
    //vertical abajo
    for(int i=1;i<=3;i++){
        if(x+i<= rows-1){
            if(board[x-1][j]!=player && board[x-1][j]!=0){
                b=1;
                break;
            }
            if(board[x+i][j]!=player && board[x+i][j]!=0 ){
                b=1;
                break;
            }
            if(board[x+i][j]==player){
                cont++;
            }
        }
    }
    if(cont==3 && b==0){
       // std::cout<<"Vertical abajo Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Vertical abajo Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=250;
    }
    cont=0;
    b=0;
    //vertical arriba
    for(int i=1;i<=3;i++){
        if(x-i>= 0){
            if(board[x-i][j]!=player && board[x-i][j]!=0 ){
                b=1;
                break;
            }
            if(board[x-i][j]==player){
                cont++;
            }

        }
    }
    if(cont==3 && b==0){
        //std::cout<<"Vertical arriba Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Vertical arriba Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=250;
    }
    cont=0;
    b=0;
    //Horizontal derecha
    for(int i=1;i<=3;i++){
        if(board[x][j+i]!=player && board[x][j+i]!=0 && j+i<= column-1){
            b=1;
            break;
        }
        if(board[x][j+i]==player ){
            cont++;
        }
    }
    if(cont==3 && b==0){
        //std::cout<<"Horizontal derecha Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Horizontal derecha Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=250;
    }
    cont=0;
    b=0;
    //Horizontal izquierda
    for(int i=1;i<=3;i++){
        if(board[x][j-i]!=player && board[x][j-i]!=0 && j-i >=0){
            b=1;
            break;
        }
        if(board[x][j-i]==player ){
            cont++;
        }
    }
    if(cont==3 && b==0){
        //std::cout<<"Horizontal izquierda Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Horizontal izquierda Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=250;
    }
    cont=0;
    b=0;
    //Diagonal arriba derecha
    for(int i=1;i<=3;i++){
        if(board[x-i][j+i]!=player && board[x-i][j+i]!=0 && x-i>=0 && j+i<=column-1){
            b=1;
            break;
        }
        if(board[x-i][j+i]==player ){
            cont++;
        }
    }
    if(cont==3 && b==0){
        //std::cout<<"Diagonal arriba derecha Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Diagonal arriba derecha Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=350;
    }
    cont=0;
    b=0;
    //Diagonal arriba izquierda
    for(int i=1;i<=3;i++){
        if(board[x-i][j-i]!=player && board[x-i][j-i]!=0&& x-i>=0 && j-i>=0){
            b=1;
            break;
        }
        if(board[x-i][j-i]==player ){
            cont++;
        }
    }
    if(cont==3 && b==0){
        //std::cout<<"Diagonal arriba izquierda Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Diagonal arriba izquierda Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=350;
    }
    cont=0;
    b=0;       cont=0;
    //Diagonal abajo izquierda
    for(int i=1;i<=3;i++){
        if(board[x+i][j-i]!=player && board[x+i][j-i]!=0 && x+i<=rows-1 && j-i>=0){
            b=1;
            break;
        }
        if(board[x+i][j-i]==player ){
            cont++;
        }
    }
    if(cont==3 && b==0){
        //std::cout<<"Diagonal abajo izquierda Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Diagonal abajo izquierda Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=350;
    }
    cont=0;
    b=0;
    //Diagonal abajo derecha
    for(int i=1;i<=3;i++){
        if(board[x+i][j+i]!=player && board[x+i][j+i]!=0 && x+i<=rows-1 && j+i<=column-1){
            b=1; break;
        }
        if(board[x+i][j+i]==player ){
            cont++;
        }
    }
    if(cont==3 && b==0){
        //std::cout<<"Diagonal abajo derecha Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=500;
    }
    if(cont==2 && b==0){
        //std::cout<<"Diagonal abajo derecha Score: "<<score<<" cont : "<<cont<<std::endl;
        score+=350;
    }
    cont=0;
    b=0;
    //print();
    //std::cout<< x <<" , "<< j <<" = "<< score <<std::endl;
  //  std::cin.get();
    return score;
}
#endif
