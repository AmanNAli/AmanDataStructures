#include <stdio.h>
#include <stdlib.h>
// I use expressway to describe the nodes that skip because Professor's use of that term got stuck in my head
struct node
{
    int val;
    int levels; // tracks number of levels
    struct node **next;
};
typedef struct node *NodeAddress;

// since my method for creating the skip list requires a sorted array, I had to include quicksort. Skip to line 52 for the actual skip list code
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int *a, int start, int stop)
{
    int pivot = a[start];
    int i = start + 1;
    int j = stop;
    while (i <= j)
    {
        if (a[i] > pivot)
        {
            swap(&a[i], &a[j]);
            j = j - 1;
        }
        else
        {
            i++;
        }
    }
    swap(&a[start], &a[j]);
    return j;
}
void quickSort(int *a, int start, int stop)
{
    if (stop >= start)
    {

        int p = partition(a, start, stop);
        quickSort(a, start, p - 1);
        quickSort(a, p + 1, stop);
    }
}

NodeAddress skipify(NodeAddress head) // function to connect the expressway
{
    NodeAddress temp = head;
    while (temp)
    {
        if (temp->levels == 2) // if the current node is part of the expressway, connect it to the following node in the expressway
        {
            NodeAddress c = temp->next[0];
            while (c && c->levels < 2) // finds the next node that is part of the expressway
            {
                c = c->next[0];
            }
            temp->next[1] = c;
            temp = temp->next[1]; // move down the expressway
        }
        else
            temp = temp->next[0]; // if the current node is just a normal node, move to the next one
    }
    return head;
}
NodeAddress skipListfromArr(int *a, int n)
{
    NodeAddress head = malloc(sizeof(struct node));
    head->levels = 2; // I chose to always make the head node part of the expressway
    head->next = malloc(2 * sizeof(struct node *));
    head->val = a[0];
    int skip = 1;
    NodeAddress temp = head;
    for (int i = 1; i < n; i++)
    {
        temp->next[0] = malloc(sizeof(struct node));
        temp = temp->next[0];
        skip = rand() % 5; // gives a random number between 0 and 4
        if (skip % 5 == 0) // 1 in 5 chance to connect the current node to the 'expressway'
        {
            temp->levels = 2;
        }
        else
        {
            temp->levels = 1;
        }
        skip = skip + 1;
        temp->next = malloc(temp->levels * sizeof(struct node *));
        temp->val = a[i];
    }
    head = skipify(head); // connect the expressway
    return head;
}

void search(NodeAddress temp, int x)
{
    int flag = 0;
    if (temp == NULL)
    {
        printf("Not found\n");
        return;
    }
    while (temp->next[1] && x > temp->next[1]->val) // take the expressway as far as possible
    {
        temp = temp->next[1];
    }
    while (temp) // now that we know x lies in a certain range (given that it is in the list at all), we must go one by one
    {
        if (x < temp->val) // since it is a sorted list, if x is smaller than the current value we can conclude that we won't find x further ahead in the list
            break;         // we must have found all appearances of x already if there were any
        if (x == temp->val)
        {
            printf("Found\n");
            flag = 1;
        }
        temp = temp->next[0];
    }
    if (flag == 0)
        printf("Not found\n");
}

int main()
{
    int n = 11;
    int *a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
    quickSort(a, 0, n - 1);
    NodeAddress head = skipListfromArr(a, n);
    NodeAddress temp = head;
    while (temp)
    {
        printf("%d\n", temp->val);
        temp = temp->next[0];
    }
    temp = head;
    while (temp)
    {
        printf("%d\n", temp->val);
        temp = temp->next[1];
    }
    search(head, 86);
}