#ifndef YOK_H
#define YOK_H

#include <string>
#include "secretary.h"
#include "researchassistant.h"
#include "officer.h"
#include "lecturer.h"
#include "university.h"
using namespace std;

string uniFunc(int num);

class YOK
{
public:
        YOK();
        Employee Employ(int id, string name, string surname, string type, University *uni);
        University buildUniversity(string type);
};

#endif