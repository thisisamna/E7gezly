#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//array sizes
const int DOC_NUM = 10;
const int PATIENT_NUM=10;
const int DATE_NUM = 10;
const int APPOINT_NUM = 10;


//structure types
struct date {
	int day;
	int month;
	int year;
}dates[DATE_NUM];
struct patient {
	string id;
	string username;
	string password;
	string name;
	int age;
} infoPatients[PATIENT_NUM];
struct doc {
	string id;
	string username;
	string password;
	string name;
} infoDocs[DOC_NUM];
struct appoint {
	patient appointPatient;
	doc appointDoc;
	date appointDate;
	string timeSlot;
}infoAppoints[APPOINT_NUM];

//global variables
string username, password;
int lastPatient = 0;
int lastDoc = 0;
int lastAppoint = 0;

//gen functions 
void chooseDate(appoint infoAppoints[], int i);
void chooseTimeSLot(appoint ainfoAppointsrr[], int i);
void display(appoint appointment);
void display(date someDate);

//patient functions
int patientLogin();
void patientReg();
void displayPatientMenu(int i);
void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex);
void viewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex);
void editAppoint(appoint infoAppoints[], int patientIndex);
void cancelAppoint(appoint infoAppoints[], int patientIndex);

//doctor functions
int docLogin();
void docReg();
void displayDocMenu(int i);


int main() //start of main
{
	menu1:
	cout << "\n**************************************************\n\n"
		<< "************** Welcome to E7gezly **************\n"
		<< "\n**************************************************\n\n";

	int status;

	menu2: //main menu
do {

	cout << "Are you a patient or doctor?\n\n"
		<< "1 \t Patient \n"
		<< "2 \t Doctor\n\n"
		<< "Selection: ";

	int userMode;
	cin >> userMode;
	int selection;


	switch (userMode)
	{
	case 1: //patient
		cout
			<< "\n"
			<< "1 \t Login \n"
			<< "2 \t Register\n"
			<< "3 \t Previous menu\n\n"//incomplete 
			<< "Selection: ";

		cin >> selection;

		switch (selection)
		{
		case 1: //login
			int patientIndex;
			patientIndex = patientLogin();
			if (patientIndex != -1)
			{
				displayPatientMenu(patientIndex);
				goto menu1;
			}
			else
				goto menu2;
			break;
		case 2: //register
			patientReg();
			break;
		case 3:
			goto menu2;
			break;
		default:
			break;
		}
		break;

	case 2: //doctor
		cout
			<< "\n"
			<< "1 \t Login \n"
			<< "2 \t Register\n"
			<< "3 \t Previos menu\n\n"//incomplete 
			<< "Selection: ";

		cin >> selection;

		switch (selection)
		{
		case 1: //doc login

			int i;
			i = docLogin();
			if (i != -1)
			{
				displayDocMenu(i);
			}
			else
				goto menu2;
			break;
		case 2:
			docReg();
			break;
		case 3:
			goto menu2;
		default:
			break;
		}
		break;

	default:
		cout << "Please enter a valid choice!";
	}
	//exit login menu
	cout << "\n**************************************************\n\n"
		<< "1 \t Main menu \n"
		<< "2 \t Exit \n\n"
		<< "Selection: ";

	cin >> status;

} while (status != 2);
//exit main menu
cout << "\n******** Thank you for using E7gezly! ********\n";

return 0;
} // end of main

//gen function declarations
// 
void chooseDate(appoint infoAppoints[], int i)
{
cout << "Please enter date: \n"
	 <<"Day: ";
cin >> infoAppoints[i].appointDate.day;
cout << "Month: ";
cin >> infoAppoints[i].appointDate.month;
cout << "Year: ";
cin >> infoAppoints[i].appointDate.year;
}
void chooseTimeSLot(appoint infoAppoints[], int i)
{

}

void display(date someDate)
{
	cout << someDate.day << "/" << someDate.month << "/" << someDate.year << "\n";

}
void display(appoint appointment)
{
	cout << "Patient:" << appointment.appointPatient.name;
	cout << "Doctor:" << appointment.appointDoc.name;
	cout << "Date:";
	display(appointment.appointDate);
	cout << "Time: " << appointment.timeSlot;
}



