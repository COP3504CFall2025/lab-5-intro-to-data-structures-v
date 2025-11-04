#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
        if (!head) {
            return;
        }

        Node* current = head;

        for (int i = 0; i < count; i++) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
	void printReverse() const {
        if (!tail) {
            return;
        }

        Node* current = tail;

        for (int i = 0; i < count; i++) {
            std::cout << current->data << std::endl;
            current = current->prev;
        }
    }

	// Accessors
	[[nodiscard]] unsigned int getCount() const
	Node* getHead() { return head; }
	const Node* getHead() const { return head; }

	Node* getTail() { return tail; }
	const Node* getTail() const { return tail; };

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};

	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    head = list->head;
    tail = list->tail;
    count = list->count;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
    head = other->head;
    tail = other->tail;
    count = other->count;

    other->head = nullptr;
    other->tail = nullptr;
    other->count = 0;
}

template <typename T>
LinkedList<T>&LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this == other) { return *this; }

    Node* newHead = other->head;
    Node* newTail = other->tail;
    unsigned int newCount = other->count;
    
    delete head;
    delete tail;
    delete count;

    head = newHead;
    tail = newTail;
    count = newCount;

    other->head = nullptr;
    other->tail = nullptr;
    other->count = 0;

    return *this;
}

template <typename T>
LinkedList<T>&LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this == other) { return *this; }
    Node* newHead = other->head;
    Node* newTail = other->tail;
    unsigned int newCount = other->count;

    delete head;
    delete tail;
    delete count;

    head = rhs->head;
    tail = rhs->tail;
    count = rhs->count;

    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    delete head;
    delete tail;
    delete count;
}

template <typename T>
unsigned int LinkedList<T>::getCount() const {
    return count;
}