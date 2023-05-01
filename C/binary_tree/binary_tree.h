
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef struct BinaryTreeNode_ {
   struct BinaryTreeNode_* left;
   struct BinaryTreeNode_* right;
   void* data;
} BinaryTreeNode;

typedef struct BinaryTree_ {
   int size;
   BinaryTreeNode* root;
   int (*compare)(const void* key1, const void* key2);
   void (*destroy)(void* data);
   void (*print)(void* data);
} BinaryTree;

BinaryTreeNode* binary_tree_root(BinaryTree* pBinaryTree);
void binary_tree_init(BinaryTree* pBinaryTree, void (*destroy)(void* data), int (*compare)(const void* key1, const void* key2), void (*print)(void* data));
void binary_tree_destroy(BinaryTree* pBinaryTree);
void binary_tree_insert(BinaryTree* pBinaryTree, void* data);
void binary_tree_rem_left(BinaryTree* pBinaryTree, BinaryTreeNode* pBinaryTreeNode);
void binary_tree_rem_right(BinaryTree* pBinaryTree, BinaryTreeNode* pBinaryTreeNode);
int  binary_tree_size(BinaryTree* pBinaryTree);
void binary_tree_print_inorder(BinaryTree* pBinaryTree);
void binary_tree_print_preorder(BinaryTree* pBinaryTree);
void binary_tree_print_postorder(BinaryTree* pBinaryTree);

#endif
