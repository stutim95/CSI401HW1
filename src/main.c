/*** Header Files ***/
#include "headers.h"
#include "struct_def.h"
#include "globals.h"
#include "prototypes.h"
/**
*returns the number of strings
*@params parse: string that holds the split strings from the inputl ine
         string: string that is going to be split
*@return count: the no of strings the input line is split into
**/
int parseString(char parse[3][10], char string[25])
{
    char* ch;
    int j=0;
    int count = 0;
    ch = strtok(string," ");
    while( ch != NULL){
        strcpy(parse[j],ch);
        ch =  strtok(NULL," ");  
        j++;
        count++;

    }
    return count;

}


/**
*The main function that is called in the program
*@params argvc: The number of arguments passed
         argv: The arguments passed
*
**/
int main(int argc, char *argv[])
{

    //The root node for the LC linked list
    LOCATION = malloc(sizeof(LC));
    LOCATION->label;
    LOCATION->lc = 0;
    LOCATION->next= 0;

    //reading the files
    if(argc!=3)
    {
      fprintf(stderr, "Usage: ftest file\n");
      exit(1);
  }
  if((ifp = fopen(argv[1],"r")) == NULL)
  {
      fprintf(stderr, "Could not open file");
      exit(1);
  }
  if((ifp2 = fopen(argv[2],"r")) == NULL)
  {
    fprintf(stderr, "Could not open file");
    exit(1);
}
//Opening the output file
ofp = fopen("obj.o","w");
//The input lines
char input[50][50];
//the parts of the instruction
char instr[3][10];
    //Parsing the file
int i=0;
//read opcodes
readOpcode();
//count to record the no of strings in each instruction
int count;
//PASS 1
    //reading each line of input
while(fgets(input[i], 50, ifp)!= NULL)
{
    //Split the instruction into strings
    count = parseString(instr, input[i]);
    //If the instruction is the START instruction
    if(strcmp(instr[1],"START")==0)
    {
        //store the program's name
      strcpy(program_name,instr[0]);
      //write the program's name to the output file
      fprintf(ofp,"%s\n",program_name);
      //record the starting LC
      readFirstLC(instr[2]);
  }
  //if instruction is not a comment
  if(input[i][0]!='.')
  {
    //If the instruction is not the "END" command
    if(strcmp(instr[0],"END")!=0)
    {
        //If a label is involved in the instruction
        //An instruction label is added only if the instruction has a label attached to it
        if(count == 3)
        {

            //Searching if the label already exists in the symbol table
            if(sym_search(instr[0], SYMBAL)==0)
            {
                //adding instruction to symbol table
                add_sym(&SYMBAL,instr[0]);
            }

        }
        //Add the LOCADDR for the location to the linked list
        add_lc(instr[0]);
             
        //adding location address
        add_locaddr(count,instr);
    }

}
//PASS 2
//incrementing to read the next input line
i++;

}
//Print the symbol table
print_sym(SYMBAL);
//Moving to the top of the file
fseek(ifp,0,SEEK_SET);
//PASS 2
while(fgets(input[i], 50, ifp)!= NULL)
{
    
    //Split the instruction into strings
    count = parseString(instr, input[i]);
  //if instruction is not a comment
  if(input[i][0]!='.')
  {
    //If the instruction is not the "END" command
    if((strcmp(instr[0],"END")!=0)&& (strcmp(instr[0],"START")!=0))
    {
        //print the object codes
           print_opcode(count, instr); 

             
    }
    else
    {
        //print the last line into the file
        fprintf(ofp,"END \n");
    }

  }
//incrementing to read the next input line
i++;
}


//closing all the files
fclose(ifp);
fclose(ifp2);
fclose(ofp);
//deleting all the sym nodes and freeing memory
delete_sym(SYMBAL);
return 0;

}