//
// Created by exa on 7/5/18.
//

#include "engine.h"

BOARDSTATE Engine::search(BOARDSTATE board) {
  std::vector<BOARDSTATE> moves = legalmovesstate(board);
  if(moves.size() == 1){
    return moves[0];
  }
  std::unordered_map<BOARDSTATE, double> transtable;
  std::vector<BOARDSTATE> pv = search_method(board, *this, params.depth, transtable);
  transtable.clear();
  if(pv.size() > 1){
    return pv[1];
  } else {
    return pv[0];
  }
}

double Engine::eval(BOARDSTATE board) {
  return eval_method(board, params);
}
