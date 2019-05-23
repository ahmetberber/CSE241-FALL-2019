#include "lecturer.h"
#include <iostream>

using namespace std;

Lecturer::Lecturer(int ID, string name, string surname, University *university) : Employee(ID, name, surname, university) {}

bool Lecturer::work(string type, University *un)
{
        if (type == "giveLesson")
        {
                if (uni != un)
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
        else if (type == "giveHW")
        {
                if (uni != un)
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
}