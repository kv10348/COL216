	.data
prompt: .asciiz " Welocme to tic-toc toe game, Enjoy!!"
input1: .asciiz "Player 1 :Enter value at\n"
input2: .asciiz "Player 2 :Enter value at\n"
brac: .asciiz ")\n"
nl: .asciiz "\n"
comma: .asciiz ","
semi: .asciiz ":"
row: .asciiz "\n  ------------\n"
colon: .asciiz " | "
wrong: .asciiz "\nwrong input, try next time \n"
tryagain: .asciiz"\ntry again\n"
taking: .asciiz "taking input\n"
	.text

main:
	li $v0, 4
	la $a0, prompt
	syscall

	li $v0, 9
	la $a0, 36
	syscall


	move $s0, $v0
	move $t0, $s0
	li $t2, 0




	li $t6, 0								#for player one: just to keep track how many time it have enter the value in game
	li $t7, 0								#for player two: just to keep track how many time it have enter the value in game
	li $t9, 9
	j put

put:											#this function load 9 at all the values for matrix

	li $t3, 9

	bge  $t2,$t3 , matrix		#checking condition that have we print whole matrix or not
	sw $t3, 0($t0)					# load the value 9 at address 0($t0)
	addi $t0, 4							#address increment by 4 as the space require for int is 4 bytes
	addi $t2,1							#increment by 1: counter for counting at howmany places we have inserted 9
	j put										#jump to put again to print further fillig the matrix place by 9

matrix :									# this function is for printing the matrix.
	move $t0, $s0
	li $t8, 0
	li $t4,3
	j print_matrix_row

print_matrix_row:				# this is for printing rows


	li $v0, 4							#commmands for printing the string
	la $a0, row
	syscall								#system call to gain service
	li $t9, 0
	bge $t8, $t4, win_row			# condtion for making sure that we have printing whole matrixes. If whole matrixes is printed then go to for checking wining condtion
	addi $t8 ,1
	j print_matrix_colon

print_matrix_colon:							#this function for printing all the values along in a row.

	li $v0, 4
	la $a0, colon
	syscall

	bge $t9, $t4, print_matrix_row			# if we have printed all the values in a row then go to row again for printing new row
	lw $a0,0($t0)												#lw = load word: fetch the value from the address store at $t0
	li $v0, 1														#priinting commmands for integer
	syscall
	addi $t0, 4													#increment address by 4
	addi $t9,1
	j print_matrix_colon								#recuresive call untill all the elements of the row is get printed

input:																#this function start taking input
	move $t0, $s0												#once again moving the adresss from $s0 to $t0
	li $t1, 4
	bgt $t6, $t1, no										#bgt: branch if greater than
	beq $t6, $t7, take_input_1					#beq: branch if they are equal, it's condition for if first participant gave the input five times then we have taken inputs for whole matrix
	j take_input_2											# if they inputs enter by participant one and two are equal then we have to input from participant one



take_input_1:													#this function taking input from participant one

	addi $t6,1
	li $v0, 4
	la $a0, taking
	syscall


	li $v0, 4
	la $a0, input1
	syscall

	li $v0, 5									# take the ith value
	syscall
	move $t1, $v0							# moving the value from $v0 to $t1



	li $t9, 3
	li $t8, 4
	bge $t1, $t9, wrong_input					#checking if enter ith value is greater than or equal to 3 or not then jump to wrong_input
	bltz $t1, wrong_input							#checking if enter ith value is less than 0 or not if not then jump to wrong_input
	li $v0, 5													#otherwise take the input
	syscall
	move $t2, $v0
	bge $t2, $t9, wrong_input					#checking if enter jth value is greater than or equal to 3 or not then jump to wrong_input
	bltz $t2, wrong_input							#checking if enter jth value is less than 0 or not if not then jump to wrong_input


	mul $t1,$t1, $t9									#fectching tha data store from adrress
	add $t1, $t1, $t2									#using the formual
	mul $t1, $t1,$t8									#address =  base_address+(row_index*col_number+ col_index)*data_size
	add $t0, $t0, $t1
	li $t9,9
	lw $t3, 0($t0)											# if the fetch data is equal to 9 then take the input
	bne $t3, $t9, wrong_input						#if the fetch data is not equal to 9 then already that place is filled so don't take input

	li $v0, 0

	sw $v0 0($t0)


	j matrix														#after taking input from participant print the whole




	take_input_2:												# take input form second participant and this will do all the thing as above function do for participant one
	addi $t7,1
	li $v0, 4
	la $a0, taking
	syscall


	li $v0, 4
	la $a0, input2
	syscall

	li $v0, 5
	syscall
	move $t1, $v0






	#li $v0, 4
	#la $a0, brac
	#syscall
	li $t9, 3
	li $t8, 4
	bge $t1, $t9, wrong_input
	bltz $t1, wrong_input
	li $v0, 5
	syscall
	move $t2, $v0
	bge $t2, $t9, wrong_input
	bltz $t2, wrong_input
	mul $t1,$t1, $t9
	add $t1, $t1, $t2
	mul $t1, $t1,$t8
	add $t0, $t0, $t1
	li $t9,9
	lw $t3, 0($t0)
	bne $t3, $t9, wrong_input

	li $v0, 1

	sw $v0 0($t0)

	j matrix

