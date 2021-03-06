//CSC220
//Assignement 3 - Graph Exploration
//Kristina Ilyovska
//05/12/20

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
void find_path(int* g, int sx, int sy, int tx, int ty);
void done(Edge* path, int capacity, int sx, int sy, int tx, int ty);

void find_path(int* g, int sx, int sy, int tx, int ty) {
  //makes a copy of the graph, so it can be modified without affecting visualization
  int graphSize = SIZE * SIZE * 4;
  int graph [graphSize];
  for (int i = 0; i < graphSize; ++i) {
    graph[i] = g[i];
  }

  //creates a queue
  Queue* q;
  q = (Queue*) malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;

  //adding all the FREE outgoing edges from vertex S
  if (sx + 1 < SIZE && graph[sx * SIZE * 4 + sy * 4 + 0] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx + 1, .target.y_coord = sy};
    add(q, temp);
    used_edge(sx, sy, sx + 1, sy);
    graph[sx * SIZE * 4 + sy * 4 + 0] = BLOCKED;
    graph[(sx + 1) * SIZE * 4 + sy * 4 + 2] = BLOCKED;
  }

  if (sy + 1 < SIZE && graph[sx * SIZE * 4 + sy * 4 + 1] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx, .target.y_coord = sy + 1};
    add(q, temp);
    used_edge(sx, sy, sx, sy + 1);
    graph[sx * SIZE * 4 + sy * 4 + 1] = BLOCKED;
    graph[sx * SIZE * 4 + (sy + 1) * 4 + 3] = BLOCKED;
  }

  if (sx - 1 >= 0 && graph[sx * SIZE  * 4 + sy * 4 + 2] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                 .target.x_coord = sx - 1, .target.y_coord = sy};
    add(q, temp);
    used_edge(sx, sy, sx - 1, sy);
    graph[sx * SIZE * 4 + sy * 4 + 2] = BLOCKED;
    graph[(sx - 1) * SIZE * 4 + sy * 4 + 0] = BLOCKED;
  }

  if (sy - 1 >= 0 && graph[sx * SIZE * 4 + sy * 4 + 3] == FREE) {
    Edge temp = {.start.x_coord = sx, .start.y_coord = sy,
                  .target.x_coord = sx, .target.y_coord = sy - 1};
    add(q, temp);
    used_edge(sx, sy, sx, sy - 1);
    graph[sx * SIZE * 4 + sy * 4 + 3] = BLOCKED;
    graph[sx * SIZE * 4 + (sy - 1) * 4 + 1] = BLOCKED;
  }

  //creates an array of edges to recreate the shortest path if it exists
  Edge path [SIZE * SIZE  * 4];
  int capacity = 0;

  while (!isEmpty(q)) {

    Edge temp = pop(q);
    path[capacity] = temp;
    ++capacity;

    if (temp.target.x_coord == tx && temp.target.y_coord == ty) {
      done(path, capacity, sx, sy, tx, ty);
      printf("Goal reached!\n");
      //free rest of queue
      while (!isEmpty(q)) {
        pop(q);
      }
      free(q);
      return;
    }

    //add free edges from temp and mark them as BLOCKED, so that they are not visited again
    //block them from both directions
    if (temp.target.x_coord + 1 < SIZE && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 0] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord + 1,
                            .target.y_coord = temp.target.y_coord};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord + 1, temp.target.y_coord);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 0] = BLOCKED;
      graph[(temp.target.x_coord + 1) * SIZE * 4 + temp.target.y_coord * 4 + 2] = BLOCKED;
    }

    if (temp.target.y_coord + 1 < SIZE && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 1] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord,
                            .target.y_coord = temp.target.y_coord + 1};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord, temp.target.y_coord + 1);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 1] = BLOCKED;
      graph[temp.target.x_coord * SIZE * 4 + (temp.target.y_coord + 1) * 4 + 3] = BLOCKED;
    }

    if (temp.target.x_coord - 1 >= 0 && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 2] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                  .start.y_coord = temp.target.y_coord,
                  .target.x_coord = temp.target.x_coord - 1,
                  .target.y_coord = temp.target.y_coord};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord - 1, temp.target.y_coord);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 2] = BLOCKED;
      graph[(temp.target.x_coord - 1) * SIZE * 4 + temp.target.y_coord * 4 + 0] = BLOCKED;
    }

    if (temp.target.y_coord - 1 >= 0 && graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 3] == FREE) {
      Edge temp_neighbor = {.start.x_coord = temp.target.x_coord,
                            .start.y_coord = temp.target.y_coord,
                            .target.x_coord = temp.target.x_coord,
                            .target.y_coord = temp.target.y_coord - 1};
      add(q, temp_neighbor);
      used_edge(temp.target.x_coord, temp.target.y_coord, temp.target.x_coord, temp.target.y_coord - 1);
      graph[temp.target.x_coord * SIZE * 4 + temp.target.y_coord * 4 + 3] = BLOCKED;
      graph[temp.target.x_coord * SIZE * 4 + (temp.target.y_coord - 1) * 4 + 1] = BLOCKED;
    }
  }
  printf("No path between a and b :-( \n");
  free(q);
}

//recreates the shortest path and colors it in orange
void done(Edge* path, int capacity, int sx, int sy, int tx, int ty) {
  int targetX = tx;
  int targetY = ty;
  while (!(sx == targetX && sy == targetY)) {
    // printf("sx == %d, sy == %d, targetX == %d, targety = %d\n", sx, sy, targetX, targetY);
    for (int i = capacity - 1; i >= 0; --i) {
      if (path[i].target.x_coord == targetX && path[i].target.y_coord == targetY) {
        path_edge(path[i].start.x_coord, path[i].start.y_coord, targetX, targetY);
        targetX = path[i].start.x_coord;
        targetY = path[i].start.y_coord;
        break;
      }
    }
  }
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
      printf("(%d, %d), (%d, %d) || ", begin->edge.start.x_coord, begin->edge.start.y_coord, begin->edge.target.x_coord, begin->edge.target.y_coord);
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
