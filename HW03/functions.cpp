/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW03         */

#include <iostream>
#include <vector>
#include <string>
#include "functions.h"

using namespace std;

const unsigned int MAXCOURSELIMIT = 3;
const unsigned int STARTHOUR = 9;/* assume that courses start at 9:00 AM */
const int FINISHHOUR = 17;/* assume that courses finish at 17:00 PM */
int numberOfCourses = 0;
int numberOfClassrooms = 0;
int numberOfLecturers = 0;
int tempHourG = STARTHOUR;/* I'm using that variable at the one by one timetable arrangement part to holds the start time of courses which we left */
int tempDayCounterG = 0;/* I'm using that variable at the one by one timetable arrangement part to holds the number which we left */
int tempCourseClassDelimeterG = 0;/* I'm using that variable at the arranging all courses timetables part */
int assignedLects = 0;/* I'm using that variable at the one by one assigment making part */
const string wholeDays[] = {"MON", "TUE", "WED", "THU", "FRI"};/* I'm using that variable at the arranging course timetables parts */
bool isComplete;/* I'm using that variable more than one place. Mostly error checking */

/* this function basicly takes the course which trying to propose and checks the proposing course limit and profession missmatch */
void Lecturer::proposeCourse(Course newCrs)
{
        isComplete = false;
        for (unsigned int i = 0; i < lectProffs.size(); i++)
        {
                if (lectProffs[i] == newCrs.courseField)
                {
                        isComplete = true;
                }
        }
        if (isComplete)
        {
                if (lectProposedCourses.size() < MAXCOURSELIMIT)
                {
                        newCrs.isMandatory = false;
                        newCrs.isTaken = false;
                        lectProposedCourses.push_back(newCrs);
                        cout << "DONE!" << endl;
                }
                else
                {
                        cout << "this lecturer already proposes 3 lessons, proposing not allowed!" << endl;
                }
        }
        else
        {
                cout << "the course which you proposed is not paired any of profession of lecturer, please try again!" << endl;
        }
}

/* this function basicly takes the course which trying to assign and checks the assigning course limit and profession missmatch */
bool Lecturer::assignCourse(Course &assigningCrs)
{
        if (lectTakenCourses.size() == MAXCOURSELIMIT)
        {
                cout << "this lecturer already takes 3 courses, assigment not allowed!" << endl;
                return false;
        }
        else
        {
                for (unsigned j = 0; j < lectProffs.size(); j++)
                {
                        if (lectProffs[j] == assigningCrs.courseField)
                        {
                                assigningCrs.isTaken = true;
                                lectTakenCourses.push_back(assigningCrs);
                                return true;
                        }
                }
                cout << "field and profession missmatch!" << endl;
                return false;
        }
}

/* this function basicly takes a string which is the proff format in txt file and assigns them to the lecturer professions */
void Lecturer::trimLectProffs(string str)
{
        int i = 0, j = 0, k = 0;
        string tempStr;
        while (str[i] != ',' && (unsigned int)i != str.length() + 1)
        {
                k = i;
                while (str[k] != ',' && (unsigned int)k != str.length())
                {
                        k++;
                }
                tempStr.resize(k - i);
                while (str[i] != ',' && (unsigned int)i != str.length())
                {
                        tempStr[j] = str[i];
                        i++, j++;
                }
                lectProffs.push_back(tempStr);
                tempStr.clear();
                i++, j = 0;
        }
}

/* this function basicly takes the whole courses and professions ordered high to low value, and assigns them to this order */
void Lecturer::assignAllCoursesFromLect(vector<Course> &crss, string prfs, int prfsCnt)
{
        for (unsigned int i = 0; i < lectProffs.size(); i++)
        {
                for (unsigned int j = 0; j < crss.size(); j++)
                {
                        if (lectProffs[i] == prfs && crss[j].isTaken != true && lectTakenCourses.size() < MAXCOURSELIMIT)
                        {
                                crss[j].isTaken = true;
                                lectTakenCourses.push_back(crss[j]);
                        }
                }
        }
}

/* this function basicly shows lecturers which takes no courses and the informations which lecturer have to propose course/s at this field and how many */
void Lecturer::showUnassignedCourses()
{
        if (lectTakenCourses.size() < MAXCOURSELIMIT)
        {
                cout << lectName << " " << lectSurname << " has to propose "
                     << MAXCOURSELIMIT - lectTakenCourses.size() << " courses at ";
                for (unsigned int i = 0; i < lectProffs.size(); i++)
                {
                        cout << lectProffs[i] << " ";
                }
                cout << "field/s" << endl;
        }
}

/* this function basicly takes the whole courses and professions and orders them high to low value and assings to the prfs and prfsCnt variables */
void Lecturer::detProffs(vector<string> &prffs, vector<int> &prffsCnt)
{
        for (unsigned int i = 0; i < lectProffs.size(); i++)
        {
                bool flag = false;
                for (unsigned j = 0; j < prffs.size(); j++)
                {
                        if (lectProffs[i] == prffs[j])
                        {
                                prffsCnt[j]++;
                                flag = true;
                        }
                }
                if (flag == false)
                {
                        prffs.push_back(lectProffs[i]);
                        prffsCnt.push_back(1);
                }
        }
}

