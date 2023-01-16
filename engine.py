import subprocess
import json
import env
import board

class Engine:
    def __init__(self):
        self.engine_running = False
        proc = subprocess.Popen(['sh', './Backend/compile.sh', 'hello', 'world'], stdout=subprocess.PIPE)
        out, err = proc.communicate()
        out = str(out)[2:-3]
        print("Back to python")
        print(out)

    def find_moves(self, square, board):
        print(board.as_str())
        proc = subprocess.Popen(['sh', './Backend/compute.sh', str(len(board.pieces)), square.piece.as_str(), board.as_str()], stdout=subprocess.PIPE)
        out, err = proc.communicate()
        out = str(out)[2:-3]
        print("Back to python")
        print(out)

    def make_move(self):
        subprocess.call(['sh', './Backend/compute.sh', 'board'])