//
// Created by exa on 6/29/18.
//

#include <string>
#include <iostream>
#include "board.h"

std::string printstate(BOARDSTATE board){
    char pieces[5] = {' ', 'b', 'B', 'r', 'R'};
    std::string side[2]{"black", "red"};
    //r=red piece, R=red king, b=black piece, B=black king
    std::string result;
    result += side[board.sidetomove];
    result += " to move\n";
    result += "-----------------\n";
    for (int r = 7; r >= 0; r--) {
        result += "|";
        for (int c = 0; c < 8; c++) {
            result += pieces[board.board[r][c]];
            result += "|";
        }
        result += "\n";

    }
    result += "-----------------\n";
    return result;
}

void Board::startpos() {
    char startpos[8][8] = {{1, 0, 1, 0, 1, 0, 1, 0},
                           {0, 1, 0, 1, 0, 1, 0, 1},
                           {1, 0, 1, 0, 1, 0, 1, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 3, 0, 3, 0, 3, 0, 3},
                           {3, 0, 3, 0, 3, 0, 3, 0},
                           {0, 3, 0, 3, 0, 3, 0, 3}};

    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            board.board[r][c] = startpos[r][c];
        }
    }
}

void Board::testpos() {
    char testpos[8][8] =  {{1, 0, 1, 0, 1, 0, 1, 0},
                           {0, 1, 0, 1, 0, 1, 0, 1},
                           {0, 0, 1, 0, 1, 0, 1, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 3, 0, 1, 0, 3, 0, 3},
                           {3, 0, 3, 0, 3, 0, 3, 0},
                           {0, 3, 0, 3, 0, 3, 0, 3}};

    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            board.board[r][c] = testpos[r][c];
        }
    }
}

BOARDSTATE copy(BOARDSTATE board){
    BOARDSTATE result{};
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            result.board[r][c] = board.board[r][c];
        }
    }
    result.ply = board.ply;
    result.sidetomove = board.sidetomove;
    result.result = board.result;
    return result;
}

char* coords(char r, char c, bool up, bool right, bool capture){
    char* result;
    result = new char[2];
    if(!capture){
        result[0] = r - 1 + 2 * up;
        result[1] = c - 1 + 2 * right;
    } else {
        result[0] = r - 2 + 4 * up;
        result[1] = c - 2 + 4 * right;
    }
    return result;
}

char* coords(char r, char c, int i, bool capture){
    bool right = !!(i%2);
    bool up = !(i/2);
    char* result;
    result = new char[2];
    if(!capture){
        result[0] = r - 1 + 2 * up;
        result[1] = c - 1 + 2 * right;
    } else {
        result[0] = r - 2 + 4 * up;
        result[1] = c - 2 + 4 * right;
    }
    return result;
}

bool setinbounds(BOARDSTATE &board, char* coords, char val){
    char r = coords[0];
    char c = coords[1];
    if(r < 0 || r >= 8 || c < 0 || c >= 8){
        return false;
    }
    board.board[r][c] = val;
    return true;
}

char getinbounds(char board[8][8], char* coords){
    char r = coords[0];
    char c = coords[1];
    if(r < 8 && r >= 0 && c < 8 && c >= 0){
        return board[r][c];
    } else {
        return 5;
    }
}

char move(BOARDSTATE &board, char* inp_coords, bool up, bool right){
    // doesn't do bounds checking. try/except and have a return value for if successful?
    char r = inp_coords[0];
    char c = inp_coords[1];
    char promotions[6]{0, 2, 2, 4, 4, 5};
    char starttype = board.board[r][c];
    char endtype = board.board[r][c];
    board.ply++;
    char* coords_tmp = coords(r, c, up, right, false);
    char* coords_cap = coords(r, c, up, right, true);
    if(getinbounds(board.board, coords_tmp) == 0) {
        if (coords_tmp[0] == 7 * up) {
            setinbounds(board, coords_tmp, promotions[board.board[r][c]]);
            endtype = promotions[board.board[r][c]];
        } else {
            setinbounds(board, coords_tmp, board.board[r][c]);
        }
    } else {

        if (coords_cap[0] == 7 * up) {
            setinbounds(board, coords_cap, promotions[board.board[r][c]]);
            endtype = promotions[board.board[r][c]];
        } else {
            setinbounds(board, coords_cap, board.board[r][c]);
        }
        setinbounds(board, coords_tmp, 0);
    }
    board.board[r][c] = 0;
    return starttype != endtype; //return 1 if promoted
}




char* hascaptures(BOARDSTATE board, char r, char c){
    if(r < 0 || r >= 8 || c < 0 || c >= 8){
        int blug = 3;
    }
    //check forward two ("forwards" depends on piece type), then if king check backwards two
    char directions[6] = {0, 1, 1, -1, -1, 0};
    char type[6] = {-1, 1, 2, 1, 2, -1};
    char offsets[3] = {2, 0, 0};
    char val = getinbounds(board.board, new char[2]{r, c});
    char* captures; // up left, up right, back left, back right
    captures = new char[4]{0, 0, 0, 0};
    char direction = directions[val];

    if(type[val] != -1 && direction != 0){ //piece, check only forwards
        char offset = offsets[direction + 1];
        for(char h = -1; h < 2; h += 2){
            char target = getinbounds(board.board, coords(r, c, direction > 0, h > 0, false));
            if(directions[target] + direction == 0){
                char space = getinbounds(board.board, coords(r, c, direction > 0, h > 0, true));
                if(space == 0){
                    captures[(h + 1)/2 + offset] = 1;
                }
            }
        }
    }
    if(type[val] == 2 && direction != 0) {
        direction = -direction;
        char offset = offsets[direction + 1];
        for(char h = -1; h < 2; h += 2){
            char target = getinbounds(board.board, coords(r, c, direction > 0, h > 0, false));
            if(directions[target] - direction == 0){
                char space = getinbounds(board.board, coords(r, c, direction > 0, h > 0, true));
                if(space == 0){
                    captures[(h + 1)/2 + offset] = 1;
                }
            }
        }
    }
    return captures;
}

