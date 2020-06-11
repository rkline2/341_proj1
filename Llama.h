#ifndef _LLAMA_H_
#define _LLAMA_H_

/* File: Llama.h

   This file has the class declaration for the LlamaNode class
   for Project 1. See project description for details.

   You may add public and private data members to the Llama class.

   You may add public and private member functions to the Llama class.

*/


#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std;


class LlamaUnderflow : public std::out_of_range {

public:

    LlamaUnderflow(const string& what) : std::out_of_range(what) { }

};


template <class T, int LN_SIZE>
class Llama {

public:

    Llama();
    Llama(const Llama<T, LN_SIZE>& other);   // copy constructor
    ~Llama();


    int size();
    void dump();
    void push(const T& data);
    T pop();


    void dup();    //  (top) A B C D -> A A B C D
    void swap();   //  (top) A B C D -> B A C D 
    void rot();    //  (top) A B C D -> C A B D


    T peek(int offset) const;


    // overloaded assignment operator
    //
    const Llama<T, LN_SIZE>& operator=(const Llama<T, LN_SIZE>& rhs);


    //
    // Add your public member functions & public data mebers here:
    //

    // Name: m_numNodes Accessor and Mutator
    // Description: These are helper functions that returns and sets
    // the number of nodes in the entire stack 
    // Pre-Conditions: Source stack exists  
    // Post-Conditions: Returns and sets the amount of nodes in the stack
    int GetNumNodes() { return m_numNodes; }
    void SetNumNodes(unsigned int& num) { m_numNodes = num; }

    // Name: m_numData Mutator
    // Description: This helper function sets the total number of 
    // items in the stack. 
    // Pre-Conditions: Source stack exists  
    // Post-Conditions: Sets the amount of items in the stack
    void SetNumData(unsigned int& num) { m_numData = num; }
    // size() replaces the getter function for m_numData

    // Name: m_top Accessor and Mutator
    // Description: These are helper functions that returns and sets
    // the top item of the stack 
    // Pre-Conditions: Source stack exists  
    // Post-Conditions: returns and sets the top item in the stack
    T* GetTop() { return m_top; }
    void SetTop(T& source) { *m_top = source; }

    // Name: m_current_node Accessor and Mutator
    // Description: These are helper functions that returns and sets
    // the current nodes of the stack 
    // Pre-Conditions: Source stack exists  
    // Post-Conditions: returns and sets the current node in the stack
    void SetCurrentNode(LlamaNode<T, LN_SIZE>& source) { *m_current_node = source; }
    LlamaNode<T, LN_SIZE>* GetCurrentNode() { return m_current_node; }


private:
    //
    // Add your private member functions & private data mebers here:
    //

    // Name: Copy_Stack 
    // Description: This is a helper function that performs a deep
    // copy of the nodes from the source stack to the new stack (*this)
    // Pre-Conditions: Source stack exists and passed as a parameter 
    // Post-Conditions: returns a deep copy of the 
    // source stack to the new stack
    void Copy_Stack(const Llama<T, LN_SIZE>& source) {
        m_head = nullptr;
        LlamaNode<T, LN_SIZE>* source_curr = source.m_head;
        LlamaNode<T, LN_SIZE>* prev_cpy = m_head, * curr_cpy = m_head;

        // creates m_head if the source is not a empty LL
        if (source_curr != nullptr) {
            m_head = new LlamaNode<T, LN_SIZE>();

            // increments the number of nodes in the stack by 1
            SetNumNodes(++m_numNodes);
            // Copy the array in the node 
            Copy_Arr(*source_curr, *m_head, source);

            // have m_tail point to the last node in the stack (m_head)
            m_tail = m_head;

            // source moves up one node
            source_curr = source_curr->m_next;

            // sets up the two pointers for deep copying
            prev_cpy = m_head;
            curr_cpy = m_head->m_next;
        }
        while (source_curr != nullptr) {

            // creates a new node and copy data  
            curr_cpy = new LlamaNode<T, LN_SIZE>();

            // increments the number of nodes in the stack by 1
            SetNumNodes(++m_numNodes);
            // Copy the array in the node 
            Copy_Arr(*source_curr, *curr_cpy, source);


            // have m_next point to the new node  
            prev_cpy->m_next = curr_cpy;

            // have m_tail point to the last node in the stack 
            m_tail = curr_cpy;

            // source & new stack move up one node
            prev_cpy = curr_cpy;
            curr_cpy = curr_cpy->m_next;
            curr_cpy = nullptr;

            source_curr = source_curr->m_next;
        }

    }

    // Name: Copy_Arr 
    // Description: This is a helper function that performs a deep
    // copy of the array from the source stack to the copy stack (*this)
    // Pre-Conditions: Source stack & node exists and passed as a parameter.
    // Copy stack node exists and passed as a parameter
    // Post-Conditions: Creates a deep copy of the source array to the copy array
    void Copy_Arr(const LlamaNode<T, LN_SIZE>& source, LlamaNode<T, LN_SIZE>& copy, const Llama<T, LN_SIZE>& sourceStack) {
        int i = LN_SIZE - 1;
        // Tests if the last element from the source is in this node  

        //int last_index = (total_source_data - (LN_SIZE * (total_num_nodes - GetNumNodes()))) - 1;
        while (i >= 0) {
            // tests if the last element is found 
            if (sourceStack.m_top == &source.arr[i]) {
                // Set the values
                copy.arr[i] = source.arr[i];

                // Set the current node of the stack
                m_current_node = &copy;

                // Set the top of the stack
                m_top = &copy.arr[i];

                // top is found so stack is not empty
                m_bottom = false;

                SetNumData(++m_numData);
                i = 0;
            }
            else {
                copy.arr[i] = source.arr[i];
                SetNumData(++m_numData);

            }
            i--;
        }
    }

    // Name: IsFull 
    // Description: This is a helper function that determines if 
    // the array in the current node is full or not.
    // Pre-Conditions: Stack & current nodes exist  
    // Post-Conditions: Returns true if the array is full. Returns false 
    // if the array is not full
    bool IsFull() {
        if (m_top == &m_current_node->arr[0] && !m_bottom) {
            return true;
        }
        return false;

    }

    unsigned int m_numData; // number of items in the stack
    unsigned int m_numNodes; // number of nodes in the stack
    T* m_top; // top item in the stack
    LlamaNode<T, LN_SIZE>* m_head; // head node
    LlamaNode<T, LN_SIZE>* m_current_node; // current node in the stack
    LlamaNode<T, LN_SIZE>* m_tail; // last node in the stack
    bool m_bottom; // very last item in the stack exists
};


#include "Llama.cpp"


#endif

