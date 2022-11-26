#include <stdio.h>
#include <stdlib.h>
struct node
{
    int val;
    struct node *parent;
    struct node *left;
    struct node *right;
    int height;
};
typedef struct node *NodeAddress;
int height(NodeAddress root) // function to get height
{
    if (root == NULL)
        return 0;
    return root->height;
}
int balanceF(NodeAddress root) // function to calculate balance factor
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
NodeAddress create(int x)
{
    NodeAddress new = malloc(sizeof(struct node));
    new->val = x;
    new->left = NULL;
    new->right = NULL;
}
NodeAddress RRotate(NodeAddress root) // function for a right rotation
{
    NodeAddress LRoot = root->left;                                     // left subtree
    NodeAddress RLRoot = LRoot->right;                                  // right subtree of left subtree
    LRoot->right = root;                                                // root node becomes the right subtree of its left subtree, making the left subtree the new root
    root->left = RLRoot;                                                // the previously-right subtree of the new root becomes the left subtree of the previous root
    LRoot->height = 1 + max(height(LRoot->left), height(LRoot->right)); // adjusting heights
    root->height = 1 + max(height(root->left), height(root->right));
    return LRoot;
}
NodeAddress LRotate(NodeAddress root) // function for a left rotation
{
    NodeAddress RRoot = root->right;                                    // right subtree
    NodeAddress LRRoot = RRoot->left;                                   // left subtree of the right subtree
    RRoot->left = root;                                                 // root node becomes the left subtree of its right subtree, making the right subtree the new root
    root->right = LRRoot;                                               // the previously-left subtree of the new root becomes the right subtree of the previous root
    RRoot->height = 1 + max(height(RRoot->left), height(RRoot->right)); // adjusting heights
    root->height = 1 + max(height(root->left), height(root->right));
    return RRoot;
}
NodeAddress balance(int x, NodeAddress top)
{
    int b = balanceF(top);
    if (b > 1 && x < top->left->val) // left left case
    {
        top = RRotate(top);
    }
    else if (b > 1 && x > top->left->val) // left right case
    {
        top->left = LRotate(top->left);
        top = RRotate(top);
    }
    else if (b < -1 && x > top->right->val) // right right case
    {
        top = LRotate(top);
    }
    else if (b < -1 && x < top->left->val) // right left case
    {
        top->right = RRotate(top->right);
        top = LRotate(top);
    }
    return top;
}
NodeAddress insert(int x, NodeAddress this) // same as regular function but with balancing
{
    if (this == NULL)
    {
        this = create(x);
        return this;
    }
    if (x < this->val) // if the value is less, we have to insert the node to the left
    {
        this->left = insert(x, this->left);
    }
    else if (x > this->val) // if the value is greater, we have to insert the node to the right
    {
        this->right = insert(x, this->right);
    }
    this->height = 1 + max(height(this->left), height(this->right)); // updating height
    this = balance(x, this);                                         // balancing tree
    return this;
}
void preOrder(NodeAddress top)
{
    if (top == NULL)
        return;
    printf("%d%d ", top->val, top->height);
    preOrder(top->left);
    preOrder(top->right);
}
NodeAddress AVLfromArr(int *arr, int n)
{
    NodeAddress top = malloc(sizeof(struct node));
    top->val = arr[0];
    top->height = 0;
    for (int i = 1; i < n; i++)
    {
        top = insert(arr[i], top); // we have to update the root each time as it will change as the tree is balanced
    }
    return top;
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
NodeAddress AVLdeleteNode(NodeAddress top, int x)
{
    int succ;
    NodeAddress temp;
    if (top == NULL) // if we reach the end of the tree and don't find the value then there is no node to delete
    {
        return NULL;
    }
    if (x > top->val) // finding the element by tree traversal
    {
        top->right = AVLdeleteNode(top->right, x);
    }
    if (x < top->val)
    {
        top->left = AVLdeleteNode(top->left, x);
    }
    if (top->val == x)
    {
        if (top->left == NULL || top->right == NULL) // if there is no child or only one child we look at individual cases
        {
            if (top->right != NULL)
                temp = top->right;
            else
                temp = top->left;
            if (temp == NULL) // if no child, just delete the node
            {
                top = NULL;
            }
            else // if one child, copy the values of that child (including the children) into the parent and then delete it
            {
                *top = *temp;
                free(temp);
            }
        }
        else // replace the node with its successor and delete it
        {
            succ = findSucc(top->right);
            top->val = succ;
            top->right = AVLdeleteNode(top->right, succ);
        }
    }
    top->height = 1 + max(height(top->left), height(top->right)); // update the height
    top = balance(0, top);                                        // balance the tree
    return top;
}
int main()
{
    printf("Enter number of nodes of tree");
    int n;
    scanf("%d", &n);
    printf("Enter values");
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    NodeAddress top = AVLfromArr(arr, n);
    preOrder(top);
    printf("Enter value to delete\n");
    scanf("%d", &n);
    top = AVLdeleteNode(top, n);
    preOrder(top);
    return 0;
}