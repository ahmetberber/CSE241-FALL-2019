/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW04         */

#include <iostream>
#include <vector>
#include <string>
#include "functions.h"

using namespace std;

namespace global
{
const unsigned int MAXCOURSELIMIT = 3;
const unsigned int STARTHOUR = 9;                               /* assume that courses start at 9:00 AM */
const int FINISHHOUR = 17;                                      /* assume that courses finish at 17:00 PM */
int tempCourseClassDelimeterG = 0;                              /* I'm using that variable at the arranging all courses timetables part */
const string wholeDays[] = {"MON", "TUE", "WED", "THU", "FRI"}; /* I'm using that variable at the arranging course timetables parts */
} // namespace global

/* classroom clas constructor */
Classroom::Classroom(int ID, int capacity, string no)
    : classID(ID), classCapacity(capacity), classNo(no)
{
        studentInRoom = 0;
        CoursesInClassroom = NULL;
        s_CoursesInClassroom = 0;
}
/* classroom clas copy constructor */
Classroom::Classroom(const Classroom &clss)
{
        CoursesInClassroom = new Course[clss.s_CoursesInClassroom];
        CoursesInClassroom = clss.CoursesInClassroom;
        s_CoursesInClassroom = clss.s_CoursesInClassroom;
        classID = clss.classID;
        classCapacity = clss.classCapacity;
        classNo = clss.classNo;
        studentInRoom = clss.studentInRoom;
}
/* classroom clas destructor */
Classroom::~Classroom()
{
        delete CoursesInClassroom;
        CoursesInClassroom = NULL;
}
/* I spilted this function 2 parts. If there is a lesson at the given time, first part works, If there is no lesson, second part works */
void Classroom::enterClassroom(Student enterStudent, string day, int hour, bool flag)
{ /* the "flag" variable controls if there is a lesson at the given time or not */
        bool stop = false;
        if (flag)
        { /* if there is a lesson, that means we should increment the attendance count of the appropiate course and student enters the class */
                for (unsigned int i = 0; i < s_CoursesInClassroom && stop == false; i++)
                {
                        for (unsigned int j = 0; j < CoursesInClassroom[i].enrolledStudents.size() && stop == false; j++)
                        {
                                if (CoursesInClassroom[i].enrolledStudents[j].studentID == enterStudent.studentID)
                                { /* checking student id, entering the student in class, incrementing attendance count and print the student count in class */
                                        CoursesInClassroom[i].enrolledStudents[j].attendanceCount++;
                                        CoursesInClassroom[i].enrolledStudents[j].isInClassroom = true;
                                        cout << ++studentInRoom << endl;
                                        stop = true;
                                }
                        }
                }
        }
        else
        {
                for (unsigned int i = 0; i < studentsInClass.size() && stop == false; i++)
                {
                        if (studentsInClass[i].studentID == enterStudent.studentID)
                        { /* checking student id, entering the student in class and print the student count in class */
                                studentsInClass[i].isInClassroom = true;
                                cout << ++studentInRoom << endl;
                                stop = true;
                        }
                }
        }
}
/* this function works like the enterClassroom function for 2 parts. First part check if given student is in any course of class,
second part check if given student is just in the class without taking attendance of any course */
bool Classroom::quitClassroom(Student quitStudent)
{
        for (unsigned int i = 0; i < s_CoursesInClassroom; i++)
        {
                for (unsigned int j = 0; j < CoursesInClassroom[i].enrolledStudents.size(); j++)
                {
                        if (CoursesInClassroom[i].enrolledStudents[j].studentID == quitStudent.studentID && CoursesInClassroom[i].enrolledStudents[j].isInClassroom)
                        { /* checking student id and is he/she is in classroom, quiting the "enrolled" student in class and print the student count in class */
                                CoursesInClassroom[i].enrolledStudents[j].isInClassroom = false;
                                cout << --studentInRoom << endl;
                                return true;
                        }
                }
        }
        for (unsigned int i = 0; i < studentsInClass.size(); i++)
        {
                if (studentsInClass[i].studentID == quitStudent.studentID && studentsInClass[i].isInClassroom)
                { /* checking student id and is he/she is in classroom, quiting the "not enrolled" student in class and print the student count in class */
                        studentsInClass[i].isInClassroom = false;
                        cout << --studentInRoom << endl;
                        return true;
                }
        }
        return false;
}
/* this function basically adding courses in the classes dynamically */
void Classroom::arrangeCoursesToClass(Course arrangingCourse)
{
        Course *temp = new Course[s_CoursesInClassroom + 1];
        for (unsigned int i = 0; i < s_CoursesInClassroom; i++)
        {
                temp[i] = CoursesInClassroom[i];
        }
        temp[s_CoursesInClassroom] = arrangingCourse;
        s_CoursesInClassroom++;
        CoursesInClassroom = temp;
}
/* this function finds and and prints the student's attendance count of given course information */
void Classroom::takeAttendance(Course attendanceCourse)
{
        for (unsigned int i = 0; i < s_CoursesInClassroom; i++)
        {
                if (CoursesInClassroom[i].courseID == attendanceCourse.courseID)
                {
                        for (unsigned int j = 0; j < CoursesInClassroom[i].enrolledStudents.size(); j++)
                        {
                                cout << CoursesInClassroom[i].enrolledStudents[j].studentName << " "
                                     << CoursesInClassroom[i].enrolledStudents[j].attendanceCount << " - ";
                        }
                }
        }
}
/* this function determines if there is a course at given time or not */
bool Classroom::detCourse(string day, int hour)
{
        for (unsigned int i = 0; i < s_CoursesInClassroom; i++)
        {
                for (unsigned int j = 0; j < CoursesInClassroom[i].courseStartDay.size(); j++)
                { /* I firstly controlled day and then the hour. The given hour must be between the start and finish hours of the course */
                        if (CoursesInClassroom[i].courseStartDay[j] == day &&
                            (global::STARTHOUR + hour) >= CoursesInClassroom[i].courseStartTime[j] &&
                            (global::STARTHOUR + hour) < CoursesInClassroom[i].courseFinishTime[j])
                        {
                                return true;
                        }
                }
        }
        return false;
}
/* this function adds students to the classes for the students which have no lesson on the given time */
void Classroom::addStudentsToClass(vector<Student> stdss)
{
        studentsInClass = stdss;
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
                        if (lectProffs[i] == prfs && crss[j].isTaken != true && lectTakenCourses.size() < global::MAXCOURSELIMIT)
                        {
                                crss[j].isTaken = true;
                                lectTakenCourses.push_back(crss[j]);
                        }
                }
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
/* this function helps arranging to the timetables of classes (appropiate with setTimeTable function) */
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
/* this function basically helps the arranging timetables of courses */
void Lecturer::setTimeTable(int &startCount, int &dayCount, int &del, vector<Course> &crss)
{
        for (unsigned int i = 0; i < lectTakenCourses.size(); i++)
        {
                if (startCount + lectTakenCourses[i].courseHours <= global::FINISHHOUR)
                { /* checking if the course day seperated two or not */
                        lectTakenCourses[i].courseClassDelimeter = del;
                        lectTakenCourses[i].courseStartTime.push_back(startCount);
                        lectTakenCourses[i].courseFinishTime.push_back(startCount + lectTakenCourses[i].courseHours);
                        lectTakenCourses[i].courseStartDay.push_back(global::wholeDays[dayCount]);
                        if (startCount + lectTakenCourses[i].courseHours == global::FINISHHOUR)
                        {
                                startCount = global::STARTHOUR;
                                dayCount++;
                        }
                        else
                        {
                                startCount += lectTakenCourses[i].courseHours;
                        }
                }
                else
                { /* one part of course at the end of day, the other part at the beginning of the next day */
                        int temp = global::FINISHHOUR - startCount;
                        lectTakenCourses[i].courseStartTime.push_back(startCount);
                        lectTakenCourses[i].courseFinishTime.push_back(global::FINISHHOUR);
                        lectTakenCourses[i].courseStartDay.push_back(global::wholeDays[dayCount]);
                        startCount = global::STARTHOUR;
                        lectTakenCourses[i].courseStartTime.push_back(startCount);
                        lectTakenCourses[i].courseFinishTime.push_back(startCount + (lectTakenCourses[i].courseHours - temp));
                        if (global::wholeDays[dayCount] == "FRI")
                        { /* checking if we reached the end of week */
                                dayCount = 0;
                                del++;
                                lectTakenCourses[i].courseClassDelimeter = del;
                                lectTakenCourses[i].courseStartDay.push_back(global::wholeDays[dayCount]);
                        }
                        else
                        {
                                lectTakenCourses[i].courseClassDelimeter = del;
                                lectTakenCourses[i].courseStartDay.push_back(global::wholeDays[++dayCount]);
                        }
                        startCount += lectTakenCourses[i].courseHours - temp;
                }
                assignAllCoursesFromAllCourses(lectTakenCourses[i], crss); /* assigning arranged course to the lecturer's courses */
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
        cout << endl;
}