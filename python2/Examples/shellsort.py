from visualarray import VisualArray
import random

def shellSort(array):
     gap = len(array) // 2
     while gap > 0:
         for i in range(gap, len(array)):
             val = array[i]
             j = i
             
             while j >= gap and array[j - gap] > val:
                 array[j] = array[j - gap]
                 j -= gap
             array[j] = val

         gap = gap/2

alist = random.sample(xrange(10,50), 10)
alist = VisualArray(alist)
shellSort(alist)
print(alist)
alist.render()