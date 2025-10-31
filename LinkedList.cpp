#include "LinkedList.hpp"
// Behaviors
template <typename T>
void LinkedList<T>::printForward() const {
    Node* node = head;
    if (node) {
        cout << node->data << " ";
        while ((node = node->next)) {
            cout << node->data << " ";
        }
        cout << endl;
    }
}
template <typename T>
void LinkedList<T>::printReverse() const {
    Node* node = tail;
    if (node) {
        cout << node->data << " ";
        while ((node = node->prev)) {
            cout << node->data << " ";
        }
        cout << endl;
    }
}

// // Insertion
template <typename T>
void LinkedList<T>::addHead(const T& data) {
    head = new Node(data, nullptr, head);
    if (head->next) {
        head->next->prev = head;
    }
    if (++count == 1) {
        tail = head;
    }
}
template <typename T>
void LinkedList<T>::addTail(const T& data) {
    tail = new Node(data, tail, nullptr);
    if (tail->prev) {
        tail->prev->next = tail;
    }
    if (++count == 1) {
        head = tail;
    }
}

// // Removal
template <typename T>
bool LinkedList<T>::removeHead() {
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
// bool removeTail();
// void Clear();

// // Operators
// LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
// LinkedList<T>& operator=(const LinkedList<T>& rhs);

// Construction/Destruction
// LinkedList(const LinkedList<T>& list);
// LinkedList(LinkedList<T>&& other) noexcept;
template <typename T>
LinkedList<T>::~LinkedList() {
    Node* prev = head;
    Node* node;
    if (node) {
        while ((node = prev->next)) {
            delete prev;
            prev = node;
        }
    }
    delete prev;
}

// Accessors
// [[nodiscard]] unsigned int getCount() const;
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() {
    return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::getHead() const {
    return head;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getTail() {
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::getTail() const {
    return tail;
}