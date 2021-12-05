#pragma once

#include "PriorityQueueDoublyLL.h"

template<class T, class CMP>
class PriorityQueue
{
public:
	PriorityQueue(int size)
	{
		assert(size > 0);
		m_size = size;
	}
	~PriorityQueue() {}

	// Priority Queue Functions
	void push(T val)
	{
		if (m_elements.GetSize() >= GetMaxSize())
			Resize(m_size + m_size);
		else
			assert(m_elements.GetSize() < m_size);

		// If the list is empty just push the val
		if (isEmpty())
			m_elements.Push_Back(val);
		else
		{
			itr = m_elements.Begin(); // set my itr to the first node

			CMP cmp;	// Placeholder for the comparisons

			while (itr.isValid())
			{
				// Move the iterator to the place where we want to insert the new node into
				if (cmp(val, *itr))
					break;	

				// Go to the next node
				itr++;
			}

			if (itr.isValid())
				m_elements.Insert_Before(itr, val);	// Insert the node before the itr marked
			else
				m_elements.Push_Back(val);
		}
	}

	void pop() { m_elements.Pop_Front(); }

	T& front()
	{
		itr = m_elements.Begin();
		return *itr;
	}
	T& back()
	{
		itr = m_elements.Last();
		return *itr;
	}

	// Helper functions
	int GetSize() {	return m_elements.GetSize(); }
	int GetMaxSize() { return m_size; }

	bool isEmpty() { return (m_elements.GetSize() == 0); }

	void Resize(int size)
	{
		assert(size > 0);
		m_size = size;
	}

private:
	DoublyLinkedList<T> m_elements; // Priority Queue Linked List
	LinkIterator<T> itr;
	int m_size;
};


// Less than compare with nonpointer type
template<class T>
class less_cmp 
{
public:
	inline bool operator()(T lVal, T rVal) { return lVal < rVal; }
};

// Less than compare with pointer types
template<class T>
class less_cmp_pointer
{
public:
	inline bool operator()(T lVal, T rVal) { return ((*lVal) < (*rVal)); }
};

// Less than compare with nonpointer type
template<class T>
class greater_cmp 
{
public:
	inline bool operator()(T lVal, T rVal) { return !(lVal < rVal); }
};

// Less than compare with pointer types
template<class T>
class greater_cmp_pointer 
{
public:
	inline bool operator()(T lVal, T rVal) { return !((*lVal) < (*rVal)); }
};