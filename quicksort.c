#include <stdio.h>
#include <stdlib.h>
struct node {
    int val;
    struct node * next;
};
typedef struct node * NodeAddress;
NodeAddress head;
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
}
void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int *a, int start, int stop)
{
    int pivot = a[start];
    int i = start+1;
    int j = stop;
    while(i<=j)
    {
        if(a[i]>pivot)
        {
            swap(&a[i],&a[j]);
            j = j-1;
        }
        else
        {
            i++;
        }
    }
    swap(&a[start],&a[j]);
    return j;
}
void quickSort(int *a, int start, int stop)
{
    if(stop>=start)
    {

        int p = partition(a,start,stop);
        quickSort(a,start,p-1);
        quickSort(a,p+1,stop);
    }
}
NodeAddress lastnode(NodeAddress head)
{

    while(head!=NULL && head->next!=NULL)
    {
        head = head->next;
    }
    return head;
}
NodeAddress partitionList(NodeAddress start, NodeAddress stop)
{
    NodeAddress pivot = start;
    NodeAddress curr = start;
    int temp = 0;
    while(curr!=NULL && curr!=stop)
    {
        if(curr->val < stop->val)
        {

            temp = start->val;
            start->val = curr->val;
            curr->val = temp;
            pivot = start;
            start = start->next;
        }
        curr = curr->next;
    }
    temp = start->val;
    start->val = stop->val;
    stop->val = temp;
    return pivot;
}
void quickSortList(NodeAddress start, NodeAddress stop)
{
    if(start==stop)
    return;
    NodeAddress pivot = partitionList(start,stop);
    if(pivot!=NULL && pivot->next!=NULL)
    quickSortList(pivot->next,stop);
    if(pivot!=NULL && pivot!=start)
    quickSortList(start,pivot);
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

    head = linkedListFromArray(a,n);
    quickSort(a,0,n-1);
    printf("The sorted array is:");
    for(int i=0;i<n;i++)
    {
        printf(" %d ",a[i]);
    }
    NodeAddress stop = lastnode(head);
    quickSortList(head,stop);
    printf("\nThe sorted list is:");
    for(NodeAddress c = head;c!=NULL;c=c->next)
    {
        printf(" %d ",c->val);
    }
    return 0;
}