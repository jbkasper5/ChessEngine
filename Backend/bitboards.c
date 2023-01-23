#include "bitboards.h"

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

int64_t* getBitboards(char* board){
    int64_t* boards = (int64_t*)calloc(12, sizeof(int64_t)); // calloc(num_items, size)
    /*
        White:
            P: 0
            N: 1
            B: 2
            R: 3
            Q: 4
            K: 5
        Black:
            P: 6
            N: 7
            B: 8
            R: 9
            Q: 10
            K: 11
    */
    char* currChar = board;
    while(*currChar != 0){
        if(*currChar == 0x5F){ // 0x5f is _ in ascii, 0x30 is 0 in ascii
            currChar++; // skip underscores and 0s
            continue;
        }else if(*currChar == 0x30){
            for(int i = 0; i < 12; ++i){
                boards[i] <<= 1;
            }
            currChar++;
        }else{
            for(int i = 0; i < 12; ++i){
                boards[i] <<= 1;
            }
            char offset = 0;
            if(*currChar == 98){ // 98 is b in ascii, piece is black
                offset = 6;
            }
            if(*(currChar + 1) == 'p'){
                boards[0 + offset]++;
            }else if(*(currChar + 1) == 'n'){
                boards[1 + offset]++;
            }else if(*(currChar + 1) == 'b'){
                boards[2 + offset]++;
            }else if(*(currChar + 1) == 'r'){
                boards[3 + offset]++;
            }else if(*(currChar + 1) == 'q'){
                boards[4 + offset]++;
            }else if(*(currChar + 1) == 'k'){
                boards[5 + offset]++;
            }
            currChar = currChar + 5;
        }
    }
    return boards;
}