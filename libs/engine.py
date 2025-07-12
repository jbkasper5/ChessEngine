import ctypes
import os

class Engine:
    def __init__(self):
        lib_path = os.path.join(os.path.dirname(__file__), "lib.so")
        self.so = ctypes.CDLL(lib_path)
        self.so.hello_world.argtypes = None
        self.so.hello_world.restype = None
        self.so.hello_world()