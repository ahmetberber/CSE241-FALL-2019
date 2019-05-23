/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW06         */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lecturer.h"
#include "secretary.h"
#include "researchassistant.h"
#include "officer.h"
#include "yok.h"

#define NUMBEROFACTIONS 50
#define EACHUNIEMP 10
#define NUMBEROFUNIVERSITIES 3
#define EMPTY 0
using namespace std;

string actFunc(int num)
{ /* this function helps randomly extending of actions (we have to create 50 random actions to 11 action types) */
        switch (num)
        {
        case 1:
                return "document";
        case 2:
                return "slackness";
        case 3:
                return "project";
        case 4:
                return "lesson";
        case 5:
                return "HomeworkTime";
        case 6:
                return "homeworkTimeout";
        case 7:
                return "incident";
        case 8:
                return "solution";
        }
}

string uniFunc(int num)
{ /* this function helps to the creating universities */
        switch (num)
        {
        case 1:
                return "research";
        case 2:
                return "linguistic";
        case 3:
                return "technical";
        }
}

string empFunc(int num)
{ /* this function helps randomly creating employee fields */
        switch (num)
        {
        case 1:
                return "lecturer";
        case 2:
                return "researchassistant";
        case 3:
                return "secretary";
        case 4:
                return "officer";
        }
}

bool checkEmp(int num, vector<Lecturer> lects, vector<ResearchAssistant> ress, vector<Secretary> secs, vector<Officer> offs)
{/* this function helps to avoiding the same student numbers coming randomly */ 
        for (unsigned int i = 0; i < lects.size(); i++)
        {
                if (lects[i].empID == num && lects[i].uni == nullptr)
                {
                        return false;
                }
        }
        for (unsigned int i = 0; i < ress.size(); i++)
        {
                if (ress[i].empID == num && ress[i].uni == nullptr)
                {
                        return false;
                }
        }
        for (unsigned int i = 0; i < secs.size(); i++)
        {
                if (secs[i].empID == num && secs[i].uni == nullptr)
                {
                        return false;
                }
        }
        for (unsigned int i = 0; i < offs.size(); i++)
        {
                if (offs[i].empID == num && offs[i].uni == nullptr)
                {
                        return false;
                }
        }
        return true;
}

