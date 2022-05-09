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
	string age;
} infoPatients[PATIENT_NUM];
struct doc {
	string id;
	string username;
	string password;
	string name;
} infoDocs[DOC_NUM];
struct appoint {
	string index;
	string patientUsername;
	string patientName;
	string docUsername;
	string docName;
	string timeSlot;
	date appointDate;
}infoAppoints[APPOINT_NUM], newAppoint[1];

//global variables
int lastPatient = -1;
int lastDoc = -1;
int lastAppoint = -1;
string timeSlots[5] = { "09:00 - 10:00","10:00 - 11:00","11:00 - 12:00","12:00 - 01:00","01:00 - 02:00" };


//gen functions 
void chooseDate(appoint infoAppoints[], int i);
void display(appoint appointment);
void display(date someDate);

//fstream functions
void loadData(appoint infoAppoints[], patient infoPatients[], doc infoDocs[]);
void saveData(appoint infoAppoints[], patient infoPatients[], doc infoDocs[]);


//patient functions
int patientLogin();
void patientReg();
void editPatientInfo(patient infoPatients[], int patientIndex);
void displayPatientMenu(int i);
void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex);
void patientViewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex);
int selectAppoint(appoint infoAppoints[], patient infoPatients[], int patientIndex);
void editAppoint(appoint infoAppoints[], int appointIndex);
void cancelAppoint(appoint infoAppoints[], int appointIndex);

//doctor functions
int docLogin();
void docReg();
void displayDocMenu(int docIndex);
void editDocInfo(doc infoDocs[], int docIndex);
void docViewAppoints(appoint infoAppoints[], doc infoDocs[], int docIndex);
void addTime();
void removeTime();

int main() //start of main
{
	loadData(infoAppoints, infoPatients, infoDocs);

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

			int docIndex;
			docIndex = docLogin();
			if (docIndex != -1)
			{
				displayDocMenu(docIndex);
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

saveData(infoAppoints, infoPatients, infoDocs);

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
	cout << "Select time: \n";
	for (int i = 0; i < 5; i++) 
		cout << i + 1 << "\t" << timeSlots[i] << "\n";
	cout << "Selection: ";
}

void display(date someDate)
{
	cout << someDate.day << "/" << someDate.month << "/" << someDate.year << "\n";

}
void display(appoint appointment)
{
	cout << "Index:" << appointment.index << "\n";
	cout << "Patient:" << appointment.patientName <<"\n";
	cout << "Doctor:" << appointment.docName << "\n";
	cout << "Date:";
	display(appointment.appointDate);
	cout << "Time: " << appointment.timeSlot <<"\n";
}



//patient fucntion declarations
void patientReg()
{
	lastPatient++;
	cout << "Enter name: ";
	cin >> infoPatients[lastPatient].name;
	cout << "Enter age: ";
	cin >> infoPatients[lastPatient].age;
	//check if username is taken
	tryagain:
	cout << "Enter username: \n";
	string username;
	cin >> username;
	for (int i = 0; i <= lastPatient; i++)
	{
		if (username == infoPatients[i].username)
		{
			cout << "Username taken! Please choose another: ";
			goto tryagain;
		}
	}
	infoPatients[lastPatient].username = username;

	cout << "Enter password: ";
	cin >> infoPatients[lastPatient].password;
}

int patientLogin()
{
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	for (int i = 0; i <=lastPatient; i++)
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
	char choice = 'n';
	do
	{
		cout << "\n**************************************************\n\n";
		cout << "What would you like to do?\n\n"
			<< "1 \t Make an appointment \n"
			<< "2 \t View my appointments \n"
			<< "3 \t Edit an appointment\n"
			<< "4 \t Cancel an appointment\n"
			<< "5 \t Edit personal info\n"
			<< "6 \t Logout\n\n"
			<< "Selection: ";
		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1: //make an appointment
			makeAppoint(infoAppoints, infoDocs, patientIndex);
			break;
		case 2: //view  my appointments
			patientViewAppoints(infoAppoints, infoPatients, patientIndex);
			break;
		case 3: //edit  an appointment
			int appointIndex;
			cout << "Enter the index of the appointmnet would you like to edit: \n";
			appointIndex = selectAppoint(infoAppoints, infoPatients, patientIndex);
			editAppoint(infoAppoints, appointIndex);
			break;
		case 4: // cancel an appointment
			cout << "Enter the index of the appointmnet would you like to cancel: \n";
			appointIndex = selectAppoint(infoAppoints, infoPatients, patientIndex);
			cancelAppoint(infoAppoints, appointIndex);
			break;
		case 5: // edit personal info
			editPatientInfo(infoPatients, patientIndex);
			break;
		case 6: // logout
			cout << "Are you sure you want to log out? (y/n)";
			cin >> choice;
			break;
		default:
			break;
		}

	} while (choice != 'y' &&  choice != 'Y');
}

