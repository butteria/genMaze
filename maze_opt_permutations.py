from itertools import permutations
direction_bits = ("11", "10", "01", "00")
for bits in permutations(direction_bits, 4):
    bits_str = "0b"
    bits_str = bits_str + ''.join('%s'%o for o in bits)
    print (hex(int(bits_str,2)))