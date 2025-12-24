#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} Vector;

// create an empty vector
Vector *Vector_Create()
{
    Vector *vector = malloc(sizeof *vector);

    if (!vector)
        return NULL;

    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;

    return vector;
}

// destroy the vector
void Vector_Destroy(Vector *vector)
{
    if (!vector)
        return;

    free(vector->data);
    free(vector);
}

// clear the vector
void Vector_Clear(Vector *vector)
{
    if (!vector)
        return;

    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

// push an item at the end of the vector
int Vector_Push(Vector *vector, int item)
{
    if (!vector)
        return 0;

    if (vector->size == vector->capacity)
    {
        size_t newCapacity = vector->capacity ? 2 * vector->capacity : 4;
        int *newData = realloc(vector->data, newCapacity * sizeof(*newData));

        if (!newData)
            return 0;

        vector->capacity = newCapacity;
        vector->data = newData;
    }

    vector->data[vector->size] = item;
    vector->size++;
    return 1;
}

// pop the item at the end of the vector
int Vector_Pop(Vector *vector, int *out)
{
    if (!vector || vector->size == 0)
        return 0;

    if (out)
        *out = vector->data[vector->size - 1];

    vector->size--;
    return 1;
}

// get the item at the index from the vector
int Vector_Get(const Vector *vector, size_t index, int *out)
{
    if (!out || !vector || index >= vector->size)
        return 0;

    *out = vector->data[index];
    return 1;
}

// set the item at the index for the vector
int Vector_Set(Vector *vector, size_t index, int item)
{
    if (!vector || index >= vector->size)
        return 0;
    vector->data[index] = item;
    return 1;
}

// print the vector
void Vector_Print(const Vector *vector)
{
    if (!vector)
        return;

    printf("[");
    for (size_t i = 0; i < vector->size; i++)
    {
        printf(i == vector->size - 1 ? "%d" : "%d, ", vector->data[i]);
    }
    printf("], Size: %zu, Capacity: %zu\n", vector->size, vector->capacity);
}

// example main
int main()
{

    Vector *vector = Vector_Create();
    if (!vector)
    {
        printf("Failed to create vector.\n");
        return EXIT_FAILURE;
    }

    int success;

    Vector_Print(vector);

    for (int i = 30; i < 36; i++)
    {
        success = Vector_Push(vector, i);
        printf("Tried to push item %d, Success: %d\n", i, success);
        Vector_Print(vector);
    }

    int popped;
    success = Vector_Pop(vector, &popped);
    printf("Tried to pop, Success: %d\n", success);
    Vector_Print(vector);

    if (success)
    {
        size_t index = vector->size / 2;
        success = Vector_Set(vector, index, popped);
        printf("Tried to set item %d in index %zu, Success: %d\n", popped, index, success);
        Vector_Print(vector);
    }

    Vector_Destroy(vector);
    return 0;
}