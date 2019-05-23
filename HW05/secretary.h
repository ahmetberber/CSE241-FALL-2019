#ifndef SECRETARY_H
#define SECRETARY_H

#include <string>
#include "administrativepersonnel.h"
using namespace std;

class Secretary : public AdministrativePersonnel
{
public:
        Secretary(int ID, string name, string surname, University *university);
        bool receivePetition();
};

#endif