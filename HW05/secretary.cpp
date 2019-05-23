#include "secretary.h"
#include <iostream>

using namespace std;

Secretary::Secretary(int ID, string name, string surname, University *university) : AdministrativePersonnel(ID, name, surname, university) {}

bool Secretary::receivePetition()
{
        if (uni == nullptr)
        {
                return true;
        }
        else
        {
                empHappiness -= 1, uni->uniContribution -= 1;
                cout << empName << " have incident. Therefore, " << empName << " receive petitions. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                return false;
        }
}