#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "test.c"
using namespace std;

void sort(int* A, int n);
void radixsort(vector<int> buckets[], int A[], int d, int bucketSize, int n);

void sort(int* A, int n) {
  int bucketSize = 65536;
  vector<int> buckets[bucketSize];
  //buckets[0].push_back(1);
  //printf("%d\n", buckets[0][0] );
  radixsort(buckets, A, 0, bucketSize, n);
  radixsort(buckets, A, 1, bucketSize, n);
}

// int main () {
//   int A[10] = {587654, 687654, 187654, 387654 , 287654, 9487654, 987654, 887654, 7787654, 9187654};
//   sort(A, 10);
//   for(int i = 0; i < 10; ++i) {
//     printf("%d ", A[i]);
//   }
//   return 0;
// }

void radixsort (vector<int> buckets[], int A[], int d, int bucketSize, int n) {
  for (int i = 0; i < n; ++i) {
    int val;
    if (d == 0) {
      val = A[i] & 0xFFFF;
    } else {
      val = (A[i] >> 16) & 0xFFFF;
    }
    buckets[val].push_back(A[i]);
  }

  int ind = 0;
  for(int i = 0; i < bucketSize; ++i) {
    for (int j = 0; j < buckets[i].size(); ++j) {
      A[ind] = buckets[i][j];
      ++ind;
    }
  }
  for(int i = 0; i < bucketSize; ++i) {
    buckets[i].clear();
  }
}
