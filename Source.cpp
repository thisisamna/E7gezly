#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//x
//array sizes
const int DOC_NUM = 10;
const int PATIENT_NUM = 10;
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
int lastPatient = 1;
int lastDoc = 1;
int lastAppoint = 1;
string timeSlots[5] = { "09:00 - 10:00","10:00 - 11:00","11:00 - 12:00","12:00 - 01:00","01:00 - 02:00" };
string extraTime[4] = { "02:00 - 03:00", "03:00 - 04:00", "04:00 - 05:00", "05:00 - 06:00" };
string timeCombined[9] = { "     " ,"     " ,"     " ,"     " ,"     " ,"     " ,"     " ,"     " ,"     " }; //to combine timeslots & extraTime;
bool chosenTime[4] = { false, false, false, false }; // default to false / dont display to patient unless its true;


//gen functions 
void chooseDate(appoint infoAppoints[], int i);
void display(appoint appointment);
void display(date someDate);
void displayTime(); // for loop to dispaly timeslots

//patient functions
int patientLogin();
void patientReg();
void editPatientInfo(patient infoPatients[], int patientIndex);
void displayPatientMenu(int i);
void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex);
void patientViewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex);
void editAppoint(appoint infoAppoints[], int patientIndex);
void cancelAppoint(appoint infoAppoints[], int patientIndex);
void displayTimePatient(); // dispaly time to patient (time slots and extraTime)

//doctor functions
int docLogin();
void docReg();
void displayDocMenu(int docIndex);
void editDocInfo(doc infoDocs[], int docIndex);
void docViewAppoints(appoint infoAppoints[], doc infoDocs[], int docIndex);
void displayExtraTimesDr(); // display extraTime to doctor ONLY; to add time
void addTime();
void removeTime();

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

	return 0;
} // end of main

//gen function declarations
//
void displayTime() {
	for (int i = 0; i < 5; i++)
		cout << i + 1 << "\t" << timeSlots[i] << "\n";
}
void chooseDate(appoint infoAppoints[], int i)
{
	cout << "Please enter date: \n"
		<< "Day: ";
	cin >> infoAppoints[i].appointDate.day;
	cout << "Month: ";
	cin >> infoAppoints[i].appointDate.month;
	cout << "Year: ";
	cin >> infoAppoints[i].appointDate.year;
}
void chooseTimeSLot(appoint infoAppoints[], int i)
{
	cout << "Select time: \n";
	displayTime();
	cout << "Selection: ";
}
void display(date someDate)
{
	cout << someDate.day << "/" << someDate.month << "/" << someDate.year << "\n";

}
void display(appoint appointment) //display info
{
	cout << "Patient:" << appointment.appointPatient.name << "\n";
	cout << "Doctor:" << appointment.appointDoc.name << "\n";
	cout << "Date:";
	display(appointment.appointDate);
	cout << "Time: " << appointment.timeSlot << "\n";
}



