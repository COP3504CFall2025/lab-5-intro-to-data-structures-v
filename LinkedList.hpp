#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T> *prev;
    Node<T> *next;
};

template <typename T>
class LinkedList
{
public:
    // Behaviors
    void printForward() const
    {
        if (!head)
        {
            return;
        }

        Node<T> *current = head;

        for (size_t i = 0; i < count; i++)
        {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
    void printReverse() const
    {
        if (!tail)
        {
            return;
        }

        Node<T> *current = tail;

        for (size_t i = 0; i < count; i++)
        {
            std::cout << current->data << std::endl;
            current = current->prev;
        }
    }

    // Accessors
    [[nodiscard]] unsigned int getCount() const { return count; }
    Node<T> *getHead() { return head; }
    const Node<T> *getHead() const { return head; }

    Node<T> *getTail() { return tail; }
    const Node<T> *getTail() const { return tail; }

    // Insertion
    void addHead(const T &data)
    {
        Node<T> *newNode = new Node<T>;

        newNode->data = data;
        if (getCount() == 0)
        {
            newNode->next = nullptr;
        }
        else
        {
            newNode->next = head;
        }
        newNode->prev = nullptr;

        if (head != nullptr)
        {
            head->prev = newNode;
        }

        head = newNode;
        if (getCount() == 0)
        {
            tail = newNode;
        }
        count++;
    }

    void addTail(const T &data)
    {
        Node<T> *newNode = new Node<T>;

        newNode->data = data;
        if (getCount() == 0)
        {
            newNode->prev = nullptr;
        }
        else
        {
            newNode->prev = tail;
        }
        newNode->next = nullptr;

        if (tail != nullptr)
        {
            tail->next = newNode;
        }

        tail = newNode;
        if (getCount() == 0)
        {
            head = newNode;
        }
        count++;
    }

    // Removal
    bool removeHead()
    {
        if (head != nullptr)
        {
            Node<T> *temp = head;

            head = head->next;

            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
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
    bool removeTail()
    {
        if (tail != nullptr)
        {
            Node<T> *temp = tail;

            tail = tail->prev;

            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
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

    void clear()
    {
        while (head != nullptr)
        {
            removeHead();
        }

        count = 0;
    }

    // Operators
    LinkedList<T> &operator=(LinkedList<T> &&other) noexcept;
    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    // Construction/Destruction
    LinkedList();
    LinkedList(const LinkedList<T> &list);
    LinkedList(LinkedList<T> &&other) noexcept;
    ~LinkedList();

    // Stores pointers to first and last Node<T>s and count
    Node<T> *head;
    Node<T> *tail;
    unsigned int count;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;

    Node<T> *current = list.head;
    while (current != nullptr)
    {
        addTail(current->data);
        current = current->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other) noexcept
{
    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    clear();

    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;

    return *this;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    clear();

    Node<T> *current = rhs.head;
    while (current != nullptr)
    {
        addTail(current->data);
        current = current->next;
    }

    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
    count = 0;
}