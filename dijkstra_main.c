#include<stdio.h>
#include<stdlib.h>

#include "dijkstra_mod.h"
#include "dijkstra.h"

int main() {
    FILE *fp = fopen("adjacencylist.txt", "r");

    int NUM_VERTICES;
    fscanf(fp, "%d\n", &NUM_VERTICES);

    gNode *g[NUM_VERTICES + 1];

    for (register int i = 0; i < NUM_VERTICES; i++)
        g[i] = NULL;

    readGraph(fp, g, NUM_VERTICES);
    
    dijkstra(g, NUM_VERTICES, NUM_VERTICES - 1);

    return 0;
}