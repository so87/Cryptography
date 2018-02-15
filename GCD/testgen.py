#!/usr/bin/env python3
from random import getrandbits
from sys import argv
from math import gcd
import subprocess
try:
    with open(argv[1], 'w') as f, open(argv[2], 'w') as ans, open(argv[3], 'w') as rans:
            num_test = int(argv[4])
            for i in range(num_test):
                num_bits = int(argv[5])
                a = getrandbits(num_bits)
                b = getrandbits(num_bits)
                c = gcd(a, b)
                proc = subprocess.Popen(['./gcd', str(a), str(b)], stdout=subprocess.PIPE)
                d = proc.stdout.readline()
                d = int(d.rstrip())
                f.write('{0} {1}\n'.format(a, b))
                ans.write('{0}\n'.format(c))
                rans.write('{0}\n'.format(d))
except:
    print('Usage: ' + argv[0] + ' <test file> <test answer file> <real answer file> <num test cases> <num bits>')
