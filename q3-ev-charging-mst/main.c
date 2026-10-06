#include <stdio.h>

#define V 7

char label[V] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
int mat[V][V] = {0};

typedef struct {
    int u, v, w;
} Edge;

int parent[V], rnk[V];

void addEdge(int u, int v, int w) {
    mat[u][v] = w;
    mat[v][u] = w;
}

int findRoot(int x) {
    if (parent[x] != x)
        parent[x] = findRoot(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) return;
    if (rnk[a] < rnk[b]) parent[a] = b;
    else if (rnk[a] > rnk[b]) parent[b] = a;
    else { parent[b] = a; rnk[a]++; }
}

int main() {
    // build graph
    addEdge(0, 1, 6);   // A-B
    addEdge(0, 3, 12);  // A-D
    addEdge(1, 3, 5);   // B-D
    addEdge(1, 2, 11);  // B-C
    addEdge(2, 3, 17);  // C-D
    addEdge(2, 6, 25);  // C-G
    addEdge(3, 4, 22);  // D-E
    addEdge(3, 5, 15);  // D-F
    addEdge(4, 5, 10);  // E-F
    addEdge(5, 6, 22);  // F-G

    printf("1. Adjacency matrix (0 = no direct connection):\n");
    printf("    ");
    for (int i = 0; i < V; i++) printf("%c   ", label[i]);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf(" %c  ", label[i]);
        for (int j = 0; j < V; j++)
            printf("%-4d", mat[i][j]);
        printf("\n");
    }

    // edge list
    Edge edges[] = {
        {0,1,6},{0,3,12},{1,3,5},{1,2,11},{2,3,17},
        {2,6,25},{3,4,22},{3,5,15},{4,5,10},{5,6,22}
    };
    int n = 10;

    // sort by cost
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (edges[j].w > edges[j+1].w) {
                Edge t = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = t;
            }
        }
    }

    printf("\n2. Connections sorted by cost:\n");
    for (int i = 0; i < n; i++)
        printf("  %c - %c : %d\n", label[edges[i].u], label[edges[i].v], edges[i].w);

    for (int i = 0; i < V; i++) { parent[i] = i; rnk[i] = 0; }

    Edge mst[V];
    int count = 0;
    int total = 0;

    printf("\nKruskal steps:\n");
    for (int i = 0; i < n && count < V - 1; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (findRoot(u) != findRoot(v)) {
            unite(u, v);
            mst[count++] = edges[i];
            total += edges[i].w;
            printf("  accept %c - %c : %d\n", label[u], label[v], edges[i].w);
        } else {
            printf("  skip   %c - %c : %d (would form cycle)\n", label[u], label[v], edges[i].w);
        }
    }

    printf("\n3. Selected Connections:\n");
    for (int i = 0; i < count; i++)
        printf("  %c - %c : %d\n", label[mst[i].u], label[mst[i].v], mst[i].w);

    printf("\n4. Total Installation Cost: %d thousand dollars\n", total);

    return 0;
}
