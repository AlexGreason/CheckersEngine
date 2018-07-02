//
// Created by exa on 6/29/18.
//

#ifndef CHECKERSENGINE_BOARD_H
#define CHECKERSENGINE_BOARD_H

#include <vector>
#include <string>



struct BOARDSTATE {
    int ply; //starts at 0 before the first move and counts upwards
    char sidetomove; //0=first player (black), 1=second player(red)
    char result; //0=not terminal, 1=first player win, 2 = second player win, 3=draw
    char board[8][8]; //0=empty, 1=black piece, 2=black king, 3=red piece, 4=red king
};

char move(BOARDSTATE &board, char r, char c, bool right, bool up);
char* hascaptures(BOARDSTATE board, char r, char c);
char* hasmoves(BOARDSTATE board, char r, char c);
std::vector<BOARDSTATE> legalmovesstate(BOARDSTATE board);

struct MOVE {
    char startr;
    char startc;
    char endr;
    char endc;
};

std::string printstate(BOARDSTATE board);

class Board{
public:
    BOARDSTATE board;
    double eval;
    void startpos();
    std::string print();
    std::vector<BOARDSTATE> legalmoves();

    void testpos();
};

#endif //CHECKERSENGINE_BOARD_H
