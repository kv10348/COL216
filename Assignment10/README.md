### Variable Delays in a Pipelined Processor 

Sometimes, operations such as floating point arithmetic or memory accesses in a pipelined
processor require variable delays. A floating point computation may depend on the data
operands. A memory access may exhibit variable delays due to the cache hierarchy. Let us try
to model the memory architecture by introducing a data memory that works as follows:
1. The operation completes in one cycle with a probability x (this is considered a HIT).
2. The operation requires N cycles with a probability 1-x (this is considered a MISS).
3. Upon a memory request, at end of one cycle, the memory indicates whether the
operation was a HIT or MISS. If HIT, the operation is complete. If not, the operation
completes N-1 cycles later.

Implement this variable delay feature in your pipeline. Demonstrate the pipeline’s working for
different values of x and N.
