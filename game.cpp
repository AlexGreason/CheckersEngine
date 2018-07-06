//
// Created by exa on 7/2/18.
//

#include <iostream>
#include <functional>
#include "game.h"

#include "board.h"
#include "eval.h"
#include "search.h"


char rungame(Engine engine1, Engine engine2){
    Board game;
    game.startpos();
    while(!game.board.result){
        if(game.board.sidetomove == 0){
            game.board = engine1.search(game.board);
        } else {
            game.board = engine2.search(game.board);
        }
        std::cout << game.print() << std::endl;
    }
    std::cout << "Game result: " << std::to_string(game.board.result) << std::endl;
    return game.board.result;
}