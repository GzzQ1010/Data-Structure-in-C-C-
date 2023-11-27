#include "bitree.h"
#include <stdio.h>

static int insert_int(BiTree *tree, BiTreeNode *node, int value, int is_left) {
    int *data = (int*)malloc(sizeof(int));
    if (data == NULL) {
        return -1; // Return an error if memory allocation fails
    }

    *data = value;

    // If the node is NULL, we are inserting the root node
    if (node == NULL) {
        if (bitree_size(tree) > 0) {
            free(data); // Avoid inserting root if the tree is not empty
            return -1;
        }
        return bitree_ins_left(tree, NULL, data);
    }

    // Insert the data to the left or right as needed
    return is_left ? bitree_ins_left(tree, node, data) : bitree_ins_right(tree, node, data);
}

// Helper function to print integers
void print_int(const void *data) {
    printf("%d ", *(int *)data);
}


int main(){
    BiTree tree1, tree2;
    bitree_init(&tree1, free);
    bitree_init(&tree2, free);

    // Build Tree #1
    insert_int(&tree1, NULL, 1, 1); // Insert root
    BiTreeNode *node;
    
    node = bitree_root(&tree1);
    insert_int(&tree1, node, 2, 1); // Insert left child of root
    insert_int(&tree1, node, 3, 0); // Insert right child of root
    
    node = bitree_left(node);
    insert_int(&tree1, node, 4, 1); // Continue inserting for left subtree
    
    node = bitree_left(node);
    insert_int(&tree1, node, 7, 1); // Continue inserting for left subtree
    
    node = bitree_root(&tree1); // Reset to root to insert right subtree
    node = bitree_right(node);
    insert_int(&tree1, node, 5, 1); // Insert left child of right subtree of root
    insert_int(&tree1, node, 6, 0); // Insert right child of right subtree of root
    
    node = bitree_right(node);
    insert_int(&tree1, node, 8, 0); // Continue inserting for right subtree
    
    node = bitree_right(node);
    insert_int(&tree1, node, 9, 0); // Continue inserting for right subtree

    insert_int(&tree2, NULL, 6, 1); // Insert root for Tree #2

    //Build tree2 
    BiTreeNode *node2;
    node2 = bitree_root(&tree2);
    
    // Insert left subtree
    insert_int(&tree2, node2, 4, 1);
    
    // Work on left child of the left subtree
    node2 = bitree_left(node2);
    insert_int(&tree2, node2, 2, 1); // Insert left child
    
    node2 = bitree_left(node2); // Go to left child
    insert_int(&tree2, node2, 1, 1); // Insert left child
    insert_int(&tree2, node2, 3, 0); // Insert right child

    // Move back to root to work on the right subtree
    node2 = bitree_root(&tree2);

    // Insert right subtree
    insert_int(&tree2, node2, 8, 0);

    // Work on the right child of the right subtree
    node2 = bitree_right(node2);
    insert_int(&tree2, node2, 5, 1); // Insert left child
    insert_int(&tree2, node2, 7, 0); // Go to right child
    insert_int(&tree2, node2, 9, 0); // Insert right child of right subtree


    /* Test functions */
    //tree1
    printf("Tree #1 leaves: %d\n", count_leaves(&tree1));
    printf("Tree #1 non-leaves: %d\n", count_non_leaves(&tree1));
    printf("Tree #1 height: %d\n", get_height(&tree1));

    printf("Pre-order Tree #1: ");
    print_pre_order(&tree1, print_int);
    printf("\n");

    printf("In-order Tree #1: ");
    print_in_order(&tree1, print_int);
    printf("\n");

    printf("Post-order Tree #1: ");
    print_post_order(&tree1, print_int);
    printf("\n");

    /* Remove leaves and print again */
    remove_leaves(&tree1);
    printf("Tree #1 after removing leaves (Pre-order): ");
    print_pre_order(&tree1, print_int);
    printf("\n");

    //tree2 
    printf("Tree #2 leaves: %d\n", count_leaves(&tree2));
    printf("Tree #2 non-leaves: %d\n", count_non_leaves(&tree2));
    printf("Tree #2 height: %d\n", get_height(&tree2));

    printf("Pre-order Tree #2: ");
    print_pre_order(&tree2, print_int);
    printf("\n");

    printf("In-order Tree #2: ");
    print_in_order(&tree2, print_int);
    printf("\n");

    printf("Post-order Tree #2: ");
    print_post_order(&tree2, print_int);
    printf("\n");

    /* Remove leaves and print again */
    remove_leaves(&tree2);
    printf("Tree #2 after removing leaves (Pre-order): ");
    print_pre_order(&tree2, print_int);
    printf("\n");

    return 0;
}