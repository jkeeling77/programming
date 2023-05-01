#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_SIZE 10

void destroy_tree_data(void* data) {
    if( data != NULL ) {
    	free(data);
    }
}

int compare_tree_data(const void* key1, const void* key2) {
   int match;

   if( key1 == NULL && key2 == NULL) {
      match = 0;
   }
   else if( key1 == NULL || key2 == NULL) {
   	  match = 1;
   }
   else {
      match = strcmp( (char*)key1, (char*)key2);
   }

   return match;
}

void print_tree_data(void* data) {
	if( data != NULL ) {
		printf("%s ", (char*)data);
	}
}

int main(void) {
    BinaryTree* pBinaryTree = (BinaryTree*)malloc(sizeof(BinaryTree));
    char* name_list[LIST_SIZE] = {"larry", "curly", "elderly", "legs", "Eli",
	                              "blix", "hans", "Moasedlri", "Flynn", "Barfo"};

    binary_tree_init(pBinaryTree, destroy_tree_data, compare_tree_data, print_tree_data);

    for(int i = 0; i < LIST_SIZE; i++) {
    	binary_tree_insert(pBinaryTree, name_list[i]);
    }

    printf("Inorder Print:\n");
    binary_tree_print_inorder(pBinaryTree);

    printf("Preorder Print:\n");
    binary_tree_print_preorder(pBinaryTree);

    printf("Postorder Print:\n");
    binary_tree_print_postorder(pBinaryTree);


	return 0;
}