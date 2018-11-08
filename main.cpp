#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <time.h>
#include "board.h"
#include "search.h"
#include "game.h"
#include "eval.h"
#include "engine.h"

std::string printarray(char array[], int len){
    std::stringstream val;
    val << "[";
    for(int i = 0; i < len; i++){
        val << (int)array[i];
        if(i + 1 != len){
            val << ",";
        }

    }
    val << "]";
    return val.str();
}

int main() {
    ENGINEPARAMS c1{11, 1};
    ENGINEPARAMS c2{11, 1};
    Engine p1{minimax_caching, materiel1, c1};
    Engine p2{minimax_caching, randomeval, c2};
//    std::cout << std::to_string(c1.depth) << " " << std::to_string(c2.depth) << std::endl;
//    rungame(p1, p2);
    Board b{};
    //b.testpos();
    //b.board.sidetomove = 1;
    //std::cout << b.print() << std::endl;
    b.startpos();
    std::unordered_map<BOARDSTATE, TTABLE_ENTRY> transtable;
//    std::vector<BOARDSTATE> pv;
    clock_t t;
    t = clock();
    auto res = alphabeta(b.board, p1, 17, -10000, 10000, transtable);
    t = clock() - t;
    std::cout << "Took " << std::to_string((float)t/(float)CLOCKS_PER_SEC) << " seconds" << std::endl;
    std::cout << std::to_string(transtable.size()) << std::endl;
    std::cout << std::to_string(res.nodes) << " " << std::to_string(res.eval) << " " << printstate(res.pv.at(1)) << std::endl;
//    for(BOARDSTATE state : pv){
//        std::cout << printstate(state) << state.eval << std::endl;
//    }
//    std::cout << perft(b, 12) << std::endl;
    return 0;
}