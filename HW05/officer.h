#ifndef OFFICER_H
#define OFFICER_H

#include <string>
#include "administrativepersonnel.h"
using namespace std;

class Officer : public AdministrativePersonnel
{
public:
        Officer(int ID, string name, string surname, University *university);
        bool makeDoc();
};

#endif