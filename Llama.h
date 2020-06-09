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
    int GetNumNodes() { return m_numNodes; }
    void SetNumNodes(unsigned int& num) { m_numNodes = num; }

    void SetNumData(unsigned int& num) { m_numData = num; }

    T* GetTop() { return m_top; }
    void SetTop(T& source) { *m_top = source; }

    void SetCurrentNode(LlamaNode<T, LN_SIZE>& source) { *m_current_node = source; }
    LlamaNode<T, LN_SIZE>* GetCurrentNode() { return m_current_node; }

    //LlamaNode<T, LN_SIZE> GetHead() { return *m_head; }

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
            Copy_Arr(*source_curr, *m_head, source.m_numData, source.m_numNodes);

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
            Copy_Arr(*source_curr, *curr_cpy, source.m_numData, source.m_numNodes);


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

    void Copy_Arr(const LlamaNode<T, LN_SIZE>& source, LlamaNode<T, LN_SIZE>& copy, const int& total_source_data, const int& total_num_nodes) {
        int i = LN_SIZE - 1;
        // Tests if the last element from the source is in this node  

        int last_index = (total_source_data - (LN_SIZE * (total_num_nodes - GetNumNodes()))) - 1;
        while (i >= 0) {
            // tests if the last element is found 
            if (i == last_index) {
                copy.arr[i] = source.arr[i];

                // Set the current node of the stack
                SetCurrentNode(copy);

                // Set the top of the stack
                SetTop(copy.arr[i]);

                SetNumData(++m_numData);
                break;
            }
            else {
                copy.arr[i] = source.arr[i];
                SetNumData(++m_numData);
                i--;
            }
        }
    }
    bool IsFull() {
        if (m_top == &m_current_node->arr[0]) {
	  return true;
	}
        return false;

    }

    unsigned int m_numData;
    unsigned int m_numNodes;
    T* m_top;
    LlamaNode<T, LN_SIZE>* m_head;
    LlamaNode<T, LN_SIZE>* m_current_node;
    LlamaNode<T, LN_SIZE>* m_tail;
    bool m_bottom;
};


#include "Llama.cpp"


#endif

