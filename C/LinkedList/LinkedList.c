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
    size_t size;
} LinkedList;

// create a Node with given data as well as next and previous Node pointers
static Node *Node_Create(int data, Node *next, Node *prev)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
        return NULL;

    node->data = data;
    node->next = next;
    node->prev = prev;

    return node;
}

// create an empty list
LinkedList *LinkedList_Create()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));

    if (list == NULL)
        return NULL;

    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

// remove all nodes from the list
void LinkedList_Clear(LinkedList *list)
{
    if (list == NULL)
        return;

    Node *current = list->first;

    while (current)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->first = list->last = NULL;
    list->size = 0;
}

// destroy the list
void LinkedList_Destroy(LinkedList *list)
{
    if (list == NULL)
        return;

    LinkedList_Clear(list);
    free(list);
}

// add an element to the start of the list
int LinkedList_AddFirst(LinkedList *list, int element)
{
    if (list == NULL)
        return 0;

    Node *node = Node_Create(element, list->first, NULL);

    if (node == NULL)
        return 0;

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
    return 1;
}

// add an element to the end of the list
int LinkedList_AddLast(LinkedList *list, int element)
{

    if (list == NULL)
        return 0;

    Node *node = Node_Create(element, NULL, list->last);

    if (node == NULL)
        return 0;

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
    return 1;
}

// remove the first element from the list
void LinkedList_RemoveFirst(LinkedList *list)
{
    if (list == NULL || list->first == NULL)
        return;

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
    if (list == NULL || list->last == NULL)
        return;

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
void LinkedList_Print(const LinkedList *list)
{
    if (list == NULL)
        return;

    const Node *current = list->first;

    printf("NULL <-> ");

    while (current != NULL)
    {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL | ");
    if (list->size == 0)
    {
        printf("First: NULL, Last: NULL, ");
    }
    else
    {
        printf("First: %d, Last: %d, ", list->first->data, list->last->data);
    }
    printf("Size: %zu\n", list->size);
}

// example main method
int main()
{
    LinkedList *list1 = LinkedList_Create();
    if (list1 == NULL)
    {
        printf("Failed to create list.\n");
        return EXIT_FAILURE;
    }

    LinkedList_Print(list1);

    for (int i = 1; i < 4; i += 1)
    {
        LinkedList_AddLast(list1, i);
        LinkedList_Print(list1);
    }

    for (int i = -1; i > -4; i -= 1)
    {
        LinkedList_AddFirst(list1, i);
        LinkedList_Print(list1);
    }

    LinkedList_Destroy(list1);

    return 0;
}
