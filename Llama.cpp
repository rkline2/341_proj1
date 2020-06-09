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
**
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
	m_head = new LlamaNode<T, LN_SIZE>;
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
	LlamaNode<T, LN_SIZE>* curr = m_head, *prev = m_head;
	while (curr != nullptr) {
		prev = curr;
		curr = curr->m_next;

		delete prev; 
		prev = nullptr;
	}

}

template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size() { return m_numData; }

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
		cout << "This stack does not have an extra node" << endl;
	}
	else {
		cout << "This stack does have an extra node" << endl;
	}

	cout << "Stack contents, top to bottom" << endl;
	cout << "----- " << curr_node << " -----" << endl;

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
	cout << "----- bottom of stack -----" << endl;
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data) {
	T cpy_data = data;
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
			SetTop(m_head->arr[LN_SIZE - 1]);
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

template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::pop() {
	T val = *m_top;
	unsigned int curr_index = 0;

	// the stack does not exist
	if (m_numNodes == 0) {
		throw LlamaUnderflow("Current stack does not exist");
		
	}

	// top is located at the very last element 
	// of the stack
	else if (m_top == &m_tail->arr[LN_SIZE - 1]) {

		// all data is earsed entire stack is deleted 
		delete m_tail;
		m_head = nullptr; m_current_node = nullptr;
		m_tail = nullptr;

		SetNumNodes(--m_numNodes);
	}

	// top is located at the last
	// element of the current node
	else if (m_top == &m_current_node->arr[LN_SIZE - 1]) {

		m_current_node = m_current_node->m_next;


		// top points to new array
		SetTop(m_current_node->arr[0]);	
	}

	// default case
	else {
		SetTop(*++m_top);
	}

	SetNumData(--m_numData);
	curr_index = m_numData % LN_SIZE;

	// removes empty node if needed 
	if (curr_index <= (LN_SIZE / 2) && m_current_node != m_head) {
		delete m_head;
		m_head = nullptr;
		m_head = m_current_node;
		SetNumNodes(--m_numNodes);
	}


	return val;
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup() {
	// stack is empty 
	if (size() == 0) { throw(LlamaUnderflow); }
	
	// deep copy top value
	T val = *m_top;
	push(val);
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::swap() {
	const int MIN_DATA = 2;
	int index = size() % LN_SIZE;

	LlamaNode<T, LN_SIZE>* nextNode = nullptr;
	T* firstVal = m_top, * secondVal = nullptr; 
	T firstCpy = *firstVal, secondCpy = NULL; 

	if (size() < MIN_DATA) { throw(LlamaUnderflow); }

	// top is at last element of current array 
	if(index == 1){
		nextNode = m_current_node->m_next;

		// points to first element of second node
		secondVal = &nextNode->arr[0];

	}

	// default case: both values are next to eachother in stack
	else {
		// initalize the value next to top
		secondVal = m_top++;
	}

	// deep copy second value
	secondCpy = *secondVal;

	// swap the two values
	*firstVal = secondCpy;
	*secondVal = firstCpy;

	SetTop(*firstVal);

}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::rot() {
	const int MIN_DATA = 3, CURR_INDEX = size() % LN_SIZE,
	ONE_VAL = 1, TWO_VAL = 2;

	LlamaNode<T, LN_SIZE>* nextNode = nullptr;
	T* firstVal = m_top, * secondVal = m_top;
	T firstCpy = *firstVal, secondCpy = NULL;

	// Stack does not have enough items to swap 
	if (size() < MIN_DATA) { throw(LlamaUnderflow); }

	// Current stack does not contain at least three items 
	switch(CURR_INDEX){

	// current node contains one element 
	case ONE_VAL:
		nextNode = m_current_node->m_next;
		secondVal = &nextNode->arr[ONE_VAL];
		break;

	// current node contains two elements 
	case TWO_VAL:
		nextNode = m_current_node->m_next;
		secondVal = &nextNode->arr[0];
		break;

	// current node contains at least three elements 
	default:
		for (int i = 0; i < TWO_VAL; i++) { secondVal++; }
		break;
	}

	// deep copy second value
	secondCpy = *secondVal;

	// swap the two values
	*firstVal = secondCpy;
	*secondVal = firstCpy;

	SetTop(*firstVal);
}

template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::peek(int offset) const {
	const int MAX_DATA = m_numData;
	unsigned int i = 0;
	LlamaNode<T, LN_SIZE>* curr_node = m_current_node;
	T* curr_data = m_top;
	T val;

	if (offset >= MAX_DATA || offset < 0) {
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
