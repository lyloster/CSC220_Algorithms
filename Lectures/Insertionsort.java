import java.util.Arrays;
/**
 * Insertion sort maintains the invariant that the array between 0 and i is already sorted.
 * If the next element (j) is out of order, jth element is placed at the right spot
 * and all other elements are shifted.
 * O(n^2), works better if array is mostly sorted.
 *
 * */
public class Insertionsort {

    public static void insertionsort(int[] arr) {
        for (int i = 1; i < arr.length; ++i) {
            int j = i - 1;
            int key = arr[i];
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    public static void main(String[] args) {
        int[] arr2 = {3,4,6,2,2,1};
        insertionsort(arr2);
        System.out.println(Arrays.toString(arr2));

    }
}
