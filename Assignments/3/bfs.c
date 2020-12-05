//CSC220
//Assignement 3 - Graph Exploration
//Kristina Ilyovska
//11/20/20

#include <stdio.h>
#include <stdlib.h>
#include "test.c"

typedef struct Vertex {
  int x_coord;
  int y_coord;
} Vertex;

typedef struct Edge {
  Vertex start;
  Vertex target;
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
void find_path(int* graph, int sx, int sy, int tx, int ty);
void done(int* graph, Edge* path, int capacity, int sx, int sy, int tx, int ty);

//should be moved in test?
void find_path(int* graph, int sx, int sy, int tx, int ty) {
  // printf("(1,1) to (1,2): %d\n", graph[1 * SIZE * SIZE + 1 * SIZE + 0]);
  // printf("(2,2) to (2,3): %d\n", graph[2 * SIZE * SIZE + 2 * SIZE + 0]);
  // printf("(2,3) to (2,4): %d\n", graph[2 * SIZE * SIZE + 3 * SIZE + 0]);
  // printf("(2,4) to (2,5): %d\n", graph[2 * SIZE * SIZE + 4 * SIZE + 0]);
  // printf("");

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      printf("i == %d, j == %d, k == 0, graph[%d][%d][0] == %d\n", i, j, i, j, graph[i * SIZE + j * SIZE]);
      printf("i == %d, j == %d, k == 1, graph[%d][%d][1] == %d\n", i, j, i, j, graph[i * SIZE + j * SIZE + 1]);
      printf("i == %d, j == %d, k == 2, graph[%d][%d][2] == %d\n", i, j, i, j, graph[i  * SIZE + j * SIZE + 2]);
      printf("i == %d, j == %d, k == 3, graph[%d][%d][3] == %d\n", i, j, i, j, graph[i  * SIZE + j * SIZE + 3]);
    }
  }
  Queue* q;
  q = (Queue*) malloc(sizeof(Queue));
  //adding all the FREE outgoing edges from vertex S
  if (sx + 1 < SIZE && graph[sx * SIZE + sy * SIZE + 0] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx + 1, .target.y_coord = sy};
    add(q, temp);
    used_edge(sx, sy, sx + 1, sy);
  }
  if (sy + 1 < SIZE && graph[sx * SIZE + sy * SIZE + 1] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx, .target.y_coord = sy + 1};
    add(q, temp);
    used_edge(sx, sy, sx, sy + 1);
  }
  if (sx - 1 > 0 && graph[sx * SIZE  + sy * SIZE + 2] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                 .target.x_coord = sx - 1, .target.y_coord = sy};
    add(q, temp);
    used_edge(sx, sy, sx - 1, sy);
  }
  if (sy - 1 > 0 && graph[sx * SIZE + sy * SIZE + 3] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx, .target.y_coord = sy - 1};
    add(q, temp);
    used_edge(sx, sy, sx, sy - 1);
  }

  Edge path [SIZE * SIZE];
  int capacity = 0;
  while (!isEmpty(q)) {
    Edge temp = pop(q);;
    path[capacity] = temp;
    ++capacity;

    if (temp.target.x_coord == tx && temp.target.y_coord == ty) {
      done(graph, path, capacity, sx, sy, tx, ty);
      break; //return?
    }

    if (temp.target.x_coord + 1 < SIZE && graph[temp.target.x_coord * SIZE + temp.target.y_coord * SIZE + 0] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord + 1,
                            .target.y_coord = temp.target.y_coord};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord, temp.target.y_coord + 1);
    }

    if (temp.target.y_coord + 1 < SIZE && graph[temp.target.x_coord * SIZE + temp.target.y_coord * SIZE + 1] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord,
                            .target.y_coord = temp.target.y_coord + 1};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord, temp.target.y_coord + 1);
    }

    if (temp.target.x_coord - 1 > 0 && graph[temp.target.x_coord * SIZE + temp.target.y_coord * SIZE + 2] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                  .start.y_coord = temp.target.y_coord,
                  .target.x_coord = temp.target.x_coord - 1,
                  .target.y_coord = temp.target.y_coord};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord - 1, temp.target.y_coord);
    }
    if (temp.target.y_coord - 1 > 0 && graph[temp.target.x_coord * SIZE + temp.target.y_coord * SIZE + 3] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord,
                            .target.y_coord = temp.target.y_coord - 1};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord, temp.target.y_coord - 1);
    }
  }
}

void done(int* graph, Edge* path, int capacity, int sx, int sy, int tx, int ty) {

}

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
      printf("(%d, %d), (%d, %d) || ", begin->edge.start.x_coord, begin->edge.start.y_coord, begin->edge.target.x_coord, begin->edge.target.y_coord);
      begin = begin->next;
    }
  }
}

Edge pop(Queue* list) {
  // if (list == NULL) {
  //   printf("NULL POINTER");
  //   return -1;
  // } else if (list->head == NULL) {
  //   printf("EMPTY QUEUE");
  //   return -1;
  // }else {
    //Edge* e = (Edge*)(malloc(sizeof(Edge))); //where to dealocate
    Edge e = list->head->edge;
    // e->start.x_coord = list->head->edge.start.x_coord;
    // e->start.y_coord = list->head->edge.start.y_coord;
    // e->target.x_coord = list->head->edge.target.x_coord;
    // e->target.y_coord = list->head->edge.target.y_coord;
    Node* temp = list->head;
    list->head = list->head->next;
    free(temp);
    return e;
  //}
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

// int main() {
//   Queue* start;
//   start = (Queue*) malloc(sizeof(Queue));
//   start->head = NULL;
//   start->tail = NULL;;
//   int empty = isEmpty(start);
//   printf("empty == %d\n", empty);
//   for (int i = 0; i < 10; ++i) {
//     Edge e;
//     e.start.x_coord = i;
//     e.start.y_coord = i;
//     e.target.x_coord = i + 1;
//     e.target.y_coord = i + 1;
//     add(start, e);
//   }
//   printf("Added edges\n");
//   printQueue(start);
//   printf("\n--------------------\n");
//    Edge i = pop(start);
//   // printf("Popped one edge\n");
//   // printQueue(start);
//   // printf("\n---------------------\n");
//   //i = pop(start);
//   printf("Popped one edge\n");
//   printQueue(start);
//   printf("\n---------------------\n");
//   printf("The popped edge: (%d, %d), (%d,%d)\n", i.start.x_coord, i.start.y_coord, i.target.x_coord, i.target.y_coord);
//   // for (int i = 0; i < 10; ++i) {
//   //   Edge* i = pop(start);
//   // }
//   // i = inspect(start);
//   // printf("i == %d\n", i);
//   // printQueue(start);
//   // printf("\n---------------------\n");
//   empty = isEmpty(start);
//   printf("empty == %d\n", empty);
//   return 0;
// }
