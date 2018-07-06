//
// Created by exa on 7/1/18.
//

#include <random>
#include "eval.h"
#include "board.h"
#include "search.h"

bool hasking(BOARDSTATE board){
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(board.board[r][c] == 2 || board.board[r][c] == 4){
                return true;
            }
        }
    }
    return false;
}

bool hasking(BOARDSTATE board, char side){
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(board.board[r][c] == side){
                return true;
            }
        }
    }
    return false;
}

bool wrongsquare(BOARDSTATE board){
    for(int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if((r + c)%2 == 1){
                if(board.board[r][c] != 0){
                    return true;
                }
            }
        }
    }
    return false;
}

bool kingmoved(BOARDSTATE board, BOARDSTATE oldboard){
    if(!hasking(oldboard)){
        return false;
    }
    for(int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if ((board.board[r][c] == 2 || board.board[r][c] == 4) && board.board[r][c] != oldboard.board[r][c]) {
                return true;
            }
        }
    }
    return false;
}

bool kingnotonlastrank(BOARDSTATE board){
    for(int r = 1; r < 7; r++) {
        for (int c = 0; c < 8; c++) {
            if(board.board[r][c] == 2 || board.board[r][c] == 4){
                return true;
            }
        }
    }
    return false;
}

bool promotefailed(BOARDSTATE board){
    for(int c = 0; c < 8; c++){
        if(board.board[0][c] == 3){
            return true;
        }
        if(board.board[8][c] == 1){
            return true;
        }
    }
    return false;
}

char testpos[8][8] =  {{1, 0, 1, 0, 1, 0, 1, 0},
                       {0, 1, 0, 1, 0, 1, 0, 1},
                       {0, 0, 1, 0, 1, 0, 1, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 3, 0, 1, 0, 3, 0, 3},
                       {3, 0, 3, 0, 3, 0, 3, 0},
                       {0, 3, 0, 3, 0, 3, 0, 3}};

bool boardequal(char pos1[8][8], char pos2[8][8]){
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(pos1[r][c] != pos2[r][c]){
                return false;
            }
        }
    }
    return true;
}

bool pieceonrank(BOARDSTATE board, char piece, char rank){
    for(int c = 0; c < 8; c++){
        if(board.board[rank][c] == piece){
            return true;
        }
    }
    return false;
}


std::vector<char> countpieces(BOARDSTATE board){
    std::vector<char> counts;
    counts.resize(6);
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            counts[board.board[r][c]]++;
        }
    }
    return counts;
}

double materiel1(BOARDSTATE board, ENGINEPARAMS params){
    if(board.result != 0){
        double vals[4]{0, 1000, -1000, 0};
        return vals[board.result];
    }
    double kingval = params.kingvalue;
    std::vector<char> counts = countpieces(board);
    double black = counts[1] + kingval * counts[2];
    double red = counts[3] + kingval * counts[4];
    return black - red;
}

double randomeval(BOARDSTATE board, ENGINEPARAMS params){
  return ((double)random()/RAND_MAX) * 2 - 1;
}

double evaluate(BOARDSTATE board, ENGINEPARAMS params) {
    return materiel1(board, params);
}