/* this function basicly assign courses after all courses assigned to the lecturer which lecturer might proposed before */
void Lecturer::assignProposedCourses()
{
        if (lectTakenCourses.size() < MAXCOURSELIMIT)
        {
                for (unsigned int i = 0; i < MAXCOURSELIMIT - lectTakenCourses.size(); i++)
                {
                        for (unsigned int j = 0; j < lectProposedCourses.size(); j++)
                        {
                                for (unsigned int k = 0; k < lectProffs.size(); k++)
                                {
                                        if (lectProposedCourses[j].courseField == lectProffs[k] && lectProposedCourses[j].isTaken == false)
                                        {
                                                lectProposedCourses[j].isTaken = true;
                                                lectTakenCourses.push_back(lectProposedCourses[j]);
                                        }
                                }
                        }
                }
        }
}

void Lecturer::assignAllCoursesFromAllCourses(Course assig, vector<Course> &crss)
{
        for (unsigned int i = 0; i < crss.size(); i++)
        {
                if (crss[i].courseID == assig.courseID)
                {
                        crss[i] = assig;
                        break;
                }
        }
}

void Lecturer::setTimeTable(int &startCount, int &dayCount, int &del, vector<Course> &crss)
{
        for (unsigned int i = 0; i < lectTakenCourses.size(); i++)
        {
                if (startCount + lectTakenCourses[i].courseHours <= FINISHHOUR)
                {
                        lectTakenCourses[i].courseClassDelimeter = del;
                        lectTakenCourses[i].courseStartTime.push_back(startCount);
                        lectTakenCourses[i].courseFinishTime.push_back(startCount + lectTakenCourses[i].courseHours);
                        lectTakenCourses[i].courseStartDay.push_back(wholeDays[dayCount]);
                        if (startCount + lectTakenCourses[i].courseHours == FINISHHOUR)
                        {
                                startCount = STARTHOUR;
                                dayCount++;
                        }
                        else
                        {
                                startCount += lectTakenCourses[i].courseHours;
                        }
                }
                else
                {
                        int temp = FINISHHOUR - startCount;
                        lectTakenCourses[i].courseStartTime.push_back(startCount);
                        lectTakenCourses[i].courseFinishTime.push_back(FINISHHOUR);
                        lectTakenCourses[i].courseStartDay.push_back(wholeDays[dayCount]);
                        startCount = STARTHOUR;
                        lectTakenCourses[i].courseStartTime.push_back(startCount);
                        lectTakenCourses[i].courseFinishTime.push_back(startCount + (lectTakenCourses[i].courseHours - temp));
                        if (wholeDays[dayCount] == "FRI")
                        {
                                dayCount = 0;
                                del++;
                                lectTakenCourses[i].courseClassDelimeter = del;
                                lectTakenCourses[i].courseStartDay.push_back(wholeDays[dayCount]);
                        }
                        else
                        {
                                lectTakenCourses[i].courseClassDelimeter = del;
                                lectTakenCourses[i].courseStartDay.push_back(wholeDays[++dayCount]);
                        }
                        startCount += lectTakenCourses[i].courseHours - temp;
                }
                assignAllCoursesFromAllCourses(lectTakenCourses[i], crss);
        }
}

/* this function basicly show timetable and class information of all courses after arrangment is over */
void show(vector<Course> crss)
{
        for (unsigned int i = 0; i < crss.size(); i++)
        {
                if (crss[i].courseClassID.size() > 1)
                {
                        cout << "(" << crss[i].courseID << ")" << crss[i].courseName << " in ";
                        for (unsigned int j = 0; j < crss[i].courseStartDay.size(); j++)
                        {
                                cout << crss[i].courseClassID[j] << " at "
                                     << crss[i].courseStartDay[j] << "_"
                                     << crss[i].courseStartTime[j] << "-"
                                     << crss[i].courseFinishTime[j];
                                if (j != crss[i].courseStartDay.size() - 1)
                                        cout << ", in ";
                        }
                        cout << endl;
                }
                else
                {
                        cout << "(" << crss[i].courseID << ")" << crss[i].courseName << " in " << crss[i].courseClassID[crss[i].courseClassID.size() - 1] << " at ";
                        for (unsigned int j = 0; j < crss[i].courseStartDay.size(); j++)
                        {
                                cout << crss[i].courseStartDay[j] << "_"
                                     << crss[i].courseStartTime[j] << "-"
                                     << crss[i].courseFinishTime[j] << ",";
                        }
                        cout << endl;
                }
        }
}

/* this function basicly checks if class id count one of more at the "-arrangeC" part */
bool isOneOrMore(string str)
{
        for (unsigned int i = 0; i < str.size(); i++)
        {
                if (str[i] == ',')
                {
                        return true;
                }
        }
        return false;
}