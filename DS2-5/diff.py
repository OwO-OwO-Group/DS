#!/usr/bin/env python
import struct
import sys

s = struct.Struct('10s 10s f')
slen = s.size
file1 = sys.argv[1]
file2 = sys.argv[2]

list1 = []
list2 = []
with open(file1, 'rb') as f:
    while True:
        data = f.read(slen)
        if not data: break
        a = s.unpack(data)
        list1.append(a)

with open(file2, 'rb') as f:
    while True:
        data = f.read(slen)
        if not data: break
        a = s.unpack(data)
        list2.append(a)

""" commpare """

if len(list1) != len(list2):
    print("size not equal")
    sys.exit(1)

for i in range(0, len(list1)):
    if list1[i] != list2[i]:
        print("diff [{}] ".format(i))
