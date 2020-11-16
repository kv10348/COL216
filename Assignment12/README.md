# SIMULATING CACHE MEMORY (Computer Architecture)

In this assignment you will develop a simulation software for cache memory. The simulated
cache will have the functionality that was discussed in the cache memory lecture videos, but
with a new Replacement Policy that works as follows. Each Cache Set is divided into two
groups:
1. One group contains the HIGH PRIORITY lines of the set
2. The other group contains the LOW PRIORITY lines of the set
How is priority established? If a line is accessed again after the initial access that fetches it into
the cache, it is promoted to the HIGH PRIORITY group. If a line is not accessed for sufficiently
long (T cache accesses) after being moved to the HIGH PRIORITY group, it is moved to the
LOW PRIORITY group. Within a priority group, the Least Recently Used policy may be used to
manage the lines.
Make any reasonable assumptions you need. The above priority scheme is just an outline; it
may not be complete. Feel free to add other details to make this work.
Inputs to the software will be: (inputs to be taken from input file)
1. Cache size
2. Cache line/block size
3. Cache associativity
4. The value of T
5. A sequence of memory access requests: Memory address, R or W (for Read or Write),
and Data (if Write)
Outputs from the software will be: (output the content and cache statistics to output file)
1. The complete content of the cache (Data, Tag, and Control bits of every cache line) in
each Way after the memory access sequence is complete.
2. Cache statistics:
a. Number of Accesses
b. Number of Reads, Read Hits, and Read Misses
c. Number of Writes, Write Hits, and Write Misses
d. Hit Ratio
