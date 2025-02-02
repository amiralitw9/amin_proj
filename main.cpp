#include <iostream>
using namespace std;

const int SIZE = 9;
bool checkRow(int row[SIZE], int num) {
    for (int i = 0; i < SIZE; ++i) {
        if (row[i] == num) {
            return true;
        }
    }
    return false;
}
void getRowColumnSquare(int sudoku[5][SIZE][SIZE], int sudokuIndex, int row, int col, int returnedRow[SIZE], int returnedCol[SIZE], int returnedSquare[3][3]) {
    for (int i = 0; i < SIZE; ++i) {
        returnedRow[i] = sudoku[sudokuIndex][row][i];
    }

    for (int i = 0; i < SIZE; ++i) {
        returnedCol[i] = sudoku[sudokuIndex][i][col];
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            returnedSquare[i][j] = sudoku[sudokuIndex][startRow + i][startCol + j];
        }
    }
}

bool checkColumn(int col[SIZE], int num) {
    for (int i = 0; i < SIZE; ++i) {
        if (col[i] == num) {
            return true;
        }
    }
    return false;
}

bool checkSquare(int square[3][3], int num) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (square[i][j] == num) {
                return true;
            }
        }
    }
    return false;
}


void initializeSudoku(int sudoku[5][SIZE][SIZE]) {
    for(int k = 0 ; k< 5 ; k++){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                sudoku[k][i][j] = 0;
            }
        }
    }
    /////////////////////////
    sudoku[0][0][1] = 3;
    sudoku[0][0][2] = 1;
    sudoku[0][0][8] = 4;
    sudoku[0][1][1] = 2;
    sudoku[0][1][3] = 5;
    sudoku[0][1][7] = 3;
    sudoku[0][2][2] = 5;
    sudoku[0][2][6] = 1;
    sudoku[0][2][7] = 8;
    sudoku[0][3][3] = 2;
    sudoku[0][3][6] = 3;
    sudoku[0][3][7] = 7;
    sudoku[0][4][0] = 8;
    sudoku[0][4][4] = 6;
    sudoku[0][4][5] = 4;
    sudoku[0][4][6] = 2;
    sudoku[0][5][4] = 1;
    sudoku[0][6][4] = 5;
    sudoku[0][6][7] = 2;
    sudoku[0][6][8] = 9;
    sudoku[0][7][0] = 6;
    sudoku[0][7][1] = 9;
    sudoku[0][8][0] = 1;
    sudoku[0][8][3] = 9;
    sudoku[0][8][4] = 7;
    sudoku[0][8][5] = 2;
    sudoku[0][8][8] = 3;

    ////////////////////////////////////
    sudoku[1][0][5] = 3;
    sudoku[1][0][7] = 1;
    sudoku[1][0][8] = 7;
    sudoku[1][1][0] = 1;
    sudoku[1][1][2] = 7;
    sudoku[1][1][3] = 4;
    sudoku[1][1][6] = 6;
    sudoku[1][2][6] = 4;
    sudoku[1][2][8] = 5;
    sudoku[1][3][2] = 3;
    sudoku[1][3][3] = 8;
    sudoku[1][3][5] = 1;
    sudoku[1][3][6] = 5;
    sudoku[1][4][4] = 5;
    sudoku[1][4][6] = 9;
    sudoku[1][5][0] = 4;
    sudoku[1][5][2] = 6;
    sudoku[1][6][1] = 8;
    sudoku[1][6][4] = 6;
    sudoku[1][6][8] = 4;
    sudoku[1][7][0] = 6;
    sudoku[1][7][3] = 7;
    sudoku[1][7][6] = 1;
    sudoku[1][8][0] = 2;
    sudoku[1][8][5] = 9;
    ///////////////////////////////
    sudoku[2][1][4] = 4;
    sudoku[2][2][3] = 1;
    sudoku[2][3][3] = 4;
    sudoku[2][5][4] = 5;
    sudoku[2][6][3] = 2;
    sudoku[2][6][4] = 1;
    sudoku[2][8][5] = 9;
    sudoku[2][3][0] = 7;
    sudoku[2][3][7] = 9;
    sudoku[2][4][0] = 3;
    sudoku[2][4][1] = 6;
    sudoku[2][4][2] = 9;
    sudoku[2][5][0] = 2;
    //////////////////////////////
    sudoku[3][0][0] = 4;
    sudoku[3][0][2] = 6;
    sudoku[3][0][4] = 2;
    sudoku[3][0][5] = 8;
    sudoku[3][0][7] = 7;
    sudoku[3][1][0] = 8;
    sudoku[3][1][3] = 7;
    sudoku[3][2][7] = 8;
    sudoku[3][3][3] = 9;
    sudoku[3][3][8] = 3;
    sudoku[3][4][0] = 5;
    sudoku[3][4][1] = 9;
    sudoku[3][4][5] = 1;
    sudoku[3][4][6] = 8;
    sudoku[3][4][8] = 7;
    sudoku[3][5][0] = 7;
    sudoku[3][5][1] = 3;
    sudoku[3][5][6] = 5;
    sudoku[3][6][2] = 7;
    sudoku[3][6][5] = 4;
    sudoku[3][6][6] = 3;
    sudoku[3][7][2] = 2;
    sudoku[3][7][4] = 1;
    sudoku[3][7][7] = 4;
    sudoku[3][8][0] = 9;
    sudoku[3][8][6] = 2;
    sudoku[3][8][7] = 6;
    //////////////////////////////
    sudoku[4][0][2] = 8;
    sudoku[4][1][1] = 5;
    sudoku[4][1][7] = 4;
    sudoku[4][2][0] = 1;
    sudoku[4][2][2] = 3;
    sudoku[4][2][5] = 4;
    sudoku[4][2][6] = 7;
    sudoku[4][3][0] = 6;
    sudoku[4][3][1] = 1;
    sudoku[4][3][4] = 8;
    sudoku[4][4][0] = 7;
    sudoku[4][4][6] = 3;
    sudoku[4][4][7] = 1;
    sudoku[4][5][4] = 5;
    sudoku[4][5][7] = 2;
    sudoku[4][5][8] = 8;
    sudoku[4][6][1] = 7;
    sudoku[4][6][2] = 4;
    sudoku[4][6][7] = 3;
    sudoku[4][7][0] = 8;
    sudoku[4][7][1] = 3;
    sudoku[4][7][4] = 6;
    sudoku[4][7][6] = 4;
    sudoku[4][8][4] = 7;
    sudoku[4][8][8] = 2;





}
void printSoudoko(int sudoku[5][SIZE][SIZE]){
    for(int i = 0 ; i<6 ; i++){
        for (int j = 0 ; j< 9 ; j++){
            cout<<sudoku[0][i][j]<<"  " ;
           if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout<<"\t"<<"\t";
        for (int j = 0 ; j< 9 ; j++){
            cout<<sudoku[1][i][j]<<"  " ;
            if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout<<"\n";
        if(i%3 == 2 ){
            cout << "---------+----------+-----------" <<"\t"<<"\t"<<"---------+----------+-----------"<< endl;
        }
    }
    for (int i  = 6 ; i<9 ; i++){
        for (int j = 0 ; j< 9 ; j++){
            cout<<sudoku[0][i][j]<<"  " ;
            if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout<<"   ";
        for(int j = 3 ; j<6 ; j++){
            cout<<sudoku[2][i-6][j]<<"  ";
        }
        cout<<"   ";
        for (int j = 0 ; j< 9 ; j++){
            cout<<sudoku[1][i][j]<<"  " ;
            if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout<<"\n";
        if(i%3 == 2 ){
            cout << "---------+----------+-----------" <<"\t"<<"\t"<<"---------+----------+-----------"<< endl;
        }

    }
    for(int i = 3 ; i<6 ; i++){
        cout<<"\t"<<"\t"<<"      ";
        for (int j = 0 ; j< 9 ; j++){
            cout<<sudoku[2][i][j]<<"  " ;
            if (j % 3 == 2 && j != 5) {
                cout << "|    ";
            }
            if(j==5)
                cout<<"   ";

        }
        cout<<"\n";
        if(i%3 == 2 ){
            cout << "---------+----------+-----------" <<"\t"<<"\t"<<"---------+----------+-----------"<< endl;
        }
    }
    for(int i = 0 ; i <3 ; i++){
        for (int j = 0 ; j< 9 ; j++){
            cout<<sudoku[3][i][j]<<"  " ;
            if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout<<"   ";
        for(int j = 3 ; j<6 ; j++){
            cout<<sudoku[2][i+6][j]<<"  ";
        }
        cout<<"   ";
        for (int j = 0 ; j< 9 ; j++){
            cout<<sudoku[4][i][j]<<"  " ;
            if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout<<"\n";
        if(i%3 == 2 ){
            cout << "---------+----------+-----------" <<"\t"<<"\t"<<"---------+----------+-----------"<< endl;
        }

    }
    for(int i = 3 ; i<9 ; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[3][i][j] << "  ";
            if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout << "\t" << "\t";
        for (int j = 0; j < 9; j++) {
            cout << sudoku[4][i][j] << "  ";
            if (j % 3 == 2 && j != 0) {
                cout << "| ";
            }
        }
        cout << "\n";
        if (i % 3 == 2) {
            cout << "---------+----------+-----------" << "\t" << "\t" << "---------+----------+-----------" << endl;
        }
    }

}
int check_Erorr(int soudoku[5][SIZE][SIZE] , int row , int col ,int num){
    bool flag = false ;
    bool flag2 = false;
    int nrow , ncol ;
    int returnedRow[SIZE];
    int returnedCol[SIZE];
    int returnedSquare[3][3];
    if(row<=9 && col <= 9){
        nrow = row-1 ;
        ncol = col-1 ;
        getRowColumnSquare(soudoku,0,nrow,ncol,returnedRow,returnedCol,returnedSquare);
        bool flag2 = true;
        if(checkRow(returnedRow,num) || checkColumn(returnedCol,num) || checkSquare(returnedSquare,num) == 1 )
            flag = 1 ;
    }
    if(row<=9 && col > 12){
        nrow = row-1 ;
        ncol = col-12-1 ;
        getRowColumnSquare(soudoku,1,nrow,ncol,returnedRow,returnedCol,returnedSquare);
        bool flag2 = true;
        if(checkRow(returnedRow,num) || checkColumn(returnedCol,num) || checkSquare(returnedSquare,num) == 1 )
            flag = 1 ;
    }
    if(row>12 && col <= 9){
        nrow = row-12-1 ;
        ncol = col-1 ;
        getRowColumnSquare(soudoku,3,nrow,ncol,returnedRow,returnedCol,returnedSquare);

        bool flag2 = true;
        if(checkRow(returnedRow,num) || checkColumn(returnedCol,num) || checkSquare(returnedSquare,num) == 1 )
            flag = 1 ;

    }
    if(row>12 && col > 12){
        nrow = row - 12-1;
        ncol = col -12-1 ;
        getRowColumnSquare(soudoku,4,nrow,ncol,returnedRow,returnedCol,returnedSquare);
        bool flag2 = true;
        if(checkRow(returnedRow,num) || checkColumn(returnedCol,num) || checkSquare(returnedSquare,num) == 1 )
            flag = 1 ;
    }
    if(row>6 && row<16 && col>6 && col<16){
        nrow = row - 6-1 ;
        ncol = col-6-1 ;
        getRowColumnSquare(soudoku,2,nrow,ncol,returnedRow,returnedCol,returnedSquare);
        bool flag2 = true;
        if(checkRow(returnedRow,num) || checkColumn(returnedCol,num) || checkSquare(returnedSquare,num) == 1 )
            flag = 1 ;


    }
    if(flag || flag2){
        cout<<"!!error!!"<<endl ;
        return 1 ;
    }
    else{
        if(row<=9 && col <= 9){
            nrow = row-1 ;
            ncol = col-1 ;
            soudoku[0][nrow][ncol] = num ;
        }
        if(row<=9 && col > 12){
            nrow = row-1 ;
            ncol = col-12-1 ;
            soudoku[1][nrow][ncol] = num ;

        }
        if(row>12 && col <= 9){
            nrow = row-12-1 ;
            ncol = col-1 ;
            soudoku[3][nrow][ncol] = num ;

        }
        if(row>12 && col > 12){
            nrow = row - 12-1;
            ncol = col -12-1 ;
            soudoku[4][nrow][ncol] = num ;

        }
        if(row>6 && row<16 && col>6 && col<16){
            nrow = row - 6-1 ;
            ncol = col-6-1 ;
            soudoku[2][nrow][ncol] = num ;
        }
        printSoudoko(soudoku);
    }
}
int main() {
    int sudoku[5][SIZE][SIZE];
    initializeSudoku(sudoku);
    printSoudoko(sudoku);
        int row , col , num  ;
        int error = 0 ;
    while (1){
        cout<<"enter row:" ;
        cin>>row;
        cout<<endl ;
        cout<<"enter col:";
        cin>>col ;
        cout<<"enter num: ";
        cin>>num ;
        error+=check_Erorr(sudoku , row, col, num) ;
        if(error == 3){
            cout<<"endgame" ;
            return 0 ;
        }
    }
    return 0;
}