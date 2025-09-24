
#pragma warning( disable : 4290 )
#include <stdexcept>
#include <new>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

template < class T >        
class List;

template < class T >
class ListNode                
{
private:

	ListNode(const T &nodeData, ListNode *nextPtr);
	T dataItem;    
	ListNode *next;   

	friend class List<T>;
};

//--------------------------------------------------------------------

template < class T >
class List
{
public:

	List(int ignored = 0);
	~List();
	void insert(const T &newData);      
	void remove();                   
	void replace(const T &newData);   
	void clear();

	bool isEmpty() const;
	bool isFull() const;

	void gotoBeginning();
	void gotoEnd();
	bool gotoNext();
	bool gotoPrior();
	T getCursor() const;              
	void showStructure() const;
	void moveToBeginning();                   
	void insertBefore(const T &newElement); 

private:
	ListNode<T> *head,    
	         *cursor;   
};

//--------------------------------------------------------------------
//
//                          listlnk.cpp
//
//--------------------------------------------------------------------

template < class T >
ListNode<T>::ListNode(const T &nodeDataItem, ListNode<T> *nextPtr) : dataItem(nodeDataItem), next(nextPtr)
{}

//--------------------------------------------------------------------

template < class T >
List<T>::List(int ignored) : head(0), cursor(0)
{}

//--------------------------------------------------------------------

template < class T >
List<T>:: ~List()
{
	clear();
}

//--------------------------------------------------------------------

template < class T >
void List<T>::insert(const T &newDataItem)
{
	if (head == 0)             // Empty list
	{
		head = new ListNode<T>(newDataItem, 0);
		cursor = head;
	}
	else                        
	{
		cursor->next = new ListNode<T>(newDataItem, cursor->next);
		cursor = cursor->next;
	}
}

//--------------------------------------------------------------------

template < class T >
void List<T>::remove()
{
	ListNode<T> *p,  
	         *q;   
	if (head == 0)
		throw logic_error("list is empty");

	if (cursor == head)            
	{
		p = head;
		head = head->next;
		cursor = head;
	}
	else if (cursor->next != 0)    
	{
		p = cursor->next;
		cursor->dataItem = p->dataItem;
		cursor->next = p->next;
	}
	else                             
	{
		p = cursor;
		for (q = head; q->next != cursor; q = q->next)
			;
		q->next = 0;
		cursor = head;
	}

	delete p;
}

//--------------------------------------------------------------------

template < class T >
void List<T>::replace(const T &newDataItem)
{
	if (head == 0)
		throw logic_error("list is empty");

	cursor->dataItem = newDataItem;
}

//--------------------------------------------------------------------

template < class T >
void List<T>::clear()
{
	ListNode<T> *p,     
	         *nextP;                  
	p = head;
	while (p != 0)
	{
		nextP = p->next;
		delete p;
		p = nextP;
	}

	head = 0;
	cursor = 0;
}

//--------------------------------------------------------------------

template < class T >
bool List<T>::isEmpty() const
{
	return (head == 0);
}
//--------------------------------------------------------------------

template < class T >
bool List<T>::isFull() const
{
	T testDataItem;
	ListNode<T> *p;

	try
	{
		p = new ListNode<T>(testDataItem, 0);
	}
	catch (bad_alloc)
	{
		return true;
	}

	delete p;
	return false;
}

//--------------------------------------------------------------------

template < class T >
void List<T>::gotoBeginning()
{
	if (head != 0)
		cursor = head;
	else
		throw logic_error("list is empty");
}

//--------------------------------------------------------------------

template < class T >
void List<T>::gotoEnd()
{
	if (head != 0)
		for (; cursor->next != 0; cursor = cursor->next)
			;
	else
		throw logic_error("list is empty");
}

//--------------------------------------------------------------------

template < class T >
bool List<T>::gotoNext()
{
	bool result;   

	if (cursor->next != 0)
	{
		cursor = cursor->next;
		result = true;
	}
	else
		result = false;

	return result;
}

//--------------------------------------------------------------------

template < class T >
bool List<T>::gotoPrior()

{
	ListNode<T> *p;   
	int result;       

	if (cursor != head)
	{
		for (p = head; p->next != cursor; p = p->next)
			;
		cursor = p;
		result = true;
	}
	else
		result = false;

	return result;
}

//--------------------------------------------------------------------

template < class T >
T List<T>::getCursor() const
{
	if (head == 0)
		throw logic_error("list is empty");

	return cursor->dataItem;
}

//--------------------------------------------------------------------

template < class T >
void List<T>::showStructure() const
{
	ListNode<T> *p;   // Iterates through the list

	if (head == 0)
		cout << "Empty list" << endl;
	else
	{
		for (p = head; p != 0; p = p->next)
			if (p == cursor)
				cout << "[" << p->dataItem << "] ";
			else
				cout << p->dataItem << " ";
		cout << endl;
	}
}

//--------------------------------------------------------------------

template < class T >
void List<T>::moveToBeginning()
{
	ListNode<T> *p;   
	if (head == 0)
		throw logic_error("list is empty");

	if (cursor != head)
	{
		for (p = head; p->next != cursor; p = p->next)
			;
		p->next = cursor->next;
		cursor->next = head;
		head = cursor;
	}
}

//--------------------------------------------------------------------

template < class T >
void List<T>::insertBefore(const T &newDataItem)

