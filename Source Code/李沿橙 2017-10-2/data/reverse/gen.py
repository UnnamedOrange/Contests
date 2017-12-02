import os
import random
import sys

def makeData(index):
    n = random.randint(5, 20)
    if (index >= 8):
        n = random.randint(1, 1000)
    if (index >= 14):
        n = random.randint(1, 100000)
    


    f = open("reverse.in", "w")
    
    for i in range(n):
        p = random.randint(0, 1)
        print(p, file = f, end = '')
    
    f.close()
    os.system("reverse.exe")

    os.system("rename reverse.in reverse" + str(index) + ".in")
    os.system("rename reverse.out reverse" + str(index) + ".out")


for i in range(2, 20):
    makeData(i)

