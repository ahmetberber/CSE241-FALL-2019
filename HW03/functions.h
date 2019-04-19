/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW03         */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

extern const unsigned int MAXCOURSELIMIT;
extern const unsigned int STARTHOUR;
extern const int FINISHHOUR;
extern int numberOfCourses;
extern int numberOfClassrooms;
extern int numberOfLecturers;
extern int tempHourG;
extern int tempDayCounterG;
extern int tempCourseClassDelimeterG;
extern int assignedLects;
extern const string wholeDays[];
extern bool isComplete;

struct Class
{
        int classID;
        int classCapacity;
        string classNo;
};

struct Course
{
        int courseID;
        int courseCode;
        int courseCredit;
        int courseHours;
        int courseClassDelimeter;/* I'm using that variable at the class arrangement part. The idea is basically like that,
        Assume that sum of courses hours is 60 and we have 40 hours total a week. I'm assigning to this variable values 
        starting from 0 and when the 40 hours are done, I increment that value and that value becomes 1 and the other 20
        hour part courses variable becomes 1. When I'm started to arrange classes, I'm checking this value and change
        the class after every 40 hours done */ 
        string courseName;
        string courseField;
        vector<string> courseStartDay;
        vector<int> courseStartTime;
        vector<int> courseFinishTime;
        vector<int> courseClassID;/* this variable holds the class id which the course having in this class */
        bool isMandatory;/* this variable holds the value if the course is mandatory or elective */
        bool isTaken;/* this variable holds the value if the course taken by a lecturer */
        bool isArrangedTimetable;/* this variable holds the value if the courses time table arranged */
};

class Lecturer
{
public:
        Lecturer(int ID, string name, string surname, string title)
            : lectID(ID), lectName(name), lectSurname(surname), lectTitle(title) {}
        int getLectID() { return lectID; }
        void proposeCourse(Course newCrs);
        bool assignCourse(Course &assignningCourse);
        void trimLectProffs(string str);
        void assignAllCoursesFromLect(vector<Course> &crss, string prfs, int prfsCnt);
        void showUnassignedCourses();
        void detProffs(vector<string> &prfss, vector<int> &prfssCnt);
        void assignProposedCourses();
        void setTimeTable(int &startCount, int &dayCount, int &del, vector<Course> &crss);
        void assignAllCoursesFromAllCourses(Course assig, vector<Course> &crss);

private:
        int lectID;
        string lectName;
        string lectSurname;
        string lectTitle;
        vector<string> lectProffs;
        vector<Course> lectTakenCourses;
        vector<Course> lectProposedCourses;
};

/* I don't need this class to the arrangement part. I put the necessary functions to the Lecturer class */
class Administrator
{
public:
        void arrangeClassroom();
        void arrangeTimeTable();

private:
        int adminID;
        int adminPass;
        vector<Course> courses;
};

void show(vector<Course> crss);
bool isOneOrMore(string str);

#endif