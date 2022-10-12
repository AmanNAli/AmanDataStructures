#include <stdio.h>
#include <stdlib.h>
struct node {
    int val;
    struct node * next;
};

typedef struct node * NodeAddress;


NodeAddress chunkReverseList(NodeAddress head,int k)
{
    NodeAddress curr,prev,nextv;
    int count = 0;
    if (head==NULL)
    {
        return NULL;
    }

    curr = head;
    prev = NULL;
    nextv = NULL;
    while(head!=NULL && count<k)
        {

            nextv = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextv;
            count++;
        }
    if (head!=NULL)
        {
            head->next = chunkReverseList(nextv,k);
        }
    return prev;
    }



NodeAddress linkedListFromArray(int * a, int n)
{
    NodeAddress head = NULL;
    NodeAddress temp = NULL;
    if(n>0)
    {
        head = malloc(sizeof(struct node));
        head->val = a[0];
        head->next = NULL;
        temp = head;
    }
    for(int i=1;i<n;i++)
    {
    temp->next = malloc(sizeof(struct node));
    temp = temp->next;
    temp->val = a[i];
    temp->next = NULL;
    }
    return head;
};


void displayList(NodeAddress head){
    for(NodeAddress c=head;c!=NULL;c=c->next)
    {
    printf(" %d ",c->val);
    }
};


int main(int argv, char ** argc)
{
    int n;
    printf("Enter array length\n");
    scanf("%d",&n);
    int * a = malloc(n * sizeof(int));
    printf("Enter values of array\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }

    NodeAddress head = linkedListFromArray(a,n);
    printf("List is:");
    displayList(head);
    printf("Enter chunk size");
    int k;
    scanf("%d",&k);
    printf("Chunk reversed list is:");
    head = chunkReverseList(head,k);
    displayList(head);
    return 0;
}