#include <iostream>
#include <string>
#include <cctype>
using namespace std;

	string getFirstWord(string s);
	string getLastWord(string s);
	string extractWord(string& s);
	bool isUppercase(string s);
	string makeUppercase(string s);
	bool hasMultipleExclamations(string s);
	bool isGibberishWord(string s);
	int spamRule1(string s);
	int spamRule2(string s);
	int spamRule3(string s);
	int spamRule4(string s);
	int spamRule5(string s);
	int wordCounter(string s);

int main() {

	int spamScoreSubj;
	int spamScoreBody;
	int finalSpamScore;
	int spamNumber = 0;
	int legitimateNumber = 0;
	string subject;
	string body;
	string reClassify;
	
	//do-while loop used to output program and obtain user input. If user wants to classify another email, the loop will restart.
	do {
		finalSpamScore = 0;
		spamScoreSubj = 0;
		spamScoreBody = 0;
		subject = "";
		body = "";
		
		cout << "Enter the subject line of the email: ";
		getline(cin, subject);

		//obtain the spam score of the subject using the spam rule functions		
		spamScoreSubj = spamRule1(subject) + spamRule2(subject) + spamRule3(subject);

		cout << "Enter the body of the email. Please Enter on an empty line to finish." << endl;
		string temporaryBody;
		
		//uses a do-while loop to obtain all of the body that the user input and ends loop when user press 'Enter' on an empty line	
		do
		{
			getline(cin, temporaryBody);
			if (temporaryBody != "")
				body += temporaryBody;
		} while (temporaryBody != "");
		spamScoreBody = spamRule4(body) + spamRule5(body);

		//determine whether email is spam or legitimate by adding up the spam scores of the subject and body
		finalSpamScore = spamScoreSubj + spamScoreBody;
		if(finalSpamScore > 100)
		{
			cout << "This email is classified as spam, because its spam score is " << finalSpamScore << "." << endl;
			spamNumber++;
		}
		else
		{
			cout << "This email is classified as legitimate, because its spam score is " << finalSpamScore << "." << endl;
			legitimateNumber++;
		}
	
		do 
		{
			cout << "Would you like to classify another email (y or n)? ";
			cin >> reClassify;
			cin.ignore(10000, '\n');
			if ((reClassify != "y") && (reClassify != "n"))
				cout << "Please enter y or n." << endl;
		} while ((reClassify != "y") && (reClassify != "n"));
			
	} while (reClassify == "y");

	//if user is done classifying, the program outputs the number of spam and legitimate messages that have been classified
	if (reClassify == "n")
	{
		cout << endl;
		cout << "Number of spam messages: " << spamNumber << endl;
		cout << "Number of legitimate messages: " << legitimateNumber << endl;
	}

	return 0;
}

//function that gets the first word of the string that the user inputs	
string getFirstWord(string s)
{
	if (s == "")
		return "";
	string firstWord;
	//for loop to append letters of the first word to a string and break when the first word ends
	for (size_t k = 0; k != s.size(); k++)
	{
		if (isalpha(s[k]))
			firstWord += s[k];
		if (! isalpha(s[k]) && firstWord != "")
			break;
	}
	return firstWord;
}

//function that gets the last word of the user input string	
string getLastWord(string s)
{
	string t;
	string r;
	int wordCounter = 0;
	
	if (s == "")
		return "";
	//for loop that counts the number of words that are in the string that the user inputs
	for (size_t k = 0; k <= s.size(); k++)
	{
		if (isalpha(s[k]))
			t += s[k];
		else if (! isalpha(s[k]) && t != "")
		{
			wordCounter++;
			t = "";
		}
	}
	//based on the number of words counted in the previous for loop, function will extract words to get the last word
	for (int k = 1; k < wordCounter; k++)
	{
		extractWord(s);
	}
	r = getFirstWord(s);
	return r;
}
	
//function that extract the first word of the string and erase that word from the rest of the string
string extractWord(string& s)
{
	int counter = 0;
	string t;
	string r = getFirstWord(s);
	if (s == "")
		s = "";
	else 
	{
		for (size_t k = 0; k < s.size(); k++)
		{
			if (! isalpha(s[k]))
				counter++;
			else
				break;
		}
		for (size_t k = counter; k < s.size(); k++)
		{
			if (isalpha(s[k]))
				t += s[k];
			else if (! isalpha(s[k]))
				break;
		}
		//erases the first word of the string and define s as the remaining of the string
		s = s.substr((t.size() + counter), s.size() -(t.size() + counter));
	}
	return r;
}

