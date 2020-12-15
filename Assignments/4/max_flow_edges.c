//CSC220
//Assignement 4
//Kristina Ilyovska
//12/12/20

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
  // int visited[n * n];
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     visited[i * n + j] = 0;
  //   }
  // }

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
      //visited[0 + j] = VISITED;
    }
  }

  while (!isEmpty(q)) {
    Edge temp = pop(q);
    path[pathLength] = temp;
    ++pathLength;

    //done
    // if () {
    //
    // }

    for (int j = 0; j < n; ++j) {
    //  printf("in for in while\n");
      // if (residual[temp.end * n + j] != 0 && visited[temp.end * n + j] != VISITED) {
      if (residual[temp.end * n + j] != 0) {
        Edge neighbor = {.begin = temp.end, .end = j};
        add(q, neighbor);
        //visited[temp.end * n + j] = VISITED;
      }
    }
  }


  printf("Possible path: ");
  for (int i = 0; i < pathLength; ++i) {
    printf(" [%d] to [%d] ||", path[i].begin, path[i].end);
  }
  printf("\n");
  printf("\n");
  //find the shortest path?
  Edge shortest[pathLength];
  int lengthS = 0;
  int start = 0;
  // int end;
  // //while (start != n){
  //   //printf("in while\n");
  //   for (int i = 0; i < pathLength; ++i) { //when one is done it doesn't find shortest path
  //       if(path[i].begin == start) {
  //         Edge t = {path[i].begin, path[i].end};
  //         start = path[i].end;
  //         shortest[lengthS] = t;
  //         ++lengthS;
  //       }
  //   //break;
  //   //}
  // }
  if (path[pathLength - 1].end != n - 1) return 0;
  int end = path[pathLength - 1].end;
  for (int i = pathLength - 1; i >= 0; --i) {
    if(path[i].end == end) {
      Edge t = {path[i].begin, path[i].end};
      end = path[i].begin;
      shortest[lengthS] = t;
      ++lengthS;
    }
  }

  //no further improvements
  //if (shortest[lengthS - 1].end != n - 1) return 0;

  //random prints

  printf("Shortest path: ");
  for (int i = 0; i < lengthS; ++i) {
    printf(" [%d] to [%d] ||", shortest[i].begin, shortest[i].end);
  }
  printf("\n");

  //find minimum improvements //doesn't work with the shortest path
  // int minimum = residual[path[0].begin * n + path[0].end];
  // for (int i = 1; i < pathLength; ++i) {
  //   minimum = min(residual[path[i].begin * n + path[i].end], minimum);
  // }
  int minimum = residual[shortest[0].begin * n + shortest[0].end];
  for (int i = 1; i < lengthS; ++i) {
    minimum = min(residual[shortest[i].begin * n + shortest[i].end], minimum);
  }

  // int minimum = residual[shortest[0].begin * n + shortest[0].end];
  // for (int i = 1; i < pathLength; ++i) {
  //   minimum = min(residual[shortest[i].begin * n + shortest[i].end], minimum);
  // }

  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     if (cap[i * n + j] - flow[i * n + j] > 0) {
  //       printf("flow before increase: %d at edge %d -> %d\n", flow[i * n + j], i, j);
  //       flow[i * n + j] += minimum;
  //       printf("flow after increase: %d at edge %d -> %d\n\n", flow[i * n + j], i, j);
  //       //residual[i*n + j] = cap[i * n + j] - flow[i * n + j];
  //     }
  //     break;
  //   }
  // }

  // Edge shortest[pathLength];
  // int lengthS = 0;
  // int start = 0;
  // //while (start != n){
  //   //printf("in while\n");
  //   for (int i = 0; i < pathLength; ++i) {
  //       if(path[i].begin == start) {
  //         Edge t = {path[i].begin, path[i].end};
  //         start = path[i].end;
  //         shortest[lengthS] = t;
  //         ++lengthS;
  //       }
  //   //break;
  //   //}
  // }


  for (int i = 0; i < lengthS; ++i) {
    flow[shortest[i].begin * n + shortest[i].end] += minimum;
    printf("flow == %d, [%d] to [%d]\n", flow[shortest[i].begin * n + shortest[i].end], shortest[i].begin, shortest[i].end);
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
