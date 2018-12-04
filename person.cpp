#include "person.h"
#define POOL_CAPACITY 10
#define BLOCK_SIZE sizeof(Person)

void *Person::init_memory_pool(size_t size)
{

    void **pool_ptr = (void**)malloc(BLOCK_SIZE * size);
    void *iterator = placeHolder;

    for (unsigned int i = 0; i < size; i++)
    {
        pool_ptr[i] = ((Person *)iterator) + 1;
        iterator = ((char *)iterator) + BLOCK_SIZE;
    }
    
    pool_ptr[size-1] =NULL;
    return *pool_ptr;
}

void *Person::s_pool = Person::init_memory_pool(POOL_CAPACITY);
void* Person::s_firstFree = Person::s_pool;



void *Person::operator new(size_t size)
{
    if(Person::s_firstFree == NULL)
    {
        return NULL;
    }

    void * tmp =Person::s_pool;
    Person::s_firstFree = (Person*)Person::s_firstFree;//!!!!
    return tmp;
}

void Person::operator delete(void *ptr)
{

    void* tmp = ptr;
    ptr = Person::s_firstFree;
    Person::s_firstFree = tmp;

}

