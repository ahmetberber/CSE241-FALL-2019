#ifndef RESEARCHASSISTANT_H
#define RESEARCHASSISTANT_H

#include <string>
#include "employee.h"
using namespace std;

class ResearchAssistant : public Employee
{
public:
        ResearchAssistant(int ID, string name, string surname, University *university);
        virtual bool work(string type, University *un);
};

#endif