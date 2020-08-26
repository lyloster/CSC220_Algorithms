#include <stdio.h>


void swap(int& a, int& b);
void bubblesort(int* arr, int length);
void printSorted(int * a, int length);

int main() {
  int a[5] = {2,6,4,1,5};
	bubblesort(a, 5);
	printSorted(a,5);

  int b[5] = {6,2,4,1,2};
	bubblesort(b, 5);
	printSorted(b,5);
}

//bubblesort with O(n^2), n-1 passes
void bubblesort(int* arr, int length) { //pairwise switches
  int temp;
  int done = 0;
  while (!done) {
    done = 1;
    for (int i = 0; i < length - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
          swap(arr[i], arr[i + 1]);
          done = 0;
        }
    }
  }
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void printSorted(int * a, int length) {
	for (int i = 0; i < length; ++i) {
		printf("%d ", a[i]);
	}
  printf("\n");
}
