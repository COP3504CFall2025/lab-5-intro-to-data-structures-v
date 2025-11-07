#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    public:
        T data;
		Node<T>* prev;
		Node<T>* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
        if (head == nullptr) { return; }

        Node<T>* current = head;

        for (size_t i = 0; i < count; i++) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }

	void printReverse() const {
        if (tail == nullptr) { return; }

        Node<T>* current = tail;

        for (size_t i = 0; i < count; i++) {
            std::cout << current->data << std::endl;
            current = current->prev;
        }
    }

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node<T>* getHead() { return head; }
	const Node<T>* getHead() const { return head; }

	Node<T>* getTail() { return tail; }
	const Node<T>* getTail() const { return tail; };

	// Insertion
	void addHead(const T& data) {
        Node<T>* newHead = new Node<T>;
        newHead->data = data;
        newHead->prev = nullptr;
        newHead->next = head;

        if (head != nullptr) { head->prev = newHead; }
        head = newHead;
        count++;
    }

	void addTail(const T& data) {
        Node<T>* newTail = new Node<T>;
        newTail->data = data;
        newTail->next = nullptr;
        newTail->prev = tail;

        if (tail != nullptr) { tail->next = newTail; }
        tail = newTail;
        count++;
    }

	// Removal
	bool removeHead() {
        if (head == nullptr) { return false; }

        Node<T>* oldHead = head;
        head = head->next;

        if (head != nullptr) { head->prev = nullptr; }
        else { tail = nullptr; }

        delete oldHead;
        count--;
        return true;
    }

	bool removeTail() {
        if (tail == nullptr) { return false; }

        Node<T>* oldTail = tail;
        tail = tail->prev;

        if (tail != nullptr) { tail->next = nullptr; }
        else { head = nullptr; }

        delete oldTail;
        count--;
        return true;
    }

	void clear() {
        while (head != nullptr) {
            removeHead();
        }

        count = 0;
    }

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept; // Done
	LinkedList<T>& operator=(const LinkedList<T>& rhs); // Done

	// Construction/Destruction
	LinkedList(); // Done
	LinkedList(const LinkedList<T>& list); // Done
	LinkedList(LinkedList<T>&& other) noexcept; // Done
	~LinkedList(); // Done

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    head = list.head;
    tail = list.tail;
    count = list.count;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
LinkedList<T>&LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this == &other) { return *this; }

    Node<T>* newHead = other.head;
    Node<T>* newTail = other.tail;
    unsigned int newCount = other.count;
    
    delete head;
    delete tail;

    head = newHead;
    tail = newTail;
    count = newCount;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;

    return *this;
}

template <typename T>
LinkedList<T>&LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this == &rhs) { return *this; }
    Node<T>* newHead = rhs.head;
    Node<T>* newTail = rhs.tail;
    unsigned int newCount = rhs.count;

    delete head;
    delete tail;

    head = newHead;
    tail = newTail;
    count = newCount;

    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}