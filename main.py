from libs.board import Board
from libs.engine import Engine
from libs.board import Board

import pygame
import sys

# Initialize Pygame
pygame.init()

# Set up window
width, height = 800, 800
screen = pygame.display.set_mode((width, height))
env = Board(screen=screen)
# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        # Handle mouse clicks
        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            button = event.button
            env.handle_click(x, y)

    # Optional: clear screen
    pygame.display.flip()

# Quit Pygame
pygame.quit()
sys.exit()