# SocketCC
This program consists of distributing prime-finding work across multiple nodes using sockets in C++. A Head server divides a numeric range among connected Nodes, collects results in parallel via threads, and totals the primes found.


# Distributed Prime Finder

Distributes prime-finding work across multiple nodes using sockets in both Java and C++. A Head server divides a numeric range among connected Nodes, collects results in parallel via threads, and totals the primes found.

## C++ Version


### Run

```bash
# Start Head first
./Head

# Then start each Node (in separate terminals)
./Node <head_ip> <head_port>
```

---

## Expected Output

**Node:**
```
Working on range: 1000 - 250000
Primes found: 21853
```

**Head:**
```
Received from Node 1: 21853
Received from Node 2: 19075
...
Total primes found: 78498
```
