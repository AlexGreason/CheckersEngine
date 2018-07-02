//
// Created by exa on 6/30/18.
//

#include <iostream>
#include <sstream>
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
    for(BOARDSTATE state : moves){
        b.board = state;
        if(pieceonrank(state, 1, 7)){
            char* crash = NULL;
            std::cout << printstate(state) << std::endl;
            std::cout << "reached from (ply " << state.ply << ") " << std::endl;
            std::cout << printstate(oldstate) << std::endl;
            std::vector<BOARDSTATE> moves = legalmovesstate(oldstate);
            for(BOARDSTATE s : moves){
                std::cout << printstate(s) << std::endl;
            }
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
        start.eval = materiel1(start);
        if(start.eval >= 4){
            start.eval = materiel1(start);
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

        }
    }
    start.eval = materiel1(start);
    bestpv.insert(bestpv.begin(), start);
    return bestpv;
}

BOARDSTATE minimaxagent(BOARDSTATE start, int depth){
    return minimax(start, depth).front();
}

BOARDSTATE randomagent(BOARDSTATE start){
    std::vector<BOARDSTATE> moves = legalmovesstate(start);
    long index = random();
    return moves[index];
}
