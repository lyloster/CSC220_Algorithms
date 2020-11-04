#include <stdio.h>

int find_min(int* A, int n);
int find_max(int* A, int n);
void sort(int* A, int n);
int* counting_sort(int* A, int n, int* C, int range);

void sort(int* A, int n) {
  int max = find_max(A, n);
  printf("1\n");
  int min = find_min(A, n);
  printf("2\n");
  int range = max - min + 1; //inclusive, example from class to double-check
  printf("3\n");
  int* C = (int*)malloc(sizeof(int) * range);
  printf("4\n");
  A = counting_sort(A, n, C, range);
  printf("%d %d %d %d %d\n", A[0], A[1], A[2], A[3], A[4]);
  printf("5\n");
  free(C);
  printf("6\n");
}

int find_min(int* A, int n) {
  int min = A[0];
  for (int i = 1; i < n; ++i) {
    if (A[i] < min) {
      min = A[i];
    }
  }
  return min;
}

int find_max(int* A, int n) {
  int max = A[0];
  for (int i = 1; i < n; ++i) {
    if (A[i] > max) {
      max = A[i];
    }
  }
  return max;
}

int* counting_sort(int* A, int n, int* C, int range) {
  printf("--------------\n");
  printf("1\n");
  for (int i = 0; i < range; ++i) { //initialize aux to 0
    C[i] = 0;
  }
  printf("After initalizing to zero: %d %d %d %d\n", C[0], C[1], C[2], C[3]);
  printf("2\n");
  for (int j = 0; j < n; ++j) { //check how many time each value in range is in A
    //C[A[j]  - range] = C[A[j]   - range] + 1;
    C[A[j]] = C[A[j]] + 1;
  }
  printf("After counting reps: %d %d %d %d \n", C[0], C[1], C[2], C[3]);
  printf("3\n");
  for (int k = 0; k < range - 1; ++k) { //find cummulative sums of values in C
    C[k] = C[k] + C[k - 1];
  }
  printf("After cumm sums: %d %d %d %d \n", C[0], C[1], C[2], C[3]);
  printf("4\n");
  int* B = (int*)malloc(sizeof(int) * n);
  printf("5\n");
  for (int m = n; m > 0; --m) { //sort A
    // B[C[A[m] - range]] = A[m];
    // C[A[m] - range] = C[A[m] - range] - 1;
    B[C[A[m]]] = A[m];
    C[A[m]] = C[A[m]] - 1;
  }
  printf("After sorting: %d %d %d %d %d\n", B[0], B[1], B[2], B[3], B[4]);
  printf("6\n");
  printf("-------------\n");
  //free(A);
  return B;
}
