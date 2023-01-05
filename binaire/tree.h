#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
	int	value;
	struct	tree	*tleft;
	struct	tree	*tright;
	struct	tree	*parent;
}				tree;

tree	*new_tree(int	x);
void	clean_tree(tree *tr);
tree	*join_tree(tree *left, tree *right, int node);
void	print_tree_prefix(tree *tr);


#endif