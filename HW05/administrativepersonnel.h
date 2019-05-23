#ifndef ADMINISTRATIVEPERSONNEL_H
#define ADMINISTRATIVEPERSONNEL_H

#include <string>
#include "employee.h"
using namespace std;

class AdministrativePersonnel : public Employee
{
public:
        AdministrativePersonnel(int ID, string name, string surname, University *university);
        bool manageProcess();
};

#endif