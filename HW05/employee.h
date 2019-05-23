#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "university.h"
using namespace std;

class Employee
{
public:
        Employee(int ID, string name, string surname, University *university);
        bool drinkTea();
        bool submitPetition();
        int empID;
        string empName;
        string empSurname;
        int empHappiness;
        University *uni;
};

#endif