win_row:						#this function check that is there the possibility of winning the game or not


	li $t1,0
	li $t2,0
	li $t3,0
	move $t0, $s0
	j check_row

check_row:									#check the case of winning along rows

	lw $t1, 0($t0)						#load the first value of an
	addi $t0, 4
	lw $t2, 0($t0)
	addi $t0, 4
	lw $t3, 0($t0)
	addi $t0, 4
	beq $t1, $t2, check_9
	j condition_1
condition_1:
	li $t5,32
	bgt $t0, $t5, win_diagonal
	j check_row
check_9:
	li $t4,9
	bne $t2, $t4, check_t3
	j condition_1
check_t3:
 	beq $t2, $t3, yes
	j condition_1



yes:
	li $t9,1
	beq $t3,$t9, output_1
	j output_0

no:
.data
loose: .asciiz "\nNo one won so match tie, better luck next time :(\n"
.text
li $v0,4
la $a0, loose
syscall

li $v0, 10
syscall

output_0:
		.data
win_0: .asciiz "\nPlayer one won:)\n"
	.text
	li $v0,4
	la $a0, win_0
	syscall

	li $v0, 10
	syscall
output_1:
.data
win_1: .asciiz "\nPlayer two won:)\n"
.text
li $v0,4
la $a0, win_1
syscall

li $v0, 10
syscall







win_diagonal:
	li $t1,0
	li $t2,0
	li $t3,0
	move $t0, $s0
	j check_diagonal_1

check_diagonal_1:

lw $t1, 0($t0)
addi $t0, 16
lw $t2, 0($t0)
addi $t0, 16
lw $t3, 0($t0)
	beq $t1, $t2, check_9_d
	j check_diagonal_2

check_9_d:
 	li $t4, 9
	bne $t2, $t4, check_3_d
	j check_diagonal_2

check_3_d:
	beq $t2, $t3, yes
	j check_diagonal_2

check_diagonal_2:
	move $t0, $s0
	addi $t0, 8
	lw $t1, 0($t0)
	addi $t0, 8
	lw $t2, 0($t0)
	addi $t0, 8
	lw $t3, 0($t0)
	beq $t1, $t2, check_9_d2

check_9_d2:
	li $t4, 9
	bne $t2, $t4, check_3_d2
	j win_colon
check_3_d2:
	beq $t2, $t3, yes
	j win_colon



win_colon:
li $t1,0
li $t2,0
li $t3,0
move $t0, $s0
j check_colon_1

check_colon_1:

lw $t1, 0($t0)
addi $t0, 12
lw $t2, 0($t0)
addi $t0, 12
lw $t3, 0($t0)

beq $t1, $t2, check_9_c
j condition_1_c


condition_1_c:
li $t5,32
bgt $t0, $t5, input
li $t5, 20
sub $t0, $t0, $t5
j check_colon_1


check_9_c:
	li $t4,9
	bne $t2, $t4, check_t4
	j condition_1_c
check_t4:
 	beq $t2, $t3, yes
	j condition_1_c






wrong_input:


	li $v0, 4
	la $a0, tryagain
	syscall

	j finish


finish:
	li $v0, 4
	la $a0, wrong
	syscall



	li $v0, 10
	syscall
