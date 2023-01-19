import pygame
import pieces
import json

class Board:
    def __init__(self, screen, playerColor):
        self.screen = screen
        dim = 100
        files = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
        ranks = ['1', '2', '3', '4', '5', '6', '7', '8']
        if playerColor == 'w':
            self.board = [[Square(color = (110 - (50 * ((i + j) % 2)), 170 - (50 * ((i + j) % 2)), 255 - ((50 * ((i + j) % 2)))), coords = (i * dim, j * dim, dim, dim), file = files[i], rank = ranks[len(ranks) - 1 - j]) for i in range(8)] for j in range(8)]
        else:
            self.board = [[Square(color = (110 - (50 * ((i + j) % 2)), 170 - (50 * ((i + j) % 2)), 255 - ((50 * ((i + j) % 2)))), coords = (i * dim, j * dim, dim, dim), file = files[len(files) - 1 - i], rank = ranks[j]) for i in range(8)] for j in range(8)]
        
        SET = 1
        
        # initial board configuration
        self.pieces = [
            pieces.Pawn(color = "w", set = SET, square = ('a', '2')),
            pieces.Pawn(color = "w", set = SET, square = ('b', '2')),
            pieces.Pawn(color = "w", set = SET, square = ('c', '2')),
            pieces.Pawn(color = "w", set = SET, square = ('d', '2')),
            pieces.Pawn(color = "w", set = SET, square = ('e', '2')),
            pieces.Pawn(color = "w", set = SET, square = ('f', '2')),
            pieces.Pawn(color = "w", set = SET, square = ('g', '2')),
            pieces.Pawn(color = "w", set = SET, square = ('h', '2')),
            pieces.Rook(color = "w", set = SET, square = ('a', '1')),
            pieces.Rook(color = "w", set = SET, square = ('h', '1')),
            pieces.Knight(color = "w", set = SET, square = ('b', '1')),
            pieces.Knight(color = "w", set = SET, square = ('g', '1')),
            pieces.Bishop(color = "w", set = SET, square = ('c', '1')),
            pieces.Bishop(color = "w", set = SET, square = ('f', '1')),
            pieces.King(color = "w", set = SET, square = ('e', '1')),
            pieces.Queen(color = "w", set = SET, square = ('d', '1')),
            pieces.Pawn(color = "b", set = SET, square = ('a', '7')),
            pieces.Pawn(color = "b", set = SET, square = ('b', '7')),
            pieces.Pawn(color = "b", set = SET, square = ('c', '7')),
            pieces.Pawn(color = "b", set = SET, square = ('d', '7')),
            pieces.Pawn(color = "b", set = SET, square = ('e', '7')),
            pieces.Pawn(color = "b", set = SET, square = ('f', '7')),
            pieces.Pawn(color = "b", set = SET, square = ('g', '7')),
            pieces.Pawn(color = "b", set = SET, square = ('h', '7')),
            pieces.Rook(color = "b", set = SET, square = ('a', '8')),
            pieces.Rook(color = "b", set = SET, square = ('h', '8')),
            pieces.Knight(color = "b", set = SET, square = ('b', '8')),
            pieces.Knight(color = "b", set = SET, square = ('g', '8')),
            pieces.Bishop(color = "b", set = SET, square = ('c', '8')),
            pieces.Bishop(color = "b", set = SET, square = ('f', '8')),
            pieces.King(color = "b", set = SET, square = ('e', '8')),
            pieces.Queen(color = "b", set = SET, square = ('d', '8'))
        ]
        
        self.assign_pieces()
        
    def assign_pieces(self):
        for file in self.board:
            for square in file:
                for piece in self.pieces:
                    if piece.square == square.identity:
                        square.piece = piece

    def draw_board(self):
        for file in self.board:
            for square in file:
                square.draw_square(screen = self.screen)
                
    def get_board(self):
        return self.board

    def as_str(self):
        string = ""
        for row in range(8):
            for square in range(8):
                if self.board[row][square].piece == None:
                    string += "0_"
                else:
                    string += f"{self.board[row][square].piece.as_str()}_"
        # print(string)
        return string[:-1]

class Square:
    def __init__(self, color, coords, file = None, rank = None):
        self.base_color = color
        self.color = color
        self.coords = coords
        self.identity = (file, rank)
        self.piece = None
    
    def draw_square(self, screen):
        pygame.draw.rect(screen, self.color, pygame.Rect(self.coords))
        if self.piece is not None:
            screen.blit(self.piece.image, (self.coords[0], self.coords[1]))
