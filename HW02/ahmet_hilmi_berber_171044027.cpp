/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW02         */

/* NOTE: PLEASE COMPILE THIS PROGRAM WITH (-std=c++11) COMMAND */
/* FOR EX: g++ -std=c++11 ahmet_hilmi_berber_171044027.cpp -o output */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

#define FIRSTCLASSCREDITRIGHT 20
#define SECONDCLASSCREDITRIGHT 21
#define THIRDCLASSCREDITRIGHT 22
#define FOURTHCLASSCREDITRIGHT 23

int numberOfCourses = 0;
int numberOfClassrooms = 0;
int numberOfStudents = 0;

struct Class{
	int classID;
	int classCapacity;
	int student_inroom;/* This variable holds number of students in the class */
	string classNo;
	vector<int> studentIDs;/* This variable holds students IDs which are in the class */
};

struct Course{
	int courseID;
	int courseCode;
	int courseCredit;
	int courseHours;
	int howMuchDay;/* This variable holds the number of days a week */
	string courseName;
	vector<string> courseStartDay;
	vector<int> courseStartTime;
	vector<int> courseFinishTime;
};

class Student{
	public:
		Student(string name, string surname, int ID, int grade, int creditRight)/* constructor */
		: studentName(name)
		, studentSurname(surname)
		, studentID(ID)
		, studentGrade(grade)
		, studentCreditRight(creditRight)
		, studentCredit(0)
		, numberOfCourseGet(0){ }
		void set_studentCredit(int i){ studentCredit = i; }
		void set_numberOfCourseGet(int i){ numberOfCourseGet = i; }
		int get_studentID(){ return studentID; }
		bool isAlreadyTakenCourse(int i);
                int enrollCourse(Course enrollingCourse);
                int disenrollCourse(Course disenrollingCourse);
		string extractSchedule();
		void enterClassroom(Class& enteringClass);
		void quitClassroom(Class& quittingClass);
	private:
		string studentName;
		string studentSurname;
		int studentID;
		int studentGrade;
		int studentCreditRight;
		int studentCredit;
		int numberOfCourseGet;
		vector<Course> studentCourses;
};

bool isTxt(string filename);
void trimmer(string str, Course& crs);
bool isOverlap(int startTime_std, int finishTime_std, int startTime_crs, int finishTime_crs);
int m_abs(int num);

