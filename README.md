# CSI402HW1
A project done for ICSI402(Systems Programming) at University at Albany in Fall 2015. 
<br>
The homework is as follows:
In this homework you are going to create a SIC assembler (simulator) using C. The assembler has to do the following:
1.	Interpret a given assembly code given in a text file
2.	Calculate LC values 
3.	Create symbol table
4.	Create an object file which contains the op-code for the program
The src files have the following functions:
main.c : The main file
lc.c : The LC table
object_code.c : Calculates the object code and adds them to an output file
readopcodes.c : Reads the opcodes from an input file
symbols.c : Contains the functions for the binary tree
