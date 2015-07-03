import sys
sys.path.insert(0,'..')
from visualarray import VisualArray
import random

def mergeSort(alist):
    if len(alist)>1:
        mid = len(alist)//2

        # Here is the problem, we're creating new arrays
        lefthalf = (alist[:mid])
        righthalf = (alist[mid:])

        alist.gfx_color(mid, "yellow")

        mergeSort(lefthalf)
        mergeSort(righthalf)

        i=0
        j=0
        k=0
        while i<len(lefthalf) and j<len(righthalf):
            if lefthalf[i]<righthalf[j]:
                alist[k]=lefthalf[i]
                i=i+1
            else:
                alist[k]=righthalf[j]
                j=j+1
            k=k+1

        while i<len(lefthalf):
            alist[k]=lefthalf[i]
            i=i+1
            k=k+1

        while j<len(righthalf):
            alist[k]=righthalf[j]
            j=j+1
            k=k+1

alist = random.sample(range(10,50), 10)
alist = VisualArray(alist)
mergeSort(alist)
print(alist)
alist.render()