int main()
{
	ifstream inputStream;
	ofstream outputStream;
	inputStream.open("courses_classrooms.txt");
	vector<Student> wholeStudents;
	vector<Course> wholeCourses;
	vector<Class> wholeClasses;
	if(inputStream.fail())
	{
		cerr << "Error to opening input file!" << endl;
	}
	else
	{
		int courseCode, courseCredit, courseHours, classID, classCapacity;
		string upperLine, courseID, courseName, courseTime, classNo;
		inputStream >> upperLine >> courseID;
		/* Initializing courses from input file */
		do
		{
			Course initCourse;
			inputStream >> courseName >> courseCode >> courseCredit >> courseHours >> courseTime;
			initCourse.courseID = stoi(courseID), initCourse.courseName = courseName, initCourse.courseCode = courseCode,
			initCourse.courseCredit = courseCredit, initCourse.courseHours = courseHours;
			trimmer(courseTime,initCourse);
			wholeCourses.push_back(initCourse);
			numberOfCourses++;
		}while(inputStream >> courseID && courseID != "CLASSROOMS");
		/* Initializing classrooms from input file */
		do
		{
			Class initClass;
			inputStream >> classID >> classNo >> classCapacity;
			initClass.classID = classID, initClass.classNo = classNo, initClass.classCapacity = classCapacity, initClass.student_inroom = 0;
			wholeClasses.push_back(initClass);
			numberOfClassrooms++;
		}while(!inputStream.eof());
	}
	string initStdName, initStdSurname, command;
	int initStdNum, initStdGrade;
	/* Student register part with (-ns) command */
	cin >> command;
	while(command != "-list")
	{
		cin >> initStdName >> initStdSurname >> initStdNum >> initStdGrade;
		if(initStdGrade == 1)
		{
			Student tempStd(initStdName, initStdSurname, initStdNum, initStdGrade, FIRSTCLASSCREDITRIGHT);
			wholeStudents.push_back(tempStd);
		}
		else if(initStdGrade == 2)
		{
			Student tempStd(initStdName, initStdSurname, initStdNum, initStdGrade, SECONDCLASSCREDITRIGHT);
			wholeStudents.push_back(tempStd);
		}
		else if(initStdGrade == 3)
		{
			Student tempStd(initStdName, initStdSurname, initStdNum, initStdGrade, THIRDCLASSCREDITRIGHT);
			wholeStudents.push_back(tempStd);
		}
		else if(initStdGrade == 4)
		{
			Student tempStd(initStdName, initStdSurname, initStdNum, initStdGrade, FOURTHCLASSCREDITRIGHT);
			wholeStudents.push_back(tempStd);
		}
		numberOfStudents++;
		cin >> command;
	}
	/* All courses with their credits appears on the terminal */
	for(int i = 0; i < numberOfCourses; i++)
	{
		cout << "(" << wholeCourses[i].courseID << ")" << wholeCourses[i].courseName << " ";
	}
	cout << endl;
	string command_1, command_2, tempFileName;
	int tempStdNo, tempStdCourseID;
	cin >> command_1;
	while(command_1 != "exit")
	{
		/* Student enrollment part. getting student number and course id from user */
		if(command_1 == "-e" && numberOfStudents == 0)
		{/* If there is no student, that means we have nothing the show */
			cout << "ERROR: NO STUDENT!" << endl;
			break;
		}
		else if(command_1 == "-e" && numberOfStudents != 0)
		{
			cin >> tempStdNo >> tempStdCourseID;
			for(int i = 0; i < numberOfStudents; i++)
			{
				if(wholeStudents[i].get_studentID() == tempStdNo)/* Checking studentID */
				{
					for(int j = 0; j < numberOfCourses; j++)
					{
						if(wholeCourses[j].courseID == tempStdCourseID)/* Checking courseID */
						{
							wholeStudents[i].enrollCourse(wholeCourses[j]);/* Returns remain credit right */
						}
					}
				}
			}
		}
		/* Student disenrollment part. getting student number and course id from user */
		else if(command_1 == "-de")
		{
			cin >> tempStdNo >> tempStdCourseID;
			for(int i = 0; i < numberOfStudents; i++)
			{
				if(wholeStudents[i].get_studentID() == tempStdNo)/* Checking studentID */
				{
					for(int j = 0; j < numberOfCourses; j++)
					{
						if(wholeCourses[j].courseID == tempStdCourseID)/* Checking courseID */
						{
							wholeStudents[i].disenrollCourse(wholeCourses[j]);/* Returns remain credit right */
						}
					}
				}
			}
		}		
		/* Printing student informations part */
		else if(command_1 == "-o")
		{
			char nextC = cin.get();
			if(nextC == '\n')/* I checked if there is newline or something else (like space) after (-o) command */
			{/* If there is newline after (-o), that means user just entered (-o) command */
				/* All student informations appears on terminal */
				for(int i = 0; i < numberOfStudents; i++)
				{
					cout << wholeStudents[i].extractSchedule() << endl;
				}
			}	
			else/* If there is no newline after (-o) command, that means user may entered two kinda commands: */
			{/* one of them student number with file name, the other one is just file name (with (-f) command of course)*/
				cin >> command_2;
				if(command_2 == "-f")
				{
					cin >> tempFileName;
					if(isTxt(tempFileName))/* I checked the dot in the string whether the string after (-o) command is file name or not */
					{
						/* If user entered file name, that means all student informations written in file which named "tempFileName" */
						outputStream.open(tempFileName.c_str());
						for(int i = 0; i < numberOfStudents; i++)
						{
							outputStream << wholeStudents[i].extractSchedule() << endl;
						}
						cout << "DONE!" << endl;
					}
					else
					{
						/* If user didn't enter file name, that means entered student number with file name */
						tempStdNo = stoi(tempFileName);/* I got the student number here */
						cin >> tempFileName;/* and the file name is second one */
						outputStream.open(tempFileName.c_str());
						for(int i = 0; i < numberOfStudents; i++)
						{/* so, the student information with given number written in file which named "tempFileName" */
							if(wholeStudents[i].get_studentID() == tempStdNo)
							{
								outputStream << wholeStudents[i].extractSchedule() << endl;
								break;
							}
						}
						cout << "DONE!" << endl;
					}		
				}
				else
				{/* If there is no newline after the (-o) command, that means user entered student number with (-o) */
					cin >> tempStdNo;
					/* The student information which given with student number appears on terminal */
					for(int i = 0; i < numberOfStudents; i++)
					{
						if(wholeStudents[i].get_studentID() == tempStdNo)
						{
							cout << wholeStudents[i].extractSchedule() << endl;
						}
					}
				}
			}
		}	
		cin >> command_1;
	}
	inputStream.close();
	outputStream.close();	
	return 0;
}
/* This function controls whether given string is file name or not */
bool isTxt(string filename)
{
	for(unsigned int i = 0; i < filename.length(); i++)
		if(filename[i] == '.')
			return true;
	return false;
}
/* This function gets a string which is in course days, start times, finish times in input file format,
and seperate them. After that assings them appropriate course variables */
void trimmer(string str, Course& crs)
{
	int i = 0, j = 0, k = 0, m = 0, dayCounter = 0;
	string tempStartDay, tempStartTime , tempFinishTime;
	while(str[i] != ',' && (unsigned int)i != str.length() + 1)
	{
		tempStartTime.resize(2),tempFinishTime.resize(2);
		m = i;
		while(str[m] != '_')
		{
			m++;
		}
		tempStartDay.resize(m - i);
		while(str[i] != '_')
		{
			tempStartDay[j] = str[i];
			i++, j++;
		}
		i++,j = 0;
		while(str[i] != '-')
		{
			tempStartTime [j] = str[i];
			i++, j++;
		}
		i++;
		while(str[i] != ',' && (unsigned int)i!=str.length())
		{
			tempFinishTime[k] = str[i];
			i++, k++;
		}
		dayCounter++;
		crs.courseStartDay.push_back(tempStartDay);
		crs.courseStartTime.push_back(stoi(tempStartTime));
		crs.courseFinishTime.push_back(stoi(tempFinishTime));
		tempStartDay.clear(),tempStartTime .clear(),tempFinishTime.clear();
		i++, j = 0, k = 0;
	}
	crs.howMuchDay = dayCounter;	
}
/* This function checks the overlap situation between 2 courses */
bool isOverlap(int startTime_std, int finishTime_std, int startTime_crs, int finishTime_crs)
{
	if((startTime_std == startTime_crs) && (finishTime_std != finishTime_crs))
	{/* Start times may equal, Finish times are different */
		if(m_abs(finishTime_std - finishTime_crs) > 1)
			return true;
	}
	else if((startTime_std != startTime_crs) && (finishTime_std == finishTime_crs))
	{/* Finish times may equal, start times are different */
		if(m_abs(startTime_std - startTime_crs) > 1)
			return true;
	}
	else if((startTime_std == startTime_crs) && (finishTime_std == finishTime_crs))
	{/* Both start and finish time may equal */
		if(m_abs(startTime_std - finishTime_std) > 1)
			return true;
	}
	else
	{/* If all of four times are different, I find the course which starts first and I checked difference 
	    between first lesson's start time and second lesson's finish time */ 
		if(m_abs(startTime_std - finishTime_std != 1) && m_abs(startTime_crs - finishTime_crs) != 1)
		{
			if(startTime_std > startTime_crs)
			{
				if(m_abs(startTime_std - finishTime_crs) > 1)
					return true;
			}
			else
			{
				if(m_abs(startTime_crs - finishTime_std) > 1)
					return true;
			}
		}
	}	
	return false;
}

