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
    LinkedList();
    ~LinkedList();
    void display();
    void addBack(T data);
    void remove(T data);
    Node *find(T data);
    Node *getHead();
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