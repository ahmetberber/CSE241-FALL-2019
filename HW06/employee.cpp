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

bool Employee::work(string type, University *un)
{
        if (type == "drinkTea")
        {
                if (uni != un)
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
        else if (type == "submitPetition")
        {
                if (uni != un)
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
}