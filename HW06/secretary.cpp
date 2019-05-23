#include "secretary.h"
#include <iostream>

using namespace std;

Secretary::Secretary(int ID, string name, string surname, University *university) : Employee(ID, name, surname, university) {}

bool Secretary::work(string type, University *un)
{
        if (type == "receivePetition")
        {
                if (uni != un)
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
}