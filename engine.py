import subprocess
import time
import env
import board

class Engine:
    def __init__(self):
        compileProc = subprocess.Popen(['sh', './Backend/compile.sh', 'hello', 'world'], stdout=subprocess.PIPE)
        out, err = compileProc.communicate()

    def find_moves(self, square, board):
        # args: 
        #   flag | number of pieces on the board | piece selected | board configuration
        start = time.time()
        # print(f"\'f\' {str(len(board.pieces))} {square.piece.as_str()} {board.as_str()}")
        proc = subprocess.Popen(['sh', './Backend/compute.sh', 'f', str(len(board.pieces)), square.piece.as_str(), board.as_str()], stdout = subprocess.PIPE)
        out, err = proc.communicate()
        print(f"Found move in {time.time() - start} seconds.")
        out = str(out)[2:-2]
        return out

    def make_move(self, color, board):
        # args:
        #   flag | number of pieces on the board | color | board configuration
        start = time.time()
        proc = subprocess.Popen(['sh', './Backend/compute.sh', str(len(board.pieces)), 'm', str(color), board.as_str()], stdout = subprocess.PIPE)
        out, err = proc.communicate()
        print(f"Move made in {time.time() - start} seconds.")
        out = str(out)[2:-3]
        return out