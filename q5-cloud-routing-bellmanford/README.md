# Q5 — Cloud Routing (Bellman-Ford)

Directed graph, Bellman-Ford from A with path rebuild + cycle check.

## Run
```
gcc -Wall -Wextra -o routing main.c
./routing
```

## Expected
- G=3 via A-B-C-G, H=16, F=16, I=14, E=16, J=13.
- Output: `No negative-weight cycle detected.`
