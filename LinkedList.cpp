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
template <typename T>
bool LinkedList<T>::removeTail() {
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
template <typename T>
void LinkedList<T>::Clear() {
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
}

// // Operators
// LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
// LinkedList<T>& operator=(const LinkedList<T>& rhs);

// Construction/Destruction
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    count = list.count;
    if (list.head) {
        head = new Node(list.head->data, nullptr, nullptr);
        Node* current_list_node = head;
        Node* other_list_node = list.head;
        while ((other_list_node = other_list_node->next)) {
            current_list_node->next = new Node(other_list_node->data, current_list_node, nullptr);
            current_list_node = current_list_node->next;
        }
        // current_list_node->next = new Node(list.tail->data, current_list_node, nullptr);
        tail = current_list_node;
}
}
// LinkedList(LinkedList<T>&& other) noexcept;
template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}

// Accessors
template <typename T>
[[nodiscard]] unsigned int LinkedList<T>::getCount() const {
    return count;
}
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