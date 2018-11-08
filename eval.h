//
// Created by exa on 7/1/18.
//

#ifndef CHECKERSENGINE_EVAL_H
#define CHECKERSENGINE_EVAL_H

#include "board.h"
#include "search.h"

bool pieceonrank(BOARDSTATE board, char piece, char rank);
double materiel1(BOARDSTATE board, ENGINEPARAMS params);
double randomeval(BOARDSTATE board, ENGINEPARAMS params);
double evaluate(BOARDSTATE board, ENGINEPARAMS params);

#endif //CHECKERSENGINE_EVAL_H
