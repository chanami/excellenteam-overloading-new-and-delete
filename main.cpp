#include "template_allocator.h"
#include "person.h"
#include <iostream>

typedef TemplateAllocator<Person,2> APerson;

bool test_bad_allocation()
{
    //Person * p = new Person("chani",111,56);
    return true;
}


int main() {
    APerson * ap = new APerson;

    std::cout << "Hello, World!" << ap<<std::endl;
    return 0;
}