//
// Created by exa on 7/2/18.
//

#ifndef CHECKERSENGINE_GAME_H
#define CHECKERSENGINE_GAME_H

#include "board.h"
#include <functional>

char rungame(std::function<BOARDSTATE(BOARDSTATE)> engine1, std::function<BOARDSTATE(BOARDSTATE)> engine2);
std::function<BOARDSTATE(BOARDSTATE)> currydepth(BOARDSTATE (*engine)(BOARDSTATE, int), int depth);

#endif //CHECKERSENGINE_GAME_H
