#include "stack.h"

template <class xType>
Stack<xType>::Stack()
{
	size = 0;
	Tos = nullptr;
}

template <class xType>
Stack<xType>::~Stack()
{
	size = 0;
	Tos = nullptr;
}

template <class xType>
bool Stack<xType>::isEmpty()
{
	return (size == 0 && Tos == nullptr);
}

template <class xType>
bool Stack<xType>::isFull()
{
	return (false);
}

template <class xType>
int Stack<xType>::Size()
{
	return (size);
}

template <class xType>
void Stack<xType>::push(xType item)
{
	stackPtr SPtr = new stackNode;
	SPtr->Element = item;
	SPtr->Next = Tos;
	Tos = SPtr;
	size++;

}

template <class xType>
void Stack<xType>::pop()
{
	Tos = Tos->Next;
	size--;
}

template <class xType>
xType Stack<xType>::top()
{
	if (!this->isEmpty())
	{
		return (Tos->Element);
	}
	else
	{
		exit(1);
	}
}