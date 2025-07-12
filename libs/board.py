import pygame
from enum import Enum

class COLOR(Enum):
    DEFAULT = None
    SELECTED = None

class COLOR1(Enum):
    DEFAULT = (0x0, 0xA0, 0x0)
    SELECTED = (0x0, 0x50, 0x0)

class COLOR2(Enum):
    DEFAULT = (0xFF, 0xFF, 0xFF)
    SELECTED = (0xAF, 0xAF, 0xAF)

def idx_to_coords(idx: int) -> tuple[int, int]:
    return (idx // 8, idx % 8)

def coords_to_idx(row: int, col: int) -> int:
    return row + col * 8

class Square:
    def __init__(self, idx, color: COLOR):
        self.base_color = color
        self.color = color.DEFAULT.value
        self.idx = idx
        row, col = idx_to_coords(idx)
        self.rect = pygame.Rect(col * 100, row * 100, 100, 100)
        self.selected = False

    def select(self, screen):
        self.color = self.base_color.SELECTED.value
        self.selected = True
        self.draw(screen=screen)

    def deselect(self, screen):
        self.color = self.base_color.DEFAULT.value
        self.selected = False
        self.draw(screen=screen)

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect)

class Board:
    def __init__(self, screen):
        self.screen = screen
        self.board: list[Square] = [Square(i, COLOR1 if (i + (i // 8))% 2 == 0 else COLOR2) for i in range(64)]
        self.selected_square_idx: int = None
        self._draw_checkerboard()

    def update(self):
        self._draw_checkerboard()

    def handle_click(self, x, y) -> None:
        row = x // 100
        col = y // 100
        idx = coords_to_idx(row, col)
        square = self.board[idx]
        if self.selected_square_idx == idx:
            square.deselect(screen=self.screen) if square.selected else square.select(screen=self.screen)
        else:
            if self.selected_square_idx is not None:
                self.board[self.selected_square_idx].deselect(screen=self.screen)
            self.board[idx].select(screen=self.screen)
            self.selected_square_idx = idx

    def _draw_checkerboard(self):
        for square in self.board:
            square.draw(screen=self.screen)

    def serialize(self):
        pass