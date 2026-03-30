#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    node *list = NULL;
    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n -> number = number;
        n -> next = NULL;

        if (list == NULL)
        {
            list = n;
        }
        else if (n -> number < list -> number)
        {
            n -> next = list;
            list = n;
        }
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr -> next)
            {
                if (ptr -> next == NULL)
                {
                    ptr -> next = n;
                    break;
                }
            }

        }
        if (n -> number < ptr -> next -> number)
        {
            n -> next = ptr -> next;
            ptr -> next = n;
            break;
        }
    //print numbers

    for (node *ptr = list; ptr != NULL; ptr = ptr -> next)
    {
        printf("%i\n", ptr -> number);
    }

    //free memory
    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr -> next;
        free(ptr);
        ptr = next;
    }
}
