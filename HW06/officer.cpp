#include "officer.h"
#include <iostream>

using namespace std;

Officer::Officer(int ID, string name, string surname, University *university) : Employee(ID, name, surname, university) {}

bool Officer::work(string type, University *un)
{
        if (type == "makeDoc")
        {
                if (uni != un)
                {
                        return true;
                }
                else
                {
                        empHappiness -= 2, uni->uniContribution += 3;
                        cout << empName << " have document. Therefore, " << empName << " makes doc. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                        return false;
                }
        }
}