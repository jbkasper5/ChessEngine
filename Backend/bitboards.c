#include "bitboards.h"

extern piece_t* playerPieces;
extern piece_t* enemyPieces;


void printBitboard(int64_t board){
    for(int j = 0; j < 8; j++){
        for (int i = 0; i < 8; i++){
            short shift_amt = 63 - ((j * 8) + i);
            short bit = (board >> shift_amt) & 0x01;
            printf("%d ", bit);
        }
        printf("\n");
    }
    printf("\n");
}

char getBitboards(char* board, char* piece, char numPlayerPieces, char numEnemyPieces){
    playerPieces = (piece_t*)calloc(numPlayerPieces, sizeof(piece_t)); // calloc(num_items, size)
    enemyPieces = (piece_t*)calloc(numEnemyPieces, sizeof(piece_t));
    char* currChar = board;
    char ppp = 0;
    char epp = 0;
    char pieceIndex = 0;
    while(*currChar != 0){
        if(*currChar == 0x5F){ // 0x5f is _ in ascii, 0x30 is 0 in ascii
            currChar++; // skip underscores
            continue;
        }else{
            if(*currChar == *piece){
                playerPieces[ppp].piece = *(currChar + 1);
                playerPieces[ppp].file = 'h' - *(currChar + 2);
                playerPieces[ppp].rank = -'1' + *(currChar + 3);
                playerPieces[ppp].moved = -'0' + *(currChar + 4);
                playerPieces[ppp].board = (int64_t) 1 << ((playerPieces[ppp].rank * 8) + playerPieces[ppp].file);
                if(((*(currChar + 2)) == (*(piece + 2))) && ((*(currChar + 3)) == (*(piece + 3)))){
                    pieceIndex = ppp;
                }
                ppp++;
            }else{
                enemyPieces[epp].piece = *(currChar + 1);
                enemyPieces[epp].rank = 'h' - *(currChar + 2);
                enemyPieces[epp].file = -'1' + *(currChar + 3);
                enemyPieces[epp].moved = -'0' + *(currChar + 4);
                enemyPieces[epp].board = (int64_t) 1 << ((enemyPieces[epp].file * 8) + enemyPieces[epp].rank);
                epp++;
            }
            currChar += 5;
        }
    }
    return pieceIndex;
}