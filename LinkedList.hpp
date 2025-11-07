#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};
template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node<T>* current = head;
		while (current->data != nullptr) {
			std::cout << current->data << std::endl;
			current = current->next;
		}
	};
	void printReverse() const {
		Node<T>* current = tail;
		while (current->value != nullptr) {
			std::cout << current->value << std::endl;
			current = current->prev;
		}
	};

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	};
	Node<T>* getHead() {
		return head;
	};
	const Node<T>* getHead() const {
		return head;
	};
	Node<T>* getTail() {
		return tail;
	};
	const Node<T>* getTail() const {
		return tail;
	};

	// Insertion
	void addHead(const T& data) {
		Node<T>* addHead = new Node<T>;
		addHead->data = data;
		if (head != nullptr) {
			addHead->next = head;
		}
		else {
			addHead->next = nullptr;
		}
		addHead->prev = nullptr;
		head = addHead;
		count++;
	};
	void addTail(const T& data) {
		Node<T>* addTail = new Node<T>;
		addTail->data = data;
		if (tail != nullptr) {
			addTail->prev = tail;
		}
		else {
			addTail->prev = nullptr;
		}
		addTail->next = nullptr;
		tail = addTail;
		count++;
	};

	// Removal
	bool removeHead() {
		if(head == nullptr)
			return false;

		Node<T>* temp = head;
		if (temp->next) {
			temp = temp->next;
			temp->prev = nullptr;
		}
		delete head;
		head = temp;
		count--;
		return true;
	};
	bool removeTail() {
		if(tail == nullptr)
			return false;

		Node<T>* temp = tail;
		if (temp->prev) {
			temp = temp->prev;
			temp->next = nullptr;
		}
		delete tail;
		tail = temp;
		count--;
		return true;
	};
	void clear() {
		while (head != nullptr) {
			Node<T>* temp = head->next;
			delete head;
			head = temp;
		}
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this != &other) {
			clear();
			head = other.getHead();
			tail = other.getTail();
			count = other.getCount();

			other.head = nullptr;
			other.tail = nullptr;
			other.count = 0;
		}
		return *this;
	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs){

		if (this != &rhs) {
			clear();
			count = rhs.getCount();
			head = rhs.getHead();
			for (size_t i = 0; i < rhs.getCount(); i++) {
				addTail(head->data);
				if (head->next != nullptr) {
					head = head->next;
				}
			}
		}
		return *this;
	};

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {};
	LinkedList(const LinkedList<T>& list) {
		count = list.getCount();
		head = list.getHead();
		for (size_t i = 0; i < list.getCount(); i++) {
			addTail(head->data);
			if (head->next != nullptr) {
				head = head->next;
			}
		}
	};
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	};
	~LinkedList() {
		clear();
	};

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};


