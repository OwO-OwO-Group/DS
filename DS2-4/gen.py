#!/usr/bin/env python
import struct
f = open('gen.bin', 'w+b')
s = struct.Struct('10s 10s f')

def add_node(a, b ,w):
    f.write(s.pack(a.encode('ascii'), b.encode('ascii'), 0.3))

add_node('105', '10', 0.3)
add_node('105', '103', 0.3)
add_node('103', '10', 0.3)
add_node('102', '10', 0.3)
add_node('102', '11', 0.3)
add_node('11', '105', 0.3)

f.close()
