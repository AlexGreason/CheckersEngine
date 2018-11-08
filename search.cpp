//
// Created by exa on 6/30/18.
//

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include "search.h"
#include "board.h"
#include "eval.h"
#include "engine.h"



int perft(Board b, int depth){
    if(depth <= 0){
        return 1;
    }
    int result = 0;
    std::vector<BOARDSTATE> moves = b.legalmoves();
    BOARDSTATE oldstate = b.board;
    for (auto state : moves) {
        b.board = state;
        int val = perft(b, depth - 1);
        result += val;
        b.board = oldstate;
    }
    return result;
}

std::vector<BOARDSTATE> minimax(BOARDSTATE start, int depth, ENGINEPARAMS params){
    std::vector<BOARDSTATE> pv;
    if(depth == 0){
        start.staticeval = evaluate(start, params);
        pv.insert(pv.begin(), start);
        return pv;
    }
    std::vector<BOARDSTATE> moves = legalmovesstate(start);
    double best = -10000;
    std::vector<BOARDSTATE> bestpv;
    if(start.sidetomove == 1){
        best = 10000;
    }
    for(BOARDSTATE state : moves){
        std::vector<BOARDSTATE> tmppv = minimax(state, depth - 1, params);
        double val = tmppv.back().staticeval;
        if((val > best && !start.sidetomove) || (val < best && start.sidetomove)){
            best = val;
            bestpv = tmppv;
        } else {
            tmppv.clear();
            tmppv.shrink_to_fit();
        }
    }
    start.staticeval = evaluate(start, params);
    bestpv.insert(bestpv.begin(), start);
    return bestpv;
}

std::vector<BOARDSTATE>
minimax_caching(BOARDSTATE start, Engine engine, int depth,
                std::unordered_map<BOARDSTATE, double> &transtable) {
    std::vector<BOARDSTATE> pv;
    auto tableeval = transtable.find(start);
    if(tableeval != transtable.end()){
        start.staticeval = tableeval->second;
        pv.insert(pv.begin(), start);
        return pv;
    }
    if(depth == 0){
        start.staticeval = engine.eval(start);
        transtable.insert({start, start.staticeval});
        pv.insert(pv.begin(), start);
        return pv;
    }
    std::vector<BOARDSTATE> moves = legalmovesstate(start);
    double best = -10000;
    std::vector<BOARDSTATE> bestpv;
    if(start.sidetomove == 1){
        best = 10000;
    }
    for(BOARDSTATE state : moves){
        std::vector<BOARDSTATE> tmppv = minimax_caching(state, engine, depth - 1, transtable);
        double val = tmppv.back().staticeval;
        if((val > best && !start.sidetomove) || (val < best && start.sidetomove)){
            best = val;
            bestpv = tmppv;
        } else {
            tmppv.clear();
            tmppv.shrink_to_fit();
        }
    }
    if(!bestpv.empty()){
        transtable.insert({start, bestpv.back().staticeval});
    } else {
        transtable.insert({start, best});
    }

    start.staticeval = engine.eval(start);
    bestpv.insert(bestpv.begin(), start);
    return bestpv;
}

TTABLE_ENTRY
alphabeta(BOARDSTATE start, Engine engine, int depth, double alpha, double beta, std::unordered_map<BOARDSTATE, TTABLE_ENTRY> &transtable){

}


BOARDSTATE randomagent(BOARDSTATE start, ENGINEPARAMS params){
    std::vector<BOARDSTATE> moves = legalmovesstate(start);
    if(moves.empty()){
        return start;
    }
    long index = random() * moves.size();
    return moves[index];
}
