//
// Created by exa on 7/2/18.
//

#include <iostream>
#include <functional>
#include "game.h"

#include "board.h"
#include "eval.h"
#include "search.h"

//BOARDSTATE (*currydepth(BOARDSTATE (*engine)(BOARDSTATE board, int depth), int depth))(BOARDSTATE){
std::function<BOARDSTATE(BOARDSTATE)> currydepth(BOARDSTATE (*engine)(BOARDSTATE, int), int depth){
        return [depth, engine](BOARDSTATE state){return engine(state, depth);};
}

char rungame(std::function<BOARDSTATE(BOARDSTATE)> engine1, std::function<BOARDSTATE(BOARDSTATE)> engine2){
    Board game;
    game.startpos();
    while(!game.board.result){
        if(game.board.sidetomove == 0){
            game.board = engine1(game.board);
        } else {
            game.board = engine2(game.board);
        }
        std::cout << game.print() << std::endl;
    }
    std::cout << "Game result: " << std::to_string(game.board.result) << std::endl;
    return game.board.result;
}