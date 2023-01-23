import pygame

class King:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/King.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/King.png")
        self.color = color
        self.square = square
        self.moved = 0

    def set_moved(self):
        self.moved = 1

    def as_str(self):
        return f"{self.color}k{self.square[0]}{self.square[1]}{self.moved}"
        
class Queen:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Queen.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Queen.png")
        self.color = color
        self.square = square
        self.moved = 0

    def set_moved(self):
        self.moved = 1

    def as_str(self):
        return f"{self.color}q{self.square[0]}{self.square[1]}{self.moved}"
           
class Bishop:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Bishop.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Bishop.png")
        self.color = color
        self.square = square
        self.moved = 0

    def set_moved(self):
        self.moved = 1

    def as_str(self):
        return f"{self.color}b{self.square[0]}{self.square[1]}{self.moved}"

class Knight:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Knight.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Knight.png")
        self.color = color
        self.square = square
        self.moved = 0

    def set_moved(self):
        self.moved = 1

    def as_str(self):
        return f"{self.color}n{self.square[0]}{self.square[1]}{self.moved}"
        
class Rook:
    def __init__(self, color, square, set = 1, moved = False):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Rook.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Rook.png")
        self.color = color
        self.square = square
        self.moved = 0

    def set_moved(self):
        self.moved = 1

    def as_str(self):
        return f"{self.color}r{self.square[0]}{self.square[1]}{self.moved}"
        
class Pawn:
    def __init__(self, color, square, set = 1, moved = False):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Pawn.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Pawn.png")
        self.color = color
        self.square = square
        self.moved = 0

    def set_moved(self):
        self.moved = 1

    def as_str(self):
        return f"{self.color}p{self.square[0]}{self.square[1]}{self.moved}"
