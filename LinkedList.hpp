#pragma once
#include <iostream>

template <typename T> class LinkedList {
  struct Node {
    T data;
    Node *prev;
    Node *next;
  };

public:
  // -- Behaviors --

  void printForward() const {
    std::cout << "[" << count;
    const Node *curr = head;

    while (curr) {
      std::cout << ", " << curr->data;
      curr = curr->next;
    }

    std::cout << "]\n";
  }

  void printReverse() const {
    std::cout << "[" << count;
    const Node *curr = tail;

    while (curr) {
      std::cout << ", " << curr->data;
      curr = curr->prev;
    }

    std::cout << "]\n";
  }

  // -- Accessors --

  [[nodiscard]]
  unsigned int getCount() const {
    return count;
  }

  Node *getHead() { return head; }

  const Node *getHead() const { return head; }

  Node *getTail() { return tail; }

  const Node *getTail() const { return tail; }

  // -- Insertion --

  void addHead(const T &data) {
    if (head) {
      head->prev = new Node{data, nullptr, head};
      head = head->prev;
    } else {
      head = new Node{data, nullptr, nullptr};
      tail = head;
    }

    count++;
  }

  void addTail(const T &data) {
    if (tail) {
      tail->next = new Node{data, tail, nullptr};
      tail = tail->next;
    } else {
      tail = new Node{data, nullptr, nullptr};
      head = tail;
    }

    count++;
  }

  // -- Removal --

  bool removeHead() {
    if (!head) {
      return false;
    }

    Node *next_head = head->next;
    delete head;
    head = next_head;

    if (head) {
      head->prev = nullptr;
    } else {
      tail = nullptr;
    }

    count--;
    return true;
  }

  bool removeTail() {
    if (!tail) {
      return false;
    }

    Node *prev_tail = tail->prev;
    delete tail;
    tail = prev_tail;

    if (tail) {
      tail->next = nullptr;
    } else {
      head = nullptr;
    }

    count--;
    return true;
  }

  void clear() {
    while (head) {
      removeHead();
    }
  }

  // -- Operators --

  LinkedList<T> &operator=(LinkedList<T> &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    clear();

    count = other.count;
    head = other.head;
    tail = other.tail;

    other.count = 0;
    other.head = nullptr;
    other.tail = nullptr;

    return *this;
  }

  LinkedList<T> &operator=(const LinkedList<T> &rhs) {
    if (this == &rhs) {
      return *this;
    }

    clear();

    const Node *curr = rhs.head;

    while (curr) {
      addTail(curr->data);
      curr = curr->next;
    }

    return *this;
  }

  // -- Construction/Destruction --

  LinkedList() : head(nullptr), tail(nullptr), count(0) {}

  LinkedList(const LinkedList<T> &list)
      : head(nullptr), tail(nullptr), count(0) {
    const Node *curr = list.head;

    while (curr) {
      addTail(curr->data);
      curr = curr->next;
    }
  }

  LinkedList(LinkedList<T> &&other) noexcept
      : head(other.head), tail(other.tail), count(other.count) {
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
  }

  ~LinkedList() { clear(); }

private:
  // Stores pointers to first and last nodes and count
  Node *head;
  Node *tail;
  unsigned int count;
};
