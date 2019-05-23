/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW04         */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "functions.h"

using namespace std;
using namespace global;

int main()
{
        ifstream inputStreamLect;
        ifstream inputStreamCourses;
        ifstream inputStreamStudent;
        inputStreamCourses.open("courses_classrooms.txt");
        inputStreamLect.open("lecturers.txt");
        inputStreamStudent.open("students.txt");
        if (inputStreamCourses.fail() || inputStreamLect.fail() || inputStreamStudent.fail())
        {
                cerr << "Error to opening input files!" << endl;
        }
        else
        {
                vector<Lecturer> wholeLecturers;
                vector<Course> wholeCourses;
                vector<Classroom> wholeClassrooms;
                vector<Student> wholeStudents;
                /* INITIALIZING CLASSES AND STRUCTURES WITH INFORMATIONS IN GIVEN TXT FILES */
                int tempLectID, tempCourseCode, tempCourseCredit, tempCourseTotalHour, tempClassID, tempClassCapacity, tempStudentID;
                string tempLectName, tempLectSurname, tempLectTitle, templectProffs, tempCourseID, tempCourseName,
                    tempCourseField, upperLine, tempClassNo, tempStudentName, tempStudentSurname;
                do
                {
                        inputStreamLect >> tempLectID >> tempLectName >> tempLectSurname >> tempLectTitle >> templectProffs;
                        Lecturer initLect(tempLectID, tempLectName, tempLectSurname, tempLectTitle);
                        initLect.trimLectProffs(templectProffs);
                        wholeLecturers.push_back(initLect);
                } while (!inputStreamLect.eof());
                inputStreamCourses >> upperLine >> tempCourseID;
                do
                {
                        Course initCourse;
                        inputStreamCourses >> tempCourseName >> tempCourseCode >> tempCourseCredit >> tempCourseTotalHour >> tempCourseField;
                        initCourse.courseID = stoi(tempCourseID), initCourse.courseName = tempCourseName,
                        initCourse.courseCode = tempCourseCode, initCourse.isTaken = false, initCourse.courseCredit = tempCourseCredit,
                        initCourse.courseHours = tempCourseTotalHour, initCourse.courseField = tempCourseField;
                        wholeCourses.push_back(initCourse);
                } while (inputStreamCourses >> tempCourseID && tempCourseID != "CLASSROOMS");
                do
                {
                        inputStreamCourses >> tempClassID >> tempClassNo >> tempClassCapacity;
                        Classroom initClassroom(tempClassID, tempClassCapacity, tempClassNo);
                        wholeClassrooms.push_back(initClassroom);
                } while (!inputStreamCourses.eof());
                do
                {
                        Student initStudent;
                        inputStreamStudent >> tempStudentName >> tempStudentSurname >> tempStudentID;
                        initStudent.studentName = tempStudentName, initStudent.studentSurname = tempStudentSurname,
                        initStudent.studentID = tempStudentID, initStudent.isInClassroom = false, initStudent.attendanceCount = 0;
                        wholeStudents.push_back(initStudent);
                } while (!inputStreamStudent.eof());
                /* ARRANGING COURSES */
                for (unsigned int i = 0; i < wholeCourses.size(); i++)
                {
                        for (unsigned int j = 0; j < wholeStudents.size(); j++)
                        {
                                wholeCourses[i].enrolledStudents.push_back(wholeStudents[j]);
                        }
                }
                for (unsigned int i = 0; i < wholeClassrooms.size(); i++)
                {
                        wholeClassrooms[i].addStudentsToClass(wholeStudents);
                }
                /* ARRANGING PROFFESSIONS */
                vector<string> wholeProffs;
                vector<int> wholeProffsCount;
                for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                {
                        wholeLecturers[i].detProffs(wholeProffs, wholeProffsCount);
                }
                int temp_i;
                string temp_s;
                for (unsigned int i = 0; i < wholeProffs.size() - 1; i++)
                {
                        for (unsigned int j = i + 1; j < wholeProffs.size(); j++)
                        {
                                if (wholeProffsCount[i] < wholeProffsCount[j])
                                {
                                        temp_i = wholeProffsCount[i];
                                        wholeProffsCount[i] = wholeProffsCount[j];
                                        wholeProffsCount[j] = temp_i;

                                        temp_s = wholeProffs[i];
                                        wholeProffs[i] = wholeProffs[j];
                                        wholeProffs[j] = temp_s;
                                }
                        }
                }
                /* ASSIGNING COURSES TO LECTURERS */
                for (unsigned int j = 0; j < wholeProffs.size(); j++)
                {
                        for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                        {
                                /* all courses assigning to the lecturers from high to low requested profession order */
                                wholeLecturers[i].assignAllCoursesFromLect(wholeCourses, wholeProffs[j], wholeProffsCount[j]);
                        }
                }
                /* ARRANGING TIMETABLES */
                int dayCounter = 0, tempStartHourL = STARTHOUR;
                for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                { /* arranging all courses timetables for delimeters */
                        wholeLecturers[i].setTimeTable(tempStartHourL, dayCounter, tempCourseClassDelimeterG, wholeCourses);
                }
                /* ARRANGING COURSES TO CLASSES */
                for (int j = 0; j <= tempCourseClassDelimeterG; j++)
                {
                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                        {
                                if (wholeCourses[i].courseClassDelimeter == j)
                                {
                                        wholeCourses[i].courseClassID.push_back(wholeClassrooms[j].getClassroomID());
                                }
                        }
                }
                /* ARRANGING CLASSES TO THE COURSES */
                for (unsigned int i = 0; i < wholeCourses.size(); i++)
                {
                        for (unsigned int j = 0; j < wholeClassrooms.size(); j++)
                        {
                                if (wholeCourses[i].courseClassID[0] == wholeClassrooms[j].getClassroomID())
                                {
                                        wholeClassrooms[j].arrangeCoursesToClass(wholeCourses[i]);
                                }
                        }
                }
                /* PRINTING TIMETABLES */
                show(wholeCourses);
                string command;
                cin >> command;
                while (command != "exit")
                {
                        if (command == "-enter")
                        {
                                bool checkStdID = false, checkClssID = false;
                                int enterStdID, enterClssID, hourOfWeek, tempStdID, tempClssID;
                                Student enterStd;
                                cin >> enterStdID >> enterClssID >> hourOfWeek;
                                for (unsigned int i = 0; i < wholeStudents.size(); i++)
                                { /* checking if there is a student with given id */
                                        if (enterStdID == wholeStudents[i].studentID)
                                        {
                                                tempStdID = i;
                                                checkStdID = true;
                                        }
                                }
                                for (unsigned int i = 0; i < wholeClassrooms.size(); i++)
                                { /* checking if there is a classroom with given id */
                                        if (enterClssID == wholeClassrooms[i].getClassroomID())
                                        {
                                                tempClssID = i;
                                                checkClssID = true;
                                        }
                                }
                                if (checkStdID && checkClssID)
                                {
                                        if (wholeStudents[tempStdID].isInClassroom)
                                        { /* checking if the student with given id is in another classroom */
                                                cout << "s/he is at another classroom!" << endl;
                                        }
                                        else
                                        {
                                                string tempDay = wholeDays[hourOfWeek / (FINISHHOUR - STARTHOUR)]; /* determining course's day */
                                                int tempHour = hourOfWeek % (FINISHHOUR - STARTHOUR);              /* determining course's hour */
                                                wholeClassrooms[tempClssID].enterClassroom(wholeStudents[tempStdID], tempDay, tempHour, wholeClassrooms[tempClssID].detCourse(tempDay, tempHour));
                                                wholeStudents[tempStdID].isInClassroom = true;
                                        }
                                }
                                else
                                {
                                        cout << "there is no student or class with given ids!" << endl;
                                }
                        }
                        else if (command == "-quit")
                        {
                                bool checkStdID = false, checkInAnyClassroom = false;
                                int quitStdID;
                                cin >> quitStdID;
                                Student quitStudent;
                                for (unsigned int i = 0; i < wholeStudents.size(); i++)
                                {
                                        if (quitStdID == wholeStudents[i].studentID)
                                        { /* checking if there is a student with given id */
                                                checkStdID = true;
                                                if (wholeStudents[i].isInClassroom)
                                                { /* checking if the student with given id is in a classroom */
                                                        quitStudent = wholeStudents[i];
                                                        wholeStudents[i].isInClassroom = false;
                                                        checkInAnyClassroom = true;
                                                }
                                                break;
                                        }
                                }
                                if (checkStdID && checkInAnyClassroom)
                                {
                                        for (unsigned int i = 0; i < wholeClassrooms.size(); i++)
                                        {
                                                if (wholeClassrooms[i].quitClassroom(quitStudent))
                                                {
                                                        break;
                                                }
                                        }
                                }
                                else if (checkStdID && checkInAnyClassroom == false)
                                {
                                        cout << "s/he is not in any classroom" << endl;
                                }
                                else
                                {
                                        cout << "there is no student with given id!" << endl;
                                }
                        }
                        else if (command == "-attendance")
                        {
                                bool checkCrsID = false;
                                int attdCrsID, tempCrsID;
                                cin >> attdCrsID;
                                for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                { /* checking if there is a course with given id */
                                        if (wholeCourses[i].courseID == attdCrsID)
                                        {
                                                tempCrsID = i;
                                                checkCrsID = true;
                                        }
                                }
                                if (checkCrsID)
                                {
                                        for (unsigned int i = 0; i < wholeClassrooms.size(); i++)
                                        {
                                                wholeClassrooms[i].takeAttendance(wholeCourses[tempCrsID]);
                                        }
                                        cout << endl;
                                }
                                else
                                {
                                        cout << "there is no course with given id!" << endl;
                                }
                        }
                        cin >> command;
                }
        }
        inputStreamCourses.close();
        inputStreamLect.close();
        inputStreamStudent.close();
        return 0;
}