#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node *head;
    int _length;

public:
    LinkedList();                       // constructor
    ~LinkedList();                      // destructor
    void display();                     // method for displaying the graph
    void addBack(T data);               // method for adding data
    void remove(T data);                // method for removing data
    Node *find(T data);                 // method for finding data
    Node *getHead();                    // method for getting the head of the linked list
    int getLength() { return _length; } // method for getting the length of the linked list
    T &operator[](int index)            // operator for accessing the data at index
    {
        Node *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), _length(0)
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
}

template <typename T>
void LinkedList<T>::display()
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void LinkedList<T>::addBack(T data)
{
    if (head == nullptr)
    {
        head = new Node(data);
        return;
    }
    Node *current = head;
    while (current->next != nullptr)
        current = current->next;

    current->next = new Node(data);
}

template <typename T>
void LinkedList<T>::remove(T data)
{
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr)
    {
        if (current->data == data)
        {
            if (previous == nullptr)
                head = current->next;
            else
                previous->next = current->next;
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::find(T data)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data == data)
            return current;
        current = current->next;
    }
    return nullptr;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::getHead()
{
    return head;
}
#endif