int main()
{
        YOK yok;
        srand(time(NULL));
        ifstream inputStream;
        inputStream.open("personnellist.txt");
        /////////////////////////
        vector<Lecturer> lecturers;
        vector<ResearchAssistant> researchAssistants;
        vector<Secretary> secretaries;
        vector<Officer> officers;
        int allEmployees = 1;
        while (!inputStream.eof())
        {/* all employees going to the appropriate area */
                string name, surname;
                inputStream >> name >> surname;
                string field = empFunc(rand() % 4 + 1);
                if (field == "lecturer")
                {
                        Lecturer lect(allEmployees, name, surname, nullptr);
                        lecturers.push_back(lect);
                        allEmployees++;
                }
                else if (field == "researchassistant")
                {
                        ResearchAssistant res(allEmployees, name, surname, nullptr);
                        researchAssistants.push_back(res);
                        allEmployees++;
                }
                else if (field == "secretary")
                {
                        Secretary sec(allEmployees, name, surname, nullptr);
                        secretaries.push_back(sec);
                        allEmployees++;
                }
                else if (field == "officer")
                {
                        Officer off(allEmployees, name, surname, nullptr);
                        officers.push_back(off);
                        allEmployees++;
                }
        }
        /////////////////////////
        vector<University> universities;
        for (int i = 0; i < NUMBEROFUNIVERSITIES; i++)
        {
                universities.push_back(yok.buildUniversity(uniFunc(i + 1)));
        }
        for (int i = 0; i < NUMBEROFUNIVERSITIES; i++)
        {
                for (int j = 0; j < EACHUNIEMP; j++)
                {
                        string req = empFunc(rand() % 4 + 1);/* university randomly request a field */
                        cout << universities[i].uniName << " requests " << req << endl;
                        int randID;
                        do
                        {/* I'm avoiding the same student numbers every time with checkEmp function */
                                randID = rand() % allEmployees + 1;
                        } while (checkEmp(randID, lecturers, researchAssistants, secretaries, officers));
                        /* YOK gives job to the given employee here */
                        for (unsigned int k = 0; k < lecturers.size(); k++)
                        {
                                if (randID == lecturers[k].empID && lecturers[k].uni == nullptr)
                                {
                                        cout << "YOK give job to " << lecturers[k].empName << " " << lecturers[k].empSurname << " as " << req << endl;
                                        cout << universities[i].uniName << " employs " << lecturers[k].empName << " " << lecturers[k].empSurname << " as " << req << endl;
                                        lecturers[k].uni = &universities[i];
                                }
                        }
                        for (unsigned int k = 0; k < researchAssistants.size(); k++)
                        {
                                if (randID == researchAssistants[k].empID && researchAssistants[k].uni == nullptr)
                                {
                                        cout << "YOK give job to " << researchAssistants[k].empName << " " << researchAssistants[k].empSurname << " as " << req << endl;
                                        cout << universities[i].uniName << " employs " << researchAssistants[k].empName << " " << researchAssistants[k].empSurname << " as " << req << endl;
                                        researchAssistants[k].uni = &universities[i];
                                }
                        }
                        for (unsigned int k = 0; k < secretaries.size(); k++)
                        {
                                if (randID == secretaries[k].empID && secretaries[k].uni == nullptr)
                                {
                                        cout << "YOK give job to " << secretaries[k].empName << " " << secretaries[k].empSurname << " as " << req << endl;
                                        cout << universities[i].uniName << " employs " << secretaries[k].empName << " " << secretaries[k].empSurname << " as " << req << endl;
                                        secretaries[k].uni = &universities[i];
                                }
                        }
                        for (unsigned int k = 0; k < officers.size(); k++)
                        {
                                if (randID == officers[k].empID && officers[k].uni == nullptr)
                                {
                                        cout << "YOK give job to " << officers[k].empName << " " << officers[k].empSurname << " as " << req << endl;
                                        cout << universities[i].uniName << " employs " << officers[k].empName << " " << officers[k].empSurname << " as " << req << endl;
                                        officers[k].uni = &universities[i];
                                }
                        }
                }
                cout << endl;
                for (unsigned int k = 0; k < NUMBEROFACTIONS; k++)
                { /* compliting actions by random appropriate employees */
                        /* if there is one appropriate field, I randomly choosed an employee of that field
                        if there is more than one appropiate field, first I randomply choosed the field, then I choosed an employee of that random field
                        by the way, ALL THE ACTION FUNCTIONS RETURNS BOOLEAN IF THE ACTOR'S UNI VARIABLE NULLPTR OR NOT 
                        THE EMPTY WHILE LOOPS USING BECAUSE OF THIS, WE HAVE TO DETERMINE THE EMPLOYEES WHICH HAVE JOB */
                        string action = actFunc(rand() % 8 + 1);
                        if (action == "document" && officers.size() != EMPTY)
                        { /* document action done by officers */
                                while (officers[rand() % officers.size()].work("makeDoc", &universities[i]))
                                {
                                }
                        }
                        else if (action == "slackness")
                        { /* slackness action done by employee */
                                size_t arr[] = {lecturers.size(), researchAssistants.size(), secretaries.size(), officers.size()};
                                int choice = rand() % 4;
                                if (arr[choice] == lecturers.size() && lecturers.size() != EMPTY)
                                {
                                        while (lecturers[rand() % lecturers.size()].work("drinkTea", &universities[i]))
                                        {
                                        }
                                }
                                else if (arr[choice] == researchAssistants.size() && researchAssistants.size() != EMPTY)
                                {
                                        while (researchAssistants[rand() % researchAssistants.size()].work("drinkTea", &universities[i]))
                                        {
                                        }
                                }
                                else if (arr[choice] == secretaries.size() && secretaries.size() != EMPTY)
                                {
                                        while (secretaries[rand() % secretaries.size()].work("drinkTea", &universities[i]))
                                        {
                                        }
                                }
                                else if (arr[choice] == officers.size() && officers.size() != EMPTY)
                                {
                                        while (officers[rand() % officers.size()].work("drinkTea", &universities[i]))
                                        {
                                        }
                                }
                        }
                        else if (action == "project" && researchAssistants.size() != EMPTY)
                        { /* project action done by all research assistans */
                                while (researchAssistants[rand() % researchAssistants.size()].work("research", &universities[i]))
                                {
                                }
                        }
                        else if (action == "lesson" && lecturers.size() != EMPTY)
                        { /* lesson action done by lecturers */
                                while (lecturers[rand() % lecturers.size()].work("giveLesson", &universities[i]))
                                {
                                }
                        }
                        else if (action == "HomeworkTime" && lecturers.size() != EMPTY)
                        { /* HomeworkTime action done by lecturer */
                                while (lecturers[rand() % lecturers.size()].work("giveHW", &universities[i]))
                                {
                                }
                        }
                        else if (action == "homeworkTimeout" && researchAssistants.size() != EMPTY)
                        { /* homeworkTimeout action done by research assistant */
                                while (researchAssistants[rand() % researchAssistants.size()].work("readHW", &universities[i]))
                                {
                                }
                        }
                        else if (action == "incident" && secretaries.size() != EMPTY)
                        { /* incident action done by secretary */
                                while (secretaries[rand() % secretaries.size()].work("receivePetition", &universities[i]))
                                {
                                }
                        }
                        else if (action == "solution")
                        { /* solution action done by employee */
                                size_t arr[] = {lecturers.size(), researchAssistants.size(), secretaries.size(), officers.size()};
                                int choice = rand() % 4;
                                if (arr[choice] == lecturers.size() && lecturers.size() != EMPTY)
                                {
                                        while (lecturers[rand() % lecturers.size()].work("submitPetition", &universities[i]))
                                        {
                                        }
                                }
                                else if (arr[choice] == researchAssistants.size() && researchAssistants.size() != EMPTY)
                                {
                                        while (researchAssistants[rand() % researchAssistants.size()].work("submitPetition", &universities[i]))
                                        {
                                        }
                                }
                                else if (arr[choice] == secretaries.size() && secretaries.size() != EMPTY)
                                {
                                        while (secretaries[rand() % secretaries.size()].work("submitPetition", &universities[i]))
                                        {
                                        }
                                }
                                else if (arr[choice] == officers.size() && officers.size() != EMPTY)
                                {
                                        while (officers[rand() % officers.size()].work("submitPetition", &universities[i]))
                                        {
                                        }
                                }
                        }
                }
                cout << endl;
                /* printing the happiness of employees */
                for (unsigned int k = 0; k < lecturers.size(); k++)
                {
                        if (lecturers[k].uni != nullptr && lecturers[k].uni->uniName == universities[i].uniName)
                                cout << lecturers[k].empName << " " << lecturers[k].empSurname << " got " << lecturers[k].empHappiness << " happiness" << endl;
                }
                for (unsigned int k = 0; k < researchAssistants.size(); k++)
                {
                        if (researchAssistants[k].uni != nullptr && researchAssistants[k].uni->uniName == universities[i].uniName)
                                cout << researchAssistants[k].empName << " " << researchAssistants[k].empSurname << " got " << researchAssistants[k].empHappiness << " happiness" << endl;
                }
                for (unsigned int k = 0; k < secretaries.size(); k++)
                {
                        if (secretaries[k].uni != nullptr && secretaries[k].uni->uniName == universities[i].uniName)
                                cout << secretaries[k].empName << " " << secretaries[k].empSurname << " got " << secretaries[k].empHappiness << " happiness" << endl;
                }
                for (unsigned int k = 0; k < officers.size(); k++)
                {
                        if (officers[k].uni != nullptr && officers[k].uni->uniName == universities[i].uniName)
                                cout << officers[k].empName << " " << officers[k].empSurname << " got " << officers[k].empHappiness << " happiness" << endl;
                }
                cout << endl;
                /* printing the total contribution of university */
                cout << "total contribution of university is " << universities[i].uniContribution << endl
                     << endl;
        }
        return 0;
}