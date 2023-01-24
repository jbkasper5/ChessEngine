#include "validMoves.h"

typedef struct piece_s{
    int64_t board;
    char rank;
    char file;
    char moved;
    char color;
} piece_t;

int64_t* boards;
int64_t enemyMoves = 0;
short enemySearch = 0;
char* str_board;

void findValidMoves(short numPieces, char* piece, char* board){
    str_board = board;
    boards = getBitboards(board);
    int64_t moves = getMoves(*piece, *(piece + 1), *(piece + 2), *(piece + 3), *(piece + 4));
    free(boards);
    movesToPython(piece, moves);
}

void getEnemyMoves(char piece, char oldRank, char oldFile, char newRank, char newFile, char enemyColor){
    enemyMoves = 0;
    enemySearch = 1;
    char* currPiece = str_board;
    char* backup[5];
    while(*currPiece != 0){
        if(*(currPiece + 2) == oldRank && *(currPiece + 3) == oldFile){
            *(currPiece)
        }
        if(*currPiece == enemyColor){
            if(*(currPiece + 5) != 95){
                currPiece ++;
                continue;
            }
            enemyMoves |= getMoves(*currPiece, *(currPiece + 1), *(currPiece + 2), *(currPiece + 3), *(currPiece + 4));
        }
        currPiece++;
    }
    enemySearch = 0;
}

void movesToPython(char* piece, int64_t moves){
    char pos = 0;
    int64_t test = (int64_t) 1 << 63;
    while(moves){
        if(moves & 1){
            if (*piece == 'w'){
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

int64_t getMoves(char color, char piece, char rank, char file, char moved){
    int64_t moves;
    if(piece == 'p'){
        moves = computePawnMoves(color, rank, file, moved);
    }else if(piece == 'n'){
        moves = computeKnightMoves(color, rank, file, moved);
    }else if(piece == 'b'){
        moves = computeBishopMoves(color, rank, file, moved);
    }else if(piece  == 'r'){
        moves = computeRookMoves(color, rank, file, moved);
    }else if(piece == 'q'){
        moves = computeQueenMoves(color, rank, file, moved);
    }else if(piece == 'k'){
        moves = computeKingMoves(color, rank, file, moved);
    }
    return moves;
}

int64_t computeBishopMoves(char color, char rank, char file, char moved){
    char offset = (color == 'w') ? 0 : 6;
    char startPos = (color == 'w') ? ((file - 48 - 1) * 8) + (104 - rank) : ((8 - (file - 48)) * 8) + (-97 + rank);
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < 6; ++i){
        playerBoard |= boards[i + offset];
        enemyBoard |= boards[11 - i - (offset)];
    }
    int64_t moves = 0;
    int64_t move = 1;

    // up to the left from the piece
    char pos = startPos + 9;
    while(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
        if((move | playerBoard) == playerBoard){
            break;
        }else if((move | enemyBoard) == enemyBoard){
            // edit bishop board to reflect new move
            if(getEnemyMoves())
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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

int64_t computeRookMoves(char color, char rank, char file, char moved){
    char offset = (color == 'w') ? 0 : 6;
    char startPos = (color == 'w') ? ((file - 48 - 1) * 8) + (104 - rank) : ((8 - (file - 48)) * 8) + (-97 + rank);
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < 6; ++i){
        playerBoard |= boards[i + offset];
        enemyBoard |= boards[11 - i - (offset)];
    }
    int64_t moves = 0;
    int64_t move = 1;

    // everything above
    char pos = startPos + 8;
    while(pos < 64){
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
    while(pos > 0){
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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

int64_t computePawnMoves(char color, char rank, char file, char moved){
    char offset = (color == 'w') ? 0 : 6;
    char startPos = (color == 'w') ? ((file - 48 - 1) * 8) + (104 - rank) : ((8 - (file - 48)) * 8) + (-97 + rank);
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < 6; ++i){
        playerBoard |= boards[i + offset];
        enemyBoard |= boards[11 - i - (offset)];
    }
    int64_t moves = 0;
    int64_t move = 1;
    if(moved == 48){ // not moved
        short shiftAmt = (enemySearch == 0 ? (startPos + 8) : 63 - (startPos + 8));
        move = (int64_t) 1 << shiftAmt;
        if(((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard)){ // cant push into piece
            moves |= move;
            move = (int64_t) 1 << (enemySearch == 0 ? (startPos + 16) : 63 - (startPos + 16));
            if((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard){ // can't push into piece
                moves |= move;
            }
        }
    }else{
        move = (int64_t) 1 << (enemySearch == 0 ? (startPos + 8) : 63 - (startPos + 8));
        if((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard){ // cant push into piece
            moves |= move;
        }
    }
    // check two diagonals for capturing:
    short pos = startPos + 7; // up left
    if((pos < 64 && ((pos % 8) < (startPos % 8)))){
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
        if((move | enemyBoard) == enemyBoard){
            moves |= move;
        }
    }

    pos = startPos + 9;
    if(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
        if((move | enemyBoard) == enemyBoard){
            moves |= move;
        }
    }

    return moves;
}

int64_t computeKingMoves(char color, char rank, char file, char moved){
    return 0;
}

int64_t computeQueenMoves(char color, char rank, char file, char moved){
    char offset = (color == 'w') ? 0 : 6;
    char startPos = (color == 'w') ? ((file - 48 - 1) * 8) + (104 - rank) : ((8 - (file - 48)) * 8) + (-97 + rank);
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < 6; ++i){
        playerBoard |= boards[i + offset];
        enemyBoard |= boards[11 - i - (offset)];
    }
    int64_t moves = 0;
    int64_t move = 1;

    // up to the left from the piece
    char pos = startPos + 9;
    while(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
    while(pos > 0){
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
        move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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

int64_t computeKnightMoves(char color, char rank, char file, char moved){
    char offset = (color == 'w') ? 0 : 6;
    char startPos = (color == 'w') ? ((file - 48 - 1) * 8) + (104 - rank) : ((8 - (file - 48)) * 8) + (-97 + rank);
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < 6; ++i){
        playerBoard |= boards[i + offset];
        enemyBoard |= boards[11 - i - (offset)];
    }
    int64_t moves = 0;
    int64_t move = 1;

    // 4 left positions
    short changes1[] = {17, 10, -6, -15};
    for(int i = 0; i < 4; ++i){
        short pos = startPos + changes1[i];
        if((pos < 64 && pos > 0) && ((pos % 8) > (startPos % 8))){
            move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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
            move = (int64_t) 1 << (enemySearch == 0 ? pos : 63 - pos);
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