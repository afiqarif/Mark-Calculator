#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//	Function Prototype------------------------------------------------------------
//	File Processing
void Menu();
bool openReadFile(ifstream&);
string* readFile(ifstream&);
void writeFile(ofstream&, double, char, int);

//	Calculation
double Weightage(double, int);
double OverallMark(double, double, double, double);
double OverallPercentage(double, int);
char DetermineGrade(double);

//	UserInput
int TotalStudent();
int TotalMark();
int* Percentage();

int main()
{
	//Initialization
	ifstream fin;
	ofstream fout;
	bool isOpen, Stop;
	char isCorrect;
	int totalStudent, totalMark;
	int per100;
	int* percent;
	string* studentDataStr;

	isOpen = openReadFile(fin);

	if(isOpen)
	{
		Menu();
		cout << "Setting is empty, filling...\n\n";
		Stop = 0;

		while(!Stop)	//Filling the setting
		{
			totalMark = TotalMark();
			totalStudent = TotalStudent();
			percent = Percentage();
			cout << "\nIs the setting correct? Y or N. ";
			cin >> isCorrect;
			cout << '\n';

			switch(isCorrect)		//Checking if setting is correct
			{
				case 'y':
				case 'Y':
					Stop = 1;	//Exit requirement met.
					break;
				case 'n':
				case 'N':
					break;
			}
		}

		double 	MatricNo[totalStudent], studentData[totalStudent][8],
				modifiedStudentData[totalStudent][11];

		double 	overallMark[totalStudent], perHundred[totalStudent];
		char 	Grade[totalStudent];

		//	Read the file into array
		for(int i = -1; i < totalStudent; i++) // i = -1 to skip the first line of string
		{
			studentDataStr = readFile(fin);
			if(i >= 0)
			{
				MatricNo[i] = stoi(studentDataStr[0]);
				for(int j = 0; j < 8; j += 2)
					studentData[i][j] = stoi(studentDataStr[(j/2)+1]);
			}
		}

		fin.close();

		for(int j = 0; j < 8; j += 2)	//	Calculating the total coursework mark for each student
		{
			per100 = 0;
			switch (j)
			{
				case 0: 	//	Weightage for Test 1
					per100 = percent[0];
					break;

				case 2: 	//	Weightage for Test 2
					per100 = percent[1];
					break;

				case 4: 	//	Weightage for Assignment 1
					per100 = percent[2];
					break;

				case 6: 	//	Weightage for Assignment 2
					per100 = percent[3];
					break;
			}

			for(int i = 0; i < totalStudent; i++)
				studentData[i][j+1] = Weightage(studentData[i][j], per100);
		}

		for(int i = 0; i < totalStudent; i++)		//	Determine student Grade
			Grade[i] = DetermineGrade(perHundred[i]);

		for(int i = 0; i < totalStudent; i++)		//	Combining all array into one array.
		{
			modifiedStudentData[i][0] = MatricNo[i]; 		//	Insert Matric number

			for(int k = 0; k < 8; k++) 		//	Insert test and Assignment with its respective weightage
				modifiedStudentData[i][k+1] = studentData[i][k];

			modifiedStudentData[i][9] = OverallMark(studentData[i][1], studentData[i][3], studentData[i][5], studentData[i][7]);	//	Calculate overall CW mark
			modifiedStudentData[i][10] = OverallPercentage(modifiedStudentData[i][9], totalMark);	//	Calculating overall percentage
			Grade[i] = DetermineGrade(modifiedStudentData[i][10]);		//	Calculate grade
		}

		fout.open("CPT111_CWMarks_Output.txt");

		fout << "Matric Number,"
			 << "Test 1,Test1_Weightage,Test 2,Test2_Weightage,"
			 << "Assignment 1,Assignment1_Weightage,Assignment 2,Assignment2_Weightage,"
			 << "TotalCW,Over 100,Grade\n";

		for(int i = 0; i < totalStudent; i++)	//	Writing to output file
		{
			for(int j = 0; j < 12; j++)
			{
				if(j == 0)
					writeFile(fout, MatricNo[i], Grade[i], j);

				else
					writeFile(fout, modifiedStudentData[i][j], Grade[i], j);
			}
		}

		fout.close();
		cout << "\nCreating file..." << endl;
		cout << "\n\nFile created successfully.";
	}

	else
		cout << "ERROR!\n";

	return 0;
}



//	Function Definition-----------------------------------------------------------
//	File Processing

//	This function will show the menu.
void Menu()
{
	cout << setw(60) << setfill('=') << '\n';
	cout << '|' << setw(37) << setfill(' ') << "Mark Calculator" << setw(22) << setfill(' ') << "|\n";
	cout << setw(60) << setfill('=') << '\n';
}

bool openReadFile(ifstream& fin)
{
	fin.open("CPT111_CWMarks.txt");
	if(fin.is_open())
		return true;
	else
		return false;
}

string* readFile(ifstream& fin)
{
	static string stringStudentData[5];
	for(int i = 0; i < 5; i++)
	{
		if(((i+1) % 5) != 0)
			getline(fin, stringStudentData[i], ',');

		else if(((i+1) % 5) == 0)
			getline(fin, stringStudentData[i]);
	}
	return stringStudentData;
}

void writeFile(ofstream& fout, double Val, char ch, int counter)
{
	switch (counter)
	{
		case 0:
		case 1:
		case 3:
		case 5:
		case 7:
			fout << setprecision(0) << fixed << Val << ',';
			break;

		case 2:
		case 4:
		case 6:
		case 8:
		case 9:
			fout << setprecision(2) << fixed << Val << ',';
			break;

		case 10:
			fout << setprecision(1) << fixed << Val << ',';
			break;

		case 11:
			fout << ch << endl;
	}
}

//	Calculation

double Weightage(double scoreMark, int rate)
{
	return (scoreMark * (rate / 100.00));
}

double OverallPercentage(double totalScore, int maxScore)
{
	return (totalScore / maxScore) * 100;
}

double OverallMark(double a, double b, double c, double d)
{
	return a + b + c + d;
}

char DetermineGrade(double overHundred)
{
	char grade;

	if(overHundred < 50)
		grade = 'F';

	else if(overHundred < 60)
		grade = 'D';

	else if(overHundred < 70)
		grade = 'C';

	else if(overHundred < 80)
		grade = 'B';

	else if(overHundred >= 80)
		grade = 'A';

	return grade;
}

//	UserInput

int TotalStudent()
{
	int totalStudent;
	cout << "Enter the number of student: ";
	cin >> totalStudent;

	return totalStudent;
}

int TotalMark()
{
	int totalMark;
	cout << "Enter the total coursework mark: ";
	cin >> totalMark;

	return totalMark;
}

int* Percentage()
{
	static int percent[4];
	cout << "Enter the percentage for:\n";
	cout << "1. Test 1: ";
	cin >> percent[0];
	cout << "2. Test 2: ";
	cin >> percent[1];
	cout << "3. Assignment 1: ";
	cin >> percent[2];
	cout << "4. Assignment 2: ";
	cin >> percent[3];

	return percent;
}
