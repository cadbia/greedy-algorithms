# Cache Simulator

This is a C++ project that simulates cache replacement policies (FIFO, LRU, and soon OPTFF), reporting the total number of cache misses. Note that the OPTFF (Optimal Furthest in Future) implementation is pending.

Caden Bialow UFID: 86822533

Jake Qiu UFID: 41352615

## Repository Structure
- `src/` : Source code (`main.cpp`, `simulator.h`, `simulator.cpp`).
- `data/` : Directory intended for input data files and request sequences.
- `tests/`: Automated test scripts and assertions (`test_small.cpp`, `run.sh`).

## Build
Compile the main simulator program with a C++17 compliant compiler:
```bash
g++ -std=c++17 -O3 -Wall -Wextra src/main.cpp src/simulator.cpp -o cache_sim
```

## Run
The program expects an input file passed via the command line argument.

**Input Format**:
The first line contains `k` (the cache size) and `m` (the total number of memory requests).

The remaining input contains exactly `m` integers representing the sequence of memory requests (these may be spaced out across multiple whitespace-separated lines).

Example run command:
```bash
./cache_sim data/example.in
```

## Testing
Basic test sequences with known miss counts are defined in `tests/test_small.cpp`. A helper wrapper script handles the testing lifecycle.

To compile and verify tests:
```bash
./tests/run.sh
```

## Output Format
The program directly creates a .out file and also prints miss counts with the same format:
```
FIFO  : <misses>
LRU   : <misses>
OPTFF : <misses>
```

## Assumptions
- Memory request IDs are purely represented as integers.
- Inputs are strictly separated by whitespace.
- The cache size limit `k` must fulfill `k >= 1`.
- A miss occurs exclusively when a requested integer is not present in the current cache footprint. On a miss, the algorithm automatically inserts it. If the cache is full relative to its limit `k`, space is reclaimed according to the explicit replacement policy (FIFO, LRU, Farthest-in-future).

##  Verification Example
A standard sample input has been provided in `data/example.in` alongside its expected output in `data/example.out`.

To quickly verify the program's correctness against the expected behavior, use `diff`:

```bash
# 1. Compile the simulator
g++ -std=c++17 -O3 -Wall -Wextra src/main.cpp src/simulator.cpp -o cache_sim

# 2. Run the executable and pipe the results to a temporary file
./cache_sim data/example.in > my_output.txt

# 3. Verify exactly matching outputs (no output means successful match)
diff my_output.txt data/example.out
```

## Writing Section

## Question 1: Empirical Comparison

Use at least three nontrivial input files (each containing 50 or more requests).  
For each file, report the number of cache misses for each policy.

| Input File     | k | m  | FIFO | LRU | OPTFF |
|----------------|---|----|------|-----|-------|
| example_1.in   | 3 | 50 | 35   | 35  | 23    |
| example_2.in   | 5 | 50 | 17   | 20  | 13    |
| example_3.in   | 4 | 80 | 54   | 58  | 31    |

**Does OPTFF have the fewest misses?**  
Yes.

**How does FIFO compare to LRU?**  
FIFO performed equal to or slightly better than LRU for all test examples.

---

## Question 2: Bad Sequence for LRU or FIFO

For k = 3, investigate whether there exists a request sequence for which OPTFF incurs strictly fewer misses than LRU or FIFO.

**Sequence**
```bash
1 2 3 4 1 2 5 1 2 3 4 5
```

| Policy | Cache Misses |
|-------|--------------|
| OPTFF | 7 |
| FIFO  | 9 |
| LRU   | 10 |

**Explanation**

OPTFF is able to keep 1 and 2 in the cache at positions 4, 5, 7, and 8, while FIFO is forced to discard them right before they are needed again.  
LRU behaves similarly to FIFO because the cache size is small and the request pattern changes frequently, but it performs slightly worse in this sequence.

## Question 3: Prove OPTFF is Optimal

- Let OPTFF be Belady’s Farthest-in-Future algorithm.
- Let A be any offline algorithm that knows the entire request sequence.

Prove that the number of misses of OPTFF is no larger than that of A on any fixed sequence.

### Proof

Assume a cache of size k and a request sequence:
```bash
d1, d2, ..., dm
```

Consider an optimal schedule A. We show that A can be transformed into a schedule that behaves exactly like OPTFF without increasing the number of misses.

Suppose that A and OPTFF make the same eviction decisions for the first j requests.  
Now consider request d(j+1).

- If d(j+1) is already in the cache, both algorithms proceed without eviction.
- If a miss occurs and both algorithms evict the same item, they still agree.

We focus on when both algorithms must evict an item but choose different items.

We see the scenario where OPTFF evicts item e, whose next use is farthest in the future, while A evicts some other item f.

Construct a new algorithm A′ that behaves like A except it evicts e instead of f at step j+1.

Because e is used later than f, the next request among these two items must be for f.

When that request occurs, A' loads f and A' evicts the same value that A would have.

At this point, the cache contents of A′ and A become identical again, and A′ incurs no more misses than A.

Thus we obtain a schedule A′ that:

- matches OPTFF for the first j+1 requests, and
- has no more misses than A

Repeating this argument step-by-step with by induction, A becomes a schedule that makes exactly the same decisions as OPTFF for the entire sequence without increasing the number of misses.

Since A was arbitrary, OPTFF incurs no more misses than any offline algorithm.

Therefore, OPTFF is optimal.
