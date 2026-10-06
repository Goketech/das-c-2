# Q4 — IoT Gateway BFS

Undirected graph, queue-based BFS from user-entered gateway.

## Run
```
gcc -Wall -Wextra -o iot main.c
./iot
Enter starting gateway: D
```

## Expected (from D)
- BFS order: D A B C E F G
- One-hop: A(12), B(5), C(17), E(22), F(15)
- Max: E 22 ms

Invalid gateway prints an error, no crash.
