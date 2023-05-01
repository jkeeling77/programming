#include "binary_tree.h"
#include <stdlib.h>
#include <string.h>


static void S_print_data(BinaryTree* pBinaryTree, BinaryTreeNode* pBinaryTreeNode) {
    if( pBinaryTreeNode != NULL ) {
        S_print_data(pBinaryTree, pBinaryTreeNode->left);
        pBinaryTree->print(pBinaryTreeNode->data);
        S_print_data(pBinaryTree, pBinaryTreeNode->right);
    }
}

static void S_print_preorder(BinaryTree* pBinaryTree, BinaryTreeNode* pBinaryTreeNode ) {
	if( pBinaryTreeNode != NULL ) {
		pBinaryTree->print(pBinaryTreeNode->data);
		S_print_data(pBinaryTree, pBinaryTreeNode->left);
		S_print_data(pBinaryTree, pBinaryTreeNode->right);
	}
}

static void S_print_postorder(BinaryTree* pBinaryTree, BinaryTreeNode* pBinaryTreeNode ) {
	if( pBinaryTreeNode != NULL ) {
		S_print_data(pBinaryTree, pBinaryTreeNode->left);
		S_print_data(pBinaryTree, pBinaryTreeNode->right);
		pBinaryTree->print(pBinaryTreeNode->data);
	}
}

static BinaryTreeNode* S_create_node(void* data) {
	BinaryTreeNode* pBinaryTreeNode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));

	pBinaryTreeNode->data = data;
	pBinaryTreeNode->left = NULL;
	pBinaryTreeNode->right = NULL;

	return pBinaryTreeNode;
}

static void S_insert_node(BinaryTree* pBinaryTree, BinaryTreeNode** ppBinaryTreeNode, void* data) {
    if( *ppBinaryTreeNode == NULL ) {
    	*ppBinaryTreeNode = S_create_node(data);
    }
    else {
    	if(pBinaryTree->compare( (*ppBinaryTreeNode)->data, data) > 0 )
    		S_insert_node(pBinaryTree, &((*ppBinaryTreeNode)->left), data);
    	else
    		S_insert_node(pBinaryTree, &((*ppBinaryTreeNode)->right), data);
    }
}

void binary_tree_print_inorder(BinaryTree* pBinaryTree) {
    S_print_data(pBinaryTree, pBinaryTree->root);
}

void binary_tree_print_preorder(BinaryTree* pBinaryTree) {
	S_print_preorder(pBinaryTree, pBinaryTree->root);
}

void binary_tree_print_postorder(BinaryTree* pBinaryTree) {
	S_print_postorder(pBinaryTree, pBinaryTree->root);
}

void binary_tree_init(BinaryTree* pBinaryTree,
	                  void       (*destroy)(void* data),
                      int        (*compare)(const void* key1, const void* key2),
                      void       (*print)(void* data)) {
   pBinaryTree->size = 0;
   pBinaryTree->destroy = destroy;
   pBinaryTree->compare = compare;
   pBinaryTree->print = print;
   pBinaryTree->root = NULL;
}

void binary_tree_destroy(BinaryTree* pBinaryTree) {
   binary_tree_rem_left(pBinaryTree, NULL);
   memset(pBinaryTree, 0, sizeof(BinaryTree));
}

void binary_tree_insert(BinaryTree* pBinaryTree, void* data) {
	S_insert_node(pBinaryTree, &pBinaryTree->root, data);
}

void binary_tree_rem_left(BinaryTree* pBinaryTree, BinaryTreeNode* pBinaryTreeNode) {
    BinaryTreeNode** position;

    if(binary_tree_size(pBinaryTree) > 0) {
    	if(pBinaryTreeNode == NULL)
    		position = &pBinaryTree->root;
    	else
    		position = &pBinaryTreeNode->left;

    	if( *position != NULL ) {
    		binary_tree_rem_left(pBinaryTree, *position);
    		binary_tree_rem_right(pBinaryTree, *position);

    		if( pBinaryTree->destroy != NULL ) {
    			pBinaryTree->destroy((*position)->data);
    		}
    		free(*position);
    		*position = NULL;
    		pBinaryTree->size--;
    	}
    }
}

void binary_tree_rem_right(BinaryTree* pBinaryTree, BinaryTreeNode* pBinaryTreeNode) {
	BinaryTreeNode** position;

	if( binary_tree_size(pBinaryTree) > 0 ) {
		if( pBinaryTreeNode == NULL )
			position = &pBinaryTree->root;
		else
			position = &pBinaryTreeNode->right;

		if( *position != NULL ) {
			binary_tree_rem_left(pBinaryTree, *position);
			binary_tree_rem_right(pBinaryTree, *position);

			if( pBinaryTree->destroy != NULL ) {
				pBinaryTree->destroy((*position)->data);
			}
			free(*position);
			*position = NULL;
			pBinaryTree->size--;
		}
	}

	return;
}

int binary_tree_size(BinaryTree* pBinaryTree) {
	return pBinaryTree->size;
}