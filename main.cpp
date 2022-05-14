#include <iostream>
#include "string.h"

void generateMoves(int **board, int m, int n, int k, int p, bool b);

void printBoard(int **board, int m, int n);

int isOver(int **board, int m, int n, int k,int p);

int checkRow(int **board, int m, int n, int k);

int checkCollumn(int **board, int m, int n, int k);

int checkDiagonal(int **board, int m, int n, int k);

int checkDiagonalToTheRight(int **board, int m, int n, int k);

int checkDiagonalToTheLeft(int **board, int m, int n, int k);

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    int m,n,k,player;
    char command[40];
    while(cin>>command) {

        cin >> m;
        cin >> n;
        cin >> k;
        cin >> player;



        int **board = new int *[m];
        for (int i = 0; i < m; i++)
            board[i] = new int[n];


        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> board[i][j];
            }
        }

        //printBoard(board,m,n);

        if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) {
            generateMoves(board, m, n, k, player, true);
        }

        else if (strcmp(command, "GEN_ALL_POS_MOV") == 0) {
            generateMoves(board, m, n, k, player, false);
        }



        for (int i = 0; i<m; i++)
            delete [] board[i];


        delete [] board;

    }

    return 0;
}

void generateMoves(int **board, int m, int n, int k, int p, bool b) {

    int moves_Amount=0;
    bool victory=false;

    if (isOver(board,m,n,k,p)!=0){
        cout<<0<<endl;
        return;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if(board[i][j]==0){
                moves_Amount++;

                if(b){
                    board[i][j]=p;
                    if(isOver(board,m,n,k,p)==p){
                        cout<<1<<endl;
                        printBoard(board,m,n);
                        victory=true;
                        return;
                    }
                    board[i][j]=0;
                }
            }
        }

    }
    if(!victory){
        cout<<moves_Amount<<endl;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(board[i][j]==0){
                    board[i][j]=p;
                    printBoard(board,m,n);
                    board[i][j]=0;
                }
            }
        }
    }

}

int isOver(int **board, int m, int n, int k,int p) {
    int rows=checkRow(board,m, n,k);
    int columns=checkCollumn(board,m, n,k);
    int diagonal= checkDiagonal(board,m,n,k);

    if(rows!=0){
        return rows;
    }
    if(columns!=0){
        return columns;
    }
    if(diagonal!=0){
        return diagonal;
    }
    return 0;
}

int checkDiagonal(int **board, int m, int n, int k) {
    int right=checkDiagonalToTheRight(board,m,n,k);
    int left=checkDiagonalToTheLeft(board,m,n,k);
    if(right!=0){
        return right;
    }
    if(left!=0){
        return left;
    }
    return 0;
}

int checkDiagonalToTheLeft(int **board, int m, int n, int k) {
    int kPlayer1=k;
    int kPlayer2=k;
    for (int i = 0; i < m; i++) {
        int y=i;
        int x=0;

        kPlayer1=k;
        kPlayer2=k;
        while (y>=0 && x<n){
            if(board[y][x]==1){
                kPlayer1--;
                kPlayer2=k;
            }
            else if(board[y][x]==2){
                kPlayer2--;
                kPlayer1=k;
            }
            else if(board[y][x]==0){
                kPlayer2=k;
                kPlayer1=k;
            }

            if(kPlayer1==0){
                return 1;
            }
            if(kPlayer2==0){
                return 2;
            }

            x++;
            y--;
        }

    }

    for (int i = n-1; i >0; i--) {
        int y=m-1;
        int x=i;
        kPlayer1=k;
        kPlayer2=k;
        while (x<n && y>=0){

            if(board[y][x]==1){
                kPlayer1--;
                kPlayer2=k;
            }
            else if(board[y][x]==2){
                kPlayer2--;
                kPlayer1=k;
            }
            else if(board[y][x]==0){
                kPlayer1=k;
                kPlayer2=k;
            }
            if(kPlayer1==0){
                return 1;
            }
            if(kPlayer2==0){
                return 2;
            }
            y--;
            x++;
        }
    }
    return 0;
}

int checkDiagonalToTheRight(int **board, int m, int n, int k) {
    int kPlayer1=k;
    int kPlayer2=k;
    for (int i = m-1; i >= 0; i--) {
        int y=i;
        int x=0;
        kPlayer1=k;
        kPlayer2=k;
        while (y<m && x<n){
            if(board[y][x]==1){
                kPlayer1--;
                kPlayer2=k;
            }
            else if(board[y][x]==2){
                kPlayer2--;
                kPlayer1=k;
            }
            else if(board[y][x]==0){
                kPlayer1=k;
                kPlayer2=k;
            }
            if(kPlayer1==0){
                return 1;
            }
            if(kPlayer2==0){
                return 2;
            }
            x++;
            y++;
        }
    }

    for (int i = 0; i < n; i++) {
        int y=0;
        int x=i;
        kPlayer1=k;
        kPlayer2=k;
        while (x<n && y<m){

            if(board[y][x]==1){
                kPlayer1--;
                kPlayer2=k;
            }
            else if(board[y][x]==2){
                kPlayer2--;
                kPlayer1=k;
            }
            else if(board[y][x]==0){
                kPlayer1=k;
                kPlayer2=k;
            }
            if(kPlayer1==0){
                return 1;
            }
            if(kPlayer2==0){
                return 2;
            }
            y++;
            x++;
        }
    }
    return 0;
}

int checkCollumn(int **board, int m, int n, int k) {
    int kPlayer1=k;
    int kPlayer2=k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(board[j][i]==1){
                kPlayer1--;
                kPlayer2=k;
            }
            else if(board[j][i]==2){
                kPlayer2--;
                kPlayer1=k;
            }
            else if(board[j][i]==0){
                kPlayer1=k;
                kPlayer2=k;
            }
            if(kPlayer1==0){
                return 1;
            }
            if(kPlayer2==0){
                return 2;
            }
        }
        kPlayer2=k;
        kPlayer1=k;
    }
    return 0;
}

int checkRow(int **board, int m, int n, int k) {
    int kPlayer1=k;
    int kPlayer2=k;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) {
                kPlayer1--;
                kPlayer2=k;
            } else if (board[i][j] == 2) {
                kPlayer2--;
                kPlayer1=k;
            } else if(board[i][j]==0){
                kPlayer1=k;
                kPlayer2=k;
            }
            if (kPlayer1 == 0) {
                return 1;
            }
            if (kPlayer2 == 0) {
                return 2;
            }
        }
        kPlayer2=k;
        kPlayer1=k;
    }
    return 0;
}


void printBoard(int **board, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
