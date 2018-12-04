#ifndef EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_PERSON_H
#define EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_PERSON_H

#include <iostream>
#include <stdlib.h>

class Person
{
public:
    Person(const char * full_name, unsigned int id, unsigned char age);
    ~Person(){ std::cout << "Person::~Person()\n"; };
    void * operator new(size_t size);
    void operator delete(void* ptr);

private:
    char full_name[32];
    unsigned int id;
    unsigned char age;
    void * operator new[](size_t size);
    void operator delete[](void* ptr);

    static void * s_pool;
    static void * s_firstFree;
    static void * init_memory_pool(size_t size);
    static const size_t POOL_CAPACITY = 10;


};


#endif //EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_PERSON_H
