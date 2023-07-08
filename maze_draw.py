from ctypes import *
from svgpathtools import parse_path, wsvg

maze = CDLL("libso\libmaze.so")
maze.generate.restype = POINTER(c_ubyte)

length = 10
width = 10
maze.draw_in_terminal(maze.generate(length, width), length, width)