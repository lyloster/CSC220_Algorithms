// CSC220
// Assignment 2
// Kristina Ilyovska
// 10/19/2020

#include <stdio.h>
#include <stdlib.h>
#include "test.c"

typedef struct Node { int value;
                    struct Node* next;
                } Node;

typedef struct LinkedList {
                  Node* head;
                  Node* tail;
                }LinkedList;

void insert (LinkedList* list, int val);
void sort(int* A, int n);
void freeBuckets(LinkedList* A[], int n);
void radixsort(LinkedList* buckets[], int A[], int d, int bucketSize, int n);

void sort(int* A, int n) {
  int bucketSize = 65536; //2^16
  LinkedList* buckets[bucketSize];
  for (int i = 0; i < bucketSize; ++i) {
    buckets[i] = (LinkedList*) malloc(sizeof(LinkedList));
    buckets[i]->head = NULL;
    buckets[i]->tail = NULL;
  }
  radixsort(buckets, A, 0, bucketSize, n);
  radixsort(buckets, A, 1, bucketSize, n);
  for (int i = 0; i < bucketSize; ++i) {
    free(buckets[i]);
  }
}

void insert (LinkedList* list, int val) { //insert a node in a LL
    if (list->head == NULL) {
      list->head = (Node*)malloc(sizeof(Node));
      list->head->value = val;
      list->head->next = NULL;
      list->tail = list->head;
    } else {
      Node* temp = (Node*)malloc(sizeof(Node));
      temp->value = val;
      temp->next = NULL;
      list->tail->next = temp;
      list->tail = temp;
    }
}

void freeBuckets(LinkedList* A[], int n) { // free nodes from a LL
  for (int i = 0; i < n; ++i) {
    while(A[i]->head != NULL) {
      Node* temp = A[i]->head;
      A[i]->head = A[i]->head->next;
      free(temp);
    }
  }
}

void radixsort (LinkedList* buckets[], int A[], int d, int bucketSize, int n) { // sort by digit
  for (int i = 0; i < n; ++i) {
    int val;
    if (d == 0) {
      val = A[i] & 0xFFFF;
    } else {
      val = (A[i] >> 16) & 0xFFFF;
    }
    insert(buckets[val], A[i]);
  }
  int ind = 0;
  for(int i = 0; i < bucketSize; ++i) {
    while(buckets[i]->head != NULL) {
      A[ind] = buckets[i]->head->value;
      buckets[i]->head = buckets[i]->head->next;
      ++ind;
    }
  }
    freeBuckets(buckets, bucketSize);
}
