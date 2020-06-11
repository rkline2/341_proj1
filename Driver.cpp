/*****************************************
** File:    Driver.cpp
** Project: CMSC 341 Project 1, Summer 2020
** Author:  Rooklyn Kline
** Date:    6/11/20
** Section: 01
** E-mail:  rkline2@umbc.edu
**
** The file Driver.cpp contains a total
** of nine tests. Each tests will implement
** one of the public functions such as push(),
** pop(), etc. The user will be able to control the size
** of the stack, how many pushes, popps to implement.
**
***********************************************/

#include <iostream>
#include "Llama.h"
using namespace std;


int main() {
	// change LN_SIZE here
	const int SIZE = 10;
	int num_items = 0;
	string usrResponce;
	cout << "******Beginning Tests******" << endl << endl;
	cout << "You will be asked to enter any value once a test is completed" << endl;
	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;
	// Test 1: Push function
	cout << "Test 1: Push()" << endl;
	Llama<int, SIZE>* stack_1 = new Llama<int, SIZE>;

	cout << "Creating int stack_1 \"T\" of LN_SIZE " << SIZE << endl;
	cout << "How many items do you want in you stack?: ";
	cin >> num_items;

	cout << "Generating stack of items 0-" << num_items - 1 << "..." << endl;

	for (int i = 0; i < num_items; i++) {
		stack_1->push(i);
	}

	cout << endl << "Displaying stack_1 (expect order to be from " << num_items - 1 << "-0):" << endl;
	stack_1->dump();

	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;

	// Test 2: Copy Constructor
	cout << "Test 2: Copy Constructor" << endl;
	cout << "Copying data from stack_1 to new int stack_2" << endl;
	Llama<int, SIZE>* stack_2 = new Llama<int, SIZE>(*stack_1);

	cout << endl << "------Displaying stack_1 & stack_2------" << endl;

	cout << "******stack_1******" << endl;
	stack_1->dump();
	cout << "******stack_2******" << endl;
	stack_2->dump();

	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;

	// Test 3: Pop Function
	cout << "Test 3: pop()" << endl;
	cout << "How many items do you want to pop stack_1?: ";
	cin >> num_items;
	for (int i = 0; i < num_items; i++) {
		try {
			stack_1->pop();
		}
		catch (LlamaUnderflow& e) {
			cerr << "*****\n";
			cerr << "Llama Stack error: " << e.what() << endl;
			cerr << "*****\n";
			break;
		}
	}

	cout << endl << "------Displaying stack_1 & stack_2------" << endl;

	cout << "******stack_1******" << endl;
	stack_1->dump();
	cout << "******stack_2******" << endl;
	stack_2->dump();

	cout << "Enter any value to continue: ";
	cin >> usrResponce;

	// Test 4: Swap Function
	cout << "Test 4: swap()" << endl;
	cout << "------Swapping stack_2------" << endl;
	cout << "**Before swap:**" << endl;
	stack_2->dump();
	try {
		stack_2->swap();
	}
	catch (LlamaUnderflow& e) {
		cerr << "*****\n";
		cerr << "Llama Stack error: " << e.what() << endl;
		cerr << "*****\n";


	}
	cout << "**After swap:**" << endl;
	stack_2->dump();

	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;

	// Test 5: Rotate Function
	cout << "Test 5: rot()" << endl;
	cout << "------Rotating stack_1------" << endl;
	cout << "**Before rotate:**" << endl;
	stack_1->dump();
	try {
		stack_1->rot();
	}
	catch (LlamaUnderflow& e) {
		cerr << "*****\n";
		cerr << "Llama Stack error: " << e.what() << endl;
		cerr << "*****\n";
	}
	cout << "**After rotate:**" << endl;
	stack_1->dump();

	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;

	// Test 6: Duplicate
	cout << "Test 6: dup()" << endl;
	cout << "How many times do you want to duplicate stack_2?: ";
	cin >> num_items;
	for (int i = 0; i < num_items; i++) {
		try {
			stack_2->dup();
		}
		catch (LlamaUnderflow& e) {
			cerr << "*****\n";
			cerr << "Llama Stack error: " << e.what() << endl;
			cerr << "*****\n";
			break;
		}
	}

	cout << "------displaying stack_2------" << endl;
	stack_2->dump();

	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;

	// Test 7: Assignment Operator
	cout << "Test 7: Assignment Operator" << endl;
	cout << "-----stack_2 = stack_1-----" << endl;
	*stack_2 = *stack_1;

	cout << "******stack_1******" << endl;
	stack_1->dump();
	cout << "******stack_2******" << endl;
	stack_2->dump();


	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;

	// Test 8: Top Item && peek()
	cout << "Test 8: Top && peek(0)" << endl;
	try {
		cout << "stack_1 top: " << *stack_1->GetTop() << " memory: " << stack_1->GetTop() << endl;
		cout << "stack_1 peek(0): " << stack_1->peek(0) << endl;
	}
	catch (LlamaUnderflow& e) {
		cerr << "*****\n";
		cerr << "Llama Stack error: " << e.what() << endl;
		cerr << "*****\n";
	}
	try {
		cout << "stack_2 top: " << *stack_2->GetTop() << " memory: " << stack_2->GetTop() << endl;
		cout << "stack_2 peek(0): " << stack_2->peek(0) << endl;
	}
	catch (LlamaUnderflow& e) {
		cerr << "*****\n";
		cerr << "Llama Stack error: " << e.what() << endl;
		cerr << "*****\n";
	}


	cout << "Enter any value to continue: ";
	cin >> usrResponce;
	cout << endl;

	delete stack_1;
	delete stack_2;

	cout << "******Tests Completed!******" << endl;
	cout << "Modify SIZE if you want to change LN_SIZE" << endl;
	cout << "Run Valgrind for any memory leaks" << endl;
	return 0;
}

