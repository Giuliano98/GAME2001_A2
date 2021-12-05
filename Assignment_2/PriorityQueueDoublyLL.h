#pragma once
#include <cassert>

// Template Class Declarations
template <class T> class LinkIterator;
template <class T> class DoublyLinkedList;
// ---------------------------

// Node Class - in a Doubly Linked List
template <class T>
class LinkNode
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class DoublyLinkedList<T>;
private:
	int m_priority;			// The level of Priority of the node
	T m_data;				// Data inside the node

	LinkNode* m_next;		// Pointer to the next node/nullptr
	LinkNode* m_previous;	// Pointer to the previous node/nullptr
};

// Iterator Class
template <class T>
class LinkIterator
{
public:
	// DoublyLL can access to private var in LinkIterator
	friend class DoublyLinkedList<T>;

	LinkIterator() : m_node(nullptr) {}
	~LinkIterator() {}

	// ----------- OVERLOADED OPERATORS ------------------
	void operator=(LinkNode<T>* node) { m_node = node; }

	T& operator*()	// Read the data stored on the node being pointed
	{
		assert(m_node != nullptr);
		return m_node->m_data;
	}

	// Move the iterator to the NEXT node
	void operator++()	// Prefix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}
	void operator++(int) // Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}
	// Move the iterator to the PREVIOUS node
	void operator--()	// Prefix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_previous;
	}
	void operator--(int)	// Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_previous;
	}
	// ---------------------------------------------------

	// Check if this->ptr is equal or different to the ptr pass
	bool operator!=(LinkNode<T>* node) { return (m_node != node); }
	bool operator==(LinkNode<T>* node) { return (m_node == node); }
	// --------------------------------------------------------

	// Check if this->ptr is pointing to something or not
	bool isValid() { return (m_node != nullptr); }
private:
	LinkNode<T>* m_node;	// Pointer to a node in the linked list
};

// Define a linked list itself
template <class T>
class DoublyLinkedList
{
private:
	// Helps to organized in UpdateNodesPointers
	// Set a guide for the direction of insertion 
	enum Location
	{
		Before = 0,
		After,
		PushFront,
		PopFront,
		PushBack,
		PopBack
	};

	// Organized Functions
	LinkNode<T>* CreateNewNode()
	{
		LinkNode<T>* node = new LinkNode<T>;
		assert(node != nullptr);
		node->m_priority = NULL;
		node->m_next = nullptr;
		node->m_previous = nullptr;
		return node;
	}

	void UpdateNodesPointerBefore(LinkNode<T>* node, LinkIterator<T>& it, T& newData)
	{
		node->m_data = newData;
		node->m_next = it.m_node;
		node->m_previous = it.m_node->m_previous;

		// Point the (previous node) to the (new node)
		if (node->m_previous != nullptr)
			node->m_previous->m_next = node;

		// (The Next Node) previous_ptr points to (the new node)
		it.m_node->m_previous = node;

		// Check to see if the iterator was pointing to the root
		if (it.m_node == m_root)
			m_root = node;
	}
	void UpdateNodesPointerAfter(LinkNode<T>* node, LinkIterator<T>& it, T& newData)
	{
		node->m_data = newData;
		node->m_next = it.m_node->m_next;
		node->m_previous = it.m_node;

		// Point the (next node) to the (new node)
		if (node->m_next != nullptr)
			node->m_next->m_previous = node;

		// (The Previous Node) next_ptr points to (the new node)
		it.m_node->m_next = node;

		// Check if the new node is the last node in the list.
		if (it.m_node == m_lastNode)
			m_lastNode = node;
	}
	void UpdateNodesPointers(Location loc, LinkNode<T>* node, LinkIterator<T>* it, T* newData)
	{
		switch (loc)
		{
		case Before:
			UpdateNodesPointerBefore(node, it, newData);
			break;
		case After:
			UpdateNodesPointerAfter(node, it, newData);
			break;
		}
	}


