//
// Created by exa on 7/1/18.
//

#include <random>
#include "eval.h"
#include "board.h"
#include "search.h"


std::vector<char> countpieces(BOARDSTATE board){
    std::vector<char> counts(6);
    for (auto &r : board.board) {
        for (char c : r) {
            counts[c]++;
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