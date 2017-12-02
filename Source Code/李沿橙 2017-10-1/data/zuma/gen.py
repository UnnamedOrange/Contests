import os
import random
import sys

def makeData(index):
    n = random.randint(5, 7)
    if (index >= 6):
        n = random.randint(1, 50)
    if (index >= 14):
        n = random.randint(1, 200)
    


    f = open("zuma.in", "w")
    
    a = []
    for i in range(n):
        p = random.randint(0, 1)
        if (i >= 2):
            if (a[i - 1] == a[i - 2] and a[i - 1] == p):
                p = p ^ 1
        a.append(p)
        print(p, file = f, end = '')
    
    f.close()
    os.system("zuma.exe")

    os.system("rename zuma.in zuma" + str(index) + ".in")
    os.system("rename zuma.out zuma" + str(index) + ".out")


for i in range(20):
    makeData(i)

