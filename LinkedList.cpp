// LinkedList.cpp : Defines the exported functions for the DLL application.
//

#include "LinkedList.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

ILinkedList::ILinkedList() : m_count(0)
{

}

Node::Node() : m_value(-1), m_next(nullptr)
{

}
Node::Node(int val) : m_value(val), m_next(nullptr)
{

}
Node::Node(int val, Node * nextNode) : m_value(val), m_next(nextNode)
{

}
void Node::setItem(const int& val)
{
	m_value = val;
}
void Node::setNext(Node* nextNodePtr)
{
	m_next = nextNodePtr;
}
int Node::getItem() const
{
	return m_value;
}
Node * Node::getNext() const
{
	return m_next;
}
Node::~Node()
{
	std::cout << "Deleting node with value " << m_value << std::endl;
	//todo
}

PointerBasedLinkedList::PointerBasedLinkedList() : ILinkedList(), m_head(nullptr)
{

}
/** Returns true  if list is empty, otherwise true */
bool PointerBasedLinkedList::isEmpty() const
{
	if (m_head == NULL){ 
		return true;
	}
	else{
		return false;
	}
}
/** Adds a value to the LinkedList.  Return true if able to, otherwise false */
bool PointerBasedLinkedList::add(int val)
{
	Node * tempPtr = new Node(); //creates ptr for data storage
	
	Node * curPtr = new Node(); //creates ptr for iterating through
	
	tempPtr ->setItem(val); //assigns the value (in this case an int val) to the temp ptr
	
	curPtr = m_head; //sets up curPtr to iterate to find end of linked list

	while(curPtr != NULL){ //this loop iterates through the linked list using curPtr
		if((curPtr-> getNext()) != NULL){
		curPtr = curPtr ->getNext();
		}
		else{
			break;
		}
	}
	if(m_head == NULL){ //if the linked list has not been constructed yet, this if statement begins it
		m_head = tempPtr;
	}
	else{ //otherwise, curPtr is set to the value of tempPtr
		curPtr -> setNext(tempPtr);
	}
	m_count++;
	curPtr = NULL; //deletion of used ptrs
	delete curPtr;

	tempPtr = NULL;
	delete tempPtr;
	//used GeeksForGeeks for assistance. code is not word for word, but functionality is there
	return true;
	//finished!
}
/** Remove a value to the LinkedList.  Return true if able to, otherwise false.
Will only remove one entry if there are multiple entries with the same value */
bool PointerBasedLinkedList::remove(int val)
{
	Node * p = new Node();
	Node * start = new Node();
	Node * temp = new Node();
	start -> setNext(m_head);
	temp -> setNext(m_head);
	p->setItem(val);
	int val_exists;
	int data;
	//checks if initial value in the linked list is present at the start
	if(start == p){
		val_exists=1;
	}
	/*iterates through the linked list to find the first instance of the variable and sets an integer to 1 if it does.
	It will continue to iterate through the list until it finds the second instance of the variable and deletes it
	*/
	while(temp->getNext() != NULL){
		temp->getNext();
		if(val_exists == 1 && temp == p){
			temp =temp->getNext()->getNext();
			return true;
		}
		if(temp == p && val_exists != 1){
			val_exists=1;
		}
	}
	p=NULL;
	delete p;
	temp=NULL;
	delete temp;
	start=NULL;
	delete start;
	return false;
	
}

/** Remove  all elements from LinkedList */
void PointerBasedLinkedList::clear()
{
	Node * curPtr = new Node();
	while(m_head != NULL){ //checks to make sure the list isn't already empty
		m_head = m_head->getNext(); //gets the next ptr after the head
		curPtr ->setNext(NULL); //sets the current ptr to one after it
		curPtr = m_head; //sets current ptr as new head

	}
	m_head = NULL; //makes sure to set head ptr to null
	m_count = 0; //resets counter
    // note: used the book's part about the clear function as a guide
	delete curPtr;
}
PointerBasedLinkedList::~PointerBasedLinkedList()
{
	clear(); //calls clear
	delete m_head; //deletes the head ptr
	//done
}

std::string PointerBasedLinkedList::toString() const
{
	string str = "";
	Node * curPtr = new Node();
	int holdVal = 0;
	curPtr = m_head; //sets up curPtr to iterate to find end of linked list

	for(int i = 0; i < m_count; i++){
		if(str == ""){ //checks to see if string is empty
			holdVal = curPtr->getItem(); //gets the item of the ptr
			str = std::to_string(holdVal); //sets string to that ptr
		}else{
			holdVal = curPtr->getItem(); //gets item of the ptr
			str = str + " " + std::to_string(holdVal); //adds to a string with a string before hand
		}
		curPtr = curPtr ->getNext(); //iterates the ptr
	}
	
	return str;
}

ArrayBasedLinkedList::ArrayBasedLinkedList() : ILinkedList()
{
	for (int i = 0; i < 10; ++i) {
		m_values[i] = -1;
	}
}

bool ArrayBasedLinkedList::isEmpty() const
{
	bool empty = true;
	for(int i = 0; i < 10; i++){
		if(m_values[i] == -1){ //checks to see if the value at the slot in the array is 'empty'
			empty = true; //if so, then keep empty at true
		}else{
			empty = false; //if not, set empty to false and then break out of the loop immediately
			break;
		}
	}
	return empty; //returns boolean value
} 
bool ArrayBasedLinkedList::add(int val)
{
	if(m_count != 10){ //very simple function to add values to the array and then iterate the count. checks to make sure values can fit inside the array
		m_values[m_count] = val;
		m_count = m_count + 1;
		return true;
	}else{
		return false;
	}

}

bool ArrayBasedLinkedList::remove(int val)
{
	bool removed = false;
	int count;
	for(int i = 0; i < m_count; i++){
		count = 0;
		if(m_values[i] == val){
			count = i;
			for(count; count <= m_count; count++){
				m_values[count] = m_values[count + 1];
			}
			m_count --;
			removed = true;
			break;
		}else{
			removed = false;
		}
	}
	return removed;
}

void ArrayBasedLinkedList::clear()
{
	for (int i = 0; i < 10; ++i) {
		m_values[i]=-1; //resets the list to -1. As far as I understand -1 is a default value for the array, as given above.
	}
	
}
ArrayBasedLinkedList::~ArrayBasedLinkedList()
{
	clear();
}

std::string ArrayBasedLinkedList::toString() const
{
	string str = "";
	
	for(int i = 0; i < m_count; i++){
		if(str == ""){
			str = std::to_string(m_values[i]);
		}else{
			str = str + " " + std::to_string(m_values[i]);
		}
	}

	return str;
}
