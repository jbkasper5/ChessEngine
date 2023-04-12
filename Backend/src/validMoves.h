#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bitboards.h"

void findValidMoves(char* piece, char* board, short numPlayerPieces, short numEnemyPieces);

int64_t getEnemyMoves(char rank, char file);

void swapReferences();

void movesToPython(int64_t moves);

int64_t getMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard);

int64_t computeBishopMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard);

int64_t computeRookMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard);

int64_t computePawnMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard);

int64_t computeKingMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard);

int64_t computeQueenMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard);

int64_t computeKnightMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard);