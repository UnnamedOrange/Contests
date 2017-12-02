import os
import random
import sys

def makeData(index):
    n = random.randint(5, 20)
    if (index >= 6):
        n = random.randint(1, 1000)
    if (index >= 12):
        n = random.randint(1, 30000)

    fl = [False for i in range(n)]
    p = [0]
    for i in range(1, n):
        p.append(random.randint(0, i - 1))

    f = open("cube.in", "w")
    print(n, file = f)
    for i in range(n):
        x = random.randint(0, 3)
        if (x):
            u = random.randint(1, n - 1)
            while (fl[u] == True):
                u = random.randint(1, n - 1)
            fl[u] = True
            if (x < 2):
                print('M ' + str(u + 1) + ' ' +  str(p[u] + 1), file = f)
            else:
                print('M ' + str(p[u] + 1) + ' ' + str(u + 1), file = f)
        else:
           print('C ' + str(random.randint(1, n)), file = f)
    


    f.close()
    os.system("cube.exe")

    os.system("rename cube.in cube" + str(index) + ".in")
    os.system("rename cube.out cube" + str(index) + ".out")


for i in range(20):
    makeData(i)

