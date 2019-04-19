/*     Ahmet Hilmi Berber    */
/*        171044027          */
/*       CSE241 HW02         */
/* 	  TEST FILE	     */

/* NOTE: PLEASE COMPILE THIS PROGRAM WITH (-std=c++11) COMMAND */
/* FOR EX: g++ -std=c++11 test.cpp -o output */

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
void trimmer(string str);
bool isOverlap(int startTime_std, int finishTime_std, int startTime_crs, int finishTime_crs);
int m_abs(int num);


int main()
{
	vector<Student> wholeStudents;
	vector<Course> wholeCourses;
	vector<Class> wholeClasses;
	//////////////////////
	Course initCourse;
	initCourse.courseID = 1, initCourse.courseName = "ROBOTICS", initCourse.courseCode =  154, initCourse.courseCredit = 5, initCourse.courseHours = 3, initCourse.courseStartDay.push_back("MONDAY"), initCourse.courseStartDay.push_back("FRIDAY"), initCourse.courseStartTime.push_back(9), initCourse.courseStartTime.push_back(15), initCourse.courseFinishTime.push_back(10), initCourse.courseFinishTime.push_back(17);
	wholeCourses.push_back(initCourse);
	initCourse.courseID = 2, initCourse.courseName = "MECHANICS", initCourse.courseCode =  182, initCourse.courseCredit = 4, initCourse.courseHours = 5, initCourse.courseStartDay.push_back("WEDNESDAY"), initCourse.courseStartDay.push_back("SATURDAY"), initCourse.courseStartTime.push_back(10), initCourse.courseStartTime.push_back(13), initCourse.courseFinishTime.push_back(13), initCourse.courseFinishTime.push_back(15);
	wholeCourses.push_back(initCourse);
	initCourse.courseID = 3, initCourse.courseName = "AI", initCourse.courseCode =  911, initCourse.courseCredit = 8, initCourse.courseHours = 8, initCourse.courseStartDay.push_back("TUESDAY"), initCourse.courseStartDay.push_back("THRUSDAY"), initCourse.courseStartDay.push_back("SUNDAY"); initCourse.courseStartTime.push_back(9), initCourse.courseStartTime.push_back(10), initCourse.courseStartTime.push_back(11), initCourse.courseFinishTime.push_back(12), initCourse.courseFinishTime.push_back(13), initCourse.courseFinishTime.push_back(13);
	wholeCourses.push_back(initCourse);
	numberOfCourses = 3;
	///////////////////////
	Class initClass;
	initClass.classID = 1, initClass.classNo = "E105", initClass.student_inroom = 0, initClass.classCapacity = 20;
	wholeClasses.push_back(initClass);
	initClass.classID = 2, initClass.classNo = "D102", initClass.student_inroom = 0, initClass.classCapacity = 25;
	wholeClasses.push_back(initClass);
	numberOfClassrooms = 2;
	/////////////////////////
	Student tempStd("BEKIR", "OZTURK", 32012, 4, FOURTHCLASSCREDITRIGHT);wholeStudents.push_back(tempStd);
	Student tempStdd("HAKAN", "SENER", 12366, 2, SECONDCLASSCREDITRIGHT);wholeStudents.push_back(tempStdd);
	numberOfStudents = 2;
	//////////////////////////
	/* ------ TESTING ------ */
	cout << "FIRST OF ALL, THERE IS 2 STUDENTS OF OUR SYSTEM" << endl;
	cout << "FIRST ONE: " << wholeStudents[0].extractSchedule() << endl;
	cout << "SECOND ONE: " << wholeStudents[1].extractSchedule() << endl << endl;
	//////////////////////////
	cout << "FIRST TEST INITIALIZING FOR isTxt FUNCTION.." << endl;
	cout << "inputs = " << "ahmet.txt" << " / " << "ahmet" << " / " << "ahmet-berber.txt" << endl;
	cout << "outputs = " << isTxt("ahmet.txt") << " / " << isTxt("ahmet") << " / " << isTxt("ahmet-berber.txt") << endl << endl;;
	/////////////////////////////
	cout << "SECOND TEST INITIALIZING FOR trimmer FUNCTION.." << endl;	
	cout << "inputs = " << "FRIDAY_11-13,SUNDAY_15-17" << " / " << "WEDNESDAY_10-13,SATURDAY_16-20" << " / " << "TUESDAY_15-22,MONDAY_20-24" << endl;
	cout << "outputs = "; trimmer("FRIDAY_11-13,SUNDAY_15-17"); cout << " / "; trimmer("WEDNESDAY_10-13,SATURDAY_16-20"); cout << " / "; trimmer("TUESDAY_15-22,MONDAY_20-24"); cout << endl << endl;
	/////////////////////////////
	cout << "THIRD TEST INITIALIZING FOR isOverlap FUNCTION.." << endl;
	cout << "inputs = " << "11-15,12-13" << " / " << "12-16,14-16" << " / " << "12-13,14-17" << endl;
	cout << "outputs = " << isOverlap(11,15,12,13) << " / " << isOverlap(12,16,14,16) << " / " << isOverlap(12,13,14,17) << endl << endl;
	///////////////////////////
	cout << "FIFTH TEST INITIALIZING FOR enrollCourse and extractSchedule FUNCTION.." << endl;
	cout << "inputs = " << "ROBOTICS COURSE TAKEN FOR BEKIR" << " / " << "AI COURSE TAKEN FOR HAKAN" << " / " << "AGAIN AI COURSE TAKEN FOR HAKAN" << endl;
	cout << "enrollment outputs = " << endl; wholeStudents[0].enrollCourse(wholeCourses[0]); wholeStudents[1].enrollCourse(wholeCourses[2]); wholeStudents[1].enrollCourse(wholeCourses[2]);
	cout << "schedule outputs = "; cout << wholeStudents[0].extractSchedule(); cout << " / " << wholeStudents[1].extractSchedule(); cout << endl << endl;
	///////////////////////////
	cout << "FIFTH TEST INITIALIZING FOR disenrollCourse and extract Schedule FUNCTION.." << endl;
	cout << "inputs = " << "ROBOTICS COURSE DROP FOR BEKIR" << " / " << "AI COURSE DROP FOR HAKAN" << " / " << "AGAIN AI COURSE DROP FOR HAKAN" << endl;
	cout << "disenrollment outputs = " << endl; wholeStudents[0].disenrollCourse(wholeCourses[0]); wholeStudents[1].disenrollCourse(wholeCourses[2]); wholeStudents[1].disenrollCourse(wholeCourses[2]);
	cout << "schedule outputs = "; cout << wholeStudents[0].extractSchedule(); cout << " / " << wholeStudents[1].extractSchedule(); cout << endl << endl;
	////////////////////////////
	cout << "FOURTH TEST INITIALIZING FOR isAlreadyTaken FUNCTION.." << endl;
	cout << "inputs = " << "ROBOTICS COURSE TAKEN FOR BEKIR, CHECKING ROBOTICS" << " / " << "AI COURSE TAKEN FOR HAKAN, CHECKING MECHANICS" << endl;
	wholeStudents[0].enrollCourse(wholeCourses[0]), wholeStudents[1].enrollCourse(wholeCourses[2]);
	cout << "outputs = " << wholeStudents[0].isAlreadyTakenCourse(1) << " / " << wholeStudents[1].isAlreadyTakenCourse(2) << endl << endl;
	///////////////////////////
	cout << "FIFTH TEST INITIALIZING FOR enterClassroom FUNCTION.." << endl;
	cout << "inputs = " << "ENTER BEKIR AT FIRST CLASSROOM" << " / " << "AGAIN ENTER BEKIR AT FIRST CLASSROOM" << endl;
	cout << "outputs = " << endl; wholeStudents[0].enterClassroom(wholeClasses[0]); wholeStudents[0].enterClassroom(wholeClasses[0]); cout << endl << endl;
	///////////////////////////
	cout << "SIXTH TEST INITIALIZING FOR quitClassroom FUNCTION.." << endl;
	cout << "inputs = " << "QUIT BEKIR AT FIRST CLASSROOM" << " / " << "AGAIN QUIT BEKIR AT FIRST CLASSROOM" << endl;
	cout << "outputs = " << endl; wholeStudents[0].quitClassroom(wholeClasses[0]); wholeStudents[0].quitClassroom(wholeClasses[0]); cout << endl << endl;
	///////////////////////////
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
void trimmer(string str)
{
	int i = 0, j = 0, k = 0, m = 0, dayCounter = 0;
	string tempStartDay, tempStartTime , tempFinishTime;
	while(str[i] != ',' && i != str.length() + 1)
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
		while(str[i] != ',' && i!=str.length())
		{
			tempFinishTime[k] = str[i];
			i++, k++;
		}
		dayCounter++;
		cout << tempStartDay << ": " << tempStartTime << "-" << tempFinishTime << " ";
		tempStartDay.clear(),tempStartTime .clear(),tempFinishTime.clear();
		i++, j = 0, k = 0;
	}
}
/* This function checks the overlap situation between 2 courses */
bool isOverlap(int startTime_std, int finishTime_std, int startTime_crs, int finishTime_crs)
{
	if((startTime_std == startTime_crs) && (finishTime_std != finishTime_crs))
	{
		if(m_abs(finishTime_std - finishTime_crs) > 1)
			return true;
	}
	else if((startTime_std != startTime_crs) && (finishTime_std == finishTime_crs))
	{
		if(m_abs(startTime_std - startTime_crs) > 1)
			return true;
	}
	else if((startTime_std == startTime_crs) && (finishTime_std == finishTime_crs))
	{
		if(m_abs(startTime_std - finishTime_std) > 1)
			return true;
	}
	else
	{
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
			if(enteringClass.studentIDs[i] == studentID)
			{
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