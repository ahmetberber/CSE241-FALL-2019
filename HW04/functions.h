/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW04         */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace global
{
extern const unsigned int MAXCOURSELIMIT;
extern const unsigned int STARTHOUR;
extern const int FINISHHOUR;
extern int tempCourseClassDelimeterG;
extern const string wholeDays[];
} // namespace global

struct Student
{
        string studentName;
        string studentSurname;
        int studentID;
        bool isInClassroom;
        int attendanceCount;
        //////////////
        int studentGrade;
        int studentCreditRight;
        int studentCredit;
        int numberOfCourseGet;
        //////////////
};

struct Course
{
        int courseID;
        int courseCode;
        int courseCredit;
        int courseHours;
        int courseClassDelimeter; /* I'm using that variable at the class arrangement part. The idea is basically like that,
        Assume that sum of courses hours is 60 and we have 40 hours total a week. I'm assigning to this variable values 
        starting from 0 and when the 40 hours are done, I increment that value and that value becomes 1 and the other 20
        hour part courses variable becomes 1. When I'm started to arrange classes, I'm checking this value and change
        the class after every 40 hours done */
        string courseName;
        string courseField;
        vector<string> courseStartDay;
        vector<unsigned int> courseStartTime;
        vector<unsigned int> courseFinishTime;
        vector<int> courseClassID;        /* this variable holds the class id which the course having in this class */
        vector<Student> enrolledStudents; /* this variable holds the students which have a lesson at given time (after enter student part) */
        bool isTaken;                     /* this variable holds the value if the course taken by a lecturer */
};

class Classroom
{
public:
        Classroom(int ID, int capacity, string no); /* constructor */
        Classroom(const Classroom &clss);           /* copy constructor */
        ~Classroom();                               /* destructor */
        Classroom &operator=(const Classroom &clss) /* assignment operator overloading */
        {
                if (&clss != this)
                {
                        s_CoursesInClassroom = clss.s_CoursesInClassroom;
                        classID = clss.classID;
                        classCapacity = clss.classCapacity;
                        classNo = clss.classNo;
                        studentInRoom = clss.studentInRoom;
                        for (unsigned int i = 0; i < studentsInClass.size(); i++)
                        {
                                studentsInClass[i] = clss.studentsInClass[i];
                        }
                        /* dynamic part */
                        delete CoursesInClassroom;
                        CoursesInClassroom = new Course[clss.s_CoursesInClassroom];
                        for (unsigned int i = 0; i < s_CoursesInClassroom; i++)
                        {
                                CoursesInClassroom[i] = clss.CoursesInClassroom[i];
                        }
                }
                return *this;
        }
        int getClassroomID() { return classID; }
        void enterClassroom(Student enterStudent, string day, int hour, bool flag);
        bool quitClassroom(Student quitStudent);
        void arrangeCoursesToClass(Course arrangingCourse);
        void takeAttendance(Course attendanceCourse);
        bool detCourse(string day, int hour);
        void addStudentsToClass(vector<Student> stdss);

private:
        int classID;
        int classCapacity;
        string classNo;
        int studentInRoom;
        Course *CoursesInClassroom;
        unsigned int s_CoursesInClassroom; /* this variable holds the number of courses in classroom */
        vector<Student> studentsInClass;   /* this variable holds the students which have no lesson at given time (after enter student part) */
};

class Lecturer
{
public:
        Lecturer(int ID, string name, string surname, string title)
            : lectID(ID), lectName(name), lectSurname(surname), lectTitle(title) {}
        void trimLectProffs(string str);
        void assignAllCoursesFromLect(vector<Course> &crss, string prfs, int prfsCnt);
        void detProffs(vector<string> &prfss, vector<int> &prfssCnt);
        void assignAllCoursesFromAllCourses(Course assig, vector<Course> &crss);
        void setTimeTable(int &startCount, int &dayCount, int &del, vector<Course> &crss);

private:
        int lectID;
        string lectName;
        string lectSurname;
        string lectTitle;
        vector<string> lectProffs;
        vector<Course> lectTakenCourses;
};

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

#endif