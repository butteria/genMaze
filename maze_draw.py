from ctypes import *
from svgpathtools import parse_path, wsvg

maze = CDLL("libso\libmaze.so")
maze.generate.restype = POINTER(c_ubyte)
bit_stream = POINTER(c_ubyte)


length = 5
width = 5
size = length * width
grid_size = 5
start_y = 10
start_x = 5
bit_stream = maze.generate(length, width)
path = 'M' + str(start_y) + ' ' + str(start_x) + 'H' + str(1)

print (path)
path_alt = parse_path(path)
wsvg(path_alt, filename='output.svg')