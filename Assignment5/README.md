### General Instructions

1. You will be using Vivado for simulation and synthesis.
2. The assignment should be done in groups of two. Only one member from each group should submit the
assignment on Moodle.
3. Both group members should understand the problem and contribute equally to the solution.
4. You will be awarded marks according to your design and the test cases you developed to evaluate the
design. Extensive testing is expected as a part of the Assignment.

### Problem

In this assignment, you will be adding MIPS conditional/unconditional branch instructions and procedure call
instructions to the processor designed in Assignment 4. Make appropriate modifications to your code:
1. Implement the following branch instructions using J-type instruction format: bne, beq, blez, bgtz, j.
2. Implement the instructions used for procedure calls: jal, jr.
3. Implement non-leaf procedures (procedures that can call other procedures) using stack.
4. The stack should be implemented in memory and should grow downwards.
5. You can assume that a maximum of four arguments can be passed to a procedure.
6. You can use https://courses.cs.washington.edu/courses/cse410/09sp/examples/MIPSCallingConventionsSummary.pdf, as a reference document to understand MIPS procedure calls and stack layout.

Once the desired modifications are done, you need to simulate and synthesize the modified VHDL processor
model. The output instructions remain the same as for Assignment 4.


