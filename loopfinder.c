struct node
{
    int val;
    struct node *next;
};
int loopdetector(struct node *head)
{
    struct node *t = head;
    struct node *r = head;
    int flag = 0;
    while (t != NULL && r != NULL && (r->next) != NULL)
    {
        t = t->next;
        r = r->next->next;
        if (t == r)
        {
            flag = 1;
            break
        };
    };

    return flag; // if there is a loop, flag = 1 otherwise flag = 0
}
