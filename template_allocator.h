
#ifndef EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_TEMPLATE_ALLOCATOR_H
#define EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_TEMPLATE_ALLOCATOR_H

#include <iostream>
#include <stdlib.h>

template<typename T, unsigned int POOL_CAPACITY>
class TemplateAllocator :public T {
public:
    void *operator new(size_t size);

    void operator delete(void *ptr);

private:
    static void *init_memory_pool(unsigned int size);

    void *operator new[](size_t size);

    void operator delete[](void *toFreePtr);

    typedef T theType;
    static void *s_pool;
    static void *s_firstFree;

};

template<typename T, unsigned int POOL_CAPACITY>
void *TemplateAllocator<T, POOL_CAPACITY>::s_firstFree = TemplateAllocator::init_memory_pool(POOL_CAPACITY);

template<typename T, unsigned int POOL_CAPACITY>
void *TemplateAllocator<T, POOL_CAPACITY>::init_memory_pool(unsigned int size) {
    TemplateAllocator::s_pool = new char[sizeof(T) * size];
    char *iterator = (char *) s_pool;
    for (size_t i = 0; i < size - 1; ++i, iterator += sizeof(T)) {
        *((void **) iterator) = iterator + sizeof(T);
    }
    *((void **) iterator) = NULL;
    return s_pool;
}

template<typename T, unsigned int POOL_CAPACITY>
void *TemplateAllocator<T, POOL_CAPACITY>::operator new(size_t size) {
    if (s_firstFree == NULL)
    throw std::bad_alloc();

    void *placeHolder = s_firstFree;
    s_firstFree = *((void**)s_firstFree);
    return placeHolder;
}

template<typename T, unsigned int POOL_CAPACITY>
void TemplateAllocator<T, POOL_CAPACITY>::operator delete(void *toFreePtr) {
    void *placeHolder = toFreePtr;
    *(void **) toFreePtr = s_firstFree;
    s_firstFree = placeHolder;
}


#endif //EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_TEMPLATE_ALLOCATOR_H
