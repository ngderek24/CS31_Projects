#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <ctime>
using namespace std;

const int MAX_WORDS = 9000;
const int MIN_WORD_LENGTH = 4;
const int MAX_WORD_LENGTH = 6;
//points to the location of the text file with the hidden words to load them into the array
const char WORDFILENAME[] = "C:/Users/Derek/Documents/Visual Studio 2012/Projects/Project5/words.txt";

int randInt(int lowest, int highest);
int loadWords(char words[][MAX_WORD_LENGTH + 1], int maxWords);
int manageOneRound(const char words[][MAX_WORD_LENGTH + 1], int num, int wordnum);

int main() 
{
	char wordList[MAX_WORDS][MAX_WORD_LENGTH + 1];
	int numberOfWords = loadWords(wordList, MAX_WORDS);
	int locationOfWord;
	int numberOfTry;
	double average;
	double totalNumberOfTry = 0;
	int minimum;
	int maximum = 0;
	int numberOfRounds;

	//if no words were loaded into the array, then terminate the program immediately
	if (numberOfWords < 1)
	{
		cout << "No words were loaded, so I can't play the game";
		return -1;
	}
	
	cout << "How many rounds do you want to play? ";
	cin >> numberOfRounds;
	cout << endl;
	if (numberOfRounds < 0)
	{
		cout << "The number of rounds must be positive";
		return -1;
	}
	cin.ignore(10000, '\n');
	
	//selects a random integer based on how many seconds have passed since a set time so that the
	//random integer is different each time the loop is ran
	std::srand(std::time(0));
	
	//loop to play however many rounds the user inputed
	for (int roundNumber = 1; roundNumber <= numberOfRounds; roundNumber++)
	{
		//store the random number generated at a location to pass it as an argument to manageOneRound
		locationOfWord = randInt(0, numberOfWords - 1);
		cout << "Round " << roundNumber << endl;
		cout << "The hidden word is " << strlen(wordList[locationOfWord]) << " letters long" << endl;
		numberOfTry = manageOneRound(wordList, numberOfWords, locationOfWord);
		
		if (numberOfTry == 1)
			cout << "You got it in 1 try" << endl;
		else
			cout << "You got it in " << numberOfTry << " tries" << endl;

		//determines the minimum and maximum number of tries
		if (roundNumber == 1)
			minimum = numberOfTry;
		if (numberOfTry < minimum)
			minimum = numberOfTry;
		if (numberOfTry > maximum)
			maximum = numberOfTry;
		
		//makes the program print 2 digits after the decimal point for "average"
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(2);
		
		totalNumberOfTry += numberOfTry;
		//static cast double for roundNumber to divide a double by another double to get digits after decimal point
		average = totalNumberOfTry/static_cast<double>(roundNumber);
		cout << "Average: " << average << ", minimum: " << minimum << ", maximum: " << maximum << endl << endl;
	}
}

//function that selects a random integer between 0 and the highest position in the hidden word array
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        std::swap(highest, lowest);
    return lowest + (std::rand() % (highest - lowest + 1));
}

//load the words from the text file into the wordList array and return the number of words that were loaded
int loadWords(char words[][MAX_WORD_LENGTH+1], int maxWords)
{
    ifstream wordfile(WORDFILENAME);
    if ( ! wordfile)
    {
        cout << "Cannot open " << WORDFILENAME << endl;
        return -1;
    }
    const int LINELIMIT = 10000;
    char line[LINELIMIT];
    int numWords = 0;
    while (wordfile.getline(line, LINELIMIT))
    {
        if (numWords == maxWords)
        {
            cout << "Using only the first " << numWords
                 << " words from " << WORDFILENAME << endl;
            break;
        }
        int k;
        for (k = 0; islower(line[k]); k++)
            ;
         
		if (line[k] == '\r')
                line[k] = '\0';

        if (line[k] == '\0'  &&  k >= MIN_WORD_LENGTH  &&  k <= MAX_WORD_LENGTH)
        {
            strcpy(words[numWords], line);
            numWords++;
        }
	}
	return numWords;
}

//asks the user for the trial word and determines how many letters are matched with the hidden word
//returns the number of tries to guess the hidden word
int manageOneRound(const char words[][MAX_WORD_LENGTH + 1], int num, int wordnum)
{
	char answer[MAX_WORD_LENGTH + 1];
	int numberOfTry = 0;
	int counter = 0;
	int count = 0;
	int nonLetter = 0;

	if (num < 0 || wordnum < 0 || wordnum >= num)
		return -1;
	
	for (;;)
	{
		counter = 0;
		nonLetter = 0;
		count = 0;
		
		cout << "Trial word: ";
		cin.getline(answer, 1000);
		
		//if the guess matches with the hidden word, then break out of for loop and return number of tries
		if (strcmp(words[wordnum], answer) == 0)
		{
			numberOfTry++;
			break;
		}

		//if the trial word is not 4 to 6 letters long, tell user and restart loop
		else if (strlen(answer) != 4 && strlen(answer) != 5 && strlen(answer) != 6)
		{
			cout << "Your trial word must be a word of 4 to 6 lower case letters" << endl;
			numberOfTry++;
			continue;
		}
		
		//if the trial word contains letters that are not lowercase, tell user and restart loop
		for (int k = 0; answer[k] != '\0'; k++)
		{
			if (! isalpha(answer[k]) || ! islower(answer[k]))
				nonLetter++;
		}
		if (nonLetter > 0)
		{
			cout << "Your trial word must be a word of 4 to 6 lower case letters" << endl;
			numberOfTry++;
			continue;
		}

		//if the trial word is not one of the valid words in the wordList array, tell user and restart loop
		for (int k = 0; k < MAX_WORDS; k++)
		{
			if (strcmp(words[k], answer) != 0)
				count++;
		}
		if (count == MAX_WORDS)
		{
			cout << "I don't know that word" << endl;
			numberOfTry++;
			continue;
		}

		//tests how many letters of the trial word are in the hidden word and output that number
		//modifies letters that have already matched with the hidden word, so that they won't be tested again
		for (int k = 0; words[wordnum][k] != '\0'; k++)
		{
			for (int n = 0; answer[n] != '\0'; n++)
			{
				if (words[wordnum][k] == answer[n])
				{
					counter++;
					answer[n] = '!';
					break;
				}
			}
		}
		cout << counter << endl;
		numberOfTry++;
	}
	return numberOfTry;
}