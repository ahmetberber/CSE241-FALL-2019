#ifndef OFFICER_H
#define OFFICER_H

#include <string>
#include "employee.h"
using namespace std;

class Officer : public Employee
{
public:
        Officer(int ID, string name, string surname, University *university);
        virtual bool work(string type, University *un);
};

#endif