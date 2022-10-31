#include <stdio.h>
#include <stdlib.h>
struct node {
    int val;
    struct node * next;
};
typedef struct node * NodeAddress;
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
int findMaxPos(int * a,int n)
{
    int max=0;
    for(int i=0;i<=n;i++)
    {
        if(a[i]>a[max])
        {
            max = i;
        }
    }
    return max;
}
void SelSort(int * a,int n)
{
    int x,t;
    for(int i=n-1;i>=0;i--)
    {
        x = findMaxPos(a,i);
        t = a[i];
        a[i] = a[x];
        a[x] = t;
    }
}
void SelSortList(NodeAddress head)
{
    NodeAddress temp;
    NodeAddress min;
    while(head)
    {
        temp = head;
        min = temp;
        while(temp)
        {
            if(min->val > temp->val)
            {
                min = temp;
            }
            temp = temp->next;

        }
        int small = head->val;
        head->val = min->val;
        min->val = small;
        head = head->next;
    }
}
int main(int argv,char **argc)
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
    SelSort(a,n);
    SelSortList(head);
    printf("The sorted array is:");
    for(int i =0;i<n;i++)
    {
        printf(" %d ",a[i]);
    }
    printf("\nThe sorted list is:");
    for(NodeAddress c = head;c!=NULL;c=c->next)
    {
        printf(" %d ",c->val);
    }
}