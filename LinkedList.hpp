#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
        if (!head) {
            return;
        }

        Node<T>* current = head;

        for (int i = 0; i < count; i++) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
	void printReverse() const {
        if (!tail) {
            return;
        }

        Node<T>* current = tail;

        for (int i = 0; i < count; i++) {
            std::cout << current->data << std::endl;
            current = current->prev;
        }
    }

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node<T>* getHead() { return head; }
	const Node<T>* getHead() const { return head; }

	Node<T>* getTail() { return tail; }
	const Node<T>* getTail() const { return tail; }

	// Insertion
	void addHead(const T& data) {
        Node<T>* newNode = new Node<T>;
        
        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = head;

        if (head != nullptr) {
            head->prev = newNode;
        }

        head = newNode;
        count++;
    }

	void addTail(const T& data) {
        Node<T>* newNode = new Node<T>;

        newNode->data = data;
        newNode->prev = tail;
        newNode->next = nullptr;

        if (tail != nullptr) {
            tail->next = newNode;
        }

        tail = newNode;
        count++;
    }

	// Removal
	bool removeHead() {
        if (head != nullptr) {
            Node<T>* temp = head;

            head = head->next;
            
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }

            temp->prev = nullptr;
            temp->next = nullptr;
            delete temp;
            temp = nullptr;

            count--;

            return true;
        }
        return false;
    }
	bool removeTail() {
        if (tail != nullptr) {
            Node<T>* temp = tail;

            if (tail->prev != nullptr) {
                tail->prev->next = nullptr;
                tail = tail->prev;
            }

            temp->prev = nullptr;
            temp->next = nullptr;
            delete temp;
            temp = nullptr;

            count--;

            return true;
        }
        return false;        
    }
	void Clear() {
        while (head != nullptr) {
            removeHead();
        }

        count = 0;
    }

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:

	// Stores pointers to first and last Node<T>s and count
	Node<T>* head;
	Node<T>* tail;
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
    if (this == &other) { return *this; }

    Node<T>* newHead = other->head;
    Node<T>* newTail = other->tail;
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
    if (this == &rhs) { return *this; }
    Node<T>* newHead = rhs->head;
    Node<T>* newTail = rhs->tail;
    unsigned int newCount = rhs->count;

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