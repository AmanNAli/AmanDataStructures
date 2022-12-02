#include <stdio.h>
#include <stdlib.h>
struct node
{
    int val;
    struct node *next;
};
typedef struct node *NodeAddress;
NodeAddress pop(NodeAddress tail, NodeAddress head)
{
    if (tail == NULL)
    {
        printf("Stack is empty");
        return NULL;
    }
    NodeAddress prev = NULL;
    NodeAddress curr = head;
    while (curr != tail && curr)
    {
        prev = curr; // trailing pointer that ends up 1 position behind the previous tail
        curr = curr->next;
    }
    printf("%d\n", tail->val); // popping value
    free(tail);

    return prev; // returning the new tail
}
NodeAddress push(NodeAddress tail, int x) // adds value to the top of the stack
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
    tail = push(tail, 10);
    tail = push(tail, 30);
    tail = push(tail, 15);
    tail = pop(tail, head);
    tail = pop(tail, head);
    tail = pop(tail, head);
    tail = pop(tail, head);
    tail = pop(tail, head);
}
