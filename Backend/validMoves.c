#include "validMoves.h"

piece_t* playerPieces;
piece_t* enemyPieces;
int64_t playerBoard = 0;
int64_t enemyBoard = 0;
char numPlayer;
char numEnemy;
char playerColor;
char pieceIndex;

void findValidMoves(char* piece, char* board, short numPlayerPieces, short numEnemyPieces){
    playerColor = *piece;
    numPlayer = numPlayerPieces;
    numEnemy = numEnemyPieces;
    pieceIndex = getBitboards(board, piece, numPlayerPieces, numEnemyPieces);
    for(int i = 0; i < numPlayer; ++i){
        playerBoard |= playerPieces[i].board;
    }
    for(int i = 0; i < numEnemy; ++i){
        enemyBoard |= enemyPieces[i].board;
    }
    int64_t moves = getMoves(playerPieces[pieceIndex]);
    // printf("Found moves are: \n");
    // printBitboard(moves);
    free(playerPieces);
    free(enemyPieces);
    movesToPython(moves);
}

// void getEnemyMoves(char piece, char oldRank, char oldFile, char newRank, char newFile, char enemyColor){
//     enemyMoves = 0;
//     enemySearch = 1;
//     char* currPiece = str_board;
//     char* backup[5];
//     while(*currPiece != 0){
//         if(*(currPiece + 2) == oldRank && *(currPiece + 3) == oldFile){
//             *(currPiece)
//         }
//         if(*currPiece == enemyColor){
//             if(*(currPiece + 5) != 95){
//                 currPiece ++;
//                 continue;
//             }
//             enemyMoves |= getMoves(*currPiece, *(currPiece + 1), *(currPiece + 2), *(currPiece + 3), *(currPiece + 4));
//         }
//         currPiece++;
//     }
//     enemySearch = 0;
// }

void movesToPython(int64_t moves){
    char pos = 0;
    int64_t test = (int64_t) 1 << 63;
    while(moves){
        if(moves & 1){
            if (playerColor == 'w'){
                printf("%c%d,", 104 - (pos % 8), (pos / 8) + 1);
            }else{
                printf("%c%d,", 97 + (pos % 8), 8 - (pos / 8));
            }
        }
        moves >>= 1;
        if(pos == 0){
            int64_t mask = (int64_t) 1 << 63;
            moves &= ~(mask);
        }
        pos++;
    }
}

int64_t inCheck(){
    return 0;
}

int64_t getMoves(piece_t piece){
    int64_t moves;
    if(piece.piece == 'p'){
        moves = computePawnMoves(piece);
    }else if(piece.piece == 'n'){
        moves = computeKnightMoves(piece);
    }else if(piece.piece == 'b'){
        moves = computeBishopMoves(piece);
    }else if(piece.piece == 'r'){
        moves = computeRookMoves(piece);
    }else if(piece.piece == 'q'){
        moves = computeQueenMoves(piece);
    }else if(piece.piece == 'k'){
        moves = computeKingMoves(piece);
    }
    return moves;
}

int64_t computeBishopMoves(piece_t piece){
    char startPos = (piece.rank * 8) + piece.file;
    int64_t moves = 0;
    int64_t move = 1;

    // up to the left from the piece
    char pos = startPos + 9;
    while(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos += 9;
        }
    }

    // up to the right from the piece
    pos = startPos + 7;
    while(pos < 64 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos += 7;
        }
    }

    // down to the left from the piece
    pos = startPos - 7;
    while(pos >= 0 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos -= 7;
        }
    }

    // down to the right from the piece
    pos = startPos - 9;
    while(pos >= 0 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos -= 9;
        }
    }
    return moves;
}

int64_t computeRookMoves(piece_t piece){
    char startPos = (piece.rank * 8) + piece.file;
    int64_t moves = 0;
    int64_t move = 1;

    // everything above
    char pos = startPos + 8;
    while(pos < 64){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos += 8;
        }
    }

    // everything below
    pos = startPos - 8;
    while(pos >= 0){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos -= 8;
        }
    }

    // everything right
    pos = startPos + 1;
    while((pos % 8) > (startPos % 8)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos++;
        }
    }

    // everything left
    pos = startPos - 1;
    while((pos % 8) < (startPos % 8) && (pos >= 0)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos--;
        }
    }
    return moves;
}

