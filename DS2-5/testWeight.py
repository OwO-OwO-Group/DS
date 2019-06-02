#!/usr/bin/env python
import struct
import sys

s = struct.Struct('10s 10s f')
slen = s.size
filename = sys.argv[1]

with open(filename, 'rb') as f:
    pre = 1.0
    count = 0
    while True:
        data = f.read(slen)
        if not data: break
        a = s.unpack(data)
        if a[2] > pre:
            print("err [{}] {} [{}] {}".format(count - 1, pre, count, a[2]))
            #break

        count = count + 1
        pre = a[2]


