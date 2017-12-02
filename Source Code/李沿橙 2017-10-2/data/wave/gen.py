import os
import random
import sys

def makeData(index):
    n = random.randint(50000, 100000)
    


    f = open("wave.in", "w")
    print(n, random.randint(500, 1000), file = f)
    for i in range(n):
        print(random.randint(0, 4000), end = ' ', file = f)
    f.close()
    os.system("wave.exe")

    os.system("rename wave.in wave" + str(index) + ".in")
    os.system("rename wave.out wave" + str(index) + ".out")


for i in range(8, 14):
    makeData(i)

