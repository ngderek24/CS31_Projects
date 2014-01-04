#include <iostream>
#include <string>
using namespace std;

int main() {
	int age;
	string student;
	string destination;
	int zoneCrossed;
	double fare;

	cout << "Age of rider: ";
	cin >> age;
	if (age < 0) {
		cout << "---" << endl;
		cout << "The age must not be negative" << endl;
		return 1; }			//return 1 means that the "if" statement failed
	
	cout << "Student? (y/n): ";
	cin >> student;
	cin.ignore(10000, '\n');		//cin.ignore tells the compiler to ignore the newline after entering the age
	if ( (student != "y") && (student != "n")) {
		cout << "---" << endl;
		cout << "You must enter y or n" << endl;
		return 1; }
	
	cout << "Destination: ";
	getline(cin, destination);		//getline tells the compiler to use the whole line of input as the destination
	if (destination == "") {
		cout << "---" << endl;
		cout << "You must enter a destination" << endl;
		return 1; }
	
	cout << "Number of zone boundaries crossed: ";
	cin >> zoneCrossed;
	if (zoneCrossed < 0) {
		cout << "---" << endl;
		cout << "The number of zone boundaries crossed must not be negative" << endl;
		return 1; }
	
	cout << "---" << endl;
	
	if ( (age < 18) && (zoneCrossed < 2))		//if-else and else if statements are used for true/false conditions
		fare = 0.65;
	else if ( (student == "y") && (age >= 18) && (age < 65) && (zoneCrossed < 2))
		fare = 0.65;
	else if ( (age >= 65)) {
		if (zoneCrossed == 0)
			fare = 0.35;
		else if ((zoneCrossed == 1) && (student == "y"))
			fare = 0.65;
		else 
			fare = 0.55 + (0.25 * zoneCrossed); }
	else 
		fare = 1.55 + (0.50 * zoneCrossed);

	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "The fare to " << destination << " is $" << fare << endl;
}