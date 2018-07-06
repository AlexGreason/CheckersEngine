//
// Created by exa on 6/30/18.
//

#ifndef CHECKERSENGINE_SEARCH_H
#define CHECKERSENGINE_SEARCH_H


#include <unordered_map>
#include <functional>
#include "board.h"
#include "engine.h"



int perft(Board b, int depth);
std::vector<BOARDSTATE> minimax(BOARDSTATE start, int depth, ENGINEPARAMS params);
std::vector<BOARDSTATE>
minimax_caching(BOARDSTATE start, Engine engine, int depth,
                std::unordered_map<BOARDSTATE, double> &transtable) ;
#endif //CHECKERSENGINE_SEARCH_H