	void UpdateNodePointersPushFront(LinkNode<T>* node)
	{
		if (m_root != nullptr) // Linked List has at least 1 item
		{
			node->m_next = m_root;
			m_root->m_previous = node;
			m_root = node;
		}
		else // Linked list is empty
		{
			m_root = node;
			m_lastNode = node;
		}
	}
	void UpdateNodePointersPopFront()
	{
		m_root = m_root->m_next;    // Set the next point of root as the new root

		if (m_root != nullptr)  	// Check if the new root is pointing to somewhere.
			m_root->m_previous = nullptr;
		else					    // If it's pointing to nullptr, set lastNode to nullptr
			m_lastNode = nullptr;
	}
	void UpdateNodePointersPushBack(LinkNode<T>* node)
	{
		// Add the new LinkNode to the existing DoublyLinkedList
		if (m_lastNode != nullptr) // DoublyLinkedList is populated. Push to the end of the list.
		{
			m_lastNode->m_next = node;
			node->m_previous = m_lastNode;
		}
		else // An empty linked list
			m_root = node;

		m_lastNode = node;
	}
	void UpdateNodePointersPopBack()
	{
		// Check if there is only 1 node
		if (m_root->m_next == nullptr)
		{
			delete m_root;
			m_root = nullptr;
			m_lastNode = nullptr;
		}
		else // Linked list has at least 2
		{
			LinkNode<T>* prevNode = m_lastNode->m_previous;

			prevNode->m_next = nullptr;
			delete m_lastNode;
			m_lastNode = prevNode;
			prevNode = nullptr;
		}
	}
	void UpdateNodePointers(Location loc, LinkNode<T>* node = nullptr)
	{
		switch (loc)
		{
		case PushFront:
			UpdateNodePointersPushFront(node);
			break;
		case PopFront:
			UpdateNodePointersPopFront();
			break;
		case PushBack:
			UpdateNodePointersPushBack(node);
			break;
		case PopBack:
			UpdateNodePointersPopBack();
			break;
		}
	}

	void IncreaseSize() { m_size++; }
	void DecreaseSize() { m_size = (m_size == 0 ? m_size : m_size - 1); } // Prevent negative sizes 
	// -------------------

public:
	// Constructor and Destructor
	DoublyLinkedList() : m_size(0), m_root(nullptr), m_lastNode(nullptr) {}
	~DoublyLinkedList()
	{
		while (m_root)
			Pop_Back();
	}
	// --------------------------

	// --------------- POSITIONING FUNCTIONS ----------------------
	LinkNode<T>* Begin()
	{
		assert(m_root != nullptr);
		return m_root;
	}
	LinkNode<T>* End() { return nullptr; }
	LinkNode<T>* Last()
	{
		assert(m_lastNode != nullptr);
		return m_lastNode;
	}
	// ------------------------------------------------------------
	
	// --------------- PRIORITY QUEUE FUNCTIONS --------------------
	void Insert_Before(LinkIterator<T>* it, T newData)
	{
		assert(it->m_node != nullptr);

		// Create a new node
		auto node = CreateNewNode();

		// Change/Update pointer of next and previous to the new node
		UpdateNodesPointers(Before, node, it, &newData);

		// You add a new Node SO increase the link list size
		IncreaseSize();
	}
	void Insert_After(LinkIterator<T>* it, T newData)
	{
		assert(it->m_node != nullptr);

		// Create a new node
		auto node = CreateNewNode();

		// Change/Update pointer of next and previous to the new node
		UpdateNodesPointers(After, node, it, &newData);

		// You add a new Node SO increase the link list size
		IncreaseSize();
	}
	// -------------------------------------------------------------
	
	// --------------- LINKED LIST OPERATIONS ---------------------
	void Push_Front(T newData)
	{
		// Create a new node
		auto node = CreateNewNode();
		node->m_data = newData;

		// Update ptr in the new node
		UpdateNodePointers(PushFront, node);

		// You add a new Node SO increase the link list size
		IncreaseSize();
	}
	void Pop_Front()
	{
		assert(m_root != nullptr);

		// Create a temp that will allow us to delete the content as needed
		LinkNode<T>* temp = m_root;

		// Reroute pointers
		UpdateNodePointers(PopFront);

		// Delete Node and deallocate ptr 
		delete temp;
		temp = nullptr;

		// You deleted a Node SO decrease the link list size
		DecreaseSize();
	}
	void Push_Back(T newData)
	{
		// Create a new node
		auto node = CreateNewNode();
		node->m_data = newData;

		// Reroute pointers
		UpdateNodePointers(PushBack, node);

		// You add a new Node SO increase the link list size
		IncreaseSize();
	}
	void Pop_Back()
	{
		assert(m_root != nullptr);

		// Reroute pointers
		UpdateNodePointers(PopBack);

		// You deleted a Node SO decrease the link list size
		DecreaseSize();
	}
	// ------------------------------------------------------------

	// Getters and Setters
	int GetSize() { return m_size; }
	// -------------------
private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};
