#include <stdio.h>
#include <stdlib.h>
struct node
{
    int val;
    int levels;
    struct node **next;
};
typedef struct node *NodeAddress;
NodeAddress skipListfromArr(int *a, int n)
{
    NodeAddress head = malloc(sizeof(struct node));
    head->levels = 2;
    head->next = malloc(2 * sizeof(struct node *));
    head->val = a[0];
    int skip = 1;
    NodeAddress temp = head;
    for (int i = 1; i < n; i++)
    {
        temp->next[0] = malloc(sizeof(struct node));
        temp = temp->next[0];
        skip = rand() % 5;
        if (skip % 5 == 0)
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
    temp = head;
    while (temp)
    {
        if (temp->levels == 2)
        {
            NodeAddress c = temp->next[0];
            while (c && c->levels < 2)
            {
                c = c->next[0];
            }
            temp->next[1] = c;
            temp = temp->next[1];
        }
        else
            temp = temp->next[0];
    }
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
    while (temp->next[1] && x > temp->next[1]->val)
    {
        temp = temp->next[1];
    }
    while (temp)
    {
        if (x < temp->val)
            break;
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
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(a) / sizeof(a[0]);
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
    search(head, -1);
}