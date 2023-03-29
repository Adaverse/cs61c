# discussion 8

### Few important points

- Pipelining increases instruction latency and throughput
- In order to pipeline, we add registers between the five datapath stages.
- The speed up of pipelined datapath is not 5x compared to the single cycle datapath because 
    1. The registers added at each step 
    2. The worst time taken of all stages as the clock cycle i.e
        ```Minimum clock cycle = max(IF, ID, EX, MEM, WB)```
- Hazards
    - Structural Hazard
        > Structural hazards occur when more than one instruction needs to use the same
datapath resource at the same time. There are two main causes of structural hazards: 
**Register File** - The register file is accessed both during ID, when it is read, and
during WB, when it is written to. We can solve this by having separate
read and write ports. To account for reads and writes to the same register,
processors usually write to the register during the first half of the clock cycle,
and read from it during in the second half. This is also known as double
pumping.
**Memory** - Memory is accessed for both instructions and data. Having a separate instruction memory (abbreviated IMEM) and data memory (abbreviated
DMEM) solves this hazard.
Also, structural hazards is that they can always be resolved
by adding more hardware

    - Data Hazards
        > Data hazards are caused by data dependencies between instructions. In CS 61C,
where we will always assume that instructions are always going through the processor
in order, we see data hazards when an instruction reads a register before a previous
instruction has finished writing to that register.

    - Control Hazards
        > Control hazards are caused by jump and branch instructions, because for
all jumps and some branches, the next PC is not PC + 4, but the result of the
computation completed in the EX stage. We could stall the pipeline for control
hazards, but this decreases performance.

# discussion 9

### Few important points

- Understanding T/I/O
    > When working with caches, we have to be able to break down the memory addresses
we work with to understand where they fit into our caches. There are three fields:
        &emsp; **Tag** - Used to distinguish different blocks that use the same index. Number of
        &emsp; bits: (# of bits in memory address) - Index Bits - Offset Bits
        &emsp; **Index** - The set that this piece of memory will be placed in. Number of bits:
        &emsp; log2 (# of indices)
        &emsp; **Offset** - The location of the byte in the block. Number of bits: log2
        &emsp; (size of block)
Given these definitions, the following is true:
    ```log2 (memory size) = address bit-width = # tag bits + # index bits + # offset bits```
Another useful equality to remember is:
```cache size = block size ∗ num blocks```
- Cache Associativity
    > In the previous problem, we had a Direct-Mapped cache, in which blocks map to
specifically one slot in our cache. This is good for quick replacement and finding out
block, but not good for efficiency of space!
This is where we bring associativity into the matter. We define associativity as
the number of slots a block can potentially map to in our cache. Thus, a FullyAssociative cache has the most associativity, meaning every block can go anywhere
in the cache.
For an N-way associative cache, the following is true:
```N ∗ # sets = # blocks```
- The 3 C’s of Cache Misses
    > 1. **Compulsory**: First time you ask the cache for a certain block. A miss that must
occur when you first bring in a block. Reduce compulsory misses by having
longer cache lines (bigger blocks), which bring in the surrounding addresses
along with our requested data. Can also pre-fetch blocks beforehand using a
hardware prefetcher (a special circuit that tries to guess the next few blocks
that you will want).
    > 2. **Conflict**: Occurs if, hypothetically, you went through the ENTIRE string of
accesses with a fully associative cache (with an LRU replacement policy) and
wouldn’t have missed for that specific access. Increasing the associativity or
improving the replacement policy would remove the miss.
    > 3. **Capacity**: Capacity misses are independent of the associativity of your cache.
If you hypothetically ran the ENTIRE string of memory accesses with a fully
associative cache (with an LRU replacement policy) of the same size as your
cache, and it was a miss for that specific access, then this miss is a capacity
miss. The only way to remove the miss is to increase the cache capacity.

# discussion 10 (Data-level Parallelism)

### Few important points

- Flynn's Taxonomy 
    - SISD
    - SIMD
    - MISD
    - MIMD

- SIMD (Single instructions Multiple Data)
    - Intel intrinsics documentation - https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html
    - Intrinsics naming convention - https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/naming-and-usage-syntax.html
    - How to use SIMD functions - https://www.cs.virginia.edu/~cr4bd/3330/S2018/simdref.html
