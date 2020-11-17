### General Instructions
1. You will be using Xilinx ISE for simulation and Vivado for synthesis.
2. The assignment has to be done in groups of 2. Only one member of each group
should submit the assignment on Moodle.
3. Each group member should understand the problem and equally contribute to the
solution. Demos would be held for each lab for evaluation.

### Problem
In this assignment you will develop and test a VHDL model for a simple processor
implementing a subset of the MIPS instruction set.
1. The program to be executed is loaded into memory at address ZERO.
2. The stack starts at address 4095 (decimal) and grows DOWNWARDS.
3. Every instruction is 32 bits wide.
4. Implement the following instructions to begin with: add, sub, lw, sw, sll,
srl. Use the MIPS instruction format.
5. Stop execution when you see an instruction with all ZEROes.

Complete the following tasks.
1. Simulate the VHDL model for correctness after providing test input programs.
2. After you are satisfied with the simulation, synthesize the design.
3. Download the generated bit file into the FPGA and run the processor on the
board. Further instructions will be posted on the FPGA demonstration.
Physical labs will be conducted for this assignment. Students are advised to
attend the labs in their respective groups in DHD lab.