char* hasmoves(BOARDSTATE board, char r, char c){
    if(r < 0 || r >= 8 || c < 0 || c >= 8){
        int blug = 3;
    }
    char directions[6] = {0, 1, 1, -1, -1, 0};
    char type[6] = {-1, 1, 2, 1, 2, -1};
    char offsets[3] = {2, 0, 0};
    char val = getinbounds(board.board, new char[2]{r, c});
    char* moves; // up left, up right, back left, back right
    moves = new char[4]{0, 0, 0, 0};
    char direction = directions[val];

    if(type[val] != -1 && direction != 0){ //piece, check only forwards
        char offset = offsets[direction + 1];
        for(char h = -1; h < 2; h += 2){
            char space = getinbounds(board.board, coords(r, c, direction > 0, h > 0, false));
            if(space == 0){
                moves[(h + 1)/2 + offset] = 1; }
        }
    }
    if(type[val] == 2 && direction != 0) {
        direction = -direction;
        char offset = offsets[direction + 1];
        for(char h = -1; h < 2; h += 2){
            char space = getinbounds(board.board, coords(r, c, direction > 0, h > 0, false));
            if(space == 0){
                    moves[(h + 1)/2 + offset] = 1;
            }
        }
    }
    return moves;
}

std::vector<BOARDSTATE> capturetree(BOARDSTATE board, char* inp_coords){
    char r = inp_coords[0];
    char c = inp_coords[1];
    if(r < 0 || r >= 8 || c < 0 || c >= 8){
        int blug = 3;
    }
    std::vector<BOARDSTATE> result;
    char rank[6]{0, 1, 2, 1, 2, 0};
    char* captures;
    captures = hascaptures(board, r, c);
    bool anycaptures = false;
    for(int i = 0; i < 4; i++){
        anycaptures |= captures[i];
    }
    if(!anycaptures){
        result.push_back(board);
        return result;
    } else {
        for(int i = 0; i < 4; i++){
            if(captures[i]) {
                BOARDSTATE tmp = copy(board);
                bool right = !!(i % 2);
                bool up = !(i / 2);
                bool promoted = move(tmp, new char[2]{r, c}, up, right);
                tmp.ply = board.ply;
                if (!promoted) {
                    std::vector<BOARDSTATE> tree = capturetree(tmp, coords(r, c, i, true));
                    for (BOARDSTATE b :tree) {
                        result.push_back(b);
                    }
                } else {
                    result.push_back(tmp);
                }
            }
        }
    }
    return result;
}

bool anycaptures(BOARDSTATE board){
    int side[6] = {-1, 0, 0, 1, 1, -1};
    char* captures;
    bool capture = false;
    for(char r = 0; r < 8; r++) {
        for (char c = 0; c < 8; c++) {
            char val = board.board[r][c];
            if (side[val] == board.sidetomove) {
                captures = hascaptures(board, r, c);
                for(int i = 0; i < 4; i++){
                    capture |= captures[i];
                }
            }
        }
    }
    return capture;
}

std::vector<BOARDSTATE> piecemoves(BOARDSTATE board, char r, char c, bool onlycaptures){
    std::vector<BOARDSTATE> result;
    char* captures;
    captures = hascaptures(board, r, c);
    if(!onlycaptures){
        char * moves;
        moves = hasmoves(board, r, c);
        for(int i = 0; i < 4; i++){
            if(moves[i]){
                BOARDSTATE tmp = copy(board);
                bool right = !!(i % 2);
                bool up = !(i / 2);
                move(tmp, new char[2]{r, c}, up, right);
                tmp.sidetomove = !board.sidetomove;
                result.push_back(tmp);
            }
        }
    } else {
        for(int i = 0; i < 4; i++){
            if(captures[i]) {
                BOARDSTATE tmp = copy(board);
                bool right = !!(i % 2);
                bool up = !(i / 2);
                bool promoted = move(tmp, new char[2]{r, c}, up, right);
                tmp.ply = board.ply;
                if (!promoted) {
                    std::vector<BOARDSTATE> tree = capturetree(tmp, coords(r, c, i, true));
                    for (BOARDSTATE b :tree) {
                        b.sidetomove = !b.sidetomove;
                        result.push_back(b);
                    }
                } else {
                    tmp.sidetomove = !tmp.sidetomove;
                    result.push_back(tmp);
                }
            }
        }
    }
    return result;
}


std::vector<BOARDSTATE> legalmovesstate(BOARDSTATE board) {
    std::vector<BOARDSTATE> moves;
    int side[6] = {-1, 0, 0, 1, 1, -1};
    bool onlycaptures = anycaptures(board);
    for(char r = 0; r < 8; r++){
        for(char c = 0; c < 8; c++){
            char val = board.board[r][c];
            if(side[val] == board.sidetomove){
                std::vector<BOARDSTATE> piece = piecemoves(board, r, c, onlycaptures);
                for(BOARDSTATE b: piece){
                    moves.push_back(b);
                }
            }
        }
    }

    return moves;
}

std::vector<BOARDSTATE> Board::legalmoves(){
    return legalmovesstate(board);
}

std::string Board::print() {
    return printstate(board);
}

char* materiel(BOARDSTATE b){
    int red;
    int black;

}
