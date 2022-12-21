#include <stdio.h>
#include <stdlib.h>
struct node
{
    int val;
    struct node *left;
    struct node *right;
};
typedef struct node *NodeAddress;
NodeAddress RRotate(NodeAddress root) // function for a right rotation (same as AVL)
{
    NodeAddress LRoot = root->left;    // left subtree
    NodeAddress RLRoot = LRoot->right; // right subtree of left subtree
    LRoot->right = root;               // root node becomes the right subtree of its left subtree, making the left subtree the new root
    root->left = RLRoot;               // the previously-right subtree of the new root becomes the left subtree of the previous root
    return LRoot;
}
NodeAddress LRotate(NodeAddress root) // function for a left rotation (same as AVL)
{
    NodeAddress RRoot = root->right;  // right subtree
    NodeAddress LRRoot = RRoot->left; // left subtree of the right subtree
    RRoot->left = root;               // root node becomes the left subtree of its right subtree, making the right subtree the new root
    root->right = LRRoot;             // the previously-left subtree of the new root becomes the right subtree of the previous root
    return RRoot;
}
NodeAddress splay(NodeAddress root, int x, int *flag)
{
    if (root == NULL || root->val == x)
        return root;

    else if (x > root->val) // x is in the right subtree
    {

        if (!root->right) // x is not in tree
        {
            *flag = 0;
            return root;
        }
        else if (root->right->val == x) // Zag or Left rotation
        {
            root = LRotate(root);
            return root;
        }
        else if (root->right->val > x) // x is in the right subtree but to the left of the right node and has a grandparent
        {
            root->right->left = splay(root->right->left, x, flag);
            root = RRotate(root);
            if (!root->right)
                return root;
            else
                return LRotate(root);  // performing the final rotation to make the node containing x the root node
        }                              // Zag-Zig or Left-Right rotation
        else if (root->right->val < x) // x is further right in the tree and has a grandparent
        {
            root->right->right = splay(root->right->right, x, flag);
            root = LRotate(root);
            if (!root->right)
                return root;
            else
                return LRotate(root); // performing the final rotation to make the node containing x the root node
        }                             // Zag-Zag or Left-Left rotation
    }
    else // x is in the left subtree
    {
        if (!root->left) // x is not in tree
        {
            *flag = 0;
            return root;
        }
        else if (root->left->val == x) // Zig or Right rotation
        {
            root = RRotate(root);
            return root;
        }
        else if (root->left->val < x) // x is in the left subtree but to the right of the left node and has a grandparent
        {
            root->left->right = splay(root->left->right, x, flag);
            root = LRotate(root);
            if (!root->left)
                return root;
            else
                return RRotate(root); // performing the final rotation to make the node containing x the root node
        }                             // Zig-Zag or Right-Left rotation
        else if (root->left->val > x) // x is further left and has a grandparent
        {
            root->left->left = splay(root->left->left, x, flag);
            root = RRotate(root);
            if (!root->left)
                return root;
            else
                return RRotate(root); // performing the final rotation to make the node containing x the root node
        }                             // Zig-zig or Right-Right rotation
    }
}
NodeAddress insert(int x, NodeAddress this, NodeAddress root) // similar insert function to the one from my BST code, just with the addition of splaying
{
    if (x == this->val)
    {
        printf("Duplicate values are not allowed.");
        return NULL;
    }
    else if (x < this->val) // x should go in the left subtree
    {
        if (this->left == NULL) // we can create the node here
        {
            this->left = malloc(sizeof(struct node));
            this->left->val = x;
            int flag = 1;
            this = splay(root, x, &flag);
            return this;
        }
        else
        {
            insert(x, this->left, root);
        }
    }
    else if (x > this->val) // x should go in the right subtree
    {
        if (this->right == NULL) // we can create the node here
        {
            this->right = malloc(sizeof(struct node));
            this->right->val = x;
            int flag = 1;
            this = splay(root, x, &flag);
            return this;
        }
        else
        {
            insert(x, this->right, root);
        }
    }
}
NodeAddress SplayfromArr(int *arr, int n) // almost the same as the AVLfromArr code
{
    NodeAddress root = malloc(sizeof(struct node));
    root->val = arr[0];
    for (int i = 1; i < n; i++)
    {
        root = insert(arr[i], root, root); // we have to update the root each time as it will change as the tree is splayed
    }
    return root;
}
NodeAddress search(NodeAddress root, int x)
{
    int flag = 1;
    NodeAddress this = splay(root, x, &flag); // the splay function already implicitly searches; I just added a flag for cases where the value is not in the tree
    if (flag == 0)
    {
        printf("Value not found in tree.\n");
        return root; // if the value is not in the tree, don't change the tree
    }
    else
    {
        printf("Value found.\n");
        return this; // if the value is in the tree, return the splayed tree
    }
}
void preOrder(NodeAddress root) // normal preorder function
{
    if (root == NULL)
        return;
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(NodeAddress root) // normal inorder function
{
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}
int main()
{
    int n = 10;
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    NodeAddress root = SplayfromArr(arr, n);
    preOrder(root);
    printf("\n");
    root = search(root, 5);
    preOrder(root);
    printf("\n");
}