//determines whether if the letters of a string is all uppercase
bool isUppercase(string s)
{	
	int letter = 0;
	int upper = 0;
	for (size_t k = 0; k != s.size(); k++)
	{
		if (isalpha(s[k]))
		{
			letter++;
			if (isupper(s[k]))
				upper++;
		}
	}
	if (upper == letter)
		return true;
	else 
		return false;
}

//makes all the letters of the string uppercase
string makeUppercase(string s)
{
	string t;
	for (size_t k = 0; k != s.size(); k++)
		t += toupper(s[k]);
	return t;
}

//determines whether a string has 3 or more exclamation marks in a row
bool hasMultipleExclamations(string s)
{
	int counter = 0;
	for (size_t k = 0; k != s.size(); k++)
	{
		if (s[k] == '!')
			counter += 1;
		else 
			counter = 0;
	}
		if (counter >= 3)
			return true;
		else 
			return false;
}

//determines whether a string contains a gibberrish word in which the word has more than 3 consonants in a row
bool isGibberishWord(string s) 
{	
	int counter = 0;

	for (int k = 0; k < s.size(); k++)
	{
		if (s[k] == ' ')
			counter = 0;
		if (isalpha(s[k]))
		{
			if (s[k] != 'a' && 
				s[k] != 'e' && 
				s[k] != 'i' && 
				s[k] != 'o' && 
				s[k] != 'u' && 
				s[k] != 'A' && 
				s[k] != 'E' && 
				s[k] != 'I' && 
				s[k] != 'O' && 
				s[k] != 'U')
			{
				counter += 1; 
				if (counter > 3)
					break;
			}
			else 
				counter = 0; 
		}
	}
		if (counter > 3) 
			return true;
		else
			return false;
}

//counts the number of words in the string	
int wordCounter(string s)
{
	int wordCounter = 0;
	string t;

	//appends letters of a word to a string until the word ends, in which the word counter will increase by 1
	for (size_t k = 0; k <= s.size(); k++)
	{
		if (isalpha(s[k]))
			t += s[k];
		else if (! isalpha(s[k]) && t != "")
		{
			wordCounter++;
			t = "";
		}
	}
	return wordCounter;
}

//function to determine whether a string satifies the first spam rule and return the spam points	
int spamRule1(string s)
{
	double uppercase = 0;
	double counter = 0;
	double percent;
	string t;

	if (s == "")
		return 0;
	
	counter = wordCounter(s);
		
	//tests if each word is all uppercase to determine the percentage of words in the string that are uppercase
	for (size_t k = 0; k < counter; k++)
	{
		t = extractWord(s);
			if (isUppercase(t))
				uppercase++;
	}
	percent = uppercase/counter;
	if (percent > 0.9)
		return 30;
	else
		return 0;
}

//function to determine whether a string satifies the second spam rule and return the spam points	
int spamRule2(string s)
{
	string t;
	t = getLastWord(s);
		
	if (isGibberishWord(t))
		return 40;
	else
		return 0;
}

//function to determine whether a string satifies the third spam rule and return the spam points	
int spamRule3(string s)
{
	if (hasMultipleExclamations(s))
		return 20;
	else 
		return 0;
}

//function to determine whether a string satifies the fourth spam rule and return the spam points	
int spamRule4(string s)
{
	double uppercase = 0;
	double counter = 0;
	double percent;
	string t;

	if (s == "")
		return 0;
	
	counter = wordCounter(s);
		
	for (size_t k = 0; k < counter; k++)
	{
		t = extractWord(s);
			if (isUppercase(t))
				uppercase++;
	}
	percent = uppercase/counter;
	if (percent > 0.5)
		return 40;
	else
		return 0;
}

//function to determine whether a string satifies the fifth spam rule and return the spam points	
int spamRule5(string s)
{
	int counter;
	int score = 0;
	string t;
	string r;

	counter = wordCounter(s);

	for (int k = 0; k < counter; k++)
	{
		t = extractWord(s);
		//makes all the characters of a word lowercase to test whether it matches with one of the "spam" words
		for (size_t k = 0; k < t.size(); k++)
		{
			r += tolower(t[k]);
		}
		if (r == "buy" ||
			r == "cheap" ||
			r == "click" ||
			r == "diploma" ||
			r == "enlarge" ||
			r == "free" ||
			r == "alone" ||
			r == "money" ||
			r == "now" ||
			r == "offer" ||
			r == "only" ||
			r == "pills" ||
			r == "sex")
			score += 5;
		r = "";
	}
	return score;
}