int m_abs(int num)
{
	if(num > 0)
		return num;
	else
		return (-num);
}
/* This function controls the enrolling course is already taken or never taken */
bool Student::isAlreadyTakenCourse(int i)
{
	for(unsigned int j = 0; j < studentCourses.size(); j++)
		if(i == studentCourses[j].courseID)
			return true;
	return false;
}

int Student::enrollCourse(Course enrollingCourse)
{
	if(isAlreadyTakenCourse(enrollingCourse.courseID))
	{/* I checked if given course is already taken */
		cout << "BLOCK! Because this course already taken!" << endl;
		return studentCredit; 
	}
	else
	{
		if((studentCredit + enrollingCourse.courseCredit) > studentCreditRight)
		{/* I checked if credit sum with given course is bigger than student credit right */
			cout << "BLOCK! Because of credits" << endl;
			return studentCredit; 
		}
		else
		{
			for(unsigned int k = 0; k < enrollingCourse.courseStartDay.size(); k++)
			{/* This loop returns till the given course's number of days in a week */
				for(int m = 0; m < numberOfCourseGet; m++)
				{/* This loop returns till number student's courses */
					for(int n = 0; n < studentCourses[m].howMuchDay; n++)
					{/* This loop returns till the mth student's course's number of days in a week */
						if(enrollingCourse.courseStartDay[k] == studentCourses[m].courseStartDay[n])
						{/* For overlap possibility, the courses have to in same days and I checked that */ 	
							if(isOverlap(studentCourses[m].courseStartTime[n], studentCourses[m].courseFinishTime[n],
								     enrollingCourse.courseStartTime[k], enrollingCourse.courseFinishTime[k]))
							{							
								cout << "BLOCK! Because of overlap" << endl;
								return studentCredit; 
							}
						}
					}
				}
			}
			studentCourses.push_back(enrollingCourse);/* If there is no overlap, I added given course to student's courses */
			set_numberOfCourseGet(numberOfCourseGet + 1);/* I updated the number of courses which student have */
			set_studentCredit(studentCredit + enrollingCourse.courseCredit);/* I updated the student's credit */
			cout << "DONE" << endl;
			return studentCreditRight - studentCredit;/* I returned the return credit right */
		}
	}
        
}