void editPatientInfo(patient infoPatients[], int patientIndex) 
{
		cout << "\n**************************************************\n\n";
		cout << "Enter your password to continue: ";
		string password;
		cin >> password;
		if (password == infoPatients[patientIndex].password)
		{
			cout << "What would you like to edit?\n\n"
				<< "1 \t Username \n"
				<< "2 \t Password \n" //request old password
				<< "3 \t Name \n"
				<< "4 \t Age\n"
				<< "5 \t Previous menu\n\n" //incomplete
				<< "Selection: ";

			int selection;
			cin >> selection;
			switch (selection)
			{
			case 1: //Username
				cout << "Update username: ";
				cin >> infoPatients[patientIndex].username;
				cout << "Successfully updated!";
				break;
			case 2: //Password
				cout << "Update password: ";
				cin >> infoPatients[patientIndex].password;
				cout << "Successfully updated!";
				break;
			case 3: //Name
				cout << "Update name: ";
				cin >> infoPatients[patientIndex].name;
				cout << "Successfully updated!";
				break;
			case 4: // Age
				cout << "Update age: ";
				cin >> infoPatients[patientIndex].age;
				cout << "Successfully updated!";
				break;
			case 5: //Previous menu
				break;
			default:
				break;
			}
			cout << "Successfully updated! \n";
		}
		else
		{
			cout << "Wrong password--edit failed. \n";
		}

}

void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex)
{
	int selection;
	cout << "Select doctor: \n";
	for (int i = 0; i <= lastDoc; i++)
	{
		cout << i+1 << "\t" << infoDocs[i].name << "\n";
	}

	cout << "\nSelection: ";
	cin >> selection;

	lastAppoint++;

	int i = lastAppoint;
	infoAppoints[i].index = i;
	infoAppoints[i].patientUsername = infoPatients[patientIndex].username;
	infoAppoints[i].patientName = infoPatients[patientIndex].name;
	infoAppoints[i].docUsername = infoDocs[selection-1].username;
	infoAppoints[i].docName = infoDocs[selection - 1].name;
	chooseDate(infoAppoints, i);

	cout << "Select time: \n";
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << "\t" << timeSlots[i] << "\n";
	}
	cout << "Selection: ";
	cin >> selection;
	infoAppoints[i].timeSlot = timeSlots[selection-1];

}
void patientViewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex)
{
	int counter = 1;
	for(int i=0; i<=lastAppoint; i++)
	{ 
		if (infoAppoints[i].patientUsername == infoPatients[patientIndex].username)
		{
			cout << "#" << counter  << "\n";
			display(infoAppoints[i]);
			cout << "\n";
			counter++;
		}
	}
}

