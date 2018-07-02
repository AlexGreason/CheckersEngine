//
// Created by exa on 6/30/18.
//

#ifndef CHECKERSENGINE_SEARCH_H
#define CHECKERSENGINE_SEARCH_H


#include "board.h"

int perft(Board b, int depth);
std::vector<BOARDSTATE> minimax(BOARDSTATE start, int depth);
#endif //CHECKERSENGINE_SEARCH_H
