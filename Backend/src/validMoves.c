#include "validMoves.h"

piece_t* playerPieces;
piece_t* enemyPieces;
char numPlayer;
char numEnemy;
char enemySearch;
char playerColor;
char pieceIndex;
char playerKingIndex;

void findValidMoves(char* piece, char* board, short numPlayerPieces, short numEnemyPieces){
    playerColor = *piece;
    numPlayer = numPlayerPieces;
    numEnemy = numEnemyPieces;
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    pieceIndex = getBitboards(board, piece, numPlayerPieces, numEnemyPieces);
    for(int i = 0; i < numPlayer; ++i){
        playerBoard |= playerPieces[i].board;
    }
    for(int i = 0; i < numEnemy; ++i){
        enemyBoard |= enemyPieces[i].board;
    }
    int64_t moves = getMoves(&playerPieces[pieceIndex], playerBoard, enemyBoard);
    free(playerPieces);
    free(enemyPieces);
    movesToPython(moves);
}

int64_t getEnemyMoves(char rank, char file){
    enemySearch = 1;
    /*
        Enemy search will be conducted exactly as a standard search, only using logic to inverse the order of the bits
        The playerColor and enemyColor will be swapped
        The enemySearch flag will be set to block recursion
        The playerBoard will need to be recalculated
    */
    // switch to enemy POV
    swapReferences();
    int64_t playerBoard = 0;
    int64_t enemyBoard = 0;
    for(int i = 0; i < numPlayer; ++i){
        if(playerPieces[i].rank == rank && playerPieces[i].file == file){
            continue;
        }else{
            playerBoard |= playerPieces[i].board; // effect of capturing the piece
        }
    }
    for(int i = 0; i < numEnemy; ++i){
        enemyBoard |= enemyPieces[i].board;
    }
    int64_t moves = 0;
    for(int i = 0; i < numPlayer; ++i){
        if(playerPieces[i].rank == rank && playerPieces[i].file == file){
            continue;
        }else{
            moves |= getMoves(&playerPieces[i], playerBoard, enemyBoard);
        }
    }
    // switch back to regular POV
    swapReferences();
    enemySearch = 0;
    return moves;
}

void swapReferences(){
    playerColor = (playerColor == 'w' ? 'b' : 'w');
    piece_t* temp1 = playerPieces;
    playerPieces = enemyPieces;
    enemyPieces = temp1;
    short temp2 = numPlayer;
    numPlayer = numEnemy;
    numEnemy = temp2;
}

void movesToPython(int64_t moves){
    char pos = 0;
    int64_t test = (int64_t) 1 << 63;
    while(moves){
        if(moves & 1){
            printf("%c%d,", 104 - (pos % 8), (pos / 8) + 1);
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

int64_t getMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard){
    int64_t moves;
    if(piece->piece == 'p'){
        moves = computePawnMoves(piece, playerBoard, enemyBoard);
    }else if(piece->piece == 'n'){
        moves = computeKnightMoves(piece, playerBoard, enemyBoard);
    }else if(piece->piece == 'b'){
        moves = computeBishopMoves(piece, playerBoard, enemyBoard);
    }else if(piece->piece == 'r'){
        moves = computeRookMoves(piece, playerBoard, enemyBoard);
    }else if(piece->piece == 'q'){
        moves = computeQueenMoves(piece, playerBoard, enemyBoard);
    }else if(piece->piece == 'k'){
        moves = computeKingMoves(piece, playerBoard, enemyBoard);
    }
    return moves;
}

int64_t computeBishopMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard){
    char startPos = (piece->rank * 8) + piece->file;
    int64_t moves = 0;
    int64_t move = 1;
    int64_t oldState = piece->board;

    // up to the left from the piece
    char pos = startPos + 9;
    while(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos += 9;
        }
    }

    // up to the right from the piece
    pos = startPos + 7;
    while(pos < 64 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos += 7;
        }
    }

    // down to the left from the piece
    pos = startPos - 7;
    while(pos >= 0 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos -= 7;
        }
    }

    // down to the right from the piece
    pos = startPos - 9;
    while(pos >= 0 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos -= 9;
        }
    }
    piece->board = oldState;
    return moves;
}

int64_t computeRookMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard){
    char startPos = (piece->rank * 8) + piece->file;
    int64_t moves = 0;
    int64_t move = 1;
    int64_t oldState = piece->board;

    // everything above
    char pos = startPos + 8;
    while(pos < 64){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos += 8;
        }
    }

    // everything below
    pos = startPos - 8;
    while(pos >= 0){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos -= 8;
        }
    }

    // everything right
    pos = startPos + 1;
    while((pos % 8) > (startPos % 8)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos++;
        }
    }

    // everything left
    pos = startPos - 1;
    while((pos % 8) < (startPos % 8) && (pos >= 0)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos--;
        }
    }
    piece->board = oldState;
    return moves;
}

