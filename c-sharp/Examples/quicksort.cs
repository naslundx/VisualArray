using System;
using VisualArray;

public class Test
{
    static int MyPartition(int[] list, int left, int right)
    {
        int start = left;
        int pivot = list[start];
        left++;
        right--;

        while (true)
        {
            while (left <= right && list[left] <= pivot)
                left++;

            while (left <= right && list[right] > pivot)
                right--;

            if (left > right)
            {
                list[start] = list[left - 1];
                list[left - 1] = pivot;

                return left;
            }


            int temp = list[left];
            list[left] = list[right];
            list[right] = temp;
        }
    }

    static void MyQuickSort(int[] list, int left, int right)
    {
        if (list.Count <= 1)
            return;

        if (left < right)
        {
            int pivotIdx = MyPartition(list, left, right);
            MyQuickSort(list, left, pivotIdx - 1);
            MyQuickSort(list, pivotIdx, right);
        }
    }

    public static void Main()
    {
        int[] numbers = {15, 23, 12, 10, 17, 30};
        VisualArray<int> varray(numbers);
        MyQuickSort(varray, 0, varray.Count);
    }
}