//CSC220
//Assignement 3 - Graph Exploration
//Kristina Ilyovska
//11/20/20

#include <stdio.h>
#include <stdlib.h>
// #include "test.c"

typedef struct Vertex {
  int x_coord;
  int y_coord;
} Vertex;

typedef struct Edge {
  Vertex start;
  Vertex target;
} Edge;

typedef struct Node {
  Edge edge; //Vertex v;
  struct Node* next;
} Node;

typedef struct Queue {
  Node* head;
  Node* tail;
} Queue;

void printQueue(Queue* list);
//void add(Queue* list, int val);
void add(Queue* list, Edge e);
//int pop(Queue* list);
Edge* pop(Queue* list);
//int inspect(Queue* list);
int isEmpty(Queue* list);
void find_path(int* graph, int sx, int sy, int tx, int ty);

void find_path(int* graph, int sx, int sy, int tx, int ty) {

}

int isEmpty(Queue* list) {
  if (list->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

// void add(Queue* list, int val) { //insert a node in a queue
//     if (list->head == NULL) {
//       list->head = (Node*)malloc(sizeof(Node));
//       list->head->value = val;
//       list->head->next = NULL;
//       list->tail = list->head;
//     } else {
//       Node* temp = (Node*)malloc(sizeof(Node));
//       temp->value = val;
//       temp->next = NULL;
//       list->tail->next = temp;
//       list->tail = temp;
//     }
// }

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
      printf("(%d, %d), (%d, %d) || ", begin->edge.start.x_coord, begin->edge.start.y_coord, begin->edge.target.x_coord, begin->edge.target.y_coord);
      begin = begin->next;
    }
  }
}

// int pop(Queue* list) {
//   if (list == NULL) {
//     printf("NULL POINTER");
//     return -1;
//   } else if (list->head == NULL) {
//     printf("EMPTY QUEUE");
//     return -1;
//   }else {
//     int first = list->head->value;
//     Node* temp = list->head;
//     list->head = list->head->next;
//     free(temp);
//     return first;
//   }
// }

Edge* pop(Queue* list) {
  if (list == NULL) {
    printf("NULL POINTER");
    return -1;
  } else if (list->head == NULL) {
    printf("EMPTY QUEUE");
    return -1;
  }else {
    Edge* e = (Edge*)(malloc(sizeof(Edge))); //where to dealocate
    e->start.x_coord = list->head->edge.start.x_coord;
    e->start.y_coord = list->head->edge.start.y_coord;
    e->target.x_coord = list->head->edge.target.x_coord;
    e->target.y_coord = list->head->edge.target.y_coord;
    Node* temp = list->head;
    list->head = list->head->next;
    free(temp);
    return e;
  }
}

// int inspect(Queue* list) {
//   if (list == NULL) {
//     printf("NULL POINTER");
//     return - 1;
//   } else if (list->head == NULL) {
//     printf("EMPTY QUEUE");
//     return -1;
//   } else {
//     return list->head->value;
//   }
// }

int main() {
  Queue* start;
  start = (Queue*) malloc(sizeof(Queue));
  start->head = NULL;
  start->tail = NULL;;
  int empty = isEmpty(start);
  printf("empty == %d\n", empty);
  for (int i = 0; i < 10; ++i) {
    Edge e;
    e.start.x_coord = i;
    e.start.y_coord = i;
    e.target.x_coord = i + 1;
    e.target.y_coord = i + 1;
    add(start, e);
  }
  printf("Added edges\n");
  printQueue(start);
  printf("\n--------------------\n");
  // Edge* i = pop(start);
  // printf("Popped one edge\n");
  // printQueue(start);
  // printf("\n---------------------\n");
  // i = pop(start);
  // printf("Popped one edge\n");
  // printQueue(start);
  // printf("\n---------------------\n");
  for (int i = 0; i < 10; ++i) {
    Edge* i = pop(start);
  }
  // i = inspect(start);
  // printf("i == %d\n", i);
  // printQueue(start);
  // printf("\n---------------------\n");
  empty = isEmpty(start);
  printf("empty == %d\n", empty);
  return 0;
}
