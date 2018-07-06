//
// Created by exa on 7/2/18.
//

#ifndef CHECKERSENGINE_GAME_H
#define CHECKERSENGINE_GAME_H

#include "board.h"
#include "search.h"
#include <functional>

char rungame(std::function<BOARDSTATE(BOARDSTATE)> engine1, std::function<BOARDSTATE(BOARDSTATE)> engine2);
std::function<BOARDSTATE(BOARDSTATE)> curryparams(BOARDSTATE (*engine)(BOARDSTATE, double (*)(BOARDSTATE, ENGINEPARAMS), ENGINEPARAMS), double (*eval)(BOARDSTATE, ENGINEPARAMS), ENGINEPARAMS params);
#endif //CHECKERSENGINE_GAME_H
