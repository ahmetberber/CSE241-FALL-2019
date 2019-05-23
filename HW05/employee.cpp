#include "employee.h"
#include <iostream>
using namespace std;

Employee::Employee(int ID, string name, string surname, University *university)
{
        empID = ID;
        empName = name;
        empSurname = surname;
        uni = university;
        empHappiness = 0;
}

bool Employee::drinkTea()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness += 5, uni->uniContribution -= 2;
                cout << empName << " have slackness. Therefore, " << empName << " drinks tea. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}

bool Employee::submitPetition()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness += 1, uni->uniContribution -= 2;
                cout << empName << " have solution. Therefore, " << empName << " submit petitons. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}
