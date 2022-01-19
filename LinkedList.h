//********************************************************************
// ASU CSE310 Assignment #7
// Name: Conner Erickson
// ASU ID: 1214908565
// Description: LinkedList data structure definition heavily based on my own Assignment1 code with some modifications to fit the arrCity struct and assignment requirements.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//price info. from the departure city
struct ArrCity
{
    string arrCityName;
    int price;
    struct ArrCity* next;
};

//class LinkedList will contains a linked list of ArrCity
class LinkedList
{
    private:
        struct ArrCity* head;

    public:
        LinkedList();
        ~LinkedList();
        ArrCity* getHead();
        ArrCity* findArrCity(string aCity);
        bool addArrCity(string aCity, int price);
        void printArrCityList();
};

//Define all remaining functions according to above function declaration
//----
//----
LinkedList::LinkedList()
{
	head = NULL;
}

LinkedList::~LinkedList()
{
	int count = 0;
	ArrCity* current = head;

	while(current != NULL)
	{
		head = current->next;
		delete current;
		current = head;
		count++;
	}
	delete head;
}

ArrCity* LinkedList::getHead()
{
	return head;
}

ArrCity* LinkedList::findArrCity(string aCity)
{
	if(head == NULL)
	{
		return NULL;
	}
	
	ArrCity* temp = head;
	if(temp->arrCityName == aCity)
	{
		return temp;
	}
	else
	{
		while(temp->next != NULL && temp->arrCityName != aCity)
		{
			temp = temp->next;
		}
		if(temp->arrCityName == aCity)
		{
			return temp;
		}
	}
	return NULL;
}

bool LinkedList::addArrCity(string aCity, int price)
{
	ArrCity* newCity = new ArrCity;
	newCity->arrCityName = aCity;
	newCity->price = price;

	if(this->findArrCity(aCity) != NULL)
	{
		return false;
	}
	
	ArrCity* temp = head;
	if(head == NULL || head->arrCityName > aCity)
	{
		newCity->next = head;
		head = newCity;
		return true;
	}

	while(temp->next != NULL && temp->next->arrCityName < aCity)
	{
		temp = temp->next;
	}
	
	newCity->next = temp->next;
	temp->next = newCity;
	return true;
}

//Prints all the elements in the linked list starting from the head.
void LinkedList::printArrCityList()
{
    struct ArrCity *temp = head;

	if(head == NULL)
    {
		cout << "Arrival city list is empty\n";
		return;
	}
	while(temp!= NULL)
    {
		cout << temp->arrCityName << "(" << temp->price << "),";
		temp = temp->next;
	}
	cout <<"\n";
}