#include <iostream>
#include "PriorityQueue.h"
using namespace std;

class MyTestClass
{
public:
	MyTestClass() : m_priority(0), m_id(0) {}
	MyTestClass(int p, int id) : m_priority(p), m_id(id) {}
	~MyTestClass() {}

	int GetPriority() { return m_priority; }
	int GetID() { return m_id; }

	// Overload operator
	bool operator<(MyTestClass& m)
	{
		if (m_priority < m.GetPriority())
			return true;

		return false;
	}
	bool operator>(MyTestClass& m) { return !(*this < m); }
private:
	int m_priority;
	int m_id;
};

int main()
{
	cout << "Priority Queue list based in a Doubly Linked List!" << endl << endl;
	
	const int SIZE = 2;
	PriorityQueue<MyTestClass, less_cmp<MyTestClass> > MyQueue(SIZE);
	cout << "Queue Max Size: " << MyQueue.GetMaxSize() << endl;
	cout << "Queue content Size: " << MyQueue.GetSize() << endl;
	cout << "---------------------------------------------"  << endl;

	MyQueue.push(MyTestClass(3, 100));
	MyQueue.push(MyTestClass(2, 286));
	MyQueue.push(MyTestClass(1, 362));
	MyQueue.push(MyTestClass(3, 435));
	MyQueue.push(MyTestClass(6, 865));

	MyQueue.pop();
	MyQueue.pop();

	MyQueue.push(MyTestClass(2, 745));
	MyQueue.push(MyTestClass(9, 385));
	MyQueue.push(MyTestClass(5, 355));

	// Display the priority queue
	cout << "After some Push and Pop"  << endl;
	cout << "Queue Max Size: " << MyQueue.GetMaxSize() << endl;
	cout << "Queue content Size: " << MyQueue.GetSize() << endl;
	cout << "---------------------------------------------"  << endl;

	while (!MyQueue.isEmpty())
	{
		cout << "  Priority: " << MyQueue.front().GetPriority();
		cout << "  ID: " << MyQueue.front().GetID();
		cout << endl;

		MyQueue.pop();
	}

	cout << "---------------------------------------------"  << endl;

	if (MyQueue.isEmpty() == true)
	{
		cout << "The container is empty." << endl;
	}
	else
	{
		cout << "The container is NOT empty." << endl;
	}

	cout << endl  << endl;

	return 0;
}