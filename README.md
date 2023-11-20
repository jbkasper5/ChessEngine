# ChessEngine2.0

## Python Front-End

The front-end board representation is created using `python 3.6.13`, specifically the `pygame`. This project was designed to create a minimax chess engine featuring alpha-beta pruning, allowing players to challenge the engine on a virtual board. 

The board mantainence and updating logic is created in python as well, changing the environment based on the user's selection of piece/color. When the user goes to move a piece, a query is made to the C engine backend, and a series of moves is returned to highlight the available moves that the selected piece can make. Logic includes castling and en passant. 

## C Backend

The backend is designed to accept a binary representation of the current state of the board. The representation is condensed to a sequence of integers corresponding to an index on the board, and an integer defining the type of piece as well as the color of that piece. From this, the program will either generate and return a sequence of moves (when the human player highlights a piece), or it will return a move to make on behalf of the engine (after performing a search using minimax to find what it considers to be the best move). 

## Scoring

Minimax engines require a scoring algorithm to determine which game states are optimal for any given player in the game. However, based on my limited knowledge of the game of chess, the engine will instead feature a _learned_ algorithm, a simple fully connected neural network designed to take in a board representation and map it to a float value. This algorithm will be **self-supervised**, and will attempt to teach itself how to play the game through many games playing against itself.

## Training and Optimization

The neural network will be trained by pitting two engines against each other, and punishing the model that loses, while rewarding the model that wins. Furthermore, the depth of the minimax search will be restricted to a small depth, as this will force the learned algorithm to become better to account for the lack of information. In other words, if the engine can only see a few moves ahead instead of dozens, it's scoring algorithm needs to be much more precise in order to be successful. Once the model has been trained, the depth restriction on the engine will be released.  