#ifndef _LLAMA_CPP_
#define  _LLAMA_CPP_
/*****************************************
** File:    Llama.cpp
** Project: CMSC 341 Project 1, Summer 2020
** Author:  Rooklyn Kline
** Date:    5/29/20
** Section: 01
** E-mail:  rkline2@umbc.edu
**
** The Llama.cpp contains the majority of the
** functions that will manipulate an array of data.
** Some of these functions include pop, push, swap, etc.
** The functions will create and keep track of having
** the correct number of nodes with the help of private
** member functions in Llama.h.
**
***********************************************/

#include <iostream>
#include "Llama.h"
using namespace std;


// Name: Default Constructor
// Creates a Llama Stack that points to one node 
// The Node's data is automatically set to an initial T value
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama() {
	m_head = new LlamaNode<T, LN_SIZE>();
	m_bottom = true;

	m_numNodes = 1;
	m_numData = 0;

	
	m_top = &m_head->arr[LN_SIZE - 1];
	
	m_tail = m_head;
	m_current_node = m_head;
}

// Name: Copy Constructor 
// Creates a deep copy of a pre-existing stack 
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama(const Llama<T, LN_SIZE>& source) {
	Llama<T, LN_SIZE>* new_stack = this;

	// deep copies nodes from the source stack
	new_stack->Copy_Stack(source);
}

// Name: Llama Destructor 
// Removes all nodes and data created in a stack 
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama() {
	LlamaNode<T, LN_SIZE>* curr = m_head, * prev = m_head;

	// Removes all nodes in stack
	while (curr != nullptr) {
		prev = curr;
		curr = curr->m_next;

		delete prev;
		prev = nullptr;
	}

	// deallocates all member variables in Llama.h
	m_current_node = nullptr;
	m_head = nullptr;
	m_tail = nullptr;
	m_top = nullptr;
	m_numNodes = 0;
	m_numData = 0;
	m_bottom = true;

}

// Name: size
// Returns the number of items in the stack 
template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size() { return m_numData; }

// Name: dump
// Displays the items, number of items, number of nodes 
// in the stack
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dump() {
	const int MAX_DATA = size();
	LlamaNode<T, LN_SIZE>* curr_node = m_current_node;
	T* curr_data = m_top;
	cout << "***** Llama Stack Dump ******" << endl;
	cout << "LN_SIZE = " << LN_SIZE << endl;
	cout << "# of items in the stack = " << MAX_DATA << endl;
	m_current_node->report();

	if (m_head == m_current_node) {
		cout << "\nThis stack does not have an extra node" << endl << endl;
	}
	else {
		cout << "\nThis stack does have an extra node: " << m_head << endl << endl;
	}

	cout << "Stack contents, top to bottom" << endl;
	cout << "----- " << curr_node << " -----" << endl;
	if (MAX_DATA != 0) {
		while (curr_data != &m_tail->arr[LN_SIZE - 1]) {

			cout << *curr_data << endl;

			// last item in current node
			if (curr_data == &curr_node->arr[LN_SIZE - 1]) {
				curr_node = curr_node->m_next;
				cout << "----- " << curr_node << " -----" << endl;
				curr_data = &curr_node->arr[0];
			}

			// default case
			else {
				curr_data++;
			}
		}
		cout << *curr_data << endl;
	}
	cout << "----- bottom of stack -----" << endl << endl;
	cout << "*****************************" << endl;
}

// Name: push
// Given a value, sets the item to the top of the stack
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data) {
	T cpy_data = data;

	// size of array must contain at least 1 item
	if (LN_SIZE > 0) {
		// if the list is full
		if (IsFull()) {
			// if there's no empty node in the stack
			if (m_current_node == m_head) {
				// creates a new node using m_curr_node
				m_current_node = nullptr;
				m_current_node = new LlamaNode<T, LN_SIZE>();

				// increment number of nodes 
				SetNumNodes(++m_numNodes);

				m_current_node->m_next = m_head;

				// move m_head to the new node
				m_head = m_current_node;

				// m_top points and sets the last element to the data given
				m_top = &m_head->arr[LN_SIZE - 1];
				SetTop(cpy_data);

			}

			// empty node exists
			else {
				// m_top points and sets the first element to the data given 
				m_top = &m_head->arr[LN_SIZE - 1];
				SetTop(cpy_data);

				// move m_current_node to m_head 
				m_current_node = m_head;
			}
		}

		// default push 
		else {

			// very first item in stack
			if (m_bottom) {
				SetTop(cpy_data);

				m_bottom = false;
			}
			else {
				SetTop(*--m_top);
				SetTop(cpy_data);
			}
		}
		SetNumData(++m_numData);
	}
}

