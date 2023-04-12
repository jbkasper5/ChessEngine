#include "makeMove.h"
#include "validMoves.h"

int main(int argc, char** argv){
    char numPlayer = atoi(*(argv + 2));
    char numEnemy = atoi(*(argv + 3));
    // fread(stdin, ,...)
    if(**(argv + 1) == 'f'){
        char* piece = argv[4];
        char* board = argv[5];
        findValidMoves(piece, board, numPlayer, numEnemy);
    }else if(**(argv + 1) == 'm'){
        char* player = argv[4];
        char* board = argv[5];
        // makeMove(num_pieces, board);
    }
    return 0;
}