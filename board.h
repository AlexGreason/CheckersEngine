//
// Created by exa on 6/29/18.
//

#ifndef CHECKERSENGINE_BOARD_H
#define CHECKERSENGINE_BOARD_H

#include <vector>
#include <string>
#include <array>

bool equalstates_void(void* val1, void* val2);

struct BOARDSTATE {
    int ply = 0; //starts at 0 before the first move and counts upwards
    char sidetomove = 0; //0=first player (black), 1=second player(red)
    char result = 0; //0=not terminal, 1=first player win, 2 = second player win, 3=draw
    char board[8][8]{}; //0=empty, 1=black piece, 2=black king, 3=red piece, 4=red king
    double staticeval = 0;
    std::vector<double> searcheval;
    int nocaptureply = 0;
    inline bool operator==(const BOARDSTATE& other) const {
        // bool comparison = result of comparing 'this' to 'other'
        return equalstates_void((void*)this, (void*)&other);
    }
};


char move(BOARDSTATE &board, char r, char c, bool right, bool up);
std::vector<char> hascaptures(BOARDSTATE board, char r, char c);
char* hasmoves(BOARDSTATE board, char r, char c);
std::vector<BOARDSTATE> legalmovesstate(BOARDSTATE &board);
bool equalstates(BOARDSTATE board1, BOARDSTATE board2);

struct MOVE {
    char startr;
    char startc;
    char endr;
    char endc;
};

std::string printstate(BOARDSTATE board);

class Board{
public:
    BOARDSTATE board;
    void startpos();
    std::string print();
    std::vector<BOARDSTATE> legalmoves();
    void testpos();

};

namespace std {
    template<typename T, size_t N>
    struct hash<array<T, N> >
    {
        typedef array<T, N> argument_type;
        typedef size_t result_type;

        result_type operator()(const argument_type& a) const
        {
            hash<T> hasher;
            result_type h = 0;
            for (result_type i = 0; i < N; ++i)
            {
                h = h * 31 + hasher(a[i]);
            }
            return h;
        }
    };


    template<>
    struct hash<BOARDSTATE> {
        inline size_t operator()(const BOARDSTATE& x) const {
            size_t value = 0;
            std::hash<std::array<char, 64>> boardhash;
            std::array<char, 64> boardarray{};
            for(char r = 0; r < 8; r++){
                for(char c = 0; c < 8; c++){
                    boardarray[8*r + c] = x.board[r][c];
                }
            }
            value ^= boardhash(boardarray);
            value ^= x.ply;
            return value;
        }
    };



}

#endif //CHECKERSENGINE_BOARD_H
