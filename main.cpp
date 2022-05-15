#include <iostream>
#include "string.h"
#include "List.h"

#define PLAYER_1 1
#define PLAYER_2 2
#define EMPTY 0

void printAllMoves(int **board, int m, int n, int k, int p, bool b);

void printBoard(int **board, int m, int n);

int whoWon(int **board, int m, int n, int k);

int checkRow(int **board, int m, int n, int k);

int checkColumn(int **board, int m, int n, int k);

int checkDiagonal(int **board, int m, int n, int k);

int checkDiagonalToTheRight(int **board, int m, int n, int k);

int checkDiagonalToTheLeft(int **board, int m, int n, int k);

List* generateAllMoves(int ** board,int m,int n,int p,int k,bool cut);
bool isFull(int ** board,int m,int n);

int Minimax(int initialPlayer,int** board,int m,int n,int k,int player);

using namespace std;

int getOponent(int player);

int main() {

    int m, n, k, player;
    char command[50];

        while(scanf("%s",command)==1){
            scanf("%i %i %i %i", &m, &n, &k, &player);


        int **board = new int *[m];
        for (int i = 0; i < m; i++)
            board[i] = new int[n];


        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%i",&board[i][j]);
            }
        }


        if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) {
            printAllMoves(board, m, n, k, player, true);
        } else if (strcmp(command, "GEN_ALL_POS_MOV") == 0) {
            printAllMoves(board, m, n, k, player, false);
        }
        else if (strcmp(command, "SOLVE_GAME_STATE") == 0) {

            int result=Minimax(player,board,m,n,k,player);
            int winningPlayer = player;
            if(result == -1) {
                winningPlayer = getOponent(player);
            }
            else if(result == 0) {
                winningPlayer = -10;
            }


           if(winningPlayer==1){
               printf("FIRST_PLAYER_WINS\n");
           }
           else if(winningPlayer==2) {
               printf("SECOND_PLAYER_WINS\n");
           }
           else{
               printf("BOTH_PLAYERS_TIE\n");
           }
        }


        for (int i = 0; i < m; i++)
            delete[] board[i];


        delete[] board;

    }

    return 0;
}

void printAllMoves(int **board, int m, int n, int k, int p, bool b) {

    int moves_Amount = 0;
    bool victory = false;

    if (whoWon(board, m, n, k) != 0) {
        printf("0\n");
        return;
    }

    List* moves = generateAllMoves( board,m, n, p,k, false);

    moves_Amount=moves->size();
    if (b) {
        for (int i = 0; i < moves->size(); i++) {
            int x = moves->get_element(i).x;
            int y = moves->get_element(i).y;
            board[y][x] = p;
            if (whoWon(board, m, n, k) == p) {
                printf("1\n");
                printBoard(board, m, n);
                victory = true;
                moves->free_memory();
                return;
            }
            board[y][x] = EMPTY;
        }
    }

    if (!victory) {
        printf("%d\n",moves->size());

        for (int i = 0; i < moves->size(); ++i) {
            int x=moves->get_element(i).x;
            int y=moves->get_element(i).y;
            board[y][x]=p;
            printBoard(board,m,n);
            board[y][x]=EMPTY;
        }
    }
    moves->free_memory();
}

int getOponent(int player) {
    if(player == PLAYER_1) {
        return 2;
    }
    return 1;
}

int Minimax(int initialPlayer,int** board,int m,int n,int k,int player){
    int game_state= whoWon(board,m,n,k);

    if(game_state==initialPlayer){
        return 1;
    }

    else if(game_state== getOponent(initialPlayer)){
        return -1;
    }

    else if(game_state == 0 && isFull(board,m,n)) {
        return 0;
    }

    List* moves = generateAllMoves(board,m,n,player,k,true);

    int best=-2;
    int worst=2;

    if(player==initialPlayer){
        for (int i = 0; i < moves->size(); ++i) {

            int y = moves->get_element(i).y;
            int x= moves->get_element(i).x;

            board[y][x]=player;
            int score= Minimax(initialPlayer,board,m,n,k, getOponent(player));
            if(score>best){
                best=score;
            }
            board[y][x]=EMPTY;
            if(best==1){
                return 1;
            }

        }
        moves->free_memory();
        return best;

    }
    else{
        for (int i = 0; i < moves->size(); ++i) {
            int y = moves->get_element(i).y;
            int x= moves->get_element(i).x;
            board[y][x]=player;
            int score= Minimax(initialPlayer,board,m,n,k, getOponent(player));
            if(score<worst){
                worst=score;
            }
            board[y][x]=EMPTY;
            if(worst==-1){
                return -1;
            }

        }
        moves->free_memory();
        return worst;

    }

}


bool isFull(int ** board,int m,int n){

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

List* generateAllMoves(int ** board,int m,int n,int p,int k,bool cut){

    List* moves=new List;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == EMPTY) {
                Position_t move{};
                move.y=i;
                move.x=j;
                if(cut){
                    board[move.y][move.x]=p;
                    if(whoWon(board,m,n,k)!=0){
                        List* Fmove=new List;
                        Fmove->addLast(move);
                        return Fmove;
                    }
                    board[move.y][move.x]=EMPTY;
                }

                moves->addLast(move);
            }
        }
    }
    return moves;
}

