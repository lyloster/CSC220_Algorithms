#include <stdio.h>
#include <stdlib.h>
#include "test.c"

typedef struct node { int value;
                   struct node *next;
                } node;

void printLL(node* start);
void insert (node* start, int val);
void printBuckets(node* A[], int n);
void sort(int* A, int n);
void freeBuckets(node* A[], int n);
int findDigit(int a, int position);
int findPow(int x, int power);

void sort(int* A, int n) {
  // for(int i = 0; i < n; ++i) {
  //   printf("%d ", A[i]);
  // }
  // printf("\n");
  int bucketSize = 64000;
  node* buckets[bucketSize];

  for (int i = 0; i < bucketSize; ++i) {
    buckets[i] = NULL;
  }

for(int j = 1; j <= 3; ++j) {
  for (int i = 0; i < n; ++i) {
    int val = findDigit(A[i], j);
    if (buckets[val] == NULL) {
      node* current = (node*) malloc(sizeof(node));
      current->value = A[i];
      current->next = NULL;
      buckets[val] = current;
    } else {
      insert(buckets[val], A[i]);
    }
  }

  // printBuckets(buckets, bucketSize);

  int ind = 0;
  for(int i = 0; i < bucketSize; ++i) {
    while(buckets[i] != NULL) {
      A[ind] = buckets[i]->value;
      buckets[i] = buckets[i]->next;
      ++ind;
    }
  }
  // for(int i = 0; i < n; ++i) {
  //   printf("%d ", A[i]);
  // }
  // printf("\n");
  freeBuckets(buckets, bucketSize);
}

}

// int main () {
//   int A[10] = {24,22,8,2,31,20,27,31,0,9};
//   sort(A, 10);
//   for(int i = 0; i < 10; ++i) {
//     printf("%d ", A[i]);
//   }
//   return 0;
// }

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

int findDigit(int a, int position) {
  return (a % findPow(4, position)) / findPow(4, position - 1);
}

int findPow(int x, int power) {
  if (power == 0) return 1;
  int base = x;
  for (int i = 1; i < power; ++i) {
    x *= base;
  }
  return x;
}
