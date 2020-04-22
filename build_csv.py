import os
import re

pattern = re.compile("Total RX rate:\s*(.*)")

for (dirpath, dirs, files) in os.walk('runs'):
    print("")
    print(dirpath)
    for fname in files:
        rows = fname.split('_')[0]
        cols = fname.split('_')[1][:-4]
        f = open(os.path.join(dirpath, fname))
        s = f.read()
        f.close()
        # print(s)
        rate = pattern.findall(s)[-1]
        print("{}, {}, {}".format(rows, cols, rate))
