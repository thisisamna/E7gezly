#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//array sizes
const int DOC_NUM = 100;
const int PATIENT_NUM=100;
const int DATE_NUM = 100;
const int APPOINT_NUM = 100;

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

//global variables
string username, password;
int lastPatient = 0;
int lastDoc = 0;

//patient functions
int patientLogin();
void patientReg();
void displayPatientMenu(int i);
void makeAppoint(int i);
void editAppoint(int i);
void cancelAppoint(int i);

//doctor functions
int docLogin();
void docReg();
void displayDocMenu(int i);

int main() //start of main
{
	cout << "\n**************************************************\n\n"
		<< "************** Welcome to E7gezly **************\n"
		<< "\n**************************************************\n\n";

	int status;

	menu1: //main menu
	do {

		cout << "Are you a doctor or patient?\n\n"
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
				<<"\n"
				<< "1 \t Login \n"
				<< "2 \t Register\n"
				<< "3 \t Previous menu\n\n"//incomplete 
				<< "Selection: ";

			cin >> selection;

			switch (selection)
			{
			case 1: //login
				int i;
				i = patientLogin();
				if (i != -1)
				{
					displayPatientMenu(i);
				}
				else
					goto menu1;
				break;
			case 2: //register
				patientReg();
				break;
			case 3:
				goto menu1;
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
					goto menu1;
				break;
			case 2:
				docReg();
				break;
			case 3:
				goto menu1;
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

//patient fucntion declarations
void patientReg()
{
	cout << "Enter username: \n";
	cin >> infoPatients[lastPatient].username;

	cout << "Enter password: ";
	cin >> infoPatients[lastPatient].password;


	cout << "Enter name: ";
	cin >> infoPatients[lastPatient].name;


	cout << "Enter age: ";
	cin >> infoPatients[lastPatient].age;

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
void displayPatientMenu(int i)
{
	int selection;
	cout << "What would you like to do?\n\n"
		<< "1 \t Make an appointment \n"
		<< "2 \t Edit an appointment\n\n"
		<< "3 \t Cancel an appointment\n\n"
		<< "Selection: ";
	cin >> selection;
	switch (selection)
	{
		case 1: //make an appointment
			makeAppoint(i);
			break;
		case 2: //edit  an appointment
			editAppoint(i);
			break;
		case 3: // cancel an appointment
			cancelAppoint(i);
			break;
		default:
			break;
	}


}
void makeAppoint(int i)
{
} 
//incomplete
void editAppoint(int i)
{

} 
//incomplete
void cancelAppoint(int i)
{
}
//incomplete

//doc function declarations
void docReg()
{
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