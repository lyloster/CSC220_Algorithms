import java.util.Arrays;

public class MergeSort {
    //begin inclusive
    //end exclusive
    public static void  mergesort(int[] a, int begin, int end) {
        if (end - begin < 2) { // one or less elements in arr
            return;
        }
        int mid = (begin + end) / 2;
        mergesort(a, begin, mid);
        mergesort(a, mid, end);
        merge(a, begin, mid, end); //mid && end exclusive
    }

    //begin inclusive and mid exclusive or mid inclusive and end exclusive
    public static void merge(int[] a, int begin, int mid, int end) {
        int[] arrSorted = new int[end - begin];
        int i = 0;
        int firstHalfB = begin;
        int secondHalfB = mid;
        while (firstHalfB < mid && secondHalfB < end) {
            if (a[firstHalfB] < a[secondHalfB]) {
                arrSorted[i] = a[firstHalfB];
                ++firstHalfB;
            } else {
                arrSorted[i] = a[secondHalfB];
                ++secondHalfB;
            }
            ++i;
        }
        if (secondHalfB == end) {
            for (int j = firstHalfB; j < mid; ++j) {
                arrSorted[i] = a[j];
                ++i;
            }
        } else {
            for (int j = secondHalfB; j < end; ++j) {
                arrSorted[i] = a[j];
                ++i;
            }
        }

        for (int k = 0; k < arrSorted.length; ++k, ++begin) {
            a[begin] = arrSorted[k];
        }
    }

    public static void main(String[] args) {
        int[] arr = {3,4, 2, 3, 6, 4, 5, 7, 8,1,4 ,56, 7,2, 5,6,354, 565,42432, -1, 0};
        mergesort(arr, 0, arr.length);
        //merge(arr, 2, 5, 9);
        System.out.println(Arrays.toString(arr));
    }
}
