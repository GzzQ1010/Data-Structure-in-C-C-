/*
 * bitree.h
 */
#ifndef BITREE_H
#define BITREE_H

#include <stdlib.h>

/* Define a structure for binary tree nodes. */
typedef struct BiTreeNode_ {

    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;

} BiTreeNode;

/* Define a structure for binary trees. */
typedef struct BiTree_ {

    int size;

    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    BiTreeNode *root;

} BiTree;

/* Public Interface */
void bitree_init(BiTree *tree, void(*destroy)(void *data));

void bitree_destroy(BiTree *tree);

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);

void bitree_rem_left(BiTree *tree, BiTreeNode *node);

void bitree_rem_right(BiTree *tree, BiTreeNode *node);

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

int count_leaves(BiTree *tree);//Returns the number of leaf nodes in the tree.

int count_non_leaves(BiTree *tree);//Returns the number of non-leaf nodes in the tree.

int get_height(BiTree *tree);//Returns the height of the tree.

/*Prints the elements of the tree to stdout using a pre-order traversal. The print 
parameter should contain the logic to print the data held in each node in the 
tree.*/
void print_pre_order(BiTree *tree, void (*print)(const void *data));

/*Prints the elements of the tree to stdout using an in-order traversal. The print 
parameter should contain the logic to print the data held in each node in the 
tree.*/
void print_in_order(BiTree *tree, void (*print)(const void *data));

/*Prints the elements of the tree to stdout using a post-order traversal. The 
print parameter should contain the logic to print the data held in each node in 
the tree.*/
void print_post_order(BiTree *tree, void (*print)(const void *data));

/*Removes all leaf nodes from the tree. Use print_pre_order, 
print_in_order, or print_post_order after calling remove_leaves
to show that remove_leaves successfully removed all leaves. */
void remove_leaves(BiTree *tree);

#define bitree_size(tree) ((tree)->size)

#define bitree_root(tree) ((tree)->root)

#define bitree_is_eob(node) ((node) == NULL)

#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)

#define bitree_data(node) ((node)->data)

#define bitree_left(node) ((node)->left)

#define bitree_right(node) ((node)->right)

#endif
