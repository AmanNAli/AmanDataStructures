#include<stdio.h>
#include<stdlib.h>
struct node
{
    int val;
    struct node* parent;
    struct node* left;
    struct node* right;
};
typedef struct node* NodeAddress;
void insert(int x, NodeAddress this)
{
    if(x < this->val)
    {
        if(this->left == NULL)
        {
            this->left = malloc(sizeof(struct node));
            this->left->val = x;
            this->left->parent = this;
            return;
        }
        else
        {
            insert(x,this->left);
        }
    }
    else if(x >= this->val)
    {
        if(this->right == NULL)
        {
            this->right = malloc(sizeof(struct node));
            this->right->val = x;
            this->right->parent = this;
            return;
        }
        else
        {
            insert(x,this->right);
        }
    }
}
void inOrder(NodeAddress top)
{
    if(top==NULL)
    return;
    inOrder(top->left);
    printf("%d ",top->val);
    inOrder(top->right);
}
int main()
{
    NodeAddress top = malloc(sizeof(struct node));
    printf("How many elements will you enter\n");
    int n;
    scanf("%d",&n);
    printf("Enter elements\n");
    int x;
    scanf("%d",&x);
    top->val = x;
    for(int i=1;i<n;i++)
    {
        scanf("%d",&x);
        insert(x,top);

    }
    printf("The tree is: ");
    inOrder(top);
    return 0;
}