int64_t computePawnMoves(piece_t piece){
    char startPos = (piece.rank * 8) + piece.file;
    int64_t moves = 0;
    int64_t move = 1;
    if(!piece.moved){ // not moved
        short shiftAmt = (startPos + 8);
        move = (int64_t) 1 << shiftAmt;
        if(((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard)){ // cant push into piece
            moves |= move;
            move = (int64_t) 1 << (startPos + 16);
            if((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard){ // can't push into piece
                moves |= move;
            }
        }
    }else{
        move = (int64_t) 1 << (startPos + 8);
        if((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard){ // cant push into piece
            moves |= move;
        }
    }
    // // check two diagonals for capturing:
    short pos = startPos + 7; // up left
    if((pos < 64 && ((pos % 8) < (startPos % 8)))){
        move = (int64_t) 1 << pos;
        if((move | enemyBoard) == enemyBoard){
            moves |= move;
        }
    }

    pos = startPos + 9;
    if(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | enemyBoard) == enemyBoard){
            moves |= move;
        }
    }
    return moves;
}

int64_t computeKingMoves(piece_t piece){
    return 0;
}

int64_t computeQueenMoves(piece_t piece){
    char startPos = (piece.rank * 8) + piece.file;
    int64_t moves = 0;
    int64_t move = 1;

    // up to the left from the piece
    char pos = startPos + 9;
    while(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos += 9;
        }
    }

    // up to the right from the piece
    pos = startPos + 7;
    while(pos < 64 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos += 7;
        }
    }

    // down to the left from the piece
    pos = startPos - 7;
    while(pos >= 0 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos -= 7;
        }
    }

    // down to the right from the piece
    pos = startPos - 9;
    while(pos >= 0 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos -= 9;
        }
    }

    // everything above
    pos = startPos + 8;
    while(pos < 64){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos += 8;
        }
    }

    // everything below
    pos = startPos - 8;
    while(pos >= 0){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos -= 8;
        }
    }

    // everything right
    pos = startPos + 1;
    while((pos % 8) > (startPos % 8)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos++;
        }
    }

    // everything left
    pos = startPos - 1;
    while((pos % 8) < (startPos % 8) && (pos >= 0)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            moves |= move;
            break;
        }else{
            moves |= move;
            pos--;
        }
    }
    return moves;
}

int64_t computeKnightMoves(piece_t piece){
    char startPos = (piece.rank * 8) + piece.file;
    int64_t moves = 0;
    int64_t move = 1;

    // 4 left positions
    short changes1[] = {17, 10, -6, -15};
    for(int i = 0; i < 4; ++i){
        short pos = startPos + changes1[i];
        if((pos < 64 && pos > 0) && ((pos % 8) > (startPos % 8))){
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard){
                moves |= move;
            }
        }
    }

    // 4 right positions
    int changes2[] = {15, 6, -10, -17};
    for(int i = 0; i < 4; ++i){
        short pos = startPos + changes2[i];
        if((pos < 64 && pos > 0) && ((pos % 8) < (startPos % 8))){
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard){
                moves |= move;
            }
        }
    }
    return moves;
}


/*
Default command -> pawn on a2 selected:
'f' 32 wpa20 bra80_bnb80_bbc80_bqd80_bke80_bbf80_bng80_brh80_bpa70_bpb70_bpc70_bpd70_bpe70_bpf70_bpg70_bph70_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_wpa20_wpb20_wpc20_wpd20_wpe20_wpf20_wpg20_wph20_wra10_wnb10_wbc10_wqd10_wke10_wbf10_wng10_wrh10

Black missing h pawn:
'f' 31 wpa20 bra80_bnb80_bbc80_bqd80_bke80_bbf80_bng80_brh80_bpa70_bpb70_bpc70_bpd70_bpe70_bpf70_bpg70_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_wpa20_wpb20_wpc20_wpd20_wpe20_wpf20_wpg20_wph20_wra10_wnb10_wbc10_wqd10_wke10_wbf10_wng10_wrh10
*/