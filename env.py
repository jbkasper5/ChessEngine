import pygame
import board
from engine import Engine

class Environment:
    def __init__(self, screen, playerColor = 'w', humanPlayer = True):
        self.screen = screen
        self.engine = Engine()
        self.board = board.Board(screen = self.screen, playerColor = playerColor)
    
    def initialize_environment(self):
        self.board.draw_board()
        
    def select_piece(self, square):
        square.color = (square.base_color[0], 255, square.base_color[2])
        square.draw_square(self.screen)
        self.highlight_moves(square)
        
    def deselect_piece(self, square):
        square.color = square.base_color
        square.draw_square(self.screen)

    def highlight_moves(self, square):
        self.engine.find_moves(square = square, board = self.board)
