#include <stdio.h>

#define V 10
#define E 15
#define INF 1000000

// A=0 B=1 C=2 D=3 E=4 F=5 G=6 H=7 I=8 J=9
char name[V] = {'A','B','C','D','E','F','G','H','I','J'};

typedef struct {
    int u, v, w;
} Edge;

Edge edges[E] = {
    {0,1,6}, {0,3,16}, {1,2,6}, {1,3,6}, {1,9,7},
    {2,6,-9}, {3,4,7}, {3,9,8}, {4,5,10}, {4,8,-2},
    {5,6,4}, {5,8,2}, {6,7,13}, {8,5,2}, {9,4,3}
};

int dist[V];
int pred[V];

void printPath(int dest) {
    int stack[V];
    int top = 0;
    int cur = dest;
    while (cur != -1) {
        stack[top++] = cur;
        cur = pred[cur];
    }
    for (int i = top - 1; i >= 0; i--) {
        printf("%c", name[stack[i]]);
        if (i > 0) printf(" -> ");
    }
}

int main() {
    int src = 0; // A

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[src] = 0;

    // relax V-1 times
    for (int i = 0; i < V - 1; i++) {
        int changed = 0;
        for (int j = 0; j < E; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
                changed = 1;
            }
        }
        if (!changed) break;
    }

    // negative cycle check (only reachable from src counts)
    int hasNegCycle = 0;
    for (int j = 0; j < E; j++) {
        int u = edges[j].u, v = edges[j].v, w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            hasNegCycle = 1;
            break;
        }
    }

    printf("Source: %c\n\n", name[src]);
    printf("%-12s %-14s %s\n", "Destination", "Shortest Cost", "Path");
    for (int i = 0; i < V; i++) {
        if (i == src) continue;
        printf("%-12c ", name[i]);
        if (dist[i] == INF) {
            printf("%-14s %s\n", "unreachable", "-");
        } else {
            printf("%-14d ", dist[i]);
            printPath(i);
            printf("\n");
        }
    }

    printf("\n");
    if (hasNegCycle)
        printf("Negative-weight cycle detected.\nShortest-path results may be undefined.\n");
    else
        printf("No negative-weight cycle detected.\n");

    return 0;
}
