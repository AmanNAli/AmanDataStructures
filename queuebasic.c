#include <stdio.h>
#include <stdlib.h>
struct node
{
    int val;
    struct node *next;
};
typedef struct node *NodeAddress;
NodeAddress dequeue(NodeAddress head, NodeAddress tail)
{
    if (head == NULL)
    {
        printf("Queue is empty");
        return NULL;
    }

    NodeAddress newhead = head->next;
    printf("%d\n", head->val); // popping value
    if (head == tail)
        return NULL;
    return newhead; // returning the new head
}
NodeAddress enqueue(NodeAddress tail, int x) // adds value to the end of the queue
{
    tail->next = malloc(sizeof(struct node));
    tail = tail->next;
    tail->val = x;
    return tail;
}
int main()
{
    NodeAddress head = malloc(sizeof(struct node));
    head->val = 5;
    NodeAddress tail = head;
    tail = enqueue(tail, 10);
    tail = enqueue(tail, 30);
    tail = enqueue(tail, 15);
    head = dequeue(head, tail);
    head = dequeue(head, tail);
    head = dequeue(head, tail);
    head = dequeue(head, tail);
    head = dequeue(head, tail);
}
