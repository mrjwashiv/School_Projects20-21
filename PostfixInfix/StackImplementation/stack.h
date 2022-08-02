#include <iostream>

using namespace std;

#ifndef STACK
#define STACK

template <class xType>
class Stack
{
	private:
		struct stackNode
		{
			xType Element;
			stackNode* Next;
		};
		typedef stackNode* stackPtr;

		stackPtr Tos;
		int size;

	public: 
		Stack();
		~Stack();
		bool isEmpty();
		bool isFull();
		void push(xType);
		void pop();
		xType top();
		int Size();
};

#endif