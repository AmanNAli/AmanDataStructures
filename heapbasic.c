#include<stdio.h>
#include<stdlib.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printHeap(int *a, int n)
{
    printf("Your heap is:");
    for(int i=0;i<n;i++)
    {
        if(i=n-1)
        printf("%d.",a[i]);
        else
        printf("%d,"a[i]);
    }
}
void reheapify(int *a, int n, int p)
{
    int lc = 2*p + 1;
    int rc = 2*p + 2;
    int min=p;
    if(lc<n && a[lc]<a[min])
    {
        min = lc;
    }
    if(rc<n && a[rc]<a[min])
    {
        min = rc;
    }
    if(min==p)
    {
        return;
    }
    else
    {
        swap(&a[min],&a[p]);
        reheapify(a,n,min);
    }
}
void heap(int *a, int n)
{
    int lastp = n/2 - 1;
    for(int i=lastp;i>=0;i--)
    {
        reheapify(a,n,i);
    }
}
int* insert(int *a, int *n, int x)
{
    int * an = realloc(a,(*n+1)*sizeof(int));
    an[*n] = x;
    *n = *n+1;
    heap(an,*n);
    return an;
}

int extractMin(int *a, int *n)
{
    swap(&a[0],&a[*n-1]);
    int min = a[*n-1];
    *n = *n-1;
    reheapify(a,*n,0);
    return min;
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
    heap(a,n);
    printf("Min is %d\n",extractMin(a,&n));

}