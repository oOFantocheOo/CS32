#include <string>
#include <iostream>
#include "PeopleList.h"

using namespace std;

class PeopleList;


PeopleList& PeopleList::operator=(const PeopleList& other)
{
	if (other.empty())
	{
		PeopleList a;
		return a;
	}
	PeopleList *pl = new PeopleList(other);
	this->~PeopleList();
	return *pl;
}

PeopleList::~PeopleList()
{
	person *p = head;
	while (p != nullptr)
	{
		p = p->next;
		delete head;
		head = p;
	}
}

PeopleList::PeopleList(const PeopleList& other)
{
	tail = nullptr;
	head = nullptr;
	person* p = nullptr;
	string fname;
	string lname;
	InfoType Value;
	int sizeOfOther = other.size();
	for (int i = 0; i < sizeOfOther; i++)
	{
		other.get(i, fname, lname, Value);
		this->add(fname, lname, Value);
	}
}

PeopleList::PeopleList()
{
	head = nullptr;
}

bool PeopleList::empty() const
{
	if (head == nullptr)
		return true;
	else return false;
}

int PeopleList::size() const
{
	int Size = 0;
	person *p = head;
	while (p != nullptr)
	{
		Size++;
		p = p->next;
	}
	return Size;
}

void PeopleList::sortAdd(string fN, string lN, person *a)
{		
	//extreme-value insert
	if (lN < head->ln)
	{
		person *p = head;
		a->next = p;
		p->previous = a;
		head = a;
		head->previous = nullptr;
		return;
	}
	if (lN > tail->ln)
	{
		person *p = tail;
		p->next = a;
		a->previous = p;
		tail = a;
		tail->next = nullptr;
		return;
	}
	if (lN == head->ln && fN < head->fn)
	{
		person *p = head;
		a->next = p;
		p->previous = a;
		head = a;
		head->previous = nullptr;
		return;
	}
	if (lN == tail->ln && fN > tail->fn)
	{
		person *p = tail;
		p->next = a;
		a->previous = p;
		tail = a;
		tail->next = nullptr;
		return;
	}

	for (person *p = head; p->next != nullptr; p = p->next)//non-extreme-value insert
	{
		if (p->ln != lN)
		{
			if (lN > p->ln && lN < p->next->ln)
			{
				p->next->previous = a;
				a->next = p->next;
				a->previous = p;
				p->next = a;
				return;
			}
		}
		else
		{
			if (fN > p->fn && fN < p->next->fn)
			{
				p->next->previous = a;
				a->next = p->next;
				a->previous = p;
				p->next = a;
				return;
			}
		}
	}
}

bool PeopleList::add(const std::string& firstName, const std::string& lastName, const InfoType& value)
{
	person *p = head;
	for (int i = 0; i < this->size(); i++)
	{
		if (p->fn == firstName && p->ln == lastName)
			return false;
		p = p->next;
	}
	person *a = new person;
	a->ln = lastName;
	a->fn = firstName;
	a->v = value;
	if (this->size() == 0)
	{
		tail = a;
		tail->next = nullptr;
		tail->previous = nullptr;
		head = a;
		head->previous = nullptr;
		head->next = nullptr;
	}
	else
		this->sortAdd(firstName,lastName,a);
	return true;
}

bool PeopleList::change(const std::string &firstName, const std::string &lastName, const InfoType& value)
{
	person *p = head;
	for (p; p != nullptr; p = p->next)
	{
		if (firstName == p->fn && lastName == p->ln)
		{
			p->v = value;
			return true;
		}
	}
	return false;
}

bool PeopleList::addOrChange(std::string firstName, std::string lastName, const InfoType& value)
{
	bool b = this->change(firstName, lastName, value);
	if (b)
		return true;
	else
	{
		this->add(firstName, lastName, value);
		return true;
	}
}

bool PeopleList::remove(const std::string& firstName, const std::string& lastName)
{
	person *p = head;
	for (p; p != nullptr; p = p->next)
	{
		if (firstName == p->fn && lastName == p->ln)
		{
			if (p == head)
			{
				p->next->previous = nullptr;
				head = p->next;
				delete p;
			}
			else if (p == tail)
			{
				p->previous->next = nullptr;
				tail = p->previous;
				delete p;
			}
			else
			{
				person *toBeDeleted = p;
				p->previous->next = p->next;
				p->next->previous = p->previous;
				delete toBeDeleted;
			}
			return true;
		}
	}
	return false;
}

bool PeopleList::contains(const std::string firstName, const std::string lastName) const
{
	person *p = head;
	for (p; p != nullptr; p = p->next)
	{
		if (p->fn == firstName && p->ln == lastName)
		{
			return true;
		}
	}
	return false;
}

bool PeopleList::lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const
{

	person *p = head;
	for (p; p != nullptr; p = p->next)
	{
		if (p->fn == firstName && p->ln == lastName)
		{
			value = p->v;
			return true;
		}
	}
	return false;
}

bool PeopleList::get(int i, std::string& firstName, std::string& lastName, InfoType& value) const
{
	person *p = head;
	if (0 <= i && i < this->size())
	{
		for (int o = 0; o < i; o++)
		{
			p = p->next;
		}
		firstName = p->fn;
		lastName = p->ln;
		value = p->v;
		return true;
	}
	return false;
}

void PeopleList::swap(PeopleList& other)
{
	std::swap(other.head, head);
}

bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result)
{
	PeopleList res;
	result = res;
	bool b = true;
	int sizeOne = m1.size();
	int sizeTwo = m2.size();
	std::string firstNameOne = "";
	std::string lastNameOne = "";
	std::string firstNameTwo = "";
	std::string lastNameTwo = "";
	InfoType valueOne;
	InfoType valueTwo;
	for (int iOne = 0; iOne < sizeOne; iOne++)
	{
		m1.get(iOne, firstNameOne, lastNameOne, valueOne);
		result.addOrChange(firstNameOne, lastNameOne, valueOne);
		for (int iTwo = 0; iTwo < sizeTwo; iTwo++)
		{
			m2.get(iTwo, firstNameTwo, lastNameTwo, valueTwo);
			if (firstNameOne == firstNameTwo && lastNameOne == lastNameTwo)
				if (valueOne != valueTwo)
				{
					result.remove(firstNameOne, lastNameOne);
					b = false;
				}
		}
	}
	for (int iTwo = 0; iTwo < sizeTwo; iTwo++)
	{
		m2.get(iTwo, firstNameTwo, lastNameTwo, valueTwo);
		result.addOrChange(firstNameTwo, lastNameTwo, valueTwo);
		for (int iOne = 0; iOne < sizeOne; iOne++)
		{
			m1.get(iOne, firstNameOne, lastNameOne, valueOne);
			if (firstNameOne == firstNameTwo && lastNameOne == lastNameTwo)
				if (valueOne != valueTwo)
				{
					result.remove(firstNameTwo, lastNameTwo);
					b = false;
				}
		}
	}
	return b;
}

void psearch(const std::string& fsearch, const std::string& lsearch, const PeopleList& p1, PeopleList& result)
{
	PeopleList res;
	result = res;
	int Size = p1.size();
	string firstname;
	string lastname;
	InfoType aValue;

	for (int i = 0; i < Size; i++)
	{
		p1.get(i, firstname, lastname, aValue);
		if (fsearch == "*" || fsearch == firstname)
			if (lsearch == "*" || lastname == lsearch)
				result.add(firstname, lastname, aValue);
	}
	return;
}