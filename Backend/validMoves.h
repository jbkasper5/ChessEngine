#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void findValidMoves(short pieces, char* piece, char* board);

void printBitboard(int64_t board);

int64_t* getBitboards(short pieces, char* board);