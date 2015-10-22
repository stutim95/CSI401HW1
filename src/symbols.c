#include "headers.h"
#include "struct_def.h"
#include "prototypes.h"
#include "externs.h"
sym *current;
/**
*Add a node to the symbol table linked list
*@params label: The label that is to be added to the symbol table
		 leaf: the address of the root leaf
*
**/
void add_sym(sym ** leaf, char label[50])
{
	//if the leaf node is empty
	if(*leaf == 0)
	{
		//creating a new sym in memory
		*leaf = (sym*) malloc( sizeof(sym));
		//putting the data into the node
		strcpy((*leaf)->label,label);
		(*leaf)->location = LOCADDR;
		(*leaf)->left = 0;
		(*leaf)->right = 0;
		return;
	}
	//if the leaf is not empty
	else
	{
		//checking if the LOCADDR is lesser than the LOCADDR of the node. If it is lesser, it will go into the left node.
		if(LOCADDR < (*leaf)->location)
		{
			add_sym(&(*leaf)->left, label);
		}
		//If the LOCADDR is greater than or equal to the location address of the leaf node, it will go into 
		else if(LOCADDR>= (*leaf)->location)
		{
			add_sym(&(*leaf)->right, label);
		}
		
	}
}

/** Find the location of a label
* @param label: the label to be located
			leaf: the root leaf
* @return the location address of the label
**/
int sym_find(char label[10],sym *leaf)
{
	//if the leaf node is not empty
		if(leaf != 0)
	  {
	  	//comparing the label and leaf's label
		if(strcmp(label,leaf->label)==0)
		{
			//returns the location address if the label is matched
			return leaf->location;
		}
		//checking if the current lOCADDR is lesser than that of the left node
		//This technique works in this instance because our address is always going to be greater than the preceeding node
		else if(LOCADDR < leaf->location)
		{
			//we are going into the left node
			return sym_find(label, leaf->left);
		}
		else
		{
			//we are going into the right sym node
			return sym_find(label, leaf->right);
		}

	}
	else
	{
		//return the location
		return leaf->location;
	}
}

/** A function that checks whether a label is present in a binary tree
* @param label: the label we are checking for
		 leaf: the root sym node 
* @return return 1 if the label is found and 0 if the label is not found
**/
int sym_search(char label[10], sym *leaf)
{
	//if leaf is not empty
	if(leaf != 0)
	{
		if(strcmp(label,leaf->label)==0)
		{
			return 1;
		}
		//checking if the current lOCADDR is lesser than that of the left node
		//This technique works in this instance because our address is always going to be greater than the preceeding node
		else if(LOCADDR < leaf->location)
		{
			//we are going into the left node
			return sym_search(label, leaf->left);
		}
		else
		{
			//we are going into the right sym node
			return sym_search(label, leaf->right);
		}

	}
	else
	{
		return 0;
	}
}


/** Print the symbol table. We use inorder traversal here.
*   @param leaf: the root sym node
**/
void print_sym(sym *leaf)
{
	//if the left node is not empty
	 if(leaf->left!=0)
	 {
	 	return print_sym(leaf->left);
	 }
	 printf("%s %d \n",leaf->label, leaf->location);
	 //if the right node is not empty
	 if(leaf->right!=0)
	 {
	 	return print_sym(leaf->right);
	 }
	
}


/** Delete all the nodes
*	@param leaf:the root sym node
**/
void delete_sym(sym *leaf)
{
	if(leaf != 0)
	{
		delete_sym(leaf->left);
		delete_sym(leaf->right);
		free(leaf);
	}
}