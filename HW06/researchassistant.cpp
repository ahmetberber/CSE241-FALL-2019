#include "researchassistant.h"
#include <iostream>

using namespace std;

ResearchAssistant::ResearchAssistant(int ID, string name, string surname, University *university) : Employee(ID, name, surname, university) {}

bool ResearchAssistant::work(string type, University *un)
{
        if (type == "research")
        {
                if (uni != un)
                {
                        return true;
                }
                else
                {
                        empHappiness += 3, uni->uniContribution += 4;
                        cout << empName << " have project. Therefore, " << empName << " researches. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                        return false;
                }
        }
        else if (type == "readHW")
        {
                if (uni != un)
                {
                        return true;
                }
                else
                {
                        empHappiness -= 3, uni->uniContribution += 2;
                        cout << empName << " have homework timeout. Therefore, " << empName << " read HWs. Happines of " << empName << " is " << empHappiness << ", contribution of uni is " << uni->uniContribution << endl;
                        return false;
                }
        }
}