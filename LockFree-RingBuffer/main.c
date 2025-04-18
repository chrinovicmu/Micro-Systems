#include <stdio.h>
#include <stdlib.h>

#define CACHE_LINE_SIZE 64 

typedef struct{
    uint32_t capacity;
    void ** buffer; 
    __attribute__((aligned(CACHE_LINE_SIZE))) uint32_t head; //index of next HEAD 
    __attribute__((aligned(CACHE_LINE_SIZE))) uint32_t tail;  //index of next TAIL 
}__attribute__((aligned(CACHE_LINE_SIZE))) ring_buffer_t; 


/*
 * NORMAL PUSH OPERATION 
 
int push(ring_buffer_t *const rb, void* value)
{
    if((rb>head - rb->tail) == rb->capacity)
    {
        return 1; 
    }
    rb->buffer[rb->head % rb->capacity] == value; 
    ++rb->head; 

    return 0; 
}
*/ 

/*ATOMIC PUSH OPERATION */ 

int push(ring_buffer_t *const rb, void *consr value){

    uint32_t int _Atail; 

    __atomic_load(&rb->tail, &_Atail, __ATOMIC_ACQUIRE);

    if((rb->head - _Atail) == rb->capacity)
    {
        return 1; 
    }

    rb->buffer[rb->head % rb->capacity] = value; 
    __atomic_fetch_add(&rb->head, 1, __ATOMIC_RELEASE); 

    return 0; 
}

/*
 * NORMAL POP OPERATION
 
int pop(ring_buffer_t *const rb, void ** value)
{
    if((rb->head - rb->tail) == 0)
    {
        return 0; 
    }

    *value = rb->buffer[rb->tail % rb->capacity]; 
    ++rb->tail; 
    return 1; 
}
*/ 

int pop(ring_buffer_t *const rb, void ** const value)
{
    uint32_t int _Ahead; 

    __atomic_load(&rb->head, &_Ahead, __ATOMIC_ACQUIRE); 

    if((_Ahead - rb->tail) == 0)
    {
        return 0; 
    }
    *value = rb->buffer[rb->tail % rb->capacity];
    __atomic_fetch_add(&rb->tail, 1, __ATOMIC_RELEASE);

    return 0 ;
}
int main(int argc, char *argv[])
{
    return EXIT_SUCCESS;
}


