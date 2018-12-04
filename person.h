#ifndef EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_PERSON_H
#define EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_PERSON_H

#include <iostream>
#include <stdlib.h>

class Person
{
public:
    static void * s_pool;
    static void * s_firstFree;
    Person(){ std::cout << "Person::Person()\n"; };
    ~Person(){ std::cout << "Person::~Person()\n"; };
    void * operator new(size_t size);
    void operator delete(void* ptr);
    static void* init_memory_pool(size_t size);
private:
    char full_name[32];
    unsigned int id;
    unsigned char age;
    void * operator new[](size_t size);
    void operator delete[](void* ptr);

};


#endif //EXCELLENTEAM_ELLA_CPP_OVERLOADING_NEW_AND_DELETE_CHANAMI_PERSON_H
