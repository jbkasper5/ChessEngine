import subprocess
import json
import env
import board

class Engine:
    def __init__(self):
        proc = subprocess.Popen(['sh', './Backend/compile.sh', 'hello', 'world'], stdout=subprocess.PIPE)
        out, err = proc.communicate()
        out = str(out)[2:-3]
        print("Back to python")
        print(out)

    def find_moves(self, square, board):
        print(board.as_str())
        # args: 
        #   flag | number of pieces on the board | piece selected | board configuration
        proc = subprocess.Popen(['sh', './Backend/compute.sh', 'f', str(len(board.pieces)), square.piece.as_str(), board.as_str()], stdout = subprocess.PIPE)
        out, err = proc.communicate()
        out = str(out)[2:-3]
        print("Back to python")
        print(out)

    def make_move(self, color):
        # args:
        #   flag | number of pieces on the board | color | board configuration
        subprocess.call(['sh', './Backend/compute.sh', str(len(board.pieces)), 'm', str(color), board.as_str()], stdout = subprocess.PIPE)