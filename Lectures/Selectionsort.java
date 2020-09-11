import java.util.Arrays;
/**
 * Always places the minimum element at the beginning by swapping the place of the minimal element
 * with the current element.
 * Every time looks for the minimum element from the beginning of the array.
 * O(n^2)
 * */
public class Selectionsort {

    public static void selectionsort(int[] arr) {
        for (int i = 0; i < arr.length - 1; ++i) {
            for (int j = i + 1; j < arr.length; ++j) {
                if (arr[j] < arr[i]) {
                    swap(arr, i, j);
                }
            }
        }
    }

    public static void selectionsortReverse(int[] arr) {
        for (int i = 0; i < arr.length - 1; ++i) {
            for (int j = i + 1; j < arr.length; ++j) {
                if (arr[j] > arr[i]) {
                    int temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                }
            }
        }
    }

    public static void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    public static void main(String[] args) {
        int[] arr = {3,4,6,2,2,1};
        selectionsort(arr);
        System.out.println(Arrays.toString(arr));
        int[] arr2 = {3,4,6,2,2,1};
        selectionsortReverse(arr2);
        System.out.println(Arrays.toString(arr2));
    }
}
