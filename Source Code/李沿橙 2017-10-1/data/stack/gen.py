import os
import random
import sys

def makeData(index):
    n = random.randint(1, 15)
    if (index >= 8):
        n = random.randint(1, 1000)
    


    f = open("stack.in", "w")
    print(n, file = f)
    f.close()
    os.system("stack.exe")

    os.system("rename stack.in stack" + str(index) + ".in")
    os.system("rename stack.out stack" + str(index) + ".out")


for i in range(20):
    makeData(i)

