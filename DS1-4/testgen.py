#!/usr/bin/env python
import random
for i in range(1, 9):
    fileout = open("input{}.txt".format(i), "w")
    print("OID\tArrival\tDuration\tTimeOut", file=fileout)
    oids = list(range(100, 300))
    random.shuffle(oids)
    for oid in oids:
        arrival = random.randint(1, 2000)
        duration = random.randint(1, 600)
        timeout = arrival + duration + random.randint(0, 300)
        print("{}\t{}\t{}\t{}".format(oid, arrival, duration, timeout), file=fileout)

