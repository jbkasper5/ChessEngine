import pygame

class King:
    def __init__(self, color, square, set = 1):
        self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/{color}/Set{set}/King.png")
        self.color = color
        self.square = square
        self.value = 0
        self.moved = False
        self.captured = False

    def capture(self):
        self.captured = True

    def as_str(self):
        return f"{self.color.lower()[0]}k{self.square[0]}{self.square[1]}"
        
class Queen:
    def __init__(self, color, square, set = 1):
        self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/{color}/Set{set}/Queen.png")
        self.color = color
        self.square = square
        self.value = 9
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color.lower()[0]}q{self.square[0]}{self.square[1]}"
           
class Bishop:
    def __init__(self, color, square, set = 1):
        self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/{color}/Set{set}/Bishop.png")
        self.color = color
        self.square = square
        self.value = 3
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color.lower()[0]}b{self.square[0]}{self.square[1]}"

class Knight:
    def __init__(self, color, square, set = 1):
        self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/{color}/Set{set}/Knight.png")
        self.color = color
        self.square = square
        self.value = 3
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color.lower()[0]}n{self.square[0]}{self.square[1]}"
        
class Rook:
    def __init__(self, color, square, set = 1, moved = False):
        self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/{color}/Set{set}/Rook.png")
        self.color = color
        self.square = square
        self.value = 5
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color.lower()[0]}r{self.square[0]}{self.square[1]}"
        
class Pawn:
    def __init__(self, color, square, set = 1, moved = False, enpassant = False):
        self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/{color}/Set{set}/Pawn.png")
        self.color = color
        self.square = square
        self.value = 1
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color.lower()[0]}p{self.square[0]}{self.square[1]}"