int whoWon(int **board, int m, int n, int k) {
    int rows = checkRow(board, m, n, k);
    int columns = checkColumn(board, m, n, k);
    int diagonal = checkDiagonal(board, m, n, k);

    if (rows != 0) {
        return rows;
    }
    if (columns != 0) {
        return columns;
    }
    if (diagonal != 0) {
        return diagonal;
    }
    return 0;
}

int checkDiagonal(int **board, int m, int n, int k) {
    int right = checkDiagonalToTheRight(board, m, n, k);
    int left = checkDiagonalToTheLeft(board, m, n, k);
    if (right != 0) {
        return right;
    }
    if (left != 0) {
        return left;
    }
    return 0;
}

int checkDiagonalToTheLeft(int **board, int m, int n, int k) {
    int kPlayer1 = k;
    int kPlayer2 = k;
    for (int i = 0; i < m; i++) {
        int y = i;
        int x = 0;

        kPlayer1 = k;
        kPlayer2 = k;
        while (y >= 0 && x < n) {
            if (board[y][x] == PLAYER_1) {
                kPlayer1--;
                kPlayer2 = k;
            } else if (board[y][x] == PLAYER_2) {
                kPlayer2--;
                kPlayer1 = k;
            } else if (board[y][x] == EMPTY) {
                kPlayer2 = k;
                kPlayer1 = k;
            }

            if (kPlayer1 == 0) {
                return 1;
            }
            if (kPlayer2 == 0) {
                return 2;
            }

            x++;
            y--;
        }

    }

    for (int i = n - 1; i > 0; i--) {
        int y = m - 1;
        int x = i;
        kPlayer1 = k;
        kPlayer2 = k;
        while (x < n && y >= 0) {

            if (board[y][x] == PLAYER_1) {
                kPlayer1--;
                kPlayer2 = k;
            } else if (board[y][x] == PLAYER_2) {
                kPlayer2--;
                kPlayer1 = k;
            } else if (board[y][x] == EMPTY) {
                kPlayer1 = k;
                kPlayer2 = k;
            }
            if (kPlayer1 == 0) {
                return 1;
            }
            if (kPlayer2 == 0) {
                return 2;
            }
            y--;
            x++;
        }
    }
    return 0;
}

int checkDiagonalToTheRight(int **board, int m, int n, int k) {
    int kPlayer1 = k;
    int kPlayer2 = k;
    for (int i = m - 1; i >= 0; i--) {
        int y = i;
        int x = 0;
        kPlayer1 = k;
        kPlayer2 = k;
        while (y < m && x < n) {
            if (board[y][x] == PLAYER_1) {
                kPlayer1--;
                kPlayer2 = k;
            } else if (board[y][x] == PLAYER_2) {
                kPlayer2--;
                kPlayer1 = k;
            } else if (board[y][x] == EMPTY) {
                kPlayer1 = k;
                kPlayer2 = k;
            }
            if (kPlayer1 == 0) {
                return 1;
            }
            if (kPlayer2 == 0) {
                return 2;
            }
            x++;
            y++;
        }
    }

    for (int i = 0; i < n; i++) {
        int y = 0;
        int x = i;
        kPlayer1 = k;
        kPlayer2 = k;
        while (x < n && y < m) {

            if (board[y][x] == PLAYER_1) {
                kPlayer1--;
                kPlayer2 = k;
            } else if (board[y][x] == PLAYER_2) {
                kPlayer2--;
                kPlayer1 = k;
            } else if (board[y][x] == EMPTY) {
                kPlayer1 = k;
                kPlayer2 = k;
            }
            if (kPlayer1 == 0) {
                return 1;
            }
            if (kPlayer2 == 0) {
                return 2;
            }
            y++;
            x++;
        }
    }
    return 0;
}

int checkColumn(int **board, int m, int n, int k) {
    int kPlayer1 = k;
    int kPlayer2 = k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[j][i] == PLAYER_1) {
                kPlayer1--;
                kPlayer2 = k;
            } else if (board[j][i] == PLAYER_2) {
                kPlayer2--;
                kPlayer1 = k;
            } else if (board[j][i] == EMPTY) {
                kPlayer1 = k;
                kPlayer2 = k;
            }
            if (kPlayer1 == 0) {
                return 1;
            }
            if (kPlayer2 == 0) {
                return 2;
            }
        }
        kPlayer2 = k;
        kPlayer1 = k;
    }
    return 0;
}

int checkRow(int **board, int m, int n, int k) {
    int kPlayer1 = k;
    int kPlayer2 = k;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == PLAYER_1) {
                kPlayer1--;
                kPlayer2 = k;
            } else if (board[i][j] == PLAYER_2) {
                kPlayer2--;
                kPlayer1 = k;
            } else if (board[i][j] == EMPTY) {
                kPlayer1 = k;
                kPlayer2 = k;
            }
            if (kPlayer1 == 0) {
                return 1;
            }
            if (kPlayer2 == 0) {
                return 2;
            }
        }
        kPlayer2 = k;
        kPlayer1 = k;
    }
    return 0;
}


void printBoard(int **board, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}