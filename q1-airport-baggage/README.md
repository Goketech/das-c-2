# Q1 — Airport Baggage Max-Heap

Array-based Max-Heap of containers (ID + priority).

## Run
```
gcc -Wall -Wextra -o baggage main.c
./baggage
```

## Flow
1. Build heap from `{56,23,91,34,72,48,85,17,63,79,42}` (A–K) with bottom-up heapify.
2. Insert X:100 (bubble up).
3. Remove X (swap with last, heapify down).

## Expected
- Initial root: C:91
- After insert root: X:100
- After remove: back to initial heap.
