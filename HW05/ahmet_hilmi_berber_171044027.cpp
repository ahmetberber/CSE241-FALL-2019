/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW05         */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lecturer.h"
#include "secretary.h"
#include "researchassistant.h"
#include "officer.h"

#define NUMBEROFACTIONS 50
#define NUMBEROFEMPLOYEES 10
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
                return "seminar";
        case 6:
                return "academicPaper";
        case 7:
                return "administration";
        case 8:
                return "HomeworkTime";
        case 9:
                return "homeworkTimeout";
        case 10:
                return "incident";
        case 11:
                return "solution";
        }
}

int main()
{
        srand(time(NULL));
        ifstream inputStream;
        inputStream.open("personnellist.txt");
        vector<string> actions;
        for (int i = 0; i < NUMBEROFACTIONS; i++)
        { /* generating 50 actions here and keeping the actions vector */
                actions.push_back(actFunc(rand() % 11 + 1));
        }
        int empCounter = 1; /* this variable helps the initialization of employee IDs */
        University *university = new University;
        vector<Lecturer> lecturers;
        vector<ResearchAssistant> researchAssistants;
        vector<Secretary> secretaries;
        vector<Officer> officers;
        do
        { /* initializing whole employees and throwing them to the appropriate field */
                string actor, name, surname;
                inputStream >> actor >> name >> surname;
                if (actor == "Lecturer")
                {
                        Lecturer temp(empCounter, name, surname, university);
                        lecturers.push_back(temp);
                }
                else if (actor == "ResearchAssistant")
                {
                        ResearchAssistant temp(empCounter, name, surname, university);
                        researchAssistants.push_back(temp);
                }
                else if (actor == "Secretary")
                {
                        Secretary temp(empCounter, name, surname, university);
                        secretaries.push_back(temp);
                }
                else if (actor == "Officer")
                {
                        Officer temp(empCounter, name, surname, university);
                        officers.push_back(temp);
                }
                empCounter++;
        } while (!inputStream.eof());
        unsigned int noJobCounter = 0;
        while (noJobCounter != (lecturers.size() + researchAssistants.size() + secretaries.size() + officers.size()) - NUMBEROFEMPLOYEES)
        {                                         /* we have to  just 10 employees, so I randomly pointed the university variable to null till 10 employees left */
                int number = rand() % empCounter; /* and I did this by the employee IDs */
                for (unsigned int j = 0; j < lecturers.size(); j++)
                {
                        if (number == lecturers[j].empID && lecturers[j].uni != nullptr)
                        {
                                lecturers[j].uni = nullptr;
                                noJobCounter++;
                        }
                }
                for (unsigned int j = 0; j < researchAssistants.size(); j++)
                {
                        if (number == researchAssistants[j].empID && researchAssistants[j].uni != nullptr)
                        {
                                researchAssistants[j].uni = nullptr;
                                noJobCounter++;
                        }
                }
                for (unsigned int j = 0; j < secretaries.size(); j++)
                {
                        if (number == secretaries[j].empID && secretaries[j].uni != nullptr)
                        {
                                secretaries[j].uni = nullptr;
                                noJobCounter++;
                        }
                }
                for (unsigned int j = 0; j < officers.size(); j++)
                {
                        if (number == officers[j].empID && officers[j].uni != nullptr)
                        {
                                officers[j].uni = nullptr;
                                noJobCounter++;
                        }
                }
        }
        for (unsigned int i = 0; i < NUMBEROFACTIONS; i++)
        { /* compliting actions by random appropriate employees */
                /* if there is one appropriate field, I randomly choosed an employee of that field
                   if there is more than one appropiate field, first I randomply choosed the field, then I choosed an employee of that random field
                   by the way, ALL THE ACTION FUNCTIONS RETURNS BOOLEAN IF THE ACTOR'S UNI VARIABLE NULLPTR OR NOT 
                   THE EMPTY WHILE LOOPS USING BECAUSE OF THIS, WE HAVE TO DETERMINE THE EMPLOYEES WHICH HAVE JOB */
                if (actions[i] == "document" && officers.size() != EMPTY)
                { /* document action done by officers */
                        while (officers[rand() % officers.size()].makeDoc())
                        {
                        }
                }
                else if (actions[i] == "slackness")
                { /* slackness action done by employee */
                        size_t arr[] = {lecturers.size(), researchAssistants.size(), secretaries.size(), officers.size()};
                        int choice = rand() % 4;
                        if (arr[choice] == lecturers.size() && lecturers.size() != EMPTY)
                        {
                                while (lecturers[rand() % lecturers.size()].drinkTea())
                                {
                                }
                        }
                        else if (arr[choice] == researchAssistants.size() && researchAssistants.size() != EMPTY)
                        {
                                while (researchAssistants[rand() % researchAssistants.size()].drinkTea())
                                {
                                }
                        }
                        else if (arr[choice] == secretaries.size() && secretaries.size() != EMPTY)
                        {
                                while (secretaries[rand() % secretaries.size()].drinkTea())
                                {
                                }
                        }
                        else if (arr[choice] == officers.size() && officers.size() != EMPTY)
                        {
                                while (officers[rand() % officers.size()].drinkTea())
                                {
                                }
                        }
                }
                else if (actions[i] == "project" && researchAssistants.size() != EMPTY)
                { /* project action done by all research assistans */
                        while (researchAssistants[rand() % researchAssistants.size()].research())
                        {
                        }
                }
                else if (actions[i] == "lesson" && lecturers.size() != EMPTY)
                { /* lesson action done by lecturers */
                        while (lecturers[rand() % lecturers.size()].giveLesson())
                        {
                        }
                }
                else if (actions[i] == "seminar")
                { /* seminar action done by academic personnel */
                        size_t arr[] = {lecturers.size(), researchAssistants.size()};
                        int choice = rand() % 2;
                        if (arr[choice] == lecturers.size() && lecturers.size() != EMPTY)
                        {
                                while (lecturers[rand() % lecturers.size()].seeSuccessfulStudent())
                                {
                                }
                        }
                        else if (arr[choice] == researchAssistants.size() && researchAssistants.size() != EMPTY)
                        {
                                while (researchAssistants[rand() % researchAssistants.size()].seeSuccessfulStudent())
                                {
                                }
                        }
                }
                else if (actions[i] == "academicPaper")
                { /* academicPaper action done by academic personnel */
                        size_t arr[] = {lecturers.size(), researchAssistants.size()};
                        int choice = rand() % 2;
                        if (arr[choice] == lecturers.size() && lecturers.size() != EMPTY)
                        {
                                while (lecturers[rand() % lecturers.size()].makePublish())
                                {
                                }
                        }
                        else if (arr[choice] == researchAssistants.size() && researchAssistants.size() != EMPTY)
                        {
                                while (researchAssistants[rand() % researchAssistants.size()].makePublish())
                                {
                                }
                        }
                }
                else if (actions[i] == "administration")
                { /* administration action done by administrative personnel */
                        size_t arr[] = {secretaries.size(), officers.size()};
                        int choice = rand() % 2;
                        if (arr[choice] == secretaries.size() && secretaries.size() != EMPTY)
                        {
                                while (secretaries[rand() % secretaries.size()].manageProcess())
                                {
                                }
                        }
                        else if (arr[choice] == officers.size() && officers.size() != EMPTY)
                        {
                                while (officers[rand() % officers.size()].manageProcess())
                                {
                                }
                        }
                }
                else if (actions[i] == "HomeworkTime" && lecturers.size() != EMPTY)
                { /* HomeworkTime action done by lecturer */
                        while (lecturers[rand() % lecturers.size()].giveHW())
                        {
                        }
                }
                else if (actions[i] == "homeworkTimeout" && researchAssistants.size() != EMPTY)
                { /* homeworkTimeout action done by research assistant */
                        while (researchAssistants[rand() % researchAssistants.size()].readHW())
                        {
                        }
                }
                else if (actions[i] == "incident" && secretaries.size() != EMPTY)
                { /* incident action done by secretary */
                        while (secretaries[rand() % secretaries.size()].receivePetition())
                        {
                        }
                }
                else if (actions[i] == "solution")
                { /* solution action done by employee */
                        size_t arr[] = {lecturers.size(), researchAssistants.size(), secretaries.size(), officers.size()};
                        int choice = rand() % 4;
                        if (arr[choice] == lecturers.size() && lecturers.size() != EMPTY)
                        {
                                while (lecturers[rand() % lecturers.size()].drinkTea())
                                {
                                }
                        }
                        else if (arr[choice] == researchAssistants.size() && researchAssistants.size() != EMPTY)
                        {
                                while (researchAssistants[rand() % researchAssistants.size()].drinkTea())
                                {
                                }
                        }
                        else if (arr[choice] == secretaries.size() && secretaries.size() != EMPTY)
                        {
                                while (secretaries[rand() % secretaries.size()].drinkTea())
                                {
                                }
                        }
                        else if (arr[choice] == officers.size() && officers.size() != EMPTY)
                        {
                                while (officers[rand() % officers.size()].drinkTea())
                                {
                                }
                        }
                }
        }
        cout << endl;
        /* printing the happiness of employees */
        for (unsigned int i = 0; i < lecturers.size(); i++)
        {
                if (lecturers[i].uni != nullptr)
                        cout << lecturers[i].empName << " " << lecturers[i].empSurname << " got " << lecturers[i].empHappiness << " happiness" << endl;
        }
        for (unsigned int i = 0; i < researchAssistants.size(); i++)
        {
                if (researchAssistants[i].uni != nullptr)
                        cout << researchAssistants[i].empName << " " << researchAssistants[i].empSurname << " got " << researchAssistants[i].empHappiness << " happiness" << endl;
        }
        for (unsigned int i = 0; i < secretaries.size(); i++)
        {
                if (secretaries[i].uni != nullptr)
                        cout << secretaries[i].empName << " " << secretaries[i].empSurname << " got " << secretaries[i].empHappiness << " happiness" << endl;
        }
        for (unsigned int i = 0; i < officers.size(); i++)
        {
                if (officers[i].uni != nullptr)
                        cout << officers[i].empName << " " << officers[i].empSurname << " got " << officers[i].empHappiness << " happiness" << endl;
        }
        cout << endl;
        /* printing the total contribution of university */
        cout << "total contribution of university is " << university->uniContribution << endl;
        free(university);
        return 0;
}