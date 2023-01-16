#include "engine.h"
//---------------------------BITBOARDS---------------------------//
struct Bitboard{
    //king: 0, queen: 1, rook: 2, bishop: 3, knight: 4, pawn: 5
    int piece;
    //white: 0, black: 1
    int color;
    int64_t board;
};
//---------------------------HELPER | FIND LEGAL MOVES---------------------------//
// std::vector<Move> FindLegalMoves(nlohmann::json input){
//     std::cout << "Hello" << std::endl;
//     std::vector<Move> legalMoves;
//     return legalMoves;
// }
//---------------------------ML ENGINE---------------------------//
void Engine::CalculateMove(nlohmann::json input){
    // FindLegalMoves(input);
    Bitboard board;
    board.color = 1;
    board.piece = 0;
    board.board = 75;
    std::cout << board.board << std::endl;
}
//---------------------------ML ENGINE---------------------------//
void MLEngine::CalculateMove(nlohmann::json input){
    // FindLegalMoves(input);
    
}