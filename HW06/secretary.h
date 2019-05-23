#ifndef SECRETARY_H
#define SECRETARY_H

#include <string>
#include "employee.h"
using namespace std;

class Secretary : public Employee
{
public:
        Secretary(int ID, string name, string surname, University *university);
        virtual bool work(string type, University* un);
};

#endif