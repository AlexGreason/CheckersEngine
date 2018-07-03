//
// Created by exa on 6/30/18.
//

#include <iostream>
#include <sstream>
#include <unordered_map>
#include "search.h"
#include "board.h"
#include "eval.h"


int perft(Board b, int depth){
    if(depth <= 0){
//        if(wrongsquare(b.board)){
//            std::cout << b.print() << std::endl;
//        }
        return 1;
    }
    int result = 0;
    std::vector<BOARDSTATE> moves = b.legalmoves();
    BOARDSTATE oldstate = b.board;
//    if(depth == 1){
//        return (int)moves.size();
//    }
    for(int i = 0; i < moves.size(); i++){
        BOARDSTATE state = moves[i];
        b.board = state;
        if(false){
            char* crash = NULL;
            std::cout << printstate(state) << std::endl;
            std::cout << "versus (ply " << state.ply << ") " << std::endl;
            std::cout << printstate(oldstate) << std::endl;
            std::vector<BOARDSTATE> moves = legalmovesstate(oldstate);
            for(BOARDSTATE s : moves){
                std::cout << printstate(s) << std::endl;
            }
            moves = legalmovesstate(oldstate);
            std::cout << *crash << std::endl;
        }

        int val = perft(b, depth - 1);
        result += val;
//        if(depth == 2 && state.sidetomove == 1){
//            std::cout << b.print() << std::endl;
//            std::cout << val << std::endl;
//
//        }

        b.board = oldstate;

    }
    return result;
}

std::vector<BOARDSTATE> minimax(BOARDSTATE start, int depth){
    std::vector<BOARDSTATE> pv;
    if(depth == 0){
        start.eval = evaluate(start);
        if(start.eval >= 4){
            start.eval = evaluate(start);
        }
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
        std::vector<BOARDSTATE> tmppv = minimax(state, depth - 1);
        double val = tmppv.back().eval;
        if((val > best && !start.sidetomove) || (val < best && start.sidetomove)){
            best = val;
            bestpv = tmppv;
        } else {
            tmppv.clear();
            tmppv.shrink_to_fit();
        }
    }
    start.eval = evaluate(start);
    bestpv.insert(bestpv.begin(), start);
    return bestpv;
}

std::vector<BOARDSTATE> minimax_caching(BOARDSTATE start, int depth, std::unordered_map<BOARDSTATE, double> &transtable){
    std::vector<BOARDSTATE> pv;
    auto tableeval = transtable.find(start);
    if(tableeval != transtable.end()){
        start.eval = tableeval->second;
        pv.insert(pv.begin(), start);
        return pv;
    }
    if(depth == 0){
        start.eval = evaluate(start);
        if(start.eval >= 4){
            start.eval = evaluate(start);
        }
        transtable.insert({start, start.eval});
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
        std::vector<BOARDSTATE> tmppv = minimax_caching(state, depth - 1, transtable);
        double val = tmppv.back().eval;
        if((val > best && !start.sidetomove) || (val < best && start.sidetomove)){
            best = val;
            bestpv = tmppv;
        } else {
            tmppv.clear();
            tmppv.shrink_to_fit();
        }
    }
    if(bestpv.size() > 0){
        transtable.insert({start, bestpv.back().eval});
    } else {
        transtable.insert({start, best});
    }

    start.eval = evaluate(start);
    bestpv.insert(bestpv.begin(), start);
    return bestpv;
}


BOARDSTATE minimaxagent(BOARDSTATE start, int depth){
    std::unordered_map<BOARDSTATE, double> transtable;
    std::vector<BOARDSTATE> pv = minimax_caching(start, depth, transtable);
    transtable.clear();
    if(pv.size() > 1){
        return pv[1];
    } else {
        return pv[0];
    }
}

BOARDSTATE randomagent(BOARDSTATE start){
    std::vector<BOARDSTATE> moves = legalmovesstate(start);
    if(moves.size() == 0){
        return start;
    }
    long index = random() * moves.size();
    return moves[index];
}
