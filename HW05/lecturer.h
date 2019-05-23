#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include "academicpersonnel.h"
using namespace std;

class Lecturer : public AcademicPersonnel
{
public:
        Lecturer(int ID, string name, string surname, University *university);
        bool giveLesson();
        bool giveHW();
};

#endif