//patient fucntion declarations
void patientReg()
{
	cout << "Enter name: ";
	cin >> infoPatients[lastPatient].name;
	cout << "Enter age: ";
	cin >> infoPatients[lastPatient].age;
	cout << "Enter username: \n";
	cin >> infoPatients[lastPatient].username;
	cout << "Enter password: ";
	cin >> infoPatients[lastPatient].password;


	lastPatient++;
}
int patientLogin()
{
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	for (int i = 0; i < PATIENT_NUM; i++)
	{
		if (username == infoPatients[i].username)
		{
			if (password == infoPatients[i].password)
			{
				cout << "Hello, " << infoPatients[i].name << "! \n\n";
				return i;
			}
		}

	}
	cout << "\n Incorrect username or password! Please try again. \n\n";
	return -1;
}
void displayPatientMenu(int patientIndex)
{
	char choice = 'y';
	do
	{
		int selection;
		cout << "What would you like to do?\n\n"
			<< "1 \t Make an appointment \n"
			<< "2 \t View my appointments \n"
			<< "3 \t Edit an appointment\n\n"
			<< "4 \t Cancel an appointment\n\n"
			<< "5 \t Logout\n\n"
			<< "Selection: ";
		cin >> selection;
		switch (selection)
		{
		case 1: //make an appointment
			makeAppoint(infoAppoints, infoDocs, patientIndex);
			break;
		case 2: //view  my appointments
			viewAppoints(infoAppoints, infoPatients, patientIndex);
			break;
		case 3: //edit  an appointment
			editAppoint(infoAppoints, patientIndex);
			break;
		case 4: // cancel an appointment
			cancelAppoint(infoAppoints, patientIndex);
			break;
		case 5: // logout
			cout << "Are you sure you want to log out? (y/n)";
			cin >> choice;
			break;
		default:
			break;
		}

	} while (choice != 'y' &&  choice != 'Y');
}
void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex)
{
	int selection;
	cout << "Select doctor: \n\n";
	for (int i = 0; i < lastDoc; i++)
	{
		cout << i + 1 << "\t" << infoDocs[i].name << "\n";
	}

		cout << "Selection: ";
	cin >> selection;

	int i = lastAppoint;
	infoAppoints[i].appointPatient = infoPatients[patientIndex];
	infoAppoints[i].appointDoc = infoDocs[selection-1];
	chooseDate(infoAppoints, i);
	chooseTimeSLot(infoAppoints, i);
	lastAppoint++;
	cout << "\n Appointment booked successfully!";
} 
void viewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex)
{
	for(int i=0; i<=lastAppoint; i++)
	{ 
		if (infoAppoints[i].appointPatient.id == infoPatients[patientIndex].id)
		{
			cout << "#" << i + 1 << "\n";
			display(infoAppoints[i]);
			cout << "\n";
		}
	}
}
void editAppoint(appoint infoAppoints[], int patientIndex)
{

} 
//incomplete
void cancelAppoint(appoint infoAppoints[], int patientIndex)
{
}
//incomplete

//doc function declarations
void docReg()
{

	cout << "Enter name: ";
	cin >> infoDocs[lastDoc].name;

	cout << "Enter username: \n";
	cin >> infoDocs[lastDoc].username;

	cout << "Enter password: ";
	cin >> infoDocs[lastDoc].password;

	lastDoc++;
}
int docLogin()
{
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	for (int i=0; i<DOC_NUM; i++)
	{
		if (username == infoDocs[i].username)
		{
			if (password == infoDocs[i].password)
				cout << "Hello, " << infoDocs[i].name <<"! \n\n";
				return i;
		}

	}
	cout << "\n Incorrect username or password! Please try again. \n\n";
	return -1;
}
void displayDocMenu(int i)
{

}

/*
void patientReg()
{
	fstream patient_file("Patient_data.txt", ios::app);

	cout << "Enter username: \n";
	cin >> username; 
	patient_file << username << " ";

	cout << "Enter password: ";
	cin >> password;
	patient_file << password << endl;

	patient_file.close();
}

bool patientLogin() 
{
	string name, pass;
	while (true)
	{
		fstream patient_file("Patient_data.txt", ios::in);

		cout << "Enter username: ";
		cin >> name;

		cout << "Enter password: ";
		cin >> pass;

		while (patient_file) 
		{
			patient_file >> username;
			patient_file >> password;

			if (name.compare(username) == 0) 
			{
				if (pass.compare(password) == 0) 
				{
					cout << "Logging successful ........ \n";
					return true;
				}
			}
		}
		cout << "Invalid username or password! Please try again.\n";
		continue;
	}
}

void docReg()
{
	fstream doc_file("Doc_data.txt", ios::app);

	cout << "Enter username: \n";
	cin >> username; 
	doc_file << username << " ";

	cout << "Enter password: ";
	cin >> password;
	doc_file << password << endl;

	doc_file.close();
}

bool docLogin() 
{
	string name, pass;

	while (true)
	{
		fstream doc_file("Doc_data.txt", ios::in);
		cout << "Enter username: ";
		cin >> name;
		cout << "Enter password: ";
		cin >> pass;
		while (doc_file) 
		{
			doc_file >> username;
			doc_file >> password;
			if (name.compare(username) == 0) 
			{
				if (pass.compare(password) == 0) 
				{
					cout << "Logging successful ........ \n\n";
					return true;
				}
			}
		}
		cout << "Invalid username or password! Please try again.\n\n";
		continue;
	}
}

*/
