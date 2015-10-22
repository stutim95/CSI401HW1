//The node for the Symbol table
struct symbol
{
	char label[10];
	int location;
	struct symbol* left;
	struct symbol* right;
};
typedef struct symbol sym;
//The structure for the loction addresses
struct location_addr
{
	char label[10];
	int	 lc;
	struct location_addr* next;
};
typedef struct location_addr LC;