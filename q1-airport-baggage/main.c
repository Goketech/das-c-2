#include <stdio.h>

#define MAX 20

typedef struct {
    char id;
    int priority;
} Container;

Container heap[MAX];
int size = 0;

void swapBox(Container *a, Container *b) {
    Container t = *a;
    *a = *b;
    *b = t;
}

void heapifyDown(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].priority > heap[largest].priority)
        largest = left;
    if (right < size && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i) {
        swapBox(&heap[i], &heap[largest]);
        heapifyDown(largest);
    }
}

void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].priority > heap[parent].priority) {
            swapBox(&heap[i], &heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

void buildHeap() {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapifyDown(i);
}

void printHeap(char *title) {
    printf("\n%s (size=%d)\n", title, size);
    printf("Index : ");
    for (int i = 0; i < size; i++)
        printf("[%d]%c:%d  ", i, heap[i].id, heap[i].priority);
    printf("\n");
}

void insertBox(char id, int p) {
    heap[size].id = id;
    heap[size].priority = p;
    size++;
    heapifyUp(size - 1);
}

int findById(char id) {
    for (int i = 0; i < size; i++)
        if (heap[i].id == id)
            return i;
    return -1;
}

void removeById(char id) {
    int idx = findById(id);
    if (idx == -1) {
        printf("Container %c not found.\n", id);
        return;
    }
    heap[idx] = heap[size - 1];
    size--;
    // the swapped item may need to go up or down
    heapifyUp(idx);
    heapifyDown(idx);
}

int main() {
    int P[] = {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42};
    int n = 11;

    for (int i = 0; i < n; i++) {
        heap[i].id = 'A' + i;
        heap[i].priority = P[i];
    }
    size = n;

    printf("Initial array (before heapify):\n");
    printHeap("Raw array");

    buildHeap();
    printHeap("1. Initial Max-Heap");

    // urgent container
    insertBox('X', 100);
    printHeap("2. After inserting X:100");

    // cancelled
    removeById('X');
    printHeap("3. After removing X");

    return 0;
}
