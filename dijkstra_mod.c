#include<stdio.h>
#include<stdlib.h>

#include"dijkstra_mod.h"

void insertGraph(gNode **a, int i, int j, int wt) {
    gNode *temp, *p;

    temp = (gNode *) malloc(sizeof(gNode));
    temp->data = j;
    temp->weight = wt;
    temp->next = NULL;

    p = a[i];
    if (p) {
        while (p->next)
            p = p->next;
        p->next = temp;
    }

    else
        a[i] = temp;
}

void readGraph(FILE *fp, gNode **a, int NUM_VERTICES) {
    int NODE_NUMBER, NODE_DEST, EDGE_WEIGHT;
    char ch;

    for (register int i = 0; i < NUM_VERTICES; i++) {
        fscanf(fp, "%d", &NODE_NUMBER);

        while (((ch = getc(fp)) != '\n') && (ch != '\r') && (!feof(fp))) {
            fscanf(fp, "%d ", &NODE_DEST);
            fscanf(fp, "%d", &EDGE_WEIGHT);

            insertGraph(a, NODE_DEST - 1, NODE_NUMBER - 1, EDGE_WEIGHT);
        }
    }
}

void display(gNode** a, int n) {
    gNode* temp;

    for (register int i = 0; i < n; i++) {
        printf("%d -> ", i);
        temp = a[i];

        while (temp != NULL) {
            printf(" <%d, %d> ", temp->data, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void bottomUpHeap(pqNode** h, int n) {
    int k, i, j;
    pqNode *key;
    for (k = (n-1) / 2; k >= 0; k--) {
        j = k; 
        key = h[j];
        i = 2 * j + 1;
        
        while (i < n) {
            if ((i + 1) < n)
                if (h[i+1]->dist < h[i]->dist)
                    i++;

            if (key->dist > h[i]->dist) {
                h[j] = h[i];
                j = i; 
                i = 2 * j + 1;
            }

            else break; 
        }

        h[j] = key;
    }
}

void heapify(pqNode** h, int n) {
    int i, j, k;
    pqNode *key;
    
    j = 0; 
    key = h[j];
    i = 2 * j + 1;

    while (i < n) {
        if ((i + 1 < n) && (h[i]->dist > h[i+1]->dist))
            i++;

        if (key->dist < h[i]->dist) {
            h[j] = h[i];
            j = i; i = 2 * i + 1;
        }

        else break;
    }

    h[j] = key;
}

pqNode *extractMin(pqNode **pq, int *n) {
    pqNode* min;

    min = pq[0]; 
    pq[0] = pq[*n-1];
    --*n;

    heapify(pq, *n-1);
    return min;
}

int inHeap(pqNode **pq, int n, int vid) {
    for (int i = 0; i < n; i++)
        if (pq[i]->vid == vid)
            return 1;
    
    return 0;
}


void updateHeap(pqNode **pq, int n, int vid, int dist, int p) {
    for (int i = 0; i < n; i++)
        if (pq[i]->vid == vid) {
            pq[i]->dist = dist;
            pq[i]->pred = p;
        }
    
    bottomUpHeap(pq, n);
}