import os
import random
import sys

def makeData(index):

    os.system("rename zuma" + str(index) + ".in number" + str(index) + ".in")
    os.system("rename zuma" + str(index) + ".out number" + str(index) + ".out")


for i in range(20):
    makeData(i)

