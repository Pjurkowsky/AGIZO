#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), _length(0)
{
}
LinkedList::~LinkedList()
{
}

void LinkedList::display()
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void LinkedList::addBack(int data)
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

void LinkedList::remove(int data)
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

LinkedList::Node *LinkedList::find(int data)
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
