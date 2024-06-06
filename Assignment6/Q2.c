//
// Shortest Distances
//
// Based on BFS algorithm, find the shortest distance from vertex v to vertex w in an undirected graph
// Vertices range from 1 to |V|
// Distance is measured by number of edges
// If there is no path from vertex v to vertex z, return -1
// May assume the graph is always valid
//
// Sample Input:
// 5
// 1 2
// 1 4
// 2 3
// 3 4
// 4 5
// a
// 1 5
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
    int vertex;
    struct _listnode *next;
} ListNode;

typedef struct _graph {
    int V;
    int E;
    int *visited;
    int **matrix;
} Graph;

typedef ListNode QueueNode;

typedef struct _queue{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

int SD (Graph G, int v, int z);
void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

int main() {
    Graph g;
    int i, j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for (i = 0; i < g.V; i++) {
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));
    }

    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++) {
            g.matrix[i][j] = 0;
        }
    }

    g.visited = (int *) malloc(sizeof(int)*g.V);
    for (i = 0; i < g.V; i++) {
        g.visited[i] = 0;
    }

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while (scanf("%d %d", &V1, &V2) == 2) {
        if ((V1 > 0) && (V1 <= g.V) && (V2 > 0) && (V2 <= g.V)) {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else {
            break;
        }
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    // printGraphMatrix(g);
    
    printf("Enter two vertices for finding their shortest distance: (press a to stop)\n");
    scanf("%d %d", &i, &j);

    int d = SD(g, i, j);
    if (d == -1) {
        printf("%d and %d are unconnected.\n", i, j);
    }
    else {
        printf("The shortest distance is %d\n", d);
    }
}

int SD(Graph g, int v, int z) {
    // if both input vertices are the same
    if (v == z) {
        return -1;
    }

    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;
    
    int *dist = (int *) malloc(g.V*sizeof(int));

    for (int i = 0; i < g.V; i++) {
        dist[i] = 0;
    }

    enqueue(&q, v);
    g.visited[v-1] = 1;

    while(isEmptyQueue(q) != 1) { // while queue is not empty
        int w = dequeue(&q);
        
        // if dequeued item is target
        if (w == z) {
            return dist[w-1];
        }
        
        for (int vertex = 1; vertex <= g.V; vertex++) { // iterate through all the vertices one by one
            // if adjacent based on adjacency matrix, and vertex yet visited
            if(g.matrix[w-1][vertex-1] == 1 && g.visited[vertex-1] == 0) {
                enqueue(&q, vertex);
                g.visited[vertex-1] = 1; // indicate that vertex already visited
                dist[vertex-1] = dist[w-1] + 1;
            }
        }
    }

    return -1;
}

void printGraphMatrix(Graph g) {
    int i, j;

    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++) {
            printf("%d\t", g.matrix[i][j]);
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        exit(0);
    }

    newNode->vertex = item;
    newNode->next = NULL;

    if (isEmptyQueue(*qPtr)) {
        qPtr->head = newNode;
    }
    else {
        qPtr->tail->next = newNode;
    }

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if (qPtr == NULL || qPtr->head == NULL) { //Queue is empty or NULL pointer
        return 0;
    }
    else {
        int headValue = qPtr->head->vertex;
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL) { //Queue is emptied
            qPtr->tail = NULL;
        }
        
        free(temp);
        qPtr->size--;
        return headValue;
    }
}

int getFront(Queue q) {
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if (q.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void removeAllItemsFromQueue(Queue *qPtr) {
    while(dequeue(qPtr));
}
