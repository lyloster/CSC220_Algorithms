//CSC220
//Assignement 4
//Kristina Ilyovska
//12/11/20

#include <stdio.h>
#include <stdlib.h>
#include "test.c"

#define VISITED -1

typedef struct Edge {
  int begin;
  int end;
} Edge;

typedef struct Node {
  Edge edge;
  struct Node* next;
} Node;

typedef struct Queue {
  Node* head;
  Node* tail;
} Queue;

void printQueue(Queue* list);
void add(Queue* list, Edge e);
Edge pop(Queue* list);
int isEmpty(Queue* list);
int maxflow(int n, int *cap, int *flow, int *residual);
int min(int a, int b);

int maxflow(int n, int *cap, int *flow, int *residual){
  //construct residual
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      residual[i * n + j] = cap[i * n + j] - flow[i * n + j];
    }
  }

  Edge path[n * n];
  int pathLength = 0;

  Queue* q;
  q = (Queue*) malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;

  //add all non-zero edges from source
  for (int j = 0; j < n; ++j) {
    if (residual[0 + j] != 0) {
      Edge temp = {.begin = 0, .end = j};
      add(q, temp);
    }
  }

  while (!isEmpty(q)) {
    Edge temp = pop(q);
    path[pathLength] = temp;
    ++pathLength;
    for (int j = 0; j < n; ++j) {
      if (residual[temp.end * n + j] != 0) {
        Edge neighbor = {.begin = temp.end, .end = j};
        add(q, neighbor);
      }
    }
  }

  // printf("Possible path: ");
  // for (int i = 0; i < pathLength; ++i) {
  //   printf(" [%d] to [%d] ||", path[i].begin, path[i].end);
  // }
  // printf("\n");

  //path does not exist
  if (path[pathLength - 1].end != n - 1) return 0;
  Edge shortest[pathLength];
  int lengthS = 0;
  int start = 0;

  int end = path[pathLength - 1].end;
  for (int i = pathLength - 1; i >= 0; --i) {
    if(path[i].end == end) {
      Edge t = {path[i].begin, path[i].end};
      end = path[i].begin;
      shortest[lengthS] = t;
      ++lengthS;
    }
  }

  // printf("Shortest path: ");
  // for (int i = 0; i < lengthS; ++i) {
  //   printf(" [%d] to [%d] ||", shortest[i].begin, shortest[i].end);
  // }
  // printf("\n");

  //find minimum edge weight
  int minimum = residual[shortest[0].begin * n + shortest[0].end];
  for (int i = 1; i < lengthS; ++i) {
    minimum = min(residual[shortest[i].begin * n + shortest[i].end], minimum);
  }

  //adjust flow with minimum edge weight
  for (int i = 0; i < lengthS; ++i) {
    flow[shortest[i].begin * n + shortest[i].end] += minimum;
    //printf("flow == %d, [%d] to [%d]\n", flow[shortest[i].begin * n + shortest[i].end], shortest[i].begin, shortest[i].end);
  }
  return minimum;
}

int min(int a, int b) {
  if (a < b) return a;
  else return b;
}

//QUEUE utility methods
int isEmpty(Queue* list) {
  if (list->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

void add(Queue* list, Edge e) { //insert a node in a queue
  if (list->head == NULL) {
    list->head = (Node*)malloc(sizeof(Node));
    list->head->edge = e;
    list->head->next = NULL;
    list->tail = list->head;
  } else {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->edge = e;
    temp->next = NULL;
    list->tail->next = temp;
    list->tail = temp;
  }
}

void printQueue(Queue* list) {
  if (list == NULL) {
    printf("NULL POINTER");
  } else if (list->head == NULL) {
    printf("EMPTY QUEUE");
  } else {
    Node* begin = list->head;
    while(begin != NULL) {
      printf("[%d] to  [%d] || ", begin->edge.begin, begin->edge.end);
      begin = begin->next;
    }
  }
}

Edge pop(Queue* list) {
  Edge e = list->head->edge;
  Node* temp = list->head;
  list->head = list->head->next;
  free(temp);
  return e;
}
