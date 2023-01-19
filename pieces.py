import pygame

class King:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/King.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/King.png")
        self.color = color
        self.square = square
        self.value = 0
        self.moved = False
        self.captured = False

    def capture(self):
        self.captured = True

    def as_str(self):
        return f"{self.color}k{self.square[0]}{self.square[1]}"
        
class Queen:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Queen.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Queen.png")
        self.color = color
        self.square = square
        self.value = 9
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color}q{self.square[0]}{self.square[1]}"
           
class Bishop:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Bishop.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Bishop.png")
        self.color = color
        self.square = square
        self.value = 3
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color}b{self.square[0]}{self.square[1]}"

class Knight:
    def __init__(self, color, square, set = 1):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Knight.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Knight.png")
        self.color = color
        self.square = square
        self.value = 3
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color}n{self.square[0]}{self.square[1]}"
        
class Rook:
    def __init__(self, color, square, set = 1, moved = False):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Rook.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Rook.png")
        self.color = color
        self.square = square
        self.value = 5
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color}r{self.square[0]}{self.square[1]}"
        
class Pawn:
    def __init__(self, color, square, set = 1, moved = False, enpassant = False):
        if color == 'w':
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/White/Set{set}/Pawn.png")
        else:
            self.image = pygame.image.load(f"/Users/jakekasper/Python/ChessEngine/Assets/Black/Set{set}/Pawn.png")
        self.color = color
        self.square = square
        self.value = 1
        self.moved = False
        self.captured = False

    def as_str(self):
        return f"{self.color}p{self.square[0]}{self.square[1]}"
