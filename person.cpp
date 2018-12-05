#include "person.h"
#include <cstring>//strcpy
#include <iostream>//cout

//#ifdef TESTING
//#define TEST_PRINT(str,p) <<cout<<str " "<<getIndex(p)<<std::endl;
//#else TEST_PRINT(str,p)
//#endif

static const size_t BLOCK_SIZE = sizeof(Person);

Person::Person()
{
    std::cout << "Person::Person()---\n";
}

Person::Person(const char * full_name, unsigned int id, unsigned char age)
:id(id),age(age)
{
    strcpy(Person::full_name,full_name);
    std::cout << "Person::Person()\n";
}

void *Person::init_memory_pool(size_t size)
{
    s_pool=new char[sizeof(Person)*size];
    char *tmp=(char*)s_pool;
    for(size_t i=0; i<size-1; i++,tmp+=BLOCK_SIZE)
    {
        *((void**)tmp)=tmp+BLOCK_SIZE;

    }
    *((void**)tmp)=NULL;
    return s_pool;
//    void *pool_ptr=(void*)malloc(BLOCK_SIZE*size);
//    void *iterator = pool_ptr;
//
//    for (unsigned int i = 0; i < size; i++)
//    {
//        *(size_t*)iterator=(size_t)(((Person*)iterator) + 1);
//        iterator = ((char *)iterator) + BLOCK_SIZE;
//    }
//
//    *(size_t *)iterator = (size_t)NULL;
//    return pool_ptr;
}

void *Person::s_pool = Person::init_memory_pool(POOL_CAPACITY);
void* Person::s_firstFree = Person::s_pool;



void *Person::operator new(size_t size)
{
    if(Person::s_firstFree == NULL)
       throw std::bad_alloc();

    void *m=s_firstFree;
    s_firstFree=*((void**)s_firstFree);
    return m;
//    void * tmp = (Person*)Person::s_pool;
//    Person::s_firstFree = (Person*)*(size_t*)Person::s_firstFree;
//    return tmp;
}

void Person::operator delete(void *ptr)
{
    *((void**)ptr)=s_firstFree;
    s_firstFree=ptr;
//    void* tmp = ptr;
//    ptr = Person::s_firstFree;
//    Person::s_firstFree = tmp;

}

//size_t Person::getIndex(void *p){
//    return ((Person*)P-(Person*)s_pool);
//}
//#ifdef TESTING
//bool Person::checkFrees(size_t arr[],size_t size){
//    return true;
//}
//#endif