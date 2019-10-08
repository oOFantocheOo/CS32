#include "PeopleList.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	PeopleList m;
	assert(m.add("Fred", "Mertz", 52));
	assert(m.add("Ethel", "Mertz", 49));
	assert(m.size() == 2);
	string first, last;
	int a;
	assert(m.get(0, first, last, a) && a == 49);
	string s1;
	assert(m.get(1, first, last, a) &&
		(first == "Fred"  &&  a == 52));
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}