#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//function prototypes
int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int rotateRight(string a[], int n, int pos);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

//assert tests the cases for all the functions
int main() 
{
	string a[6] = {
		"alpha", "beta", "gamma", "gamma", "beta", "delta" };
	string test1[2] = { "hi", "hello" };
	string test2[4] = { "abc", "def", "ghi", "jkl" };
	string test3[4] = { "abc", "def", "jkl", "ghi" };
	string test4[4] = { "abc", "def", "ghi", "jkl" };
	string test5[4] = { "abc", "def", "ghi", "jkl" };
	string test6[4] = { "abc", "def", "ghi", "jkl" };
	string test7a[3] = { "abc", "ghi", "jkl" };
	string test7b[3] = { "abc", "def", "ghi" };
	string test8a[4] = { "abc", "def", "ghi", "jkl" };
	string test8b[3] = { "def", "ghi", "jkl" };
	string test9a[4] = { "abc", "def", "ghi", "jkl" };
	string test9b[2] = { "zzz", "ghi" };
	string test10[4] = { "abc", "jkl", "def", "mno" };

	assert(appendToAll(test1, 2, "!") == 2 && test1[0] == "hi!" && test1[1] == "hello!");
	assert(lookup(test2, 4, "def") == 1);
	assert(positionOfMax(a, 6) == 2);
	assert(rotateLeft(test4, 4, 1) == 1 && test4[0] == "abc" && test4[1] == "ghi" && test4[3] == "def");
	assert(rotateRight(test5, 4, 2) == 2 && test5[0] == "ghi" && test5[1] == "abc" && test5[2] == "def");
	assert(flip(test6, 4) == 4 && test6[0] == "jkl" && test6[1] == "ghi" && test6[3] == "abc");
	assert(differ(test7a, 3, test7b, 3) == 1);
	assert(subsequence(test8a, 4, test8b, 3) == 1);
	assert(lookupAny(test9a, 4, test9b, 2) == 2);
	assert(split(test10, 4, "ghi") == 2);
	cout << "All tests succeeded" << endl;
}

//add value to the end of each element in the array
int appendToAll(string a[], int n, string value)
{
	if (n < 0)
		return -1;
	for (int k = 0; k < n; k++)
		a[k] += value;

	return n;
}

//return the value of the position in the array that matches target
int lookup(const string a[], int n, string target)
{
	for (int k = 0; k < n; k++)
	{
		if (a[k] == target)
			return k;
	}
	return -1;
}

//returns the position of the element in the array that is last in alphabetical order
int positionOfMax(const string a[], int n)
{
	int position = 1;
	if (n <= 0)
		return -1;

	for (int k = 1; k < n; k++)
	{
		if (a[k] > a[k - 1])
			position = k;
	}
	return position;
}

//rotates elements on the right side of the pos to the left and places what was at pos at the end of the array
int rotateLeft(string a[], int n, int pos)
{
	string t;
	
	if (n < 0)
		return -1;
	t = a[pos];
	for (int k = pos; k < n - 1; k++)
	{
		a[k] = a[k + 1];
	}
	a[n - 1] = t;
	return pos;
}

//rotates elements on the left side of the pos to the right and places what was at pos at the beginning of the array
int rotateRight(string a[], int n, int pos)
{
	string t;

	if (n < 0)
		return -1;
	t = a[pos];
	for (int k = pos; k > 0 ; k--)
	{
		a[k] = a[k - 1];
	}
	a[0] = t;
	return pos;
}

//reverses the order of the elements in the array 
int flip(string a[], int n)
{
	string t;

	if (n < 0)
		return -1;
	for (int i = n - 1; i > 0; i--)
	{
		for (int k = 0; k < i; k++)
		{
			t = a[k];
			a[k] = a[k + 1];
			a[k + 1] = t;
		}
	}
	return n;
}

//returns the first position in the array in which the respective elements differ from each other
//if elements are the same up until one array runs out of elements, return the smaller number of elements
int differ(const string a1[], int n1, const string a2[], int n2)
{
	int pos;
	
	if (n1 < 0 || n2 < 0)
		return -1;
	
	if (n1 < n2)
		pos = n1;
	else
		pos = n2;

	int k = 0;
	while(k < pos)
	{
		if (a1[k] == a2[k])
		{
			k++;
			continue;
		}
		else 
			break;
	}
	return k;
}

//return the position in the first array in which the elements of the second array matches, in order, 
//with elements of the first array
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	int k = 0;
	if (k == n1 && n2 == 0)
		return 0;
	
	while (k < n1)
	{
		int position = k;
		int i = 0;
		while (i < n2)
		{
			if (a2[i] == a1[k])
			{
				i++;
				k++;
				continue;
			}
			else
			{
				k -= i;
				break;
			}
		}
		if (i == n2)
			return position;
		k++;
	}
	return -1;
}

//return the smallest position in the first array in which the element matches with any elements of the second array
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	for (int k = 0; k < n1; k++)
	{
		for (int i = 0; i < n2; i++)
		{
			if (a2[i] == a1[k])
				return k;
		}
	}
	return -1;
}

//split elements that are alphabetically before the splitter from the ones that are after the splitter
//return the first position in the array in which the element is alphabetically after the splitter
int split(string a[], int n, string splitter)
{
	int counter = 0;
	int position;
	if (n < 0)
		return -1;

	for (int k = 0; k < n; k++)
	{
		if (counter == n)
			break;
		if (a[k] < splitter)
		{
			counter++;
			continue;
		}
		else
		{	
			rotateLeft(a, n, k);
			k--;
			counter++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= splitter)
		{
			position = i;
			break;
		}
	}
	return position;
}