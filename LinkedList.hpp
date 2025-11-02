#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(T data, Node* prev, Node* next): data(data), prev(prev), next(next) {};
	};
	// Behaviors
	void printForward() const {
		Node* node = head;
		if (node) {
			cout << node->data << " ";
			while ((node = node->next)) {
				cout << node->data << " ";
			}
			cout << endl;
		}
	}
	void PrintReverse() const {
		Node* node = tail;
		if (node) {
			cout << node->data << " ";
			while ((node = node->prev)) {
				cout << node->data << " ";
			}
			cout << endl;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node* getHead() {return head;}
	const Node* getHead() const {return head;}
	Node* getTail() {return tail;}
	const Node* getTail() const {return tail;}

	// Insertion
	void AddHead(const T& data) {
		head = new Node(data, nullptr, head);
		if (head->next) {
			head->next->prev = head;
		}
		if (++count == 1) {
			tail = head;
		}
	}
	void AddTail(const T& data) {
		tail = new Node(data, tail, nullptr);
		if (tail->prev) {
			tail->prev->next = tail;
		}
		if (++count == 1) {
			head = tail;
		}
	}

	// Removal
	bool RemoveHead() {
		if (head) {
			Node* next = head->next;
			if (next) {
				delete head;
				head = next;
				next->prev = nullptr;
			} else {
				delete head;
			}
			return true;
		} else {
			return false;
		}
	}
	bool RemoveTail() {
		if (tail) {
			Node* prev = tail->prev;
			if (prev) {
				delete tail;
				tail = prev;
				prev->next = nullptr;
			} else {
				delete tail;
			}
			return true;
		} else {
			return false;
		}
	}
	void Clear() {
	    Node* prev = head;
		Node* node;
		if (prev) {
			while ((node = prev->next)) {
				delete prev;
				prev = node;
			}
		}
		delete prev;
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		Clear();
		head = list.head;
		tail = list.tail;
		count = list.count;
		list.head = nullptr;
		list.tail = nullptr;
		list.count = 0;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		Clear();
		count = list.count;
		if (list.head) {
			head = new Node(list.head->data, nullptr, nullptr);
			Node* current_list_node = head;
			Node* other_list_node = list.head;
			while ((other_list_node = other_list_node->next)) {
				current_list_node->next = new Node(other_list_node->data, current_list_node, nullptr);
				current_list_node = current_list_node->next;
			}
			tail = current_list_node;
		}
	}

	// Construction/Destruction
	LinkedList() = default;
	LinkedList(const LinkedList<T>& list) {
		count = list.count;
		if (list.head) {
			head = new Node(list.head->data, nullptr, nullptr);
			Node* current_list_node = head;
			Node* other_list_node = list.head;
			while ((other_list_node = other_list_node->next)) {
				current_list_node->next = new Node(other_list_node->data, current_list_node, nullptr);
				current_list_node = current_list_node->next;
			}
			tail = current_list_node;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = list.head;
		tail = list.tail;
		count = list.count;
		list.head = nullptr;
		list.tail = nullptr;
		list.count = 0;
	}
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node* head = nullptr;
	Node* tail = nullptr;
	unsigned int count = 0;

};

