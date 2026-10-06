#include <stdio.h>
#include <ctype.h>

#define V 7

char label[V] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
int g[V][V] = {0};

void addLink(int u, int v, int w) {
    g[u][v] = w;
    g[v][u] = w;
}

int toIndex(char c) {
    c = toupper(c);
    for (int i = 0; i < V; i++)
        if (label[i] == c) return i;
    return -1;
}

int main() {
    addLink(0, 1, 6);
    addLink(0, 3, 12);
    addLink(1, 3, 5);
    addLink(1, 2, 11);
    addLink(2, 3, 17);
    addLink(2, 6, 25);
    addLink(3, 4, 22);
    addLink(3, 5, 15);
    addLink(4, 5, 10);
    addLink(5, 6, 22);

    char input;
    printf("Enter starting gateway: ");
    if (scanf(" %c", &input) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int start = toIndex(input);
    if (start == -1) {
        printf("Invalid gateway '%c'. Valid gateways are A B C D E F G.\n", input);
        return 1;
    }

    // BFS with a simple array queue
    int visited[V] = {0};
    int queue[V * V];
    int front = 0, rear = 0;
    int order[V * V];
    int orderLen = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int cur = queue[front++];
        order[orderLen++] = cur;
        // neighbours in A..G order so result is predictable
        for (int i = 0; i < V; i++) {
            if (g[cur][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\nBFS visit order from %c: ", label[start]);
    for (int i = 0; i < orderLen; i++)
        printf("%c ", label[order[i]]);
    printf("\n");

    // one-hop neighbours = direct links, in BFS encounter order
    // BFS encounters them in index order, so just collect from order list
    printf("\nGateways directly connected to %c (one hop, BFS order):\n", label[start]);
    int best = -1, bestW = -1;
    for (int k = 0; k < orderLen; k++) {
        int node = order[k];
        if (node != start && g[start][node] != 0) {
            printf("  %c (time %d ms)\n", label[node], g[start][node]);
            if (g[start][node] > bestW) {
                bestW = g[start][node];
                best = node;
            }
        }
    }

    if (best != -1) {
        printf("\nHighest transfer time among direct neighbours: %c (%d ms)\n",
               label[best], bestW);
    } else {
        printf("\nNo direct neighbours found.\n");
    }

    return 0;
}
