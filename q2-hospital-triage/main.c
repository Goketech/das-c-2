#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    char id[5];
    char name[20];
    int priority;
} Patient;

Patient heap[MAX];
int size = 0;

void swapP(Patient *a, Patient *b) {
    Patient t = *a;
    *a = *b;
    *b = t;
}

void heapifyDown(int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && heap[l].priority > heap[largest].priority)
        largest = l;
    if (r < size && heap[r].priority > heap[largest].priority)
        largest = r;
    if (largest != i) {
        swapP(&heap[i], &heap[largest]);
        heapifyDown(largest);
    }
}

void heapifyUp(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[i].priority > heap[p].priority) {
            swapP(&heap[i], &heap[p]);
            i = p;
        } else break;
    }
}

void buildHeap() {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapifyDown(i);
}

void printHeap(char *title) {
    printf("\n%s\n", title);
    for (int i = 0; i < size; i++)
        printf("  [%d] %s %s %d\n", i, heap[i].id, heap[i].name, heap[i].priority);
}

void insertPatient(Patient p) {
    heap[size] = p;
    size++;
    heapifyUp(size - 1);
}

// returns 1 if ok
int extractMax(Patient *out) {
    if (size == 0) return 0;
    *out = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return 1;
}

int findById(char *id) {
    for (int i = 0; i < size; i++)
        if (strcmp(heap[i].id, id) == 0)
            return i;
    return -1;
}

void removeById(char *id) {
    int idx = findById(id);
    if (idx == -1) {
        printf("Patient %s not found.\n", id);
        return;
    }
    heap[idx] = heap[size - 1];
    size--;
    heapifyUp(idx);
    heapifyDown(idx);
}

int main() {
    Patient init[] = {
        {"P01", "Amina", 72},
        {"P02", "Daniel", 45},
        {"P03", "Eric", 91},
        {"P04", "Grace", 63},
        {"P05", "Hassan", 88},
        {"P06", "Irene", 54},
        {"P07", "Jean", 76}
    };
    int n = 7;
    for (int i = 0; i < n; i++)
        heap[i] = init[i];
    size = n;

    buildHeap();
    printHeap("1. Initial Max-Heap (root = highest priority):");

    // treatment order: work on a copy so original heap stays
    printf("\n2. Treatment order (highest to lowest):\n");
    Patient backup[MAX];
    int backupSize = size;
    for (int i = 0; i < size; i++) backup[i] = heap[i];

    Patient p;
    int order = 1;
    while (extractMax(&p)) {
        printf("  %d. Patient %s (%s) - Priority %d\n", order++, p.id, p.name, p.priority);
    }

    // restore heap
    for (int i = 0; i < backupSize; i++) heap[i] = backup[i];
    size = backupSize;

    // new emergency patient
    Patient kofi;
    strcpy(kofi.id, "P08");
    strcpy(kofi.name, "Kofi");
    kofi.priority = 98;
    insertPatient(kofi);
    printHeap("3. After inserting P08 Kofi 98:");

    // patient cleared
    removeById("P08");
    printHeap("4. After removing P08:");

    return 0;
}
