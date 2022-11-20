#include <stdio.h>
#include <stdlib.h>
struct node
{
    int val;
    struct node *parent;
    struct node *left;
    struct node *right;
};
typedef struct node *NodeAddress;
void insert(int x, NodeAddress this)
{
    if (x < this->val)
    {
        if (this->left == NULL)
        {
            this->left = malloc(sizeof(struct node));
            this->left->val = x;
            this->left->parent = this;
            return;
        }
        else
        {
            insert(x, this->left);
        }
    }
    else if (x >= this->val)
    {
        if (this->right == NULL)
        {
            this->right = malloc(sizeof(struct node));
            this->right->val = x;
            this->right->parent = this;
            return;
        }
        else
        {
            insert(x, this->right);
        }
    }
}
void inOrder(NodeAddress top)
{
    if (top == NULL)
        return;
    inOrder(top->left);
    printf("%d ", top->val);
    inOrder(top->right);
}
int findSucc(NodeAddress root)
{
    if (root->left == NULL)
    {
        return root->val; // if there are no more elements to the left, we are at the minimum element and thus have found the successor
    }
    else
        findSucc(root->left); // the successor will be the minimum element of the right subtree, which we find by going left within that subtree
}
int findPred(NodeAddress root)
{
    if (root->right == NULL)
    {
        return root->val; // if there are no more elements to the right, we are at the maximum element and thus have found the predecessor
    }
    else
        findPred(root->right); // the predecessor will be the maximum element of the left subtree, which we find by going right within that subtree
}
NodeAddress deleteNode(NodeAddress top, int x)
{
    int succ, pred;
    if (top == NULL)
    {
        return NULL;
    }
    if (x > top->val) // finding the element by tree traversal
    {
        top->right = deleteNode(top->right, x);
    }
    if (x < top->val)
    {
        top->left = deleteNode(top->left, x);
    }
    if (top->val == x)
    {
        if (top->left == NULL && top->right == NULL) // if it is a leaf node, just set it to NULL
        {
            top == NULL;
        }
        else if (top->right != NULL) // if there is a right child, replace the node with its successor and delete it
        {
            succ = findSucc(top->right);
            top->val = succ;
            top->right = deleteNode(top->right, succ);
        }
        else if (top->right == NULL && top->left != NULL) // if there is a left child and no right child, replace the node with its predecessor and then delete it
        {
            pred = findPred(top->left);
            top->val = pred;
            top->left = deleteNode(top->left, pred);
        }
    }
    return top;
}
int main()
{
    NodeAddress top = malloc(sizeof(struct node));
    printf("How many elements will you enter\n");
    int n;
    scanf("%d", &n);
    printf("Enter elements\n");
    int x;
    scanf("%d", &x);
    top->val = x;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &x);
        insert(x, top);
    }
    printf("The tree is: ");
    inOrder(top);
    printf("\n Enter node to delete");
    scanf("%d", &x);
    top = deleteNode(top, x);
    inOrder(top);
    return 0;
}