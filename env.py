import pygame
import board
from engine import Engine

class Environment:
    def __init__(self, screen, playerColor = 'w', humanPlayer = True):
        self.screen = screen
        self.engine = Engine()
        self.board = board.Board(screen = self.screen, playerColor = playerColor)
        self.playerColor = playerColor
        self.highlighted_moves = []
    
    def initialize_environment(self):
        self.board.draw_board()
        
    def select_piece(self, square):
        square.color = (square.base_color[0], 255, square.base_color[2])
        square.draw_square(self.screen)
        self.highlight_moves(square)
        
    def deselect_piece(self, square):
        square.color = square.base_color
        square.draw_square(self.screen)
        self.deselect_moves()

    def highlight_moves(self, square):
        self.moves = []
        moves = self.engine.find_moves(square = square, board = self.board).split(",")
        if moves[0] != '':
            for move in moves:
                self.moves.append((move[0], move[1]))
            for row in self.board.board:
                for square in row:
                    if square.identity in self.moves:
                        self.highlighted_moves.append(square)
        
        for square in self.highlighted_moves:
            square.color = (square.base_color[0] - 50, 175, square.base_color[2] - 100)
            square.draw_square(self.screen)
            square.highlighted = True
    
    def deselect_moves(self):
        for square in self.highlighted_moves:
            square.color = square.base_color
            square.draw_square(self.screen)
            square.highlighted = False
        self.highlighted_moves = []
        pygame.display.update()

    def make_move(self, old_square, new_square):
        new_square.piece = old_square.piece
        new_square.draw_square(self.screen)
        old_square.piece = None
        new_square.piece.square = new_square.identity
        new_square.piece.set_moved()