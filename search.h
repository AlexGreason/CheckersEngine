//
// Created by exa on 6/30/18.
//

#ifndef CHECKERSENGINE_SEARCH_H
#define CHECKERSENGINE_SEARCH_H


#include <unordered_map>
#include "board.h"
#include <functional>


struct ENGINEPARAMS{
    int depth = 1;
    double kingvalue = 1;
};

int perft(Board b, int depth);
std::vector<BOARDSTATE> minimax(BOARDSTATE start, int depth, ENGINEPARAMS params);
std::vector<BOARDSTATE> minimax_caching(BOARDSTATE start, int depth, double (*eval)(BOARDSTATE, ENGINEPARAMS), ENGINEPARAMS params,
        std::unordered_map<BOARDSTATE, double> &transtable);
BOARDSTATE minimaxagent(BOARDSTATE start, double (*eval)(BOARDSTATE, ENGINEPARAMS), ENGINEPARAMS params);
#endif //CHECKERSENGINE_SEARCH_H
