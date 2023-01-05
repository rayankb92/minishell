#include "tree.h"

int main(void)
{
	struct tree *arbre;
	
	arbre = join_tree((join_tree(new_tree(8), new_tree(3), 2)), new_tree(4) , 6);

	print_tree_prefix(arbre);

	clean_tree(arbre);
	return 0;
}