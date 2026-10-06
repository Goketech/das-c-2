# Q2 — Hospital Triage Max-Heap

Array-based Max-Heap of patients (ID + name + priority).

## Run
```
gcc -Wall -Wextra -o triage main.c
./triage
```

## Flow
1. Build heap from 7 patients (root: Eric 91).
2. Treatment order via repeated extract-max on a copy.
3. Insert P08 Kofi 98, then remove P08.

## Expected
- Order: Eric 91, Hassan 88, Jean 76, Amina 72, Grace 63, Irene 54, Daniel 45.
- After insert root: P08 98.
