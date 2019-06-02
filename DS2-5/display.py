#!/usr/bin/env python
import struct
import sys

s = struct.Struct('10s 10s f')
slen = s.size
filename = sys.argv[1]

with open(filename, 'rb') as f:
    while True:
        data = f.read(slen)
        if not data: break
        a = s.unpack(data)
        print ("{} {} {}".format(a[0].decode('ascii', errors="ignore"),
                                 a[1].decode('ascii', errors="ignore"), a[2]))