{
	if (head == 0)             // Empty list
	{
		head = new ListNode<T>(newDataItem, 0);
		cursor = head;
	}
	else                         // Before cursor
	{
		cursor->next = new ListNode<T>(cursor->dataItem, cursor->next);
		cursor->dataItem = newDataItem;
	}
}

//--------------------------------------------------------------------
//                        hashtbl.h
//--------------------------------------------------------------------


template < class T, class KF >
class HashTbl
{
public:
	HashTbl(int initTableSize);
	~HashTbl();

	void insert(const T &newDataItem);
	bool remove(KF searchKey);
	bool retrieve(KF searchKey, T &dataItem);
	void clear();

	bool isEmpty() const;
	bool isFull() const;

	void showStructure() const;

private:
	int hash(const string& str) const {
		int val = 0;
		for (char c : str) {
			val +=c;
		}
		return val;   //here
	}
	int tableSize;
	List<T> *dataTable;
};

//--------------------------------------------------------------------
//                        hashtbl.cpp
//--------------------------------------------------------------------

template < class T, class KF >
HashTbl<T, KF>::HashTbl(int initTableSize) : tableSize(initTableSize)
{
	dataTable = new List<T>[tableSize];
}

template < class T, class KF >
HashTbl<T, KF>:: ~HashTbl()
{
	delete[] dataTable;
}

template < class T, class KF >
void HashTbl<T, KF>::insert(const T &newDataItem)
{
	int index = hash(newDataItem.getKey()) % tableSize;

	if (dataTable[index].isEmpty())
		dataTable[index].insert(newDataItem);
	else
	{
		dataTable[index].gotoBeginning();
		do
		{
			if (dataTable[index].getCursor().getKey() == newDataItem.getKey())
			{
				dataTable[index].replace(newDataItem);
				return;
			}
		} while (dataTable[index].gotoNext());

		dataTable[index].insert(newDataItem);
	}
}

template < class T, class KF >
bool HashTbl<T, KF>::remove(KF searchKey)
{
	T temp;
	int index = hash(searchKey) % tableSize;

	if (dataTable[index].isEmpty())
		return false;

	dataTable[index].gotoBeginning();
	do
	{
		if (dataTable[index].getCursor().getKey() == searchKey)
		{
			dataTable[index].remove();
			return true;
		}
	} while (dataTable[index].gotoNext());

	return false;
}

template < class T, class KF >
bool HashTbl<T, KF>::retrieve(KF searchKey, T &dataItem)
{

	int index = hash(searchKey) % tableSize;

	if (dataTable[index].isEmpty())
		return false;

	dataTable[index].gotoBeginning();
	do
	{
		if (dataTable[index].getCursor().getKey() == searchKey)
		{
			dataItem = dataTable[index].getCursor();
			return true;
		}
	} while (dataTable[index].gotoNext());

	return false;
}

template < class T, class KF >
void HashTbl<T, KF>::clear()
{
	for (int i = 0; i<tableSize; i++)
	{
		dataTable[i].clear();
	}
}

template < class T, class KF >
bool HashTbl<T, KF>::isEmpty() const
{
	for (int i = 0; i<tableSize; i++)
	{
		if (!dataTable[i].isEmpty())
			return false;
	}

	return true;
}

template < class T, class KF >
bool HashTbl<T, KF>::isFull() const
{
	for (int i = 0; i<tableSize; i++)
	{
		if (!dataTable[i].isFull())
			return false;
	}

	return true;
}

template < class T, class KF >
void HashTbl<T, KF>::showStructure() const
{
	cout << "The Hash Table has the following entries" << endl;
	for (int i = 0; i<tableSize; i++)
	{
		cout << i << ": ";
		if (dataTable[i].isEmpty())
			cout << "_";
		else
		{
			dataTable[i].gotoBeginning();
			do
			{
				cout << dataTable[i].getCursor().getKey() << " ";
			} while (dataTable[i].gotoNext());
		}
		cout << endl << endl;
	}
}

//--------------------------------------------------------------------
//                         login.cpp
//
//  program that reads in username/login pairs and then
//  performs authentication of usernames.
//--------------------------------------------------------------------

struct Password
{
	void setKey(string newKey) {
		username = newKey;
	}
	string getKey() const {
		return username;
	}

	int hash(const string str) const
	{
		int val = 0;

		for (unsigned int i = 0; i<str.length(); i++)
			val += str[i];
		return val;
	}
	string username,
	       password;
};

int main() {
	HashTbl<Password, string> passwords(10);
	Password tempPass;
	string name;      
	string pass;      
	bool userFound;   

	//*********************************************************
	// Read in the password file
	//*********************************************************
	ifstream passFile("password.txt");

	if (!passFile) {
		cout << "Unable to open 'password.txt'!" << endl;
		exit(0);
	}

	passFile >> tempPass.username;
	while (!passFile.eof() && !passwords.isFull())
	{
		passFile >> tempPass.password;

		passwords.insert(tempPass);

		passFile >> tempPass.username;
	}



	//*********************************************************
	//  Prompt for a Login and Password and check if valid
	//*********************************************************
	cout << "Login: ";
	while (cin >> name) {                                               
		Password retrievedUser;
		bool userFound = passwords.retrieve(name, retrievedUser);

		cout << "Password: ";
		cin >> pass;

		if (userFound && retrievedUser.password == pass) {
			cout << "Authentication successful!" << endl;
		} else {
			cout << "Authentication failure!" << endl;
		}

		cout << "Login: ";
	}
	cout << endl;

	return 0;
}
