#!/usr/bin/env python
import sys
import csv
select = [8, 7]

def checkFile(file1):
    first = True
    pre = 0
    count = 1
    with open(file1,  encoding='Big5', newline='', errors='ignore') as csvfile:
        spamerader = csv.reader(csvfile, delimiter='\t')

        for row in spamerader:
            cur = [int(row[i]) for i in select]
            if first is True:
                first = False
                pre = cur
            else:
                if pre < cur:
                    print(' '.join(row))
                    print(file1 + " bug🐞line " + str(count))
                    print("pre: {} cur: {}".format(pre, cur))
                pre = cur
            count += 1


for file1 in sys.argv[1:]:
    print(file1)
    checkFile(file1)