int selectAppoint(appoint infoAppoints[], patient infoPatients[], int patientIndex)
{
	int appointIndex;
	patientViewAppoints(infoAppoints, infoPatients, patientIndex);
	cin >> appointIndex;
	return appointIndex;
}
void editAppoint(appoint infoAppoints[], int appointIndex) 
{
	display(infoAppoints[appointIndex]); // dispalay before editing

	cout << "You are editing your appointment's date and time... \n";
		cout << "Enter new date: ";
		chooseDate(newAppoint, 1);

		cout << "Select time: \n";
		for (int i = 0; i < 5; i++)
		{
			cout << i + 1 << "\t" << timeSlots[i] << "\n";
		}
		int selection;
		cout << "Selection: ";
		cin >> selection;
		selection--; // correct array index

		bool available = true;
		
		for (int i = 0; i <= lastAppoint; i++)
		{
			if (newAppoint[1].appointDate.day == infoAppoints[i].appointDate.day)
				if (newAppoint[1].appointDate.month == infoAppoints[i].appointDate.month)
					if (newAppoint[1].appointDate.year == infoAppoints[i].appointDate.year)
						if (newAppoint[1].timeSlot == infoAppoints[i].timeSlot)
							available = false;
		}


		if (available)
		{
			infoAppoints[appointIndex].appointDate.day = newAppoint[1].appointDate.day;
			infoAppoints[appointIndex].appointDate.month = newAppoint[1].appointDate.month;
			infoAppoints[appointIndex].appointDate.year = newAppoint[1].appointDate.year;
			infoAppoints[appointIndex].timeSlot = timeSlots[selection];
			cout << "Updated successfully!";

		}
		else
			cout << "Sorry. The changes you made aren't available.";
	
	display(infoAppoints[appointIndex]); //display after editing
	
} 

void cancelAppoint(appoint infoAppoints[], int appointIndex) 
{
	for (lastAppoint; lastAppoint >= appointIndex; lastAppoint--)
	{
		infoAppoints[lastAppoint - 1] = infoAppoints[lastAppoint];
	}
	lastAppoint--;


}


//doc function declarations
void docReg()
{
	lastDoc++;
	cout << "Enter name: ";
	cin >> infoDocs[lastDoc].name;

	//check if username is taken
tryagain:
	cout << "Enter username: \n";
	string username;
	cin >> username;
	for (int i = 0; i <= lastDoc; i++)
	{
		if (username == infoDocs[i].username)
		{
			cout << "Username taken!\n ";
			goto tryagain;
		}
	}
	infoDocs[lastDoc].username = username;

	cout << "Enter password: ";
	cin >> infoDocs[lastDoc].password;

}

int docLogin()
{
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	for (int i=0; i<=lastDoc; i++)
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
void displayDocMenu(int docIndex)
{
	char choice = 'n';
	do
	{
		cout << "\n**************************************************\n\n";
		cout << "What would you like to do?\n\n"
			<< "1 \t Add available time \n"
			<< "2 \t Remove available time \n"
			<< "3 \t View patients with appointments\n"
			<< "4 \t Edit personal info\n"
			<< "5 \t Logout\n\n"
			<< "Selection: ";
		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1: //Add available time
			addTime();
			break;
		case 2: //Remove available time
			removeTime();
			break;
		case 3: //View Docs with appointments
			docViewAppoints(infoAppoints, infoDocs, docIndex);
			break;
		case 4: // Edit personal info
			editDocInfo(infoDocs, docIndex);
			break;
		case 5: // logout
			cout << "Are you sure you want to log out? (y/n)";
			cin >> choice;
			break;
		default:
			break;
		}

	} while (choice != 'y' && choice != 'Y');
}

void editDocInfo(doc infoDocs[], int docIndex) 
{

	cout << "\n**************************************************\n\n";
	cout << "Enter your password to continue: ";
	string password;
	cin >> password;
	if (password == infoDocs[docIndex].password)
	{
		cout << "What would you like to edit?\n\n"
			<< "1 \t Username \n"
			<< "2 \t Password \n" //request old password
			<< "3 \t Name \n"
			<< "4 \t Previous menu\n\n" //incomplete
			<< "Selection: ";

		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1: //Username
			cout << "Update username: ";
			cin >> infoDocs[docIndex].username;
			break;
		case 2: //Password
			cout << "Update password: ";
			cin >> infoDocs[docIndex].password;
			break;
		case 3: //Name
			cout << "Update name: ";
			cin >> infoDocs[docIndex].name;
			break;
		case 4: //Previous menu
			break;
		default:
			break;
		}
		cout << "Successfully updated! \n";
	}
	else
	{
		cout << "Wrong password--edit failed. \n";
	}
	
}

