#include "headers.h"
#include "struct_def.h"
#include "prototypes.h"
#include "externs.h"
char instr[3][10];
/**
*Reads the opcode from the input file
**/
void readOpcode()
{
 char input[50][50];
    //Parsing the file
    int i=0;
    int j=0;
    //pointing to the beginning of the file
    fseek(ifp2,0,SEEK_SET);
    //reading the input file
    while(fgets(input[i], 50, ifp2)!= NULL)
    {
    	//obtaining mnemonics and opcode no
        parseString(instr, input[i]);
        strcpy(operation[j], instr[0]);
        j++;
        i++;

    }  
    return;

}
