#ifndef ACADEMICPERSONNEL_H
#define ACADEMICPERSONNEL_H

#include <string>
#include "employee.h"
using namespace std;

class AcademicPersonnel : public Employee
{
public:
        AcademicPersonnel(int ID, string name, string surname, University *university);
        bool seeSuccessfulStudent();
        bool makePublish();
};

#endif