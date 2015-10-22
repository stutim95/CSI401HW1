#include "headers.h"
#include "struct_def.h"
#include "prototypes.h"
#include "externs.h"
/** Function to print the object code
* This program both looks at cases where opcode is saved in the opcode file and when we have commands like 'WORD' and 'BYTE'
* @params: instr: String that accepts the instruction to print the opcode
*/
void print_opcode(int count,char instr[3][10])
{
	//the string to hold the object code
	char object_code[10];
	int loc;
	char location[10];
	int length = 0;
	//flag to determine if we found the string
	int flag = 0;
	//opcode of the instruction
	char opcode[3][10];
	//input from the opcode file
	char input[25][25];
	int i=0;
	//the label of the instruction
	char label[10];
	//moving to the beginning of the file
	fseek(ifp2,0,SEEK_SET);
	//parse through the opcode input file
	while(fgets(input[i], 50, ifp2)!= NULL)
	{
		//call a function to get the opcode mnemonic and opcode
		parseString(opcode, input[i]);
		i++;
		//if the instruction has a label
		if(count == 3)
		{
			//compare the instruction[instr[1]] and the opcode. We go into the condition if the instruction opcode and the opcode from
			//our file are the same
			if(strcmp(instr[1],opcode[0]) == 0)
			{

				
			  //Creating a suitable label string that can be matched
				for(int j=0; instr[2][j+1] != '\n'; j++)
				{
					//setting the label so that we can compare it to the label from the SYMBAL at a later point
					label[length] = instr[2][j];
					length++;
				}
				//adding a null-terminating character
				label[length]='\0';
			  //If the label is present in the symbol table
				if(sym_search(label,SYMBAL)==1)
				{
					//copy the opcode taken from the opcode input file into the object_code string
					strcpy(object_code,opcode[1]);
					//getting the location address of the label
					loc = sym_find(label, SYMBAL);
					sprintf(location, "%d", loc);
			    //For concatenating the two strings
					length = 0;
					//getting the object_code string in the correct format
					for(int j=0;opcode[1][j]!='\n';j++)
					{
						object_code[length] = opcode[1][j];
						length ++;
					}
					//getting the second half i.e the location address of the label stored
					for(int k=0;location[k]!='\0';k++)
					{
						object_code[length] = location[k];
						length++;
					}
					//adding a null-terminating character
					object_code[length] = '\0';
					//setting flag
					flag = 1;
					//writing to output file
					fprintf(ofp,"%s\n",object_code);
				}

			}
			
			
		}
		else
		{
			//if no label is present
			if(count == 2)
			{
				//compare the instruction[instr[1]] and the opcode. We go into the condition if the instruction opcode and the opcode from
			    //our file are the same
				if(strcmp(instr[0],opcode[0]) == 0)
				{
					
			  //Creating a suitable label string that can be matched
					for(int j=0; instr[1][j+1] != '\n'; j++)
					{
						//setting the label so that we can compare it to the label from the SYMBAL at a later point
						label[length] = instr[1][j];
						length++;
					}
					//adding a null-terminating character
					label[length]='\0';
			  //If the label is present in the symbol table
					if(sym_search(label,SYMBAL)==1)
					{
						//copy the opcode taken from the opcode input file into the object_code string
						strcpy(object_code,opcode[1]);
						//getting the location address of the label
						loc = sym_find(label, SYMBAL);
						sprintf(location, "%d", loc);
			    //For concatenating the two strings
						length = 0;
						//getting the object_code string in the correct format
						for(int j=0;opcode[1][j]!='\n';j++)
						{
							object_code[length] = opcode[1][j];
							length ++;
						}
						//getting the second half of the object_code string in the correct format
						for(int k=0;location[k]!='\0';k++)
						{
							object_code[length] = location[k];
							length++;
						}
						//adding a null-terminating character
						object_code[length] = '\0';
						//setting flag=1
						flag = 1;
						//outputting to the file
						fprintf(ofp,"%s\n",object_code);
					}

				}
			}
		}
	}
	//if instruction isn't found yet
	if(flag == 0)
	{
		//word_code reads the word
		char word_code[10];
		length = 0;
		//if the instruction is a WORD
		if(strcmp(instr[1],"WORD")==0)
		{
			//copy the instr[2] into the word_code
			strcpy(word_code,instr[2]);
			//1 is added to acount for "\n"
			int noOfZeroes = 6 - strlen(instr[2])+1;
			//adding the required number of zeroes to the beginning 
			for(int i = 0; i<=noOfZeroes;i++)
			{
				object_code[length] ='0';
				fprintf(ofp,"%c",object_code[length]);
				length++;
			}
			//adding the word to object_code
			for(int i= 0; instr[2][i]!='\n';i++)
			{
				object_code[length] = instr[2][i];
				fprintf(ofp,"%c",object_code[length]);
				length++;
			}
			//changing flag
			flag = 1;
			//writing to output file
			fprintf(ofp,"\n");

		}
		else
		{
			length =0;
			//If the instruction type is BYTE
			if(strcmp(instr[1],"BYTE")==0){
				//if the BYTE is a char type
				if(instr[2][0]=='C')
				{
					int i=2; //this is where the constant starts
					//We do not want the single quotations included
					 	while(instr[2][i] != '\'')
					 	{
					 		//storing the BYTE characters in object_code
					 		object_code[length] = instr[2][i];
					 		//printing the opcode into the file
					 		fprintf(ofp,"%x",object_code[length]);
					 		i++;length++;
					 	}
					 	//write to output file
					 	fprintf(ofp,"\n");
					 	flag=1;
					 	
				}
			}
		}
	}
	return;
}