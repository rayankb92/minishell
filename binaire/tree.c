#include "tree.h"

tree	*new_tree(int x)
{
	tree *tr = malloc(sizeof(*tr));
	if (!tr)
		return (NULL);
	tr->value = x;
	tr->tleft = NULL;
	tr->tright = NULL;
	tr->parent = NULL;

	printf("creation de %d\n", tr->value);
	return tr;
}

void	clean_tree(tree *tr)
{
	if (!tr)
		return;
	printf("Suppression de %i\n", tr->value);
	clean_tree(tr->tleft);
	clean_tree(tr->tright);
	
	free(tr);
}

tree	*join_tree(tree *left, tree *right, int node)
{
	tree *tr = new_tree(node);

	tr->tleft = left;
	tr->tright = right;

	if (left)
		left->parent = tr;
	
	if (right)
		right->parent = tr;
	return (tr);
}

void	print_tree_prefix(tree *tr)
{
	if (!tr)
		return ;

	if (tr->parent)
		printf("(%d) -> (%d)\n", tr->parent->value, tr->value);
	else
		printf("(%d)\n", tr->value);
	
	if (tr->tleft)
		print_tree_prefix(tr->tleft);
	if (tr->tright)
		print_tree_prefix(tr->tright);
}

/*

ls	&&	ls	||	ls
ls && ls | cat
			|
	&& 			cat
ls		ls


*/