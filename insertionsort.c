#include <stdio.h>
#include <stdlib.h>
struct node {
    int val;
    struct node * next;
};
typedef struct node * NodeAddress;
NodeAddress head = NULL;
NodeAddress sortedhead = NULL;
NodeAddress linkedListFromArray(int * a, int n)
{

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
}
void inSort(int *a, int n)
{
    int key,j;
    for(int i=1;i<n;i++)
    {
        key = a[i];
        j = i-1;
        while(j>=0 && a[j]>key)
        {
            a[j+1]=a[j];
            j=j-1;
        }
        a[j+1]=key;
    }
}
void insert(NodeAddress new)
{
    if((sortedhead==NULL) || (sortedhead->val >= new->val))
    {
        new->next = sortedhead;
        sortedhead = new;
    }
    else
    {
        NodeAddress curr = sortedhead;
        while((curr->next!=NULL) && (curr->next->val < new->val))
        {
            curr = curr->next;
        }
        new->next = curr->next;
        curr->next = new;
    }
}
void inSortList()
{
    NodeAddress curr = head;
    while(curr!=NULL)
    {
        NodeAddress next = curr->next;
        insert(curr);
        curr = next;
    }

}
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
    inSort(a,n);
    inSortList(head);
    printf("The sorted array is:");
    for(int i =0;i<n;i++)
    {
        printf(" %d ",a[i]);
    }
    printf("\nThe sorted list is:");
    for(NodeAddress c=sortedhead;c!=NULL;c=c->next)
    {
        printf(" %d ",c->val);
    }
    return 0;
}