from visualarray import VisualArray

def quickSort(alist):
   quickSortHelper(alist,0,len(alist)-1,0)

def quickSortHelper(alist,first,last,level):
    if first<last:
    	alist.gfx_separate(first, width=2*level+1) # Add separators to mark
    	alist.gfx_separate(last+1, width=2*level+1) # where the current operations are

    	splitpoint = partition(alist,first,last)

    	quickSortHelper(alist,first,splitpoint-1,level+1)
    	quickSortHelper(alist,splitpoint+1,last,level+1)

    	alist.gfx_deseparate(first) # Remove the
    	alist.gfx_deseparate(last+1) # separators

def partition(alist,first,last):
   pivotvalue = alist[first]
   alist.gfx_color(first, "green") # Color the pivot element green

   leftmark = first+1
   rightmark = last

   done = False
   while not done:

       while leftmark <= rightmark and \
               alist[leftmark] <= pivotvalue:
           leftmark = leftmark + 1

       while alist[rightmark] >= pivotvalue and \
               rightmark >= leftmark:
           rightmark = rightmark -1

       if rightmark < leftmark:
           done = True
       else:
           temp = alist[leftmark]
           alist[leftmark] = alist[rightmark]
           alist[rightmark] = temp

   temp = alist[first]
   alist[first] = alist[rightmark]
   alist[rightmark] = temp

   alist.gfx_decolor(first) # Change the pivot element back to default color

   return rightmark

alist = [54,26,93,17,77,31,44,55,20]
alist = VisualArray(alist) # This is the only change needed
quickSort(alist)
alist.render()
