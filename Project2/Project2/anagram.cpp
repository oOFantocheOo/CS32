#include <iostream>
#include <fstream>
#include <string>
#include <istream>
using namespace std;

const int MAXRESULTS = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in
 
void printPermutions(string prefix, string rest, string *potential);
string BinaryDict(string word, const string dictionary[], int low, int high); //To efficiently search the dictionary

void TraversalPotential(string wordlist[], const string dictionary[], int indicatorW, int indicatorR, int size, string results[], int &countWord)
{
	if (wordlist[indicatorW] == "")
		return;
	if (results[indicatorR] != "")
		return TraversalPotential(wordlist, dictionary, indicatorW, indicatorR + 1, size, results, countWord);
	else if (BinaryDict(wordlist[indicatorW], dictionary, 0, size-1) == "")
		return TraversalPotential(wordlist, dictionary, indicatorW + 1, indicatorR, size, results, countWord);
	else
	{
		countWord++;
		results[indicatorR] = BinaryDict(wordlist[indicatorW], dictionary, 0, size-1);
		return TraversalPotential(wordlist, dictionary, indicatorW + 1, indicatorR, size, results, countWord);
	}
}

string BinaryDict(string word, const string dictionary[], int low, int high)
{
	string temp = dictionary[(low + high) / 2];//Prevent the influence of words in dictionary that start with capital letter
	if (temp[0] >= 65 && temp[0] <= 90)
	    temp[0] += 32;
	if (word[0] >= 65 && word[0] <= 90)//Prevent the influence of word as input that starts with capital letter
		word[0] += 32;
	if (word == temp)
		return dictionary[(low + high) / 2];
	if (low >= high)
		return "";
	if (word < temp)
		return BinaryDict(word, dictionary, low, ((high + low) / 2) - 1);
	else
		return BinaryDict(word, dictionary, ((low + high) / 2) + 1, high);

}

void store(string word, string list[], int a)//Store words first; used to exclude repetitions of word conveniently
{
	if (list[a] == "")
		list[a] = word;
	else
	{
		a++;
		store(word, list, a);
	}
}

void loopPP(int i, int max, string prefix, string rest, string tempp, string tempr, string *potential)//loop helper that uses loop with recursion code
{
	if (i >= max)
		return;
	prefix += rest[i];//Add the character to the end of prefix.
	rest.erase(i, 1);//Remove character from rest.
	printPermutions(prefix, rest, potential);//Use recursion to generate permutations with the updated values for prefix and rest.
	prefix = tempp;
	rest = tempr;
	loopPP(i + 1, max, prefix, rest, tempp, tempr, potential);
}

void printPermutions(string prefix, string rest, string *potential) {
	string tempp;
	string tempr;
	if (rest == "")
		store(prefix, potential, 0);
	else 
	{
		tempp = prefix;
		tempr = rest;
		loopPP(0, (unsigned int)rest.size(), prefix, rest, tempp, tempr, potential);
	}
}

int LoopReadDictionary(int i, int max, string dict[], istream &dictfile, int count)
{
	if (i >= max)
		return count;
	if (dictfile)
	{
		dictfile >> dict[i];
		count++;
	}
	return LoopReadDictionary(i + 1, max, dict, dictfile, count);
}//loop helper

int readDictionary(istream &dictfile, string dict[])
{
	int count = 0;
	count = LoopReadDictionary(1, MAXDICTWORDS, dict, dictfile, count);
	return count;
}

int recursivePermute(string word, const string dict[], int size, string results[], int dictSize, int &countWord, string *potential)
{
	printPermutions("", word, potential);
	TraversalPotential(potential, dict, 0, 0, dictSize, results, countWord);
	return countWord;
}

void recurPrint(const string results[], int size)
{
	if (size == 0)
		return;
	if (results[size - 1] != "")
		cout << "Matching word: " << results[size - 1] << endl;
	return recurPrint(results, size - 1);
}

void loopRR(int i, int o, int max, string* repeated)
{
	if (i >= max)
		return;
	if (o >= max)
		return loopRR(i + 1, 0, max, repeated);
	if (o != i && repeated[i] == repeated[o] && repeated[i] != "")
	{
		repeated[i] = "";
		return loopRR(0, 0, max, repeated);
	}
	return loopRR(i, o + 1, max, repeated);
} 

void removeRepeatition(string *repeated)
{
	loopRR(0, 0, MAXRESULTS, repeated);
	return;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <csignal>

using namespace std;

void testone(int n)
{
	string dictionary[MAXDICTWORDS];
	string results[MAXRESULTS];

	switch (n)
	{
	default: {
		cout << "Bad argument" << endl;
	} break; case  1: {
		istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
		int numResults = readDictionary(iss, dictionary);
		sort(dictionary, dictionary + numResults);
		assert(numResults == 9 && dictionary[0] == "act" && dictionary[1] == "art");
	} break; case  2: {
		// File is empty, Checks that file is empty and readDictionary returns 0.
		istringstream iss("");
		int numResults = readDictionary(iss, dictionary);
		assert(numResults == 0 && dictionary[0] == "");
	} break; case  3: {
		// Dictionary has been read properly
		istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
		int numResults = readDictionary(iss, dictionary);
		sort(dictionary, dictionary + numResults);
		assert(numResults == 9 && dictionary[0] == "act" && dictionary[numResults - 1] == "tar");
	} break; case  4: {
		// Input file is larger than the dictionary size
		istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\ntoo\nmany\nwords");
		int numResults = readDictionary(iss, dictionary);
		sort(dictionary, dictionary + numResults);
		assert(numResults == 10 && dictionary[MAXDICTWORDS - 1] == "too");

	}
	}
}

	int main()
	{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout << "Passed" << endl;
}