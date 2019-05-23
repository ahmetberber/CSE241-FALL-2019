#include "administrativepersonnel.h"
#include <iostream>

using namespace std;

AdministrativePersonnel::AdministrativePersonnel(int ID, string name, string surname, University *university) : Employee(ID, name, surname, university) {}

bool AdministrativePersonnel::manageProcess()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness -= 1, uni->uniContribution += 2;
                cout << empName << " have administration. Therefore, " << empName << " manage processes. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}
