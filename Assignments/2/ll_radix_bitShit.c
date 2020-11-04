#include <stdio.h>
#include <stdlib.h>
//#include "test.c"

typedef struct node { int value;
                   struct node *next;
                } node;

void printLL(node* start);
void insert (node* start, int val);
void printBuckets(node* A[], int n);
void sort(int* A, int n);
void freeBuckets(node* A[], int n);
void radixsort(node* buckets[], int A[], int d, int bucketSize, int n);

void sort(int* A, int n) {
  int bucketSize = 65536;
  node* buckets[bucketSize];
  for (int i = 0; i < bucketSize; ++i) {
    buckets[i] = NULL;
  }
  radixsort(buckets, A, 0, bucketSize, n);
  radixsort(buckets, A, 1, bucketSize, n);
}

int main () {
  int A[10] = {587654, 687654, 187654, 387654 , 287654, 9487654, 987654, 887654, 7787654, 9187654};
  sort(A, 10);
  for(int i = 0; i < 10; ++i) {
    printf("%d ", A[i]);
  }
  return 0;
}

void insert (node* start, int val) {
    while(start->next != NULL) {
      start = start->next;
    }
    node* temp = (node*)malloc(sizeof(node));
    temp->value = val;
    temp->next = NULL;
    start->next = temp;
}

void printLL(node* start) {
  while(start != NULL) {
    printf("%d ", start->value);
    start = start->next;
  }
}

void printBuckets(node* A[], int n) {
  for (int i = 0; i < n; ++i) {
      printf("%d: ", i);
      printLL(A[i]);
      printf("\n");
  }
}

void freeBuckets(node* A[], int n) {
  for (int i = 0; i < n; ++i) {
    while(A[i] != NULL) {
      node* temp = A[i];
      A[i] = A[i]->next;
      free(temp);
    }
    free(A[i]);
  }
}


void radixsort (node* buckets[], int A[], int d, int bucketSize, int n) {
  for (int i = 0; i < n; ++i) {
    int val;
    if (d == 0) {
      val = A[i] & 0xFFFF;
    } else {
      val = (A[i] >> 16) & 0xFFFF;
    }
    if (buckets[val] == NULL) {
      node* current = (node*) malloc(sizeof(node));
      current->value = A[i];
      current->next = NULL;
      buckets[val] = current;
    } else {
      insert(buckets[val], A[i]);
    }
  }
  int ind = 0;
    for(int i = 0; i < bucketSize; ++i) {
      while(buckets[i] != NULL) {
        A[ind] = buckets[i]->value;
        buckets[i] = buckets[i]->next;
        ++ind;
      }
    }
    freeBuckets(buckets, bucketSize);
}
