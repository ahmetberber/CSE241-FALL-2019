#include "researchassistant.h"
#include <iostream>

using namespace std;

ResearchAssistant::ResearchAssistant(int ID, string name, string surname, University *university) : AcademicPersonnel(ID, name, surname, university) {}

bool ResearchAssistant::research()
{
        if (uni == nullptr)
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

bool ResearchAssistant::readHW()
{
        if (uni == nullptr)
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
