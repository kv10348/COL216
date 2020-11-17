### Instructions

1. The assignment should be done in groups of two. Only one member from each group should
submit the assignment on Moodle.
2. Both group members should understand the problem and contribute equally to the solution.
3. You will be awarded marks according to your design and the test cases you developed to
evaluate the design. Extensive testing is expected as a part of the Assignment.
4. Any sort of plagiarism leads to -10 Marks for the assignment.


### Statement
In this and the subsequent assignments, you will build a software simulator in C++ for the MIPS
processor.

1. The input to your program is a MIPS program (limited to the instructions you have
already implemented in previous assignments). Read this input into an array of
instructions.
2. Simulation starts with the Program Counter (PC) pointing to the first instruction.
3. Execute the instruction. Display the values of the Register File and Memory contents as
a result of executing the instruction.
4. Proceed to the next instruction and continue the execution.
5. Simulation stops when there is no further instruction to execute.

This version of the processor is a MULTICYCLE design (not PIPELINED). Assume that you will
be given a file that indicates the information of how many clock cycles each instruction requires.

At the end of execution, print out statistics about the clock cycle counts and average Instructions
Per Cycle (IPC) for the input program.
