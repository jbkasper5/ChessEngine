import pygame
from env import Environment
from board import Board
from action import Action


color = input("Choose a color to play (w/b): ")
while(color.lower() != 'w' and color.lower() != 'b'):
    print("Invalid input.")
    color = input("Choose a color to play (w/b): ")
    
pygame.init()

BOARD_HEIGHT = 800
BOARD_WIDTH = 800
screen = pygame.display.set_mode((BOARD_HEIGHT, BOARD_WIDTH))

running = True
piece_selected = None
old_piece = None

env = Environment(screen = screen, playerColor = color, humanPlayer = True)
env.initialize_environment()
event = Action(env = env)

while running:
    for game_event in pygame.event.get():
        if game_event.type == pygame.QUIT:
            running = False
            
        if game_event.type == pygame.MOUSEBUTTONDOWN:
            square = event.square_selected() # determine if a square was selected
            if square is not None:
                env.deselect_piece(piece_selected)
                env.make_move(piece_selected, square)
                piece_selected = None
            else:
                piece_selected = event.piece_selected()
            if piece_selected is not None and old_piece is None:
                env.select_piece(piece_selected) # select the piece and find moves
            elif (piece_selected is not None and old_piece is not None) and piece_selected is not old_piece:
                env.deselect_piece(old_piece) # unhighlight moves and deselect piece
                env.select_piece(piece_selected) # highlight new piece and find moves
            elif piece_selected is None and old_piece is not None:
                env.deselect_piece(old_piece) # unhighlight moves and deselect piece
            elif piece_selected is not None and piece_selected == old_piece:
                env.deselect_piece(piece_selected)
                piece_selected = None
            old_piece = piece_selected # change the old piece to be the piece selected
        pygame.display.update()