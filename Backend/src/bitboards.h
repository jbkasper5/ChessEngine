#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct piece_s{
    int64_t board;
    char piece;
    char rank;
    char file;
    char moved;
} piece_t;

void printBitboard(int64_t board);

char getBitboards(char* board, char* piece, char numPlayerPieces, char numEnemyPieces);