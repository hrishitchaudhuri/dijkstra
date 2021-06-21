#include<stdio.h>
#include<stdlib.h>

#include"dijkstra_mod.h"
#include"dijkstra.h"

void dijkstra(gNode **g, int n, int dest) {
    int distance[n], predecessor[n];
    int count_nodes = n;
    int key;

    pqNode *pq[n];
    pqNode *CURR;
    gNode *TEMP;

    for (register int i = 0; i < n; i++) {
        pq[i] = (pqNode *) malloc(sizeof(pqNode));
        pq[i]->dist = 99999;
        pq[i]->vid = i;
        pq[i]->pred = -1;

        distance[i] = 99999;
        predecessor[i] = -1;
    }

    pq[dest]->dist = 0;
    distance[dest] = 0;

    bottomUpHeap(pq, n);

    while (count_nodes > 0) {
        CURR = extractMin(pq, &count_nodes);

        key = CURR->vid;

        TEMP = g[key];
        while (TEMP != NULL) {
            if (inHeap(pq, count_nodes, TEMP->data) && (distance[key] != 99999) && (TEMP->weight + distance[key] < distance[TEMP->data])) {
                distance[TEMP->data] = distance[key] + TEMP->weight;
                predecessor[TEMP->data] = key;
                updateHeap(pq, count_nodes, TEMP->data, distance[TEMP->data], key);
            }

            TEMP = TEMP->next;
        }
    }

    int var;
    for (register int i = 0; i < n - 1; i++) {
        var = predecessor[i];
        printf("%d ", i + 1);
        if (var != -1) {
            while (var != 19) {
                printf("%d ", var + 1);
                var = predecessor[var];
            }
            printf("\n");
        }

        else {
            printf("NO PATH\n");
        }
    }
}