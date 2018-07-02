//
// Created by exa on 6/30/18.
//

#include <iostream>
#include <sstream>
#include "search.h"
#include "board.h"

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

int perft(Board b, int depth){
    if(depth <= 0){
//        if(wrongsquare(b.board)){
//            std::cout << b.print() << std::endl;
//        }
        return 1;
    }
    int result = 0;
    std::vector<BOARDSTATE> moves = b.legalmoves();
    BOARDSTATE oldstate = b.board;
//    if(depth == 1){
//        return (int)moves.size();
//    }
    for(BOARDSTATE state : moves){
        b.board = state;
        if(pieceonrank(state, 1, 7)){
            char* crash = NULL;
            std::cout << printstate(state) << std::endl;
            std::cout << "reached from (ply " << state.ply << ") " << std::endl;
            std::cout << printstate(oldstate) << std::endl;
            std::vector<BOARDSTATE> moves = legalmovesstate(oldstate);
            for(BOARDSTATE s : moves){
                std::cout << printstate(s) << std::endl;
            }
            std::cout << *crash << std::endl;
        }

        int val = perft(b, depth - 1);
        result += val;
//        if(depth == 2 && state.sidetomove == 1){
//            std::cout << b.print() << std::endl;
//            std::cout << val << std::endl;
//
//        }

        b.board = oldstate;

    }
    return result;
}
