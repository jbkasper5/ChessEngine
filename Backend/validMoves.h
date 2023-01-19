#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bitboards.h"

void findValidMoves(short pieces, char* piece, char* board);

int64_t computeBishopMoves(char* piece, int64_t* boards);

int64_t computeRookMoves(char* piece, int64_t* boards);

int64_t computePawnMoves(char* piece, int64_t* boards);

int64_t computeKingMoves(char* piece, int64_t* boards);

int64_t computeQueenMoves(char* piece, int64_t* boards);

int64_t computeKnightMoves(char* piece, int64_t* boards);

int64_t computeDiagonalMoves(char* piece, int64_t* boards);

int64_t computeVerticalMoves(char* piece, int64_t* boards);

int64_t computeHorizontalMoves(char* piece, int64_t* boards);