//patient fucntion declarations
void patientReg()
{
	cout << "Enter name: ";
	cin >> infoPatients[lastPatient].name;
	cout << "Enter age: ";
	cin >> infoPatients[lastPatient].age;
	cout << "Enter username: ";
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

	for (int i = 1; i < PATIENT_NUM; i++)
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
			<< "5 \t Edit personal info\n\n"
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
			editAppoint(infoAppoints, patientIndex);
			break;
		case 4: // cancel an appointment
			cancelAppoint(infoAppoints, patientIndex);
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

	} while (choice != 'y' && choice != 'Y');
}
void editPatientInfo(patient infoPatients[], int patientIndex) // F1 
{
}
void makeAppoint(appoint infoAppoints[], doc infoDocs[], int patientIndex)
{
	int selection;
	cout << "Select doctor: \n";
	for (int i = 1; i < lastDoc; i++)
	{
		cout << i << "\t" << infoDocs[i].name << "\n";
	}

	cout << "\nSelection: ";
	cin >> selection;

	int i = lastAppoint;
	infoAppoints[i].appointPatient = infoPatients[patientIndex];
	infoAppoints[i].appointDoc = infoDocs[selection - 1];
	chooseDate(infoAppoints, i);

	cout << "Select time: \n";
	displayTimePatient(); // the only change in this function;
	cout << "Selection: ";
	cin >> selection;
	selection--;

	infoAppoints[i].timeSlot = timeCombined[selection];
	lastAppoint++;

}
void displayTimePatient() // to display removed and added time;
{
	int e = 1; //for extra time // i forgot whyy lol but lets keep it 1 for now :)

	for (int i = 0; i < 5; i++) {
		if (timeSlots[i] == "     ") { 
			break;
		}
		else {
			cout << i + 1 << "\t" << timeSlots[i] << "\n";
			timeCombined[e-1] = timeSlots[i]; // e-1 to start from zero
			e++;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (chosenTime[i]) { // chosen time is true when dr add time;
			if (extraTime[i] == "     ")
				break;
			else {
				timeCombined[e-1] = extraTime[i];
				cout << e++ << "\t" << extraTime[i] << "\n";
			}
		}
	}

	/*cout << "\nThis is for checking: \n";
	for (int m = 0; m < 9; m++) {
		cout << m + 1 << "\t" << timeCombined[m] << "\n";
	}*/

	
}
void patientViewAppoints(appoint infoAppoints[], patient infoPatients[], int patientIndex)
{
	for (int i = 1; i <= lastAppoint; i++)
	{
		if (infoAppoints[i].appointPatient.id == infoPatients[patientIndex].id)
		{
			cout << "#" << i << "\n";
			display(infoAppoints[i]);
			cout << "\n";
		}
	}
}
void editAppoint(appoint infoAppoints[], int patientIndex) //F4
{
}
void cancelAppoint(appoint infoAppoints[], int patientIndex) //F5
{
	for (lastAppoint; lastAppoint >= patientIndex; lastAppoint--) {
		infoAppoints[lastAppoint] = infoAppoints[lastAppoint - 1];
	}
	lastAppoint--;

	// to check
	for (int j = 0; j <= lastAppoint; j++) {
		for (int i = 0; i <= lastAppoint; i++) {
			{
				cout << "#" << i << "\n";
				display(infoAppoints[i]);
				cout << "\t";
			}
		}
	}
}


//doc function declarations
void docReg()
{

	cout << "Enter name: ";
	cin >> infoDocs[lastDoc].name;

	cout << "Enter username: ";
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

	for (int i = 0; i < DOC_NUM; i++)
	{
		if (username == infoDocs[i].username)
		{
			if (password == infoDocs[i].password)
				cout << "Hello, " << infoDocs[i].name << "! \n\n";
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
		case 3: //View patients with appointments
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
void editDocInfo(doc infoDocs[], int docIndex) //F2
{

}
void docViewAppoints(appoint infoAppoints[], doc infoDocs[], int docIndex) //F3
{
	
}
void displayExtraTimesDr()
{
	for (int j = 0; j < 4; j++) {
		cout << j+1 << "\t" << extraTime[j] << "\n";
	}
	
}
void addTime() //F6
{
	int selection;
	char choice;
	do {
		cout << "Select time: \n";
		displayExtraTimesDr(); 
		cout << "selection: ";  cin >> selection;
		switch (selection) {
		case 1:
			chosenTime[0] = true; // if true display
			break;
		case 2:
			chosenTime[1] = true;
			break;
		case 3:
			chosenTime[2] = true;
			break;
		case 4:
			chosenTime[3] = true;
			break;
		}
		cout << "Do you want to choose another? (y/n) \n";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}
void removeTime() //F7
{
	int selection;
	cout << "choose time to delete: \n";
	displayTime(); //orginal time aka timeSlots
	cin >> selection;
	selection = selection - 1;


	for (int i = selection; i < 4; i++) {
		timeSlots[i] = timeSlots[i + 1];
	}
	timeSlots[4] = "     ";
}
