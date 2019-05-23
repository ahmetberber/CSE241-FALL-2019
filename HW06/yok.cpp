#include "yok.h"
#include <iostream>
using namespace std;

YOK::YOK() {}

Employee YOK::Employ(int id, string name, string surname, string type, University *uni)
{
        if (type == "Lecturer")
        {
                Lecturer lect(id, name, surname, uni);
                return lect;
        }
        else if (type == "ResearchAssistant")
        {
                ResearchAssistant res(id, name, surname, uni);
                return res;
        }
        else if (type == "Secretary")
        {
                Secretary sec(id, name, surname, uni);
                return sec;
        }
        else if (type == "Officer")
        {
                Officer off(id, name, surname, uni);
                return off;
        }
}

University YOK::buildUniversity(string type)
{
        if (type == "research")
        {
                University uni("RTU");
                return uni;
        }
        else if (type == "linguistic")
        {
                University uni("LTU");
                return uni;
        }
        else if (type == "technical")
        {
                University uni("TTU");
                return uni;
        }
}