#include "fifo.h"
#include "../common.h"

/** @see fifo.h */
typedef struct s_fifo {
    uint blocSize;  /**< Taille d'un bloc d'allocation. */
    uint first;     /**< Numéro du premier élément. */
    uint last;      /**< Numéro du dernier élément. */
    void **data;    /**< Éléments. */
} Fifo;

Fifo *fifo_new (uint blocSize)
{
    Fifo *fifo = (Fifo*)malloc(sizeof(Fifo));
    fifo->blocSize = blocSize;
    fifo_clear(fifo);
    return fifo;
}

void fifo_delete (Fifo **fifo)
{
    free((*fifo)->data);
    free(*fifo);
    *fifo = NULL;
}

uint fifo_size (Fifo *fifo)
{
    return fifo->last - fifo->first;
}

void fifo_clear (Fifo *fifo)
{
    fifo->first = 0;
    fifo->last = 0;
    if (fifo->data != NULL) {
        free(fifo->data);
    }
    fifo->data = (void**)malloc(sizeof(void*) * fifo->blocSize);
}

void fifo_push (Fifo *fifo, void *data)
{
    fifo->data[fifo->last] = data;
    fifo->last++;
    if (fifo->last % fifo->blocSize == 0) {
        size_t size = sizeof(void *) * ((fifo->last / fifo->blocSize) + 1);
        fifo->data = (void**)realloc(fifo->data, size * fifo->blocSize);
    }
}

void *fifo_pop (Fifo *fifo)
{
    void *data = NULL;
    if (fifo->first < fifo->last) {
        data = fifo->data[fifo->first];
        fifo->first++;
        if (fifo->first == fifo->blocSize) {
            size_t size = sizeof(void *) * (fifo->last / fifo->blocSize);
            size *= fifo->blocSize;
            void **nData = (void**)malloc(size);
            memcpy(nData, fifo->data + fifo->first, size);
            free(fifo->data);
            fifo->data = nData;
            fifo->last -= fifo->first;
            fifo->first = 0;
        }
    }
    return data;
}

void fifo_print (Fifo *fifo)
{
    uint i;
    printf("\n--FIFO--\n");
    printf("blocSize: %d\n", fifo->blocSize);
    printf("first: %d; last: %d\n", fifo->first, fifo->last);
    printf("# Bloc 0\n");
    for (i = fifo->first; i < fifo->last; i++) {
        if (i > 0 && (i % fifo->blocSize) == 0) {
            printf("# Bloc %d\n", i / fifo->blocSize);
        }
        printf(" - %p\n", fifo->data[i]);
    }
    printf("\n");
}
