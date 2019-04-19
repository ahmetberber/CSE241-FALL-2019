/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW03         */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "functions.h"

using namespace std;

int main()
{
        ifstream inputStreamLect;
        ifstream inputStreamCourses;
        inputStreamCourses.open("courses_classrooms.txt");
        inputStreamLect.open("lecturers.txt");
        vector<Lecturer> wholeLecturers;
        vector<Course> wholeCourses;
        vector<Class> wholeClasses;
        if (inputStreamCourses.fail() || inputStreamLect.fail())
        {
                cerr << "Error to opening input files!" << endl;
        }
        else
        {
                /* INITIALIZING CLASSES AND STRUCTURES WITH INFORMATIONS IN GIVEN TXT FILES */
                int tempLectID, tempCourseCode, tempCourseCredit, tempCourseTotalHour, tempClassID, tempClassCapacity;
                string tempLectName, tempLectSurname, tempLectTitle, templectProffs, tempCourseID, tempCourseName, tempCourseField, upperLine, tempClassNo;
                do
                {
                        inputStreamLect >> tempLectID >> tempLectName >> tempLectSurname >> tempLectTitle >> templectProffs;
                        Lecturer initLect(tempLectID, tempLectName, tempLectSurname, tempLectTitle);
                        initLect.trimLectProffs(templectProffs);
                        wholeLecturers.push_back(initLect);
                        numberOfLecturers++;
                } while (!inputStreamLect.eof());
                inputStreamCourses >> upperLine >> tempCourseID;
                do
                {
                        Course initCourse;
                        inputStreamCourses >> tempCourseName >> tempCourseCode >> tempCourseCredit >> tempCourseTotalHour >> tempCourseField;
                        initCourse.courseID = stoi(tempCourseID), initCourse.courseName = tempCourseName, initCourse.courseCode = tempCourseCode,
                        initCourse.courseCredit = tempCourseCredit, initCourse.courseHours = tempCourseTotalHour, initCourse.courseField = tempCourseField;
                        initCourse.isMandatory = true, initCourse.isTaken = false;
                        wholeCourses.push_back(initCourse);
                        numberOfCourses++;
                } while (inputStreamCourses >> tempCourseID && tempCourseID != "CLASSROOMS");
                do
                {
                        Class initClass;
                        inputStreamCourses >> tempClassID >> tempClassNo >> tempClassCapacity;
                        initClass.classID = tempClassID, initClass.classNo = tempClassNo, initClass.classCapacity = tempClassCapacity;
                        wholeClasses.push_back(initClass);
                        numberOfClassrooms++;
                } while (!inputStreamCourses.eof());
        }
        /////////////////////////////////
        /* ordering courses high to low value */
        /* this means the course which most requested proffession will assign first */
        /* most requested profession holds in first element in wholeProffs vector */
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
        //////////////////////////////////
        string command;
        bool arrangeFlag = false;
        bool isAllCoursesAssigned = false;
        bool isAllCoursesTimeTableArranged = false;
        cin >> command;
        while (command != "exit")
        {
                if (command == "-propose")
                {
                        if (numberOfLecturers == 0)
                        {
                                cout << "no lecturers to propose!" << endl;
                        }
                        else
                        {
                                Course proposedCrs;
                                string proposedCrsName, proposedCrsField;
                                int proposedCrsCode, proposedCrsCredit, proposedCrsHours, pid, tempPid;
                                isComplete = false;
                                cin >> pid >> proposedCrsName >> proposedCrsCode >> proposedCrsCredit >> proposedCrsHours >> proposedCrsField;
                                for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                {
                                        if (wholeLecturers[i].getLectID() == pid)
                                        {
                                                tempPid = i;
                                                isComplete = true;/* no lecturer with given id error check */
                                        }
                                }
                                if (isComplete)
                                {
                                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                        {
                                                /* unique course specifications error check */
                                                if (proposedCrsName == wholeCourses[i].courseName)
                                                {
                                                        cout << "you are trying to propose a course which got same course name with existing courses, proposing not allowed!" << endl;
                                                        isComplete = false;
                                                        break;
                                                }
                                                else if (proposedCrsCode == wholeCourses[i].courseCode)
                                                {
                                                        cout << "you are trying to propose a course which got same course codes with existing courses, proposing not allowed!" << endl;
                                                        isComplete = false;
                                                        break;
                                                }
                                        }
                                        if (isComplete)
                                        {
                                                /* assigning course informations to temporary structure object */
                                                proposedCrs.courseName = proposedCrsName, proposedCrs.courseCode = proposedCrsCode,
                                                proposedCrs.courseCredit = proposedCrsCredit, proposedCrs.courseHours = proposedCrsHours,
                                                proposedCrs.courseField = proposedCrsField, proposedCrs.courseID = numberOfCourses + 1;
                                                wholeLecturers[tempPid].proposeCourse(proposedCrs);/* calling propose course member function */
                                        }
                                }
                                else
                                {
                                        cout << "there is no such a lecturer which has " << pid << " id number!" << endl;
                                }
                        }
                }
                else if (command == "-assign")
                {
                        if (numberOfCourses == 0 || numberOfLecturers == 0)
                        {
                                cout << "no lecturers or courses to assign!" << endl;
                        }
                        else
                        {
                                char nextC = cin.get();
                                if (nextC == '\n')/* just "-assign" command */
                                {
                                        for (unsigned int j = 0; j < wholeProffs.size(); j++)
                                        {
                                                for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                                {
                                                        /* all courses assigning to the lecturers from high to low requested profession order */
                                                        wholeLecturers[i].assignAllCoursesFromLect(wholeCourses, wholeProffs[j], wholeProffsCount[j]);
                                                }
                                        }
                                        for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                        {
                                                /* if any proposed courses before assigment, the proposed courses assigns to the lectuer */
                                                wholeLecturers[i].assignProposedCourses();
                                        }
                                        for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                        {
                                                /* showing lecturers which takes no course after the assigment */
                                                /* this means show the lecturer which have to propose courses with given count and appropiate profession */
                                                wholeLecturers[i].showUnassignedCourses();
                                        }
                                        isAllCoursesAssigned = true;
                                }
                                else/* "-assign" command with lecturer and course ids */
                                {
                                        bool isCompleteLid = false, isCompleteCid = false;
                                        int lid, cid, tempLid, tempCid;
                                        cin >> lid >> cid;
                                        for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                        {
                                                if (wholeLecturers[i].getLectID() == lid)
                                                {/* is given lecturer id matches the any of lecturer ids? */
                                                        tempLid = i;
                                                        isCompleteLid = true;
                                                        break;
                                                }
                                        }
                                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                        {
                                                if (wholeCourses[i].courseID == cid)
                                                {/* is given course id matches the any of course ids? */
                                                        tempCid = i;
                                                        isCompleteCid = true;
                                                        break;
                                                }
                                        }
                                        if (wholeCourses[tempCid].isTaken)
                                        {/* is given course assigned before? */
                                                cout << "this course already taken by another lecturer!" << endl;
                                        }
                                        else if (isCompleteCid && isCompleteLid)
                                        {
                                                if (wholeLecturers[tempLid].assignCourse(wholeCourses[tempCid]))
                                                {
                                                        cout << "DONE" << endl;
                                                        assignedLects++;
                                                        if (assignedLects == numberOfCourses)/* this means all courses assigned one by one and ready to arrangement */
                                                        {
                                                                cout << "all mandatory courses has been assigned!" << endl;
                                                                for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                                                {
                                                                /* if any proposed courses before assigment, the proposed courses assigns to the lectuer */
                                                                        wholeLecturers[i].assignProposedCourses();
                                                                }
                                                                for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                                                {
                                                                        /* showing lecturers which takes no course after the assigment */
                                                                        /* this means show the lecturer which have to propose courses with given count and appropiate profession */
                                                                        wholeLecturers[i].showUnassignedCourses();
                                                                }
                                                                isAllCoursesAssigned = true;
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                /* course id and lecturer id error checking */
                                                if (isCompleteCid == false && isCompleteLid == true)
                                                {
                                                        cout << "there is no course with given cid!" << endl;
                                                }
                                                else if (isCompleteCid == true && isCompleteLid == false)
                                                {
                                                        cout << "there is no lecturer with given lid!" << endl;
                                                }
                                                else
                                                {
                                                        cout << "there is no course and lecturer with given lid and cid!" << endl;
                                                }
                                        }
                                }
                        }
                }
                else if (command == "-timetable")
                {/* I arranged courses timetables from the beginning of the week */
                        if (numberOfCourses == 0)
                        {
                                cout << "no courses to arrange timetable!" << endl;
                        }
                        else
                        {
                                char nextC = cin.get();
                                if (nextC == '\n')/* just "-timetable" command */
                                {
                                        if (isAllCoursesAssigned == false)
                                        {/* if you want to arrange timetable of the all courses, then you have to assign all mandatory courses */
                                                cout << "you have to assign all the mandatory courses first!" << endl;
                                        }
                                        else
                                        {
                                                int dayCounter = 0, tempStartHourL = STARTHOUR;
                                                for (unsigned int i = 0; i < wholeLecturers.size(); i++)
                                                {/* arranging all courses timetables for delimeters */
                                                        wholeLecturers[i].setTimeTable(tempStartHourL, dayCounter, tempCourseClassDelimeterG, wholeCourses);
                                                }
                                                cout << "DONE!" << endl;
                                                isAllCoursesTimeTableArranged = true;
                                        }
                                }
                                else/* "-timetable" command with course id */
                                {
                                        int cid;
                                        cin >> cid;
                                        isComplete = false;
                                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                        {
                                                if (wholeCourses[i].isArrangedTimetable == false && wholeCourses[i].courseID == cid)
                                                {/* chechking if given course is arranged before and is id matches */
                                                        if (tempHourG + wholeCourses[i].courseHours <= FINISHHOUR)
                                                        {/* if courses start hour overflowing, then it belongs to the next day */
                                                                wholeCourses[i].courseStartTime.push_back(tempHourG);
                                                                wholeCourses[i].courseFinishTime.push_back(tempHourG + wholeCourses[i].courseHours);
                                                                wholeCourses[i].courseStartDay.push_back(wholeDays[tempDayCounterG]);
                                                                if (tempHourG + wholeCourses[i].courseHours == FINISHHOUR)
                                                                {
                                                                        tempHourG = STARTHOUR;
                                                                        tempDayCounterG++;
                                                                }
                                                                else
                                                                {
                                                                        tempHourG += wholeCourses[i].courseHours;
                                                                }
                                                        }
                                                        else
                                                        {/* if courses start hour not overflowing, then it belongs to the current day */
                                                                int temp = FINISHHOUR - tempHourG;
                                                                wholeCourses[i].courseStartTime.push_back(tempHourG);
                                                                wholeCourses[i].courseFinishTime.push_back(FINISHHOUR);
                                                                wholeCourses[i].courseStartDay.push_back(wholeDays[tempDayCounterG]);
                                                                tempHourG = STARTHOUR;
                                                                wholeCourses[i].courseStartTime.push_back(tempHourG);
                                                                wholeCourses[i].courseFinishTime.push_back(tempHourG + (wholeCourses[i].courseHours - temp));
                                                                if (wholeDays[tempDayCounterG] == "FRI")
                                                                {/* if we are in the last day of week, then go to the first day of the week */
                                                                        tempDayCounterG = 0;
                                                                        wholeCourses[i].courseStartDay.push_back(wholeDays[tempDayCounterG]);
                                                                }
                                                                else
                                                                {/* if not, then go to the next day of week */
                                                                        wholeCourses[i].courseStartDay.push_back(wholeDays[++tempDayCounterG]);
                                                                }
                                                                tempHourG += wholeCourses[i].courseHours - temp;
                                                        }
                                                        wholeCourses[i].isArrangedTimetable = true;
                                                        isComplete = true;
                                                        cout << "DONE!" << endl;
                                                        break;
                                                }
                                        }
                                        if (isComplete == false)
                                        {/* is given courses timetable arranged before? */
                                                cout << "this course's timetable has already arranged!" << endl;
                                        }
                                }
                        }
                }
                else if (command == "-arrangeC")
                {
                        if (numberOfClassrooms == 0 || numberOfCourses == 0)
                        {
                                cout << "no courses or classrooms!" << endl;
                        }
                        else
                        {
                                char nextC = cin.get();
                                if (nextC != '\n')/* "-arrangeC" command with course id and class id/s */
                                {
                                        int cid;
                                        isComplete = true;
                                        string tempClassNo;
                                        cin >> cid >> tempClassNo;
                                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                        {
                                                if (wholeCourses[i].courseID == cid && wholeCourses[i].courseClassID.size() != 0)
                                                {/* checking course id matching and if given course arranged a class before */
                                                        isComplete = false;
                                                        break;
                                                }
                                        }
                                        if (isComplete)/* if given course arranged before with a class? */
                                        {
                                                isComplete = false;
                                                if (isOneOrMore(tempClassNo))
                                                {/* that means if given course separated the other days or not */
                                                 /* and that means, user entered class ids which are more than 1 */
                                                        vector<int> classNumsV;/* creating vector to hold all class ids */
                                                        int i = 0, j = 0;
                                                        string tempStr;
                                                        while (tempClassNo[i] != ',' && (unsigned int)i != tempClassNo.size() + 1)
                                                        {
                                                                j = i;
                                                                while (tempClassNo[j] != ',' && (unsigned int)j != tempClassNo.size())
                                                                {
                                                                        j++;
                                                                }
                                                                tempStr.resize(j - i);
                                                                j = 0;
                                                                while (tempClassNo[i] != ',' && (unsigned int)i != tempClassNo.size())
                                                                {
                                                                        tempStr[j] = tempClassNo[i];
                                                                        i++, j++;
                                                                }
                                                                classNumsV.push_back(stoi(tempStr));
                                                                tempStr.clear();
                                                                i++, j = 0;
                                                        }
                                                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                                        {
                                                                if (wholeCourses[i].courseID == cid && wholeCourses[i].courseStartDay.size() == classNumsV.size())
                                                                {/* checking course id match and is the course count in a week is one or more? */
                                                                        for (unsigned int j = 0; j < wholeCourses[i].courseStartDay.size(); j++)
                                                                        {
                                                                                wholeCourses[i].courseClassID.push_back(classNumsV[j]);
                                                                                isComplete = true;
                                                                        }
                                                                        break;
                                                                }
                                                        }
                                                        if (isComplete == false)
                                                        {
                                                                cout << "you are trying to arrange course which at only 1 day in a week!" << endl;
                                                        }
                                                        else
                                                        {
                                                                /* showing course information */
                                                                cid--;
                                                                cout << "(" << wholeCourses[cid].courseID << ")" << wholeCourses[cid].courseName << " in ";
                                                                for (unsigned int j = 0; j < wholeCourses[cid].courseStartDay.size(); j++)
                                                                {
                                                                        cout << wholeCourses[cid].courseClassID[j] << " at "
                                                                             << wholeCourses[cid].courseStartDay[j] << "_"
                                                                             << wholeCourses[cid].courseStartTime[j] << "-"
                                                                             << wholeCourses[cid].courseFinishTime[j];
                                                                        if (j != wholeCourses[cid].courseStartDay.size() - 1)
                                                                                cout << ", in ";
                                                                }
                                                                cout << endl;
                                                        }
                                                }
                                                else/* if the course 1 day in a week */
                                                {
                                                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                                        {
                                                                if (wholeCourses[i].courseID == cid)
                                                                {/* checking course id match */
                                                                        for (unsigned int j = 0; j < wholeCourses[i].courseStartDay.size(); j++)
                                                                        {
                                                                                wholeCourses[i].courseClassID.push_back(stoi(tempClassNo));
                                                                                isComplete = true;
                                                                        }
                                                                        break;
                                                                }
                                                        }
                                                        /* showing course information */
                                                        cid--;
                                                        cout << "(" << wholeCourses[cid].courseID << ")" << wholeCourses[cid].courseName << " in ";
                                                        for (unsigned int j = 0; j < wholeCourses[cid].courseStartDay.size(); j++)
                                                        {
                                                                cout << wholeCourses[cid].courseClassID[j] << " at "
                                                                        << wholeCourses[cid].courseStartDay[j] << "_"
                                                                        << wholeCourses[cid].courseStartTime[j] << "-"
                                                                        << wholeCourses[cid].courseFinishTime[j];
                                                                if (j != wholeCourses[cid].courseStartDay.size() - 1)
                                                                        cout << ", in ";
                                                        }
                                                        cout << endl;                                      
                                                }
                                        }
                                        else
                                        {
                                                cout << "this course has already arranged with other class!" << endl;
                                        }
                                }
                                else if (arrangeFlag == false && nextC == '\n')/* just "-arrangeC" command */
                                {/* all courses arranging by the overflow of week hour, assume that there are 40 hours in a week, if sum of course hours is 60, then 20 hours goes to the next class */
                                        if (isAllCoursesTimeTableArranged)
                                        {
                                                for (int j = 0; j <= tempCourseClassDelimeterG; j++)
                                                {
                                                        for (unsigned int i = 0; i < wholeCourses.size(); i++)
                                                        {
                                                                if (wholeCourses[i].courseClassDelimeter == j)
                                                                {
                                                                        wholeCourses[i].courseClassID.push_back(wholeClasses[j].classID);
                                                                }
                                                        }
                                                }
                                                arrangeFlag = true;
                                                show(wholeCourses);/* showing all course informations */
                                        }
                                        else
                                        {/* if courses timetables not arranged before */
                                                cout << "you have to arrange all courses timetable first!" << endl;
                                        }
                                }
                                else if (arrangeFlag)
                                {/* if the "-arrangeC" command called before, that means no need to arrange all the courses again, just show */
                                        show(wholeCourses);
                                }
                        }
                }
                cin >> command;
        }
        inputStreamCourses.close();
        inputStreamLect.close();
        return 0;
}