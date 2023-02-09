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