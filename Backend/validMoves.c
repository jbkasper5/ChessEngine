#include "validMoves.h"

void findValidMoves(short pieces, char* piece, char* board){
    // printf("Board is %s\n", board);
    int64_t* boards = getBitboards(board);
    printf("White pawn board: \n");
    printBitboard(boards[0]);
    printf("White knight board: \n");
    printBitboard(boards[1]);
    printf("White bishop board: \n");
    printBitboard(boards[2]);
    printf("White rook board: \n");
    printBitboard(boards[3]);
    printf("White queen board: \n");
    printBitboard(boards[4]);
    printf("White king board: \n");
    printBitboard(boards[5]);
    printf("Black pawn board: \n");
    printBitboard(boards[6]);
    printf("Black knight board: \n");
    printBitboard(boards[7]);
    printf("Black bishop board: \n");
    printBitboard(boards[8]);
    printf("Black rook board: \n");
    printBitboard(boards[9]);
    printf("Black queen board: \n");
    printBitboard(boards[10]);
    printf("Black king board: \n");
    printBitboard(boards[11]);
    int64_t allBoard = 0;
    for(int i = 0; i < 12; ++i){
        allBoard = allBoard | boards[i];
    }
    printf("All board: \n");
    printBitboard(allBoard);
    free(boards);
}

int64_t computeBishopMoves(char* piece, int64_t* boards){
    return computeDiagonalMoves(piece, boards);
}

int64_t computeRookMoves(char* piece, int64_t* boards){
    return (computeHorizontalMoves(piece, boards) & computeVerticalMoves(piece, boards));
}

int64_t computePawnMoves(char* piece, int64_t* boards){
    return 0;
}

int64_t computeKingMoves(char* piece, int64_t* boards){
    return 0;
}

int64_t computeQueenMoves(char* piece, int64_t* boards){
    return (computeDiagonalMoves(piece, boards) & computeHorizontalMoves(piece, boards) & computeVerticalMoves(piece, boards));
}

int64_t computeKnightMoves(char* piece, int64_t* boards){
    return 0;
}

int64_t computeDiagonalMoves(char* piece, int64_t* boards){
    char startPos = ((atoi(piece + 3) - 1) * 8) + (104 - *(piece + 2));
    printf("Starting pos is %d\n", startPos);
    return 0;
}

int64_t computeVerticalMoves(char* piece, int64_t* boards){
    return 0;
}

int64_t computeHorizontalMoves(char* piece, int64_t* boards){
    return 0;
}

/*
    Flag: f
    Pieces: 32
    Sample piece: wpa2 wbc1
    Original white state board: bra8_bnb8_bbc8_bqd8_bke8_bbf8_bng8_brh8_bpa7_bpb7_bpc7_bpd7_bpe7_bpf7_bpg7_bph7_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_wpa2_wpb2_wpc2_wpd2_wpe2_wpf2_wpg2_wph2_wra1_wnb1_wbc1_wqd1_wke1_wbf1_wng1_wrh1
    Original black state board: wrh1_wng1_wbf1_wke1_wqd1_wbc1_wnb1_wra1_wph2_wpg2_wpf2_wpe2_wpd2_wpc2_wpb2_wpa2_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_bph7_bpg7_bpf7_bpe7_bpd7_bpc7_bpb7_bpa7_brh8_bng8_bbf8_bke8_bqd8_bbc8_bnb8_bra8
    Test board: bra8_bnb8_bbc8_bqd8_bke8_bbf8_bng8_brh8_bpa7_bpb7_bpc7_bpd7_bpe7_bpf7_0_bph7_0_0_0_0_0_0_bpg6_0_0_0_0_0_0_0_0_0_0_0_0_wpd4_0_0_0_0_0_0_wpc3_0_0_0_0_0_wpa2_wpb2_0_0_wpe2_wpf2_wpg2_wph2_wra1_wnb1_wbc1_wqd1_wke1_wbf1_wng1_wrh1 -> london and kings indian
*/