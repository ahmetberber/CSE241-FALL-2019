#include "lecturer.h"
#include <iostream>

using namespace std;

Lecturer::Lecturer(int ID, string name, string surname, University *university) : AcademicPersonnel(ID, name, surname, university) {}

bool Lecturer::giveLesson()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness += 1, uni->uniContribution += 5;
                cout << empName << " have lesson. Therefore, " << empName << " gives lesson. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}

bool Lecturer::giveHW()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness -= 2, uni->uniContribution += 1;
                cout << empName << " have homework time. Therefore, " << empName << " gives HW. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}
