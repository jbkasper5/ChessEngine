#include "makeMove.h"
#include "validMoves.h"

int main(int argc, char** argv){
    /*
        Argument index setup:
            0. executable name, ignore
            1. number of pieces on the board
            2. either piece (find moves) or board(make move)
            3. board (if find moves)
    */
    short num_pieces = atoi(argv[1]);
    if(argc == 4){
        char* piece = argv[2];
        char* board = argv[3];
        findValidMoves(num_pieces, piece, board);
    }else{
        char* board = argv[2];
        makeMove(num_pieces, board);
    }
}