#!/usr/bin/env python
import struct
import sys

s = struct.Struct('10s 10s f')
slen = s.size
filename = sys.argv[1]

outlist = []
with open(filename, 'rb') as f:
    while True:
        data = f.read(slen)
        if not data: break
        a = s.unpack(data)
        outlist.append(a)

def sorVal(val):
    return val[2]

outlist = sorted(outlist, key=sorVal, reverse=True)

f = open(filename+".sorted", 'w+b')

for row in outlist:
    f.write(s.pack(row[0], row[1], row[2]))

f.close()
