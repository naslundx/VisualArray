import sys
sys.path.insert(0,'..')
from visualarray import VisualArray
import random

def bubblesort(alist):
    for num in range(len(alist)-1,0,-1):
        for i in range(num):
            if alist[i]>alist[i+1]:
            	alist[i], alist[i+1] = alist[i+1], alist[i]

alist = random.sample(xrange(10,50), 10)
alist = VisualArray(alist)
bubblesort(alist)
alist.render()