int Student::disenrollCourse(Course disenrollingCourse)
{
	if(!isAlreadyTakenCourse(disenrollingCourse.courseID))
	{/* I checked if given course is ever taken */
		cout << "BLOCK! Because this class ever taken!" << endl;
		return studentCredit;
	}
	else
	{
		for(unsigned int i = 0; i < studentCourses.size(); i++)
		{
			if(studentCourses[i].courseID == disenrollingCourse.courseID)
			{/* I paired the courseID's and erased the given course */
				studentCourses.erase(studentCourses.begin() + i);
			}
		}
		set_numberOfCourseGet(numberOfCourseGet - 1);/* I updated the number of courses which student have */
		set_studentCredit(studentCredit - disenrollingCourse.courseCredit);/* I updated the student's credit */
		cout << "DONE" << endl;
		return studentCreditRight + studentCredit;/* I returned the return credit right */
	}
}
/* This function combines the student informations and returns as a string */
string Student::extractSchedule()
{
	string schedule = studentName + " " + studentSurname + " [";
	for(int i = 0; i <  numberOfCourseGet; i++)
	{
		schedule = schedule + studentCourses[i].courseName + "(" + to_string(studentCourses[i].courseCredit) + ") ";
	}
	schedule = schedule + "] total credits: " + to_string(studentCredit) + " credit right: " + to_string(studentCreditRight);
	return schedule;
}

void Student::enterClassroom(Class& enteringClass)
{
	if(enteringClass.student_inroom == enteringClass.classCapacity)
	{/* If classroom is full, that means no one can enter */
		cout << "BLOCK! Full class capacity!" << endl;
		return;
	}
	else
	{
		for(unsigned int i = 0; i < enteringClass.studentIDs.size(); i++)
		{
			if(studentID == enteringClass.studentIDs[i])
			{/* If given student already in classroom */
				cout << "BLOCK! Because this student already in this class!" << endl;
				return;
			}
		}	
		enteringClass.student_inroom++;/* I incremented the number which holds number of students in the classroom */
		enteringClass.studentIDs.push_back(studentID);
		cout << "DONE!" << endl;
		return;
	}
}

void Student::quitClassroom(Class& quittingClass)
{
	if(quittingClass.student_inroom == 0)
	{/* If classroom is empty, that means there is no student */
		cout << "BLOCK! There is no student in the class!" << endl;
	}
	else
	{
		for(unsigned int i = 0; i < quittingClass.studentIDs.size(); i++)
		{
			if(studentID == quittingClass.studentIDs[i])
			{
				quittingClass.studentIDs.erase(quittingClass.studentIDs.begin() + i);
				quittingClass.student_inroom--;/* I decremented the number which holds number of students in the classroom */
				cout << "DONE" << endl;
				return;
			}
		}
		/* If studentID did not pair, that means given student never been in this classroom */
		cout << "BLOCK! Because this student never been in this class!" << endl;
		return;
	}
	
}