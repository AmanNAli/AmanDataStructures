#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
NodeAddress splay(NodeAddress root, int x)
{

    if (!root) // base case
        return root;
    if (x == root->val) // base case
        return root;
    else if (x > root->val) // x is in the right subtree
    {

        if (!root->right) // x is not in the tree
        {
            return root;
        }
        else if (x < root->right->val) // x is in the right subtree but is to the left and has a grandparent
        {                              // Zig-Zag or Right-Left rotation

            root->right->left = splay(root->right->left, x); // bring x to the right-left node

            if (root->right->left)
                root->right = RRotate(root->right); // perform a right rotation, x moves up a node
        }
        else if (x > root->right->val) // x is further right and has a grandparent
        {                              // Zag-Zag or Left-Left rotation

            root->right->right = splay(root->right->right, x); // bring x to the right-right node
            root = LRotate(root);                              // perform a left rotation, x moves up a node
        }
        if (root->right)
        {
            root = LRotate(root); // perform a final rotation to move x to the root. This also serves as the rotation required for the Zag case.
            return root;
        }
        else
            return root;
    }

    else // x is in the left subtree
    {

        if (!root->left) // x is not in the tree
        {
            return root;
        }

        else if (x > root->left->val) // x is in the left subtree but is to the right and has a grandparent
        {                             // Zag-Zig or Left-Right rotation

            root->left->right = splay(root->left->right, x); // bring x to the left-right node

            if (!root->left->right)
                root->left = LRotate(root->left); // perform a left rotation, x moves up a node
        }
        else if (x < root->left->val)                      // x is further left and has a grandparent
        {                                                  // Zig-Zig or Right-Right rotation
            root->left->left = splay(root->left->left, x); // bring x to the left-left node

            root = RRotate(root); // perform a right rotation, x moves up a node
        }
        if (root->left)
        {
            root = RRotate(root); // perform a final rotation to move x to the root. This also serves as the rotation required for the Zig case.
            return root;
        }
        else
            return root;
    }
}

NodeAddress create(int x) // same create function as in my AVL code
{
    NodeAddress new = malloc(sizeof(struct node));
    new->val = x;
    new->left = NULL;
    new->right = NULL;
    return new;
}
NodeAddress insert(int x, NodeAddress this) // same as regular function but with splaying
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
    int flag = 1;
    this = splay(this, x); // splaying node at each step
    return this;
}

NodeAddress SplayfromArr(int *arr, int n) // almost the same as the AVLfromArr code
{
    NodeAddress root = malloc(sizeof(struct node));
    root->val = arr[0];
    for (int i = 1; i < n; i++)
    {
        root = insert(arr[i], root); // we have to update the root each time as it will change as the tree is splayed
    }
    return root;
}
NodeAddress search(NodeAddress root, int x) // normal search function with the addition of splaying
{
    NodeAddress this = root;
    int flag = 0;
    while (this != NULL)
    {
        if (this->val == x) // if we find the value, splay it and say we found it
        {
            printf("Value found.\n");
            flag = 1;
            root = splay(root, x);
            break;
        }
        else if (x > this->val) // if x is greater than the current node's value, it must be to the right
        {
            this = this->right;
        }
        else // if x is smaller than the current node's value, it must be to the left
        {
            this = this->left;
        }
    }
    if (flag == 0) // if flag is 0, x was not found
        printf("Value not in tree.\n");
    return root;
}
void preOrder(NodeAddress root, NodeAddress this) // normal preorder function, helps show that the splayed node ends up at the root
{
    if (root == NULL)
    {
        printf("Tree is empty");
        return;
    }
    if (this == NULL)
        return;
    printf("%d ", this->val);
    preOrder(root, this->left);
    preOrder(root, this->right);
}
void inOrder(NodeAddress root, NodeAddress this) // normal inorder function if needed for testing
{
    if (root == NULL)
    {
        printf("Tree is empty.");
        return;
    }
    if (this == NULL)
        return;
    inOrder(root, this->left);
    printf("%d ", this->val);
    inOrder(root, this->right);
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

NodeAddress delete(NodeAddress root, NodeAddress this, int x)
{
    if (this == NULL) // x is not in the tree
        return root;
    if (x > this->val) // x is in the right subtree
    {
        if (!this->right) // x is not in the tree
            return root;  // if x is not in the tree, we return the unchanged tree
        else
            delete (root, this->right, x);
    }
    else if (x < this->val) // x is in the left subtree
    {
        if (!this->left) // x is not in the tree
            return root; // if x is not in the tree, we return the unchanged tree
        else
            delete (root, this->left, x);
    }
    else if (x == this->val)
    {
        int flag = 1;
        this = splay(root, x); // splay the node containing the value to the root
        if (this->val == x)
        {
            NodeAddress LSub = this->left;  // stores the left subtree
            NodeAddress RSub = this->right; // stores the right subtree
            if (!LSub)                      // if there is no left subtree, we can just return the right subtree as the new tree
            {
                free(this); // deleting the node
                return RSub;
            }
            else
            {
                int pred = findPred(LSub); // find the maximum value in the left subtree
                LSub = splay(LSub, pred);  // splay it to the top
                LSub->right = RSub;        // the right subtree of the original tree can be made the right subtree of the predecessor
                free(this);
                return LSub;
            }
        }
        else
            return root;
    }
}

int valid(char input[]) // checks if the input is valid by always taking a string and evaluating if it consists of only digits
{
    int length = strlen(input);
    int flag = 0;
    if (length > 0)
    {
        for (int i = 0; i < length; i++)
        {
            if (input[0] == 45)
            {
                continue;
            }
            if (!isdigit(input[i])) // if any character is not a digit, flag becomes 1 i.e. the input is not valid
            {
                flag = 1;
            }
        }
    }
    int x = atoi(input);
    if (x > 2147483647 || x < -2147483647)
        flag = 1;
    return flag;
}
int main()
{
    char inp[10];
    printf("Enter the number of elements in the tree.\n");
    scanf("%s", inp);
    if (valid(inp) == 1) // validating input
    {
        printf("Invalid input.\n");
    }
    else
    {
        int n = atoi(inp); // if the input is valid, convert it to an integer
        if (n <= 0)
            printf("No values can be entered.");
        else
        {
            int x;
            int *arr = malloc(n * sizeof(int));
            printf("Enter the values\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%s", inp);
                if (valid(inp) == 1)
                {
                    printf("Invalid input.\n"); // validating input at each step
                }
                else
                {
                    arr[i] = atoi(inp);
                }
            }
            printf("Values entered:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
            NodeAddress root = SplayfromArr(arr, n); // turning the array we just created into a splay tree
            printf("Preorder traversal of tree:\n");
            preOrder(root, root);
            printf("\n");
            printf("Enter the value you want to search for\n");
            scanf("%s", inp);
            if (valid(inp) == 1)
                printf("Invalid input.\n");
            else // if input is valid, search normally
            {
                x = atoi(inp);
                NodeAddress temp = root;
                root = search(root, x);
                printf("\nTree after searching:\n");
                preOrder(root, root);
                printf("\n");
                temp = root;
                printf("Enter the value you want to delete\n");
                scanf("%s", inp);
                if (valid(inp) == 1)
                    printf("Invalid input.\n");
                else // if input is valid, delete normally
                {
                    x = atoi(inp);
                    NodeAddress temp = root;
                    root = delete (root, temp, x);
                    printf("\nTree after deletion:\n");
                    preOrder(root, root);
                    printf("\n");
                }
            }
        }
    }
}