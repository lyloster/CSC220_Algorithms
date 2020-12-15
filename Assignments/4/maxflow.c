// //CSC220
// //Assignement 4
// //Kristina Ilyovska
// //12/12/20
//
// #include <stdio.h>
// #include <stdlib.h>
// #include "test.c"
//
// typedef struct Vertex {
//   int x_coord;
//   int y_coord;
// } Vertex;
//
// typedef struct Node {
//   Vertex v;
//   struct Node* next;
// } Node;
//
// typedef struct Queue {
//   Node* head;
//   Node* tail;
// } Queue;
//
// void printQueue(Queue* list);
// void add(Queue* list, Vertex v);
// Vertex pop(Queue* list);
// int isEmpty(Queue* list);
// int maxflow(int n, int *cap, int *flow, int *residual);
//
// int maxflow(int n, int *cap, int *flow, int *residual){
//
//
// //   for (int i = 0; i < n; ++i) {
// //     for (int j = 0; j < n; ++j) {
// //       printf("%d ", cap[i * n + j]);
// //     }
// //     printf("\n");
// //   }
// //
// //
// // printf("\n");
// //construct residual
// for (int i = 0; i < n; ++i) {
//   for (int j = 0; j < n; ++j) {
//     residual[i * n + j] = cap[i *n + j] - flow[i * n + j];
//   }
//   printf("\n");
// }
//
// int res[n][n];
// for (int i = 0; i < n; ++i) {
//   for (int j = 0; j < n; ++j) {
//     res[i][j] = residual[i * n + j];
//   }
// }
// for (int i = 0; i < n; ++i) {
//     for (int j = 0; j < n; ++j) {
//       printf("%d ", residual[i * n + j]);
//     }
//     printf("\n");
// }
// printf("\n");
// printf("\n");
// printf("\n");
// for (int i = 0; i < n; ++i) {
//   for (int j = 0; j < n; ++j) {
//     printf("%d ", res[i][j]);
//   }
//   printf("\n");
// }
// // printf("\n");
// //   for (int i = 0; i < n; ++i) {
// //     for (int j = 0; j < n; ++j) {
// //       printf("%d ", flow[i * n + j]);
// //     }
// //     printf("\n");
// //   }
//   Vertex* path[n * n];
//   int pathLength = 0;
//   Queue* q;
//   q = (Queue*) malloc(sizeof(Queue));
//   q->head = NULL;
//   q->tail = NULL;
//   Vertex vertex;
//   vertex.x_coord = 0;
//   vertex.y_coord = 1;
//   add(q,vertex);
//   printQueue(q);
//
//   while (!isEmpty(q)) {
//     Vertex temp = pop(q);
//     path[pathLength] = temp;
//     ++pathLength;
//
//     if(temp.x_coord + 1 < n && res[temp.x_coord][temp.y_coord] > 0){
//       Vertex v = {temp.x_coord + 1, temp.y_coord};
//       add(q, v);
//     }
//   }
//   return 0;
// }
//
// //QUEUE utility methods
// int isEmpty(Queue* list) {
//   if (list->head == NULL) {
//     return 1;
//   } else {
//     return 0;
//   }
// }
//
// void add(Queue* list, Vertex vertex) { //insert a node in a queue
//     if (list->head == NULL) {
//       list->head = (Node*)malloc(sizeof(Node));
//       list->head->v.x_coord = vertex.x_coord;
//       list->head->v.y_coord = vertex.y_coord;
//       list->head->next = NULL;
//       list->tail = list->head;
//     } else {
//       Node* temp = (Node*)malloc(sizeof(Node));
//       list->head->v.x_coord = vertex.x_coord;
//       list->head->v.y_coord = vertex.y_coord;
//       temp->next = NULL;
//       list->tail->next = temp;
//       list->tail = temp;
//     }
// }
//
// void printQueue(Queue* list) {
//   if (list == NULL) {
//     printf("NULL POINTER");
//   } else if (list->head == NULL) {
//     printf("EMPTY QUEUE");
//   } else {
//     Node* begin = list->head;
//     while(begin != NULL) {
//       printf("(%d, %d)", begin->v.x_coord, begin->v.y_coord);
//       begin = begin->next;
//     }
//   }
// }
//
// Vertex pop(Queue* list) {
//     Vertex v = list->head->v;
//     Node* temp = list->head;
//     list->head = list->head->next;
//     free(temp);
//     return v;
// }
