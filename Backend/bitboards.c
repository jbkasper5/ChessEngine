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
        printf("Current char is %c\n", *currChar);
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
            printf("Piece is %c\n", *(currChar + 1));
            if(*currChar == 0x77){ // 0x77 is w in ascii, piece is white
                if(*(currChar + 1) == 'p'){
                    boards[0]++;
                }else if(*(currChar + 1) == 'n'){
                    boards[1]++;
                }else if(*(currChar + 1) == 'b'){
                    boards[2]++;
                }else if(*(currChar + 1) == 'r'){
                    boards[3]++;
                }else if(*(currChar + 1) == 'q'){
                    boards[4]++;
                }else if(*(currChar + 1) == 'k'){
                    boards[5]++;
                }
            }else{ // piece is black
                if(*(currChar + 1) == 'p'){
                    boards[6]++;
                }else if(*(currChar + 1) == 'n'){
                    boards[7]++;
                }else if(*(currChar + 1) == 'b'){
                    boards[8]++;
                }else if(*(currChar + 1) == 'r'){
                    boards[9]++;
                }else if(*(currChar + 1) == 'q'){
                    boards[10]++;
                }else if(*(currChar + 1) == 'k'){
                    boards[11]++;
                }
            }
            currChar = currChar + 4;
        }
    }
    return boards;
}