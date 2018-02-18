#!/bin/usr/env/ python3
from random import getrandbits
from sys import argv
from math import gcd

bits = argv[1]

u = getrandbits(int(bits))
v = getrandbits(int(bits))
answer = gcd(u, v)
with open('test-gcd', 'w') as test, open('answer-gcd', 'w') as ans:
    test.write(str(u))
    test.write('\n')
    test.write(str(v))
    test.write('\n')
    ans.write(str(answer))
    ans.write('\n')
