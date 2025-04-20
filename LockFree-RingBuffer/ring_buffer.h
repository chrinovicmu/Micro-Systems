#ifndef RING_BUFFER_H_ 
#define RING_BUFFER_H_

#include <stdio.h>


#define CACHE_LINE_SIZE 64 

static inline unsigned int align32_pow2(unsigned int x)
{
    --x; 
    x |= x >> 1; 
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return x + 1;
}

typedef struct{

    __attribute__((aligned(CACHE_LINE_SIZE))) unsigned int  cached_head; 
    __attribute__((aligned(CACHE_LINE_SIZE))) unsigned int  cached_tail;  
    __attribute__((aligned(CACHE_LINE_SIZE))) unsigned int  head; 
    __attribute__((aligned(CACHE_LINE_SIZE))) unsigned int  tail;
    
    unsigned int capacity; 
    unsigned int mask;
    void **buffer;
}__attribute__((aligned(CACHE_LINE_SIZE))) ring_buffer_t; 


inline int ring_buffer_init(ring_buffer_t *const rb, unsigned int capacity)
{
    rb->capacity =align32_pow2(capacity); 
    rb->mask =  rb->capacity - 1; 
    rb->head = 0;
    rb->tail = 0;
    rb->cached_head = 0;
    rb->cached_tail = 0; 

    return 1; 
}

inline int push(ring_buffer_t *const rb, void *const value)
{

    __atomic_load(&rb->tail, &rb->cached_tail, __ATOMIC_ACQUIRE);

    if((rb->head - rb->cached_tail) == rb->capacity)
    {
        return 0; 
    }

    rb->buffer[rb->head & rb->mask] = value; 
    __atomic_fetch_add(&rb->head, 1, __ATOMIC_RELEASE); 

    return 1; 
}

inline int pop(ring_buffer_t *const rb, void ** value)
{

    __atomic_load(&rb->head, &rb->cached_head, __ATOMIC_ACQUIRE); 

    if((rb->cached_head - rb->tail) == 0)
    {
        return 0; 
    }
    *value = rb->buffer[rb->tail & rb->mask];
    __atomic_fetch_add(&rb->tail, 1, __ATOMIC_RELEASE);

    return 1 ;
}

#endif
