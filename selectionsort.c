#include <stdio.h>
#include <stdlib.h>
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
    SelSort(a,n);
    printf("The sorted array is:");
    for(int i =0;i<n;i++)
    {
        printf(" %d ",a[i]);
    }
}