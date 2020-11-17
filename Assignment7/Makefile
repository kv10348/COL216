all: execute
execute:
	gcc -c reg_file.c -o reg_file.o
	gcc -c operation.c -o operation.o
	gcc -c data_mem.c -o data_mem.o
	gcc -c inst_mem.c -o inst_mem.o
	gcc -c functions.c -o functions.o
	gcc -c main.c -o main.o
	gcc -o main reg_file.o operation.o data_mem.o inst_mem.o functions.o main.o
	./main input.txt

	
	
	
	