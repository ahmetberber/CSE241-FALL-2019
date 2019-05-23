#include "academicpersonnel.h"
#include <iostream>

using namespace std;

AcademicPersonnel::AcademicPersonnel(int ID, string name, string surname, University *university) : Employee(ID, name, surname, university) {}

bool AcademicPersonnel::seeSuccessfulStudent()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness += 10;
                cout << empName << " have seminar. Therefore, " << empName << " sees succesfull student. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}

bool AcademicPersonnel::makePublish()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness += 2, uni->uniContribution += 5;
                cout << empName << " have academic paper. Therefore, " << empName << " makes publish. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}
