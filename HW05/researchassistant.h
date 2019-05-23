#ifndef RESEARCHASSISTANT_H
#define RESEARCHASSISTANT_H

#include <string>
#include "academicpersonnel.h"
using namespace std;

class ResearchAssistant : public AcademicPersonnel
{
public:
        ResearchAssistant(int ID, string name, string surname, University *university);
        bool research();
        bool readHW();
};

#endif