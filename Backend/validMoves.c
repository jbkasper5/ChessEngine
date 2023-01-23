#include "validMoves.h"

void findValidMoves(short pieces, char* piece, char* board){
    // printf("Board is %s\n", board);
    int64_t* boards = getBitboards(board);
    // printf("White pawn board: \n");
    // printBitboard(boards[0]);
    // printf("White knight board: \n");
    // printBitboard(boards[1]);
    // printf("White bishop board: \n");
    // printBitboard(boards[2]);
    // printf("White rook board: \n");
    // printBitboard(boards[3]);
    // printf("White queen board: \n");
    // printBitboard(boards[4]);
    // printf("White king board: \n");
    // printBitboard(boards[5]);
    // printf("Black pawn board: \n");
    // printBitboard(boards[6]);
    // printf("Black knight board: \n");
    // printBitboard(boards[7]);
    // printf("Black bishop board: \n");
    // printBitboard(boards[8]);
    // printf("Black rook board: \n");
    // printBitboard(boards[9]);
    // printf("Black queen board: \n");
    // printBitboard(boards[10]);
    // printf("Black king board: \n");
    // printBitboard(boards[11]);
    // int64_t allBoard = 0;
    // for(int i = 0; i < 12; ++i){
    //     allBoard = allBoard | boards[i];
    // }
    // printf("All board: \n");
    // printBitboard(allBoard);
    int64_t moves;
    if(*(piece + 1) == 'p'){
        // printf("Finding pawn moves...\n");
        moves = computePawnMoves(piece, boards);
    }else if(*(piece + 1) == 'n'){
        // printf("Finding knight moves...\n");
        moves = computeKnightMoves(piece, boards);
    }else if(*(piece + 1) == 'b'){
        // printf("Finding bishop moves...\n");
        moves = computeBishopMoves(piece, boards);
    }else if(*(piece + 1) == 'r'){
        // printf("Finding rook moves...\n");
        moves = computeRookMoves(piece, boards);
    }else if(*(piece + 1) == 'q'){
        // printf("Finding queen moves...\n");
        moves = computeQueenMoves(piece, boards);
    }else if(*(piece + 1) == 'k'){
        // printf("Finding king moves...\n");
        moves = computeKingMoves(piece, boards);
    }
    // printf("Found moves are: \n");
    // printBitboard(moves);
    free(boards);
    movesToPython(piece, moves);
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

int64_t computeBishopMoves(char* piece, int64_t* boards){
    return computeDiagonalMoves(piece, boards);
}

int64_t computeRookMoves(char* piece, int64_t* boards){
    return (computeHorizontalMoves(piece, boards) | computeVerticalMoves(piece, boards));
}

int64_t computePawnMoves(char* piece, int64_t* boards){
    char offset = (*piece == 'w') ? 0 : 6;
    char startPos = (*piece == 'w') ? ((*(piece + 3) - 48 - 1) * 8) + (104 - *(piece + 2)) : ((8 - (*(piece + 3) - 48)) * 8) + (-97 + *(piece + 2));
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < 6; ++i){
        playerBoard |= boards[i + offset];
        enemyBoard |= boards[11 - i - (offset)];
    }
    int64_t moves = 0;
    int64_t move = 1;
    if(*(piece + 4) == 48){ // not moved
        move = (int64_t) 1 << (startPos + 8);
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
    // check two diagonals for capturing:
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
        // printBitboard(move);
        if((move | enemyBoard) == enemyBoard){
            moves |= move;
        }
    }

    return moves;
}

int64_t computeKingMoves(char* piece, int64_t* boards){
    return 0;
}

int64_t computeQueenMoves(char* piece, int64_t* boards){
    return (computeDiagonalMoves(piece, boards) | computeHorizontalMoves(piece, boards) | computeVerticalMoves(piece, boards));
}

int64_t computeKnightMoves(char* piece, int64_t* boards){
    return 0;
}

int64_t computeDiagonalMoves(char* piece, int64_t* boards){
    char offset = (*piece == 'w') ? 0 : 6;
    unsigned char startPos = (*piece == 'w') ? ((*(piece + 3) - 48 - 1) * 8) + (104 - *(piece + 2)) : ((8 - (*(piece + 3) - 48)) * 8) + (-97 + *(piece + 2));
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

int64_t computeVerticalMoves(char* piece, int64_t* boards){
    char offset = (*piece == 'w') ? 0 : 6;
    unsigned char startPos = (*piece == 'w') ? ((*(piece + 3) - 48 - 1) * 8) + (104 - *(piece + 2)) : ((8 - (*(piece + 3) - 48)) * 8) + (-97 + *(piece + 2));
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
    while(pos > 0){
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

    return moves;
}

int64_t computeHorizontalMoves(char* piece, int64_t* boards){
    char offset = (*piece == 'w') ? 0 : 6;
    unsigned char startPos = (*piece == 'w') ? ((*(piece + 3) - 48 - 1) * 8) + (104 - *(piece + 2)) : ((8 - (*(piece + 3) - 48)) * 8) + (-97 + *(piece + 2));
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < 6; ++i){
        playerBoard |= boards[i + offset];
        enemyBoard |= boards[11 - i - (offset)];
    }
    int64_t moves = 0;
    int64_t move = 1;

    // everything right
    char pos = startPos + 1;
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

/*
    Flag: f
    Pieces: 32
    Sample piece: wpa20 wbc10
    Original white state board: bra8_bnb8_bbc8_bqd8_bke8_bbf8_bng8_brh8_bpa7_bpb7_bpc7_bpd7_bpe7_bpf7_bpg7_bph7_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_wpa2_wpb2_wpc2_wpd2_wpe2_wpf2_wpg2_wph2_wra1_wnb1_wbc1_wqd1_wke1_wbf1_wng1_wrh1
    Original black state board: wrh1_wng1_wbf1_wke1_wqd1_wbc1_wnb1_wra1_wph2_wpg2_wpf2_wpe2_wpd2_wpc2_wpb2_wpa2_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_bph7_bpg7_bpf7_bpe7_bpd7_bpc7_bpb7_bpa7_brh8_bng8_bbf8_bke8_bqd8_bbc8_bnb8_bra8
    Test board: bra8_bnb8_bbc8_bqd8_bke8_bbf8_bng8_brh8_bpa7_bpb7_bpc7_bpd7_bpe7_bpf7_0_bph7_0_0_0_0_0_0_bpg6_0_0_0_0_0_0_0_0_0_0_0_0_wpd4_0_0_0_0_0_0_wpc3_0_0_0_0_0_wpa2_wpb2_0_0_wpe2_wpf2_wpg2_wph2_wra1_wnb1_wbc1_wqd1_wke1_wbf1_wng1_wrh1 -> london and kings indian
    Other test board: wrh1_wng1_wbf1_wke1_wqd1_wbc1_wnb1_wra1_wph2_wpg2_wpf2_wpe2_wpd2_wpc2_wpb2_wpa2_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_bph7_bpg7_0_0_0_0_0_0_brh8_bng8_bbf8_bke8_bqd8_bbc8_bnb8_bra8
*/