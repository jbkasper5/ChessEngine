#include "makeMove.h"
#include "validMoves.h"

int main(int argc, char** argv){
    short num_pieces = atoi(*(argv + 2));
    if(**(argv + 1) == 102){
        char* piece = argv[3];
        char* board = argv[4];
        findValidMoves(num_pieces, piece, board);
    }else if(**(argv + 1) == 109){
        char* player = argv[3];
        char* board = argv[4];
        makeMove(num_pieces, board);
    }
    return 0;
}