// Name: pop
// Returns top item of the stack 
// and sets the top to the next item in the stack
template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::pop() {
	T val = *m_top;
	unsigned int curr_index = 0;

	// the stack does not exist
	if (m_numNodes == 0 || m_numData == 0) {
		throw LlamaUnderflow("Current stack is empty");
	}
	
		// top is located at the very last element 
		// of the stack
		if (m_top == &m_tail->arr[LN_SIZE - 1]) {

			// all data is earsed  
			m_top = &m_tail->arr[LN_SIZE - 1];

			m_bottom = true;

			SetNumNodes(--m_numNodes);
		}

		// top is located at the last
		// element of the current node
		else if (m_top == &m_current_node->arr[LN_SIZE - 1]) {

			m_current_node = m_current_node->m_next;

			// top points to new array
			m_top = &m_current_node->arr[0];
		}

		// default case
		else {
			SetTop(*++m_top);
		}

		SetNumData(--m_numData);
		curr_index = m_numData % LN_SIZE;



		// default case: removes empty node if needed 
		if ((curr_index <= (LN_SIZE / 2)) && (m_current_node != m_head) && (curr_index != 0) && (LN_SIZE != 1)) {
			delete m_head;
			m_head = nullptr;
			m_head = m_current_node;
			SetNumNodes(--m_numNodes);
		}

		// special case: LN_SIZE == 1
		else if (LN_SIZE == 1 && m_head->m_next != m_current_node) {
			LlamaNode<T, LN_SIZE>* curr = m_head;
			m_head = m_head->m_next;
			delete curr;
			curr = nullptr;
			SetNumNodes(--m_numNodes);
		}

	

	return val;
}

// Name: dup
// Duplicates the top item of the stack 
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup() {
	// stack is empty
	if (size() == 0 || m_numNodes == 0) { throw LlamaUnderflow("Current stack is empty"); }

	// deep copy top value
	T val = *m_top;
	push(val);
	
}

// Name: swap
// Swaps the top two items in the stack
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::swap() {
	const int MIN_DATA = 2;

	LlamaNode<T, LN_SIZE>* nextNode = nullptr;
	T* firstVal = m_top, * secondVal = nullptr;
	T firstCpy = *firstVal, secondCpy;

	if (size() < MIN_DATA || m_numNodes == 0) { throw LlamaUnderflow("Cannot swap items"); }

	// top is at last element of current array 
	if (m_top == &m_current_node->arr[LN_SIZE - 1]) {
		nextNode = m_current_node->m_next;

		// points to first element of second node
		secondVal = &nextNode->arr[0];

	}

	// default case: both values are next to eachother in stack
	else {
		// initalize the value next to top
		secondVal = ++m_top;
	}

	// deep copy second value
	secondCpy = *secondVal;

	// swap the two values
	*firstVal = secondCpy;
	*secondVal = firstCpy;

	m_top = firstVal;
	
}

// Name: rot
// Rotates the top three items in the stack
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::rot() {
	const int MIN_DATA = 3, CURR_INDEX = size() % LN_SIZE,
		ONE_VAL = 1, TWO_VAL = 2;

	LlamaNode<T, LN_SIZE>* nextNode = nullptr;
	T* firstVal = m_top, * secondVal = nullptr, * thirdVal = nullptr;
	T firstCpy = *firstVal, secondCpy, thirdCpy;

	// Stack does not have enough items to swap 
	if (size() < MIN_DATA || m_numNodes == 0 || size() == 0) { throw LlamaUnderflow("Not enough items to swap"); }

	
	// Special case: Size of the array is 1
	if (LN_SIZE == 1) {
		nextNode = m_current_node->m_next;

		secondVal = &nextNode->arr[0];

		nextNode = nextNode->m_next;

		thirdVal = &nextNode->arr[0];

	}

	// default case
	else {
		// Current stack does not contain at least three items 
		switch (CURR_INDEX) {

			// current node contains one element 
		case ONE_VAL:
			nextNode = m_current_node->m_next;
			secondVal = &nextNode->arr[0];
			thirdVal = &nextNode->arr[ONE_VAL];
			break;

			// current node contains two elements 
		case TWO_VAL:
			nextNode = m_current_node->m_next;
			secondVal = &m_current_node->arr[LN_SIZE - 1];
			thirdVal = &nextNode->arr[0];
			break;

			// current node contains at least three elements 
		default:
			secondVal = firstVal;
			thirdVal = firstVal;
			for (int i = 0; i < TWO_VAL; i++) {
				secondVal = thirdVal;
				thirdVal++;
			}
			break;
		}
	}

	// deep copy for second value
	secondCpy = *secondVal;

	// deep copy third value
	thirdCpy = *thirdVal;

	// swap the values
	*firstVal = thirdCpy;
	*secondVal = firstCpy;
	*thirdVal = secondCpy;

	m_top = firstVal;
	
}

// Name: peek
// Given an integer, returns the item located at 
// the given integer
template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::peek(int offset) const {
	const int MAX_DATA = m_numData;
	int i = 0;
	LlamaNode<T, LN_SIZE>* curr_node = m_current_node;
	T* curr_data = m_top;
	T val;

	if (offset >= MAX_DATA || offset < 0 || m_numNodes == 0) {
		throw LlamaUnderflow("Cannot access current value");
	}
	
	while (i != offset) {
		// last item in current node
		if (curr_data == &curr_node->arr[LN_SIZE - 1]) {
			curr_node = curr_node->m_next;
			curr_data = &curr_node->arr[0];
		}

		// default case
		else {
			curr_data++;
		}
		i++;
	}
	val = *curr_data;
	
	return val;
}

// Name: Overloaded Assignment Operator
// Given a stack, returns a deep copy of the given stack 
template <class T, int LN_SIZE>
const Llama<T, LN_SIZE>& Llama<T, LN_SIZE>::operator= (const Llama<T, LN_SIZE>& source) {
	if (this != &source) {
		Llama<T, LN_SIZE>* new_stack = this;

		// removes nodes from the new stack
		new_stack->~Llama();
		// deep copies nodes from the source stack
		new_stack->Copy_Stack(source);
	}

	return *this;
}


#endif 
