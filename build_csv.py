import os
import re

pattern = re.compile("Total RX rate:\s*(.*)")


def get_rate(fpath):
    f = open(fpath)
    s = f.read()
    f.close()
    # print(s)
    flist = pattern.findall(s)
    # print(fname, flist)
    try:
        rate = flist[-1]
    except:
        rate = -1
    return rate


if(__name__ == '__main__'):
    for (dirpath, dirs, files) in os.walk('runs'):
        print("")
        print(dirpath)
        for fname in files:
            try:
                rows = fname.split('_')[0]
                cols = fname.split('_')[1][:-4]
                rate = get_rate(os.path.join(dirpath, fname))
                print("{}, {}, {}".format(rows, cols, rate))
            except:
                pass
