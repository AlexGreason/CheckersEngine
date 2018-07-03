#include <iostream>
#include <sstream>
#include <unordered_map>
#include "board.h"
#include "search.h"
#include "game.h"

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
    rungame(currydepth(minimaxagent, 9), currydepth(minimaxagent, 10));
    Board b{};
    //b.testpos();
    //b.board.sidetomove = 1;
    //std::cout << b.print() << std::endl;
//    b.startpos();
//    std::unordered_map<BOARDSTATE, double> transtable;
//    std::vector<BOARDSTATE> pv;
//    pv = minimax_caching(b.board, 10, transtable);
//    std::cout << transtable.size() << std::endl;
//    for(BOARDSTATE state : pv){
//        std::cout << printstate(state) << state.eval << std::endl;
//    }
 //   std::cout << perft(b, 10) << std::endl;
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