int64_t computePawnMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard){
    char startPos = (piece->rank * 8) + piece->file;
    int64_t moves = 0;
    int64_t move = 1;
    int64_t oldState = piece->board;
    if(!enemySearch){ // ignore checking the forward moves if we're looking for enemy attacks
        if(!piece->moved){ // not moved
            char pos = (playerColor == 'w' ? (startPos + 8) : (startPos - 8));
            move = (int64_t) 1 << pos;
            if(((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard)){ // cant push into piece
                if(enemySearch){
                    moves |= move;
                }else{
                    piece->board = move;
                    if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                        moves |= move;
                    }
                    piece->board = oldState;
                }
                pos = (playerColor == 'w' ? (startPos + 16) : (startPos - 16));
                move = (int64_t) 1 << pos;
                if((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard){ // can't push into piece
                    if(enemySearch){
                        moves |= move;
                    }else{
                        piece->board = move;
                        if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                            moves |= move;
                        }
                        piece->board = oldState;
                    }
                }
            }
        }else{
            char pos = (playerColor == 'w' ? (startPos + 8) : (startPos - 8));
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard && (move | enemyBoard) != enemyBoard){ // cant push into piece
                if(enemySearch){
                    moves |= move;
                }else{
                    piece->board = move;
                    if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                        moves |= move;
                    }
                    piece->board = oldState;
                }
            }
        }
    }
    // // check two diagonals for capturing:
    short pos = (playerColor == 'w' ? (startPos + 7) : (startPos - 9)); // up left
    if((pos < 64 && ((pos % 8) < (startPos % 8)))){
        move = (int64_t) 1 << pos;
        if((move | enemyBoard) == enemyBoard || enemySearch){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
        }
    }

    pos = (playerColor == 'w' ? (startPos + 9) : (startPos - 7));
    if(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | enemyBoard) == enemyBoard || enemySearch){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
        }
    }

    piece->board = oldState;
    return moves;
}

int64_t computeKingMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard){
    char startPos = (piece->rank * 8) + piece->file;
    int64_t moves = 0;
    int64_t move = 1;
    int64_t oldState = piece->board;

    // king left moves
    short leftMoves[] = {9, 1, -7};
    for(int i = 0; i < 3; ++i){
        short pos = startPos + leftMoves[i];
        if((pos < 64 && pos >= 0) && ((pos % 8) > (startPos % 8))){
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard){
                if(enemySearch){
                    moves |= move;
                }else{
                    piece->board = move;
                    if(!(getEnemyMoves(pos / 8, pos % 8) & move)){ // EM & move == 1 -> intersection between enemy sight and new king spot
                        moves |= move;
                    }
                    piece->board = oldState;
                }
            }else{
                if(enemySearch){
                    moves |= move;
                }else{
                    continue;
                }
            }
        }
    }

    // king right moves
    short rightMoves[] = {7, -1, -9};
    for(int i = 0; i < 3; ++i){
        short pos = startPos + rightMoves[i];
        if((pos < 64 && pos >= 0) && ((pos % 8) < (startPos % 8))){
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard){
                if(enemySearch){
                    moves |= move;
                }else{
                    piece->board = move;
                    if(!(getEnemyMoves(pos / 8, pos % 8) & move)){ // EM & move == 1 -> intersection between enemy sight and new king spot
                        moves |= move;
                    }
                    piece->board = oldState;
                }
            }else{
                if(enemySearch){
                    moves |= move;
                }else{
                    continue;
                }
            }
        }
    }

    // king vertical moves
    short verticalMoves[] =  {8, -8};
    for(int i = 0; i < 2; ++i){
        short pos = startPos + verticalMoves[i];
        if((pos < 64 && pos >= 0)){
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard){
                if(enemySearch){
                    moves |= move;
                }else{
                    piece->board = move;
                    if(!(getEnemyMoves(pos / 8, pos % 8) & move)){ // EM & move == 1 -> intersection between enemy sight and new king spot
                        moves |= move;
                    }
                    piece->board = oldState;
                }
            }else{
                if(enemySearch){
                    moves |= move;
                }else{
                    continue;
                }
            }
        }
    }
    // check for king side castling
    if(!piece->moved && !enemySearch && !(getEnemyMoves(startPos / 8, startPos % 8) & piece->board)){
        char invalid = 0;
        for(int i = 2; i >= 1; --i){
            int64_t move = (int64_t) 1 << (startPos - i);
            if((move | playerBoard) == playerBoard){
                invalid = 1;
                break;
            }else{
                piece->board = move;
                if((getEnemyMoves(i / 8, i % 8) & move)){
                    invalid = 1;
                }
                piece->board = oldState;
            }
        }
        char idx = 0;
        for(int i = 0; i < numPlayer; ++i){
            if(playerPieces[i].rank == piece->rank && playerPieces[i].file == (piece->file - 3)){
                idx = i;
            }
        }
        if(!invalid){
            if(playerPieces[idx].piece == 'r' && !playerPieces[idx].moved){
                int64_t move = (int64_t) 1 << ((piece->rank * 8) + (piece->file - 2));
                moves |= move;
            }
        }
    }

    // check for queen side castling
    if(!piece->moved && !enemySearch && !(getEnemyMoves(startPos / 8, startPos % 8) & piece->board)){
        char invalid = 0;
        for(int i = 2; i >= 1; --i){
            int64_t move = (int64_t) 1 << (startPos + i);
            if((move | playerBoard) == playerBoard){
                invalid = 1;
                break;
            }else{
                piece->board = move;
                if((getEnemyMoves(i / 8, i % 8) & move)){
                    invalid = 1;
                }
                piece->board = oldState;
            }
        }
        char idx = 0;
        for(int i = 0; i < numPlayer; ++i){
            if(playerPieces[i].rank == piece->rank && playerPieces[i].file == (piece->file + 4)){
                idx = i;
            }
        }
        if(!invalid){
            if(playerPieces[idx].piece == 'r' && !playerPieces[idx].moved){
                int64_t move = (int64_t) 1 << ((piece->rank * 8) + (piece->file + 2));
                moves |= move;
            }
        }
    }
    return moves;
}

