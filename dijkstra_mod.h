typedef struct graphNode {
    int data;
    int weight;
    struct graphNode *next;
} gNode;

typedef struct ptyQueueNode {
    int vid;
    int dist;
    int pred;
} pqNode;

void insertGraph(gNode **a, int i, int j, int wt);
void readGraph(FILE *fp, gNode **a, int NUM_VERTICES);
void display(gNode** a, int n);
void bottomUpHeap(pqNode** h, int n);
void heapify(pqNode** h, int n);
pqNode *extractMin(pqNode **pq, int *n);
int inHeap(pqNode **pq, int n, int vid);
void updateHeap(pqNode **pq, int n, int vid, int dist, int p);