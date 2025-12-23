#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LinkedList
{
    Node *first;
    Node *last;
    int size;
} LinkedList;

// create a Node with given data as well as next and previous Node pointers
Node *Node_Create(int data, Node *next, Node *prev)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->next = next;
    node->prev = prev;

    return node;
}

// create an empty list
LinkedList *LinkedList_Create()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));

    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

// add an element to the start of the list
void LinkedList_AddFirst(LinkedList *list, int element)
{
    Node *node = Node_Create(element, list->first, NULL);

    if (list->first == NULL)
    {
        list->last = node;
    }
    else
    {
        list->first->prev = node;
    }

    list->first = node;
    list->size++;
}

// add an element to the end of the list
void LinkedList_AddLast(LinkedList *list, int element)
{
    Node *node = Node_Create(element, NULL, list->last);

    if (list->last == NULL)
    {
        list->first = node;
    }
    else
    {
        list->last->next = node;
    }

    list->last = node;
    list->size++;
}

// remove the firstelement from the list
void LinkedList_RemoveFirst(LinkedList *list)
{
    if (list->first == NULL)
    {
        return;
    }

    Node *removed = list->first;
    list->first = list->first->next;
    if (list->first == NULL)
    {
        list->last = NULL;
    }
    else
    {
        list->first->prev = NULL;
    }

    free(removed);
    list->size--;
}

// remove the last element from the list
void LinkedList_RemoveLast(LinkedList *list)
{
    if (list->last == NULL)
    {
        return;
    }

    Node *removed = list->last;
    list->last = list->last->prev;
    if (list->last == NULL)
    {
        list->first = NULL;
    }
    else
    {
        list->last->next = NULL;
    }

    free(removed);
    list->size--;
}

// print method for the list
void LinkedList_Print(LinkedList *list)
{
    Node *current = list->first;

    printf("NULL <-> ");

    while (current != NULL)
    {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL | First: %d, Last: %d, Size: %d\n", list->first == NULL ? 0 : list->first->data, list->last == NULL ? 0 : list->last->data, list->size);
}

// example main method
int main()
{
    LinkedList *list = LinkedList_Create();
    LinkedList_Print(list);

    for (int i = 2; i < 8; i += 2)
    {
        LinkedList_AddLast(list, i);
        LinkedList_Print(list);
    }

    for (int i = 8; i < 14; i += 2)
    {
        LinkedList_AddFirst(list, i);
        LinkedList_Print(list);
    }

    while (list->size > 0)
    {
        LinkedList_RemoveLast(list);
        LinkedList_Print(list);
    }

    return 0;
}
