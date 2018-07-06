#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include "board.h"
#include "search.h"
#include "game.h"
#include "eval.h"

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
    ENGINEPARAMS p1{11, 1};
    ENGINEPARAMS p2{11, 1.5};
    std::cout << std::to_string(p1.depth) << " " << std::to_string(p2.depth) << std::endl;
    rungame(curryparams(minimaxagent, materiel1, p1), curryparams(minimaxagent, materiel1, p2));
//    Board b{};
    //b.testpos();
    //b.board.sidetomove = 1;
    //std::cout << b.print() << std::endl;
//    b.startpos();
//    std::unordered_map<BOARDSTATE, double> transtable;
//    std::vector<BOARDSTATE> pv;
//    pv = minimax_caching(b.board, 13, transtable);
//    std::cout << transtable.size() << std::endl;
//    for(BOARDSTATE state : pv){
//        std::cout << printstate(state) << state.eval << std::endl;
//    }
//    std::cout << perft(b, 12) << std::endl;
//    std::cout << b.print() << std::endl;
//    move(b.board, 2, 0, 1, 1);
//    std::cout << b.print() << std::endl;
//    move(b.board, 5, 1, 1, 0);
//    std::cout << b.print() << std::endl;
//    move(b.board, 2, 2, 1, 1);
//    std::cout << b.print() << std::endl;
//    std::cout << printarray(hasmoves(b.board, 3, 3), 4) << std::endl;
//    move(b.board, 4, 2, 0, 0);
//    std::cout << b.print() << std::endl;
//    std::vector<BOARDSTATE> moves = b.legalmoves();
//    for(BOARDSTATE s : moves){
//        std::cout << printstate(s) << std::endl;
//    }
    return 0;
}