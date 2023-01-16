import pygame

import env
import board
import engine

class Action:
    def __init__(self, env):
        self.env = env
        self.board = self.env.board.get_board()
        
    def piece_selected(self):
        x, y = pygame.mouse.get_pos()
        for file in self.board:
            for square in file:
                if x > square.coords[0] and x < (square.coords[0] + square.coords[2]) and y > square.coords[1] and y < (square.coords[1] + square.coords[2]):
                    if square.piece is not None:
                        return square
        return None
