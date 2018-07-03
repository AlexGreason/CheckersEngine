//
// Created by exa on 7/1/18.
//

#ifndef CHECKERSENGINE_EVAL_H
#define CHECKERSENGINE_EVAL_H

#include "board.h"

bool pieceonrank(BOARDSTATE board, char piece, char rank);
double materiel1(BOARDSTATE board);
double evaluate(BOARDSTATE board);

#endif //CHECKERSENGINE_EVAL_H
