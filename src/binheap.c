#include <stdlib.h>
#include <stdio.h>

struct binheap
{
    int n;                      // number of elements
    void * data[MAX_HEAP];      // Pointer to data
};

struct binheap * binheap__init(void);
void binheap__insert(void * data);
int binheap__delete_min(void);

