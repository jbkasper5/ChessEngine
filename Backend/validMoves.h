#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bitboards.h"

void findValidMoves(short numPieces, char* piece, char* board);

void getEnemyMoves(char* board, char enemyColor);

void movesToPython(char* piece, int64_t moves);

int64_t getMoves(char color, char piece, char rank, char file, char moved);

int64_t computeBishopMoves(char color, char rank, char file, char moved);

int64_t computeRookMoves(char color, char rank, char file, char moved);

int64_t computePawnMoves(char color, char rank, char file, char moved);

int64_t computeKingMoves(char color, char rank, char file, char moved);

int64_t computeQueenMoves(char color, char rank, char file, char moved);

int64_t computeKnightMoves(char color, char rank, char file, char moved);

int64_t computeDiagonalMoves(char color, char rank, char file, char moved);

int64_t computeVerticalMoves(char color, char rank, char file, char moved);

int64_t computeHorizontalMoves(char color, char rank, char file, char moved);
