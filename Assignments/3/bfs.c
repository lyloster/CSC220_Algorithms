//CSC220
//Assignement 3 - Graph Exploration
//Kristina Ilyovska
//11/20/20

#include <stdio.h>
#include <stdlib.h>
#include "test.c"

#define VISITED 2

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


  // for (int i = 0; i < SIZE; ++i) {
  //   for (int j = 0; j < SIZE; ++j) {
  //     printf("i == %d, j == %d, k == 0, graph[%d][%d][0] == %d\n", i, j, i, j, graph[i * SIZE * 4 + j * 4]);
  //     printf("i == %d, j == %d, k == 1, graph[%d][%d][1] == %d\n", i, j, i, j, graph[i * SIZE * 4 + j * 4 + 1]);
  //     printf("i == %d, j == %d, k == 2, graph[%d][%d][2] == %d\n", i, j, i, j, graph[i  * SIZE * 4 + j * 4 + 2]);
  //     printf("i == %d, j == %d, k == 3, graph[%d][%d][3] == %d\n", i, j, i, j, graph[i  * SIZE * 4 + j * 4 + 3]);
  //   }
  // }
  Queue* q;
  //printf("1\n");
  q = (Queue*) malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  int elements = 0;
  //printf("2\n");
  //adding all the FREE outgoing edges from vertex S
  if (sx + 1 < SIZE && graph[sx * SIZE * 4 + sy * 4 + 0] == FREE) {
    //printf("3\n");
    ++elements;
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx + 1, .target.y_coord = sy};
    //printf("4\n");
    add(q, temp);
    //printf("5\n");
    used_edge(sx, sy, sx + 1, sy);
    graph[sx * SIZE * 4 + sy * 4 + 0] = BLOCKED;
    graph[(sx + 1) * SIZE * 4 + sy * 4 + 2] = BLOCKED;
    //printf("6\n");
  }
  if (sy + 1 < SIZE && graph[sx * SIZE * 4 + sy * 4 + 1] == FREE) {
    //printf("7\n");
    ++elements;
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx, .target.y_coord = sy + 1};
    //printf("8\n");
    add(q, temp);
    //printf("9\n");
    used_edge(sx, sy, sx, sy + 1);
    graph[sx * SIZE * 4 + sy * 4 + 1] = BLOCKED;
    graph[sx * SIZE * 4 + (sy + 1) * 4 + 3] = BLOCKED;
    //printf("10\n");
  }
  if (sx - 1 >= 0 && graph[sx * SIZE  * 4 + sy * 4 + 2] == FREE) {
    //printf("11\n");
    ++elements;
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                 .target.x_coord = sx - 1, .target.y_coord = sy};
    //printf("12\n");
    add(q, temp);
    //printf("13\n");
    used_edge(sx, sy, sx - 1, sy);
    graph[sx * SIZE * 4 + sy * 4 + 2] = BLOCKED;
    graph[(sx - 1) * SIZE * 4 + sy * 4 + 0] = BLOCKED;
    //printf("14\n");
  }
  if (sy - 1 >= 0 && graph[sx * SIZE * 4 + sy * 4 + 3] == FREE) {
    //printf("15\n");
    ++elements;
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx, .target.y_coord = sy - 1};
    //printf("16\n");
    add(q, temp);
    //printf("17\n");
    used_edge(sx, sy, sx, sy - 1);
    graph[sx * SIZE * 4 + sy * 4 + 3] = BLOCKED;
    graph[sx * SIZE * 4 + (sy - 1) * 4 + 1] = BLOCKED;
    //printf("18\n");
  }
  //printf("19\n");
  //Edge path [SIZE * SIZE * SIZE * 4];
  //printf("20\n");
  int capacity = 0;
  //printf("21\n");
  while (!isEmpty(q)) {
    //printf("22\n");
    Edge temp = pop(q);
    --elements;
    //printf("23\n");
    //path[capacity] = temp;
    //printf("24\n");
    ++capacity;
    if (capacity % 500 == 0) {
      printf("iteration == %d, elements in queue == %d\n", capacity, elements);
    }
    // if (capacity >= SIZE * SIZE * SIZE * 4) {
    //   printf("Queue is too small\n");
    // }
    //printf("25\n");

    if (temp.target.x_coord == tx && temp.target.y_coord == ty) {
      //printf("26\n");
      //done(graph, path, capacity, sx, sy, tx, ty);
      //printf("27\n");
      printf("Goal reached!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
      while(1);
      return; //return?
      //printf("28\n");
    }

    if (temp.target.x_coord + 1 < SIZE && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 0] == FREE) {
      ++elements;
      //printf("29\n");
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord + 1,
                            .target.y_coord = temp.target.y_coord};
      //printf("30\n");
      add(q, temp_neighbor);
      //printf("31\n");
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord + 1, temp.target.y_coord);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 0] = BLOCKED;
      graph[(temp.target.x_coord + 1) * SIZE * 4 + temp.target.y_coord * 4 + 2] = BLOCKED;
      //printf("32\n");
    }

    if (temp.target.y_coord + 1 < SIZE && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 1] == FREE) {
      ++elements;
      //printf("33\n");
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord,
                            .target.y_coord = temp.target.y_coord + 1};
      //printf("34\n");
      add(q, temp_neighbor);
      //printf("35\n");
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord, temp.target.y_coord + 1);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 1] = BLOCKED;
      graph[temp.target.x_coord * SIZE * 4 + (temp.target.y_coord + 1) * 4 + 3] = BLOCKED;
      // //printf("36\n");
    }

    if (temp.target.x_coord - 1 >= 0 && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 2] == FREE) {
      ++elements;
      //printf("37\n");
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                  .start.y_coord = temp.target.y_coord,
                  .target.x_coord = temp.target.x_coord - 1,
                  .target.y_coord = temp.target.y_coord};
      //printf("38\n");
      add(q, temp_neighbor);
      //printf("39\n");
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord - 1, temp.target.y_coord);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 2] = BLOCKED;
      graph[(temp.target.x_coord - 1) * SIZE * 4 + temp.target.y_coord * 4 + 0] = BLOCKED;
      //printf("40\n");
    }

    if (temp.target.y_coord - 1 >= 0 && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 3] == FREE) {
      ++elements;
      //printf("41\n");
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord,
                            .target.y_coord = temp.target.y_coord - 1};
      //printf("1\n");
      add(q, temp_neighbor);
      //printf("42\n");
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord, temp.target.y_coord - 1);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 3] = BLOCKED;
      graph[temp.target.x_coord * SIZE * 4 + (temp.target.y_coord - 1) * 4 + 1] = BLOCKED;
      //printf("43\n");
    }
  }
  printf("No path between a and b :-( \n");
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
  //printf("in add: 1\n");
    if (list->head == NULL) {
      //printf("in add, if: 2\n");
      list->head = (Node*)malloc(sizeof(Node));
      //printf("in add, if: 3\n");
      list->head->edge = e;
      //printf("in add, if: 4\n");
      list->head->next = NULL;
      //printf("in add, if: 5\n");
      list->tail = list->head;
      //printf("in add, if: 6\n");
    } else {
      //printf("in add, else: 2\n");
      Node* temp = (Node*)malloc(sizeof(Node));
      //printf("in add, else: 3\n");
      temp->edge = e;
      //printf("in add, else: 4\n");
      temp->next = NULL;
      //printf("in add, else: 5\n");
      list->tail->next = temp;
      //printf("in add, else: 6\n");
      list->tail = temp;
      //printf("in add, else: 7\n");
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