int64_t computeQueenMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard){
    char startPos = (piece->rank * 8) + piece->file;
    int64_t moves = 0;
    int64_t move = 1;
    int64_t oldState = piece->board;

    // up to the left from the piece
    char pos = startPos + 9;
    while(pos < 64 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos += 9;
        }
    }

    // up to the right from the piece
    pos = startPos + 7;
    while(pos < 64 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos += 7;
        }
    }

    // down to the left from the piece
    pos = startPos - 7;
    while(pos >= 0 && ((pos % 8) > (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos -= 7;
        }
    }

    // down to the right from the piece
    pos = startPos - 9;
    while(pos >= 0 && ((pos % 8) < (startPos % 8))){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos -= 9;
        }
    }

    // everything above
    pos = startPos + 8;
    while(pos < 64){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos += 8;
        }
    }

    // everything below
    pos = startPos - 8;
    while(pos >= 0){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos -= 8;
        }
    }

    // everything right
    pos = startPos + 1;
    while((pos % 8) > (startPos % 8)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos++;
        }
    }

    // everything left
    pos = startPos - 1;
    while((pos % 8) < (startPos % 8) && (pos >= 0)){
        move = (int64_t) 1 << pos;
        if((move | playerBoard) == playerBoard){
            if(enemySearch){
                moves |= move;
                break;
            }else{
                break;
            }
        }else if((move | enemyBoard) == enemyBoard){
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            break;
        }else{
            if(enemySearch){
                moves |= move;
            }else{
                piece->board = move;
                if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                    moves |= move;
                }
                piece->board = oldState;
            }
            pos--;
        }
    }

    piece->board = oldState;
    return moves;
}

int64_t computeKnightMoves(piece_t* piece, int64_t playerBoard, int64_t enemyBoard){
    char startPos = (piece->rank * 8) + piece->file;
    int64_t moves = 0;
    int64_t move = 1;
    int64_t oldState = piece->board;

    // 4 left positions
    short changes1[] = {17, 10, -6, -15};
    for(int i = 0; i < 4; ++i){
        short pos = startPos + changes1[i];
        if((pos < 64 && pos >= 0) && ((pos % 8) > (startPos % 8))){
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard){
                if(enemySearch){
                    moves |= move;
                }else{
                    piece->board = move;
                    if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                        moves |= move;
                    }
                    piece->board = oldState;
                }
            }else{
                if(enemySearch){
                    moves |= move;
                }
            }
        }
    }

    // 4 right positions
    int changes2[] = {15, 6, -10, -17};
    for(int i = 0; i < 4; ++i){
        short pos = startPos + changes2[i];
        if((pos < 64 && pos >= 0) && ((pos % 8) < (startPos % 8))){
            move = (int64_t) 1 << pos;
            if((move | playerBoard) != playerBoard){
                if(enemySearch){
                    moves |= move;
                }else{
                    piece->board = move;
                    if(!(getEnemyMoves(pos / 8, pos % 8) & playerPieces[playerKingIndex].board)){
                        moves |= move;
                    }
                    piece->board = oldState;
                }
            }else{
                if(enemySearch){
                    moves |= move;
                }
            }
        }
    }

    piece->board = oldState;
    return moves;
}


/*
Default command -> pawn on a2 selected:
'f' 32 wpa20 bra80_bnb80_bbc80_bqd80_bke80_bbf80_bng80_brh80_bpa70_bpb70_bpc70_bpd70_bpe70_bpf70_bpg70_bph70_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_wpa20_wpb20_wpc20_wpd20_wpe20_wpf20_wpg20_wph20_wra10_wnb10_wbc10_wqd10_wke10_wbf10_wng10_wrh10

Black missing h pawn:
'f' 31 wpa20 bra80_bnb80_bbc80_bqd80_bke80_bbf80_bng80_brh80_bpa70_bpb70_bpc70_bpd70_bpe70_bpf70_bpg70_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_wpa20_wpb20_wpc20_wpd20_wpe20_wpf20_wpg20_wph20_wra10_wnb10_wbc10_wqd10_wke10_wbf10_wng10_wrh10
*/