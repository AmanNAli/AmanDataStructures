#include <stdio.h>
#include <stdlib.h>
struct node {
    int val;
    struct node * next;
};

typedef struct node * NodeAddress;


NodeAddress ReverseList(NodeAddress head)
{
    NodeAddress curr,prev;
    if(head!=NULL)
    {
        prev = head;
        curr = head->next;
        head = head->next;
        prev->next = NULL;
        while(head!=NULL)
        {
            head = head->next;
            curr->next = prev;
            prev = curr;
            curr = head;
        }
        head = prev;
    }
    return head;
};


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
    printf("Reversed list is:");
    head = ReverseList(head);
    displayList(head);
    return 0;
}