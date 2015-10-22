#include "headers.h"
#include "struct_def.h"
#include "externs.h"
#include "prototypes.h"
LC *current;
/**
*Add a node to the symbol table linked list
*@params label: The label that is to be added to the symbol table
*
**/
void add_lc(char label[50])
{
	//if the linked list is empty
	if(LOCATION->lc==0)
	{
		//create a new node
		strcpy(LOCATION->label,label);
		LOCATION->lc = LOCADDR;
		LOCATION->next = 0;
	}
	else
	{
		//traverse to the last node
		current = LOCATION;
		while(current->next!=0)
		{
			current = current->next;
		}
		//creating a new node
		LC *newNode;
		newNode= malloc(sizeof(LC));
		current->next = newNode;
		strcpy(newNode->label,label);
		newNode->lc=LOCADDR;
		newNode->next = 0;
		
	}
}


/**look for a label in a linked list
*	@param label:The label we are looking for
**/
int lc_search(char label[10])
{
	//traversing through the list 
	current = LOCATION;
	int flag = 0;
	while(current->next!=0)
	{
		//looking for new node
		if(strcmp(label,current->label)==0)
		{
			flag = 1;
			return 0;
		}
		current = current->next;
	}
	//for last node. Comparing for new node
	if(strcmp(label,current->label)==0)
	{
		flag = 1;
		return 0;
	}
	return 1;
}


/** Print the location address table
**/
void print_lc()
{
	current = LOCATION;
	if(LOCATION->lc==0)
	{
		puts("LOCATION TABLE EMPTY");
	}
	else{
		//for last node
		puts("LOCATION TABLE");
		//Traverse through the list and print
	while(current->next!=0)
	{
		printf("%s %d \n",current->label,current->lc);
		current = current->next;
	}
	//for last node
		printf("%s %d \n",current->label,current->lc);
	}
	
}


/** Delete the linked list
**/
void delete_lc()
{
	LC *delete;
	current = LOCATION;
	//Delete all nodes
	while(current!=0)
	{
		delete = current;
		current = current->next;
	}
}
//Sets the initial value of the LC(lOCADDR)
void readFirstLC(char first_addr[10])
{
	//LOCADDR is initialized to the first address
	LOCADDR = atoi(first_addr);
	return;
}


/**
*To update the LC values.
*@params count: The number of paramets held by the string
         instr: The instruction whose address has to been added to the LC values
*
**/
void add_locaddr(int count, char instr[3][10])
{
	int pos;
	//if there is no label
	if(count == 2)
	{
		pos = 0;
	}
	//if there is a label
	else
	{
		pos = 1;
	}
	//The opcodes will increment address by 3
	if(strcmp(instr[pos],operation[0])==0 || strcmp(instr[pos],operation[1])==0|| strcmp(instr[pos],operation[2])==0 || strcmp(instr[pos],operation[3])==0)
	{
		//increment it by 3
		LOCADDR+=3;
	}
	else
	{
		//if the instruction is "WORD"
		if((strcmp(instr[pos],"WORD") == 0))
		{
			//increment by 3
			LOCADDR+=3;
		}
		else
		{
			//if the instruction is "RESW"
			if((strcmp(instr[pos],"RESW") == 0))
			{
				//adding the no of words*3
				LOCADDR=LOCADDR + atoi(instr[2])*3;
			}
			else
			{
				//if the instruction is "RESB"
				if((strcmp(instr[pos],"RESB") == 0))
				{
					//adding the number of nodes
					LOCADDR+=atoi(instr[2]);
				}
				else
				{
					//if the instruction is "BYTE"
					if((strcmp(instr[pos],"BYTE") == 0))
				   {
				   	//if instr[2] starts with 'C' or 'X'
					 if(instr[pos+1][0]=='C' || instr[pos+1][0] == 'X')
					 {

					 	int i=2; //this is where the constant starts
					 	int byte = 0; //number to add to LOCADDR
					 	//while we do not reach \'
					 	while(instr[pos+1][i] != '\'')
					 	{
					 		//increment byte
					 		byte++;
					 		i++;
					 	}
					 	//adding LOCADDR by byte
					 	LOCADDR= LOCADDR+byte;

					 }
				   }	
				}
			}
		}
	}
	return;
}