void docViewAppoints(appoint infoAppoints[], doc infoDocs[], int docIndex) 
{
	for (int i = 0; i <= lastAppoint; i++)
	{
		int counter = 1;
		if (infoAppoints[i].docUsername == infoDocs[docIndex].username)
		{
			cout << "#" << counter << "\n";
			display(infoAppoints[i]);
			cout << "\n";
			counter++;
		}
	}
}
void addTime() //F6
{

}
void removeTime() //F7
{

}

void loadData(appoint infoAppoints[], patient infoPatients[], doc infoDocs[])
{
	ifstream infoFile("info.txt");
	if (infoFile.is_open())
	{
		infoFile >> lastPatient >> lastDoc >> lastAppoint;
		infoFile.close();
	}
	else
		cout << "Unable to open info file";

	int i;
	string line;

	ifstream patientFile("patients.txt");
	i = -1;
	if (patientFile.is_open())
	{
		while (getline(patientFile, line, '\t'))
		{
			i++;
			infoPatients[i].id=i; //getline ignores first character so i dealt with it alone

			patientFile 
				>> infoPatients[i].name
				>> infoPatients[i].age
				>> infoPatients[i].username
				>> infoPatients[i].password;
		}
		patientFile.close();
	}
	else 
		cout << "Unable to open patient file";

	ifstream docFile("doctors.txt");
	i = -1;
	if (docFile.is_open())
	{
		while (getline(docFile, line, '\t'))
		{
			i++;
			infoDocs[i].id = i; //getline ignores first character so i dealt with it alone

			docFile
				>> infoDocs[i].name
				>> infoDocs[i].username
				>> infoDocs[i].password;
		}
		docFile.close();
	}
	else
		cout << "Unable to open doc file";

	ifstream appointFile("appointments.txt");
	i = -1;
	if (appointFile.is_open())
	{
		while (getline(appointFile, line, '\t'))
		{
			i++;
			infoAppoints[i].index = i; //getline ignores first character so i dealt with it alone

			appointFile
				>> infoAppoints[i].patientUsername
				>> infoAppoints[i].docUsername
				>> infoAppoints[i].timeSlot
				>> infoAppoints[i].appointDate.day
				>> infoAppoints[i].appointDate.month 
				>> infoAppoints[i].appointDate.year;
		}
		appointFile.close();
	}
	else
		cout << "Unable to open doctor file";
	
}


void saveData(appoint infoAppoints[], patient infoPatients[], doc infoDocs[])
{
	ofstream infoFile;
	infoFile.open("info.txt");
	infoFile << lastPatient << endl
		<< lastDoc << endl
		<< lastAppoint << endl;
	infoFile.close();

	ofstream patientFile;
	patientFile.open("patients.txt");
	for (int i = 0; i <= lastPatient; i++)
	{
		patientFile << infoPatients[i].id << "\t"
			<< infoPatients[i].name << "\t"
			<< infoPatients[i].age << "\t"
			<< infoPatients[i].username << "\t"
			<< infoPatients[i].password << "\n";
	}
	patientFile.close();

	ofstream docFile;
	docFile.open("doctors.txt");
	for (int i = 0; i <= lastDoc; i++)
	{
		docFile << infoDocs[i].id << "\t"
			<< infoDocs[i].name << "\t"
			<< infoDocs[i].username << "\t"
			<< infoDocs[i].password << "\n";
	}
	docFile.close();

	ofstream appointFile;
	appointFile.open("appointments.txt");
	for (int i = 0; i <= lastAppoint; i++)
	{
		appointFile << infoAppoints[i].index << "\t"
			<< infoAppoints[i].patientUsername << "\t"
			<< infoAppoints[i].docUsername << "\t"
			<< infoAppoints[i].timeSlot << "\t"
			<< infoAppoints[i].appointDate.day << " "
			<< infoAppoints[i].appointDate.month << " "
			<< infoAppoints[i].appointDate.year << "\n";
	}
	appointFile.close();
}
