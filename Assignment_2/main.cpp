#include <iostream>
#include "PriorityQueue.h"
using namespace std;

class MyTestClass
{
public:

private:
	int m_priority;
	int m_id;
};


class NetworkMessage
{
public:
	NetworkMessage() : m_priority(0), m_id(0) {}
	NetworkMessage(int p, int id) : m_priority(p), m_id(id) {}
	~NetworkMessage() {}

	int GetPriority()
	{
		return m_priority;
	}
	int GetID()
	{
		return m_id;
	}

	// Overload operator
	bool operator<(NetworkMessage& m)
	{
		// Check the priority level of both network messages
		if (m_priority < m.GetPriority())
		{
			return true;
		}
		else if (m_id < m.GetID())
		{
			return true;
		}

		return false;
	}
	bool operator>(NetworkMessage& m)
	{
		return !(*this < m);	// NOT( this is less than m )
	}
private:
	int m_priority;
	int m_id;
};

int main()
{
	cout << "Priority queue data structure example!" << endl << endl;

	const int SIZE = 2;
	PriorityQueue<NetworkMessage, less_cmp<NetworkMessage> > que(SIZE);
	cout << que.GetMaxSize() << endl;
	cout << "Priority queue content (Size - " << que.GetSize() << ") : " << endl;

	que.push(NetworkMessage(3, 100));
	que.push(NetworkMessage(2, 286));
	que.push(NetworkMessage(1, 362));
	que.push(NetworkMessage(3, 435));

	// Display the priority queue
	cout << "Priority queue content (Size - " << que.GetSize() << ") : " << endl;
	cout << que.GetMaxSize() << endl;

	while (que.isEmpty() == false)
	{
		cout << "  Priority: " << que.front().GetPriority();
		cout << "  ID: " << que.front().GetID();
		cout << endl;

		que.pop();
	}

	cout << endl;

	if (que.isEmpty() == true)
	{
		cout << "The container is empty." << endl;
	}
	else
	{
		cout << "The container is NOT empty." << endl;
	}

	return 0;
}