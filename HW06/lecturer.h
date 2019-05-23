#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include "employee.h"
using namespace std;

class Lecturer : public Employee
{
public:
        Lecturer(int ID, string name, string surname, University *university);
        virtual bool work(string type, University *un);
};

#endif