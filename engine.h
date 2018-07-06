//
// Created by exa on 7/5/18.
//



#ifndef CHECKERSENGINE_ENGINE_H
#define CHECKERSENGINE_ENGINE_H

#include <unordered_map>
#include "board.h"

struct ENGINEPARAMS{
    int depth = 1;
    double kingvalue = 1;
};

class Engine {
public:
    Engine(std::vector<BOARDSTATE>
           (*search_func)(BOARDSTATE start, Engine engine, int depth, std::unordered_map<BOARDSTATE, double> &transtable),
           double (*eval_func)(BOARDSTATE, ENGINEPARAMS), ENGINEPARAMS inpparams){
      search_method = search_func;
      eval_method = eval_func;
      params = inpparams;
    }

    BOARDSTATE search(BOARDSTATE board);
    double eval(BOARDSTATE board);

private:
    std::vector<BOARDSTATE>
    (*search_method)(BOARDSTATE start, Engine engine, int depth, std::unordered_map<BOARDSTATE, double> &transtable);
    double (*eval_method)(BOARDSTATE, ENGINEPARAMS);
    ENGINEPARAMS params;
};

#endif //CHECKERSENGINE_ENGINE_H