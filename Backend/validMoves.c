#include "validMoves.h"

void findValidMoves(short pieces, char* piece, char* board){
    int64_t* boards = getBitboards(pieces, board);
    int64_t all_board = *boards;                // get the positions of all pieces on the board
    int64_t white_board = *(boards + 1);        // get the positions of only white pieces
    int64_t black_board = *(boards + 2);        // get the positions of only black pieces
    printBitboard(all_board);
    printf("\n");
    printBitboard(white_board);
    printf("\n");
    printBitboard(black_board);
    printf("\n");

    free(boards);
}

void printBitboard(int64_t board){
    for(int j = 0; j < 8; j++){
        for (int i = 0; i < 8; i++){
            short shift_amt = 63 - ((j * 8) + i);
            short bit = (board >> shift_amt) & 0x01;
            printf("%d ", bit);
        }
        printf("\n");
    }
}

int64_t* getBitboards(short pieces, char* board){
    int64_t* boards = (int64_t*)calloc(3, sizeof(int64_t)); // calloc(num_items, size)
    char* substr = board;
    short pieces_processed = 0;
    while(pieces_processed < pieces){
        if(*substr == 0x5F){ // 0x5f is _ in ascii
            pieces_processed++;
            substr = substr + 1;
            continue;
        }else{
            int64_t piece = 0x01; // start with a blank piece before shifting it into the proper location
            if(*substr == 0x77){ // 0x77 is w in ascii, piece is white
                
            }else{ // piece is black

            }
        }
    }
    return boards;
}

/*
    Original state board: wpa2_wpb2_wpc2_wpd2_wpe2_wpf2_wpg2_wph2_wra1_wrh1_wnb1_wng1_wbc1_wbf1_wke1_wqd1_bpa7_bpb7_bpc7_bpd7_bpe7_bpf7_bpg7_bph7_bra8_brh8_bnb8_bng8_bbc8_bbf8_bke8_bqd8_
    Sample piece: bpf7
    Command: ./engine 32 bpf7 wpa2_wpb2_wpc2_wpd2_wpe2_wpf2_wpg2_wph2_wra1_wrh1_wnb1_wng1_wbc1_wbf1_wke1_wqd1_bpa7_bpb7_bpc7_bpd7_bpe7_bpf7_bpg7_bph7_bra8_brh8_bnb8_bng8_bbc8_bbf8_bke8_bqd8_
*/