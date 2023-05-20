#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include <cstring>

template <typename T>
class Array
{
public:
    Array();                         // constructor
    ~Array();                        // destructor
    std::string toString();          // return a string representation of the list
    void addBack(const T &data);     // insert a node at back
    void addFront(const T &data);    // insert a node at front
    void removeFromIndex(int index); // delete a node from index
    void remove(const T &data);      // delete a node with given data
    bool contains(const T &data);    // check if list contains data
    size_t getLength();              // get length of list
    T &operator[](int index);

private:
    T *_data;
    size_t _length;
};

template <typename T>
Array<T>::Array() : _data(nullptr), _length(0)
{
}
template <typename T>
Array<T>::~Array()
{
    delete[] _data; // delete the array
}

// converts data from array to string
template <typename T>
std::string Array<T>::toString()
{
    std::string str;
    for (int i = 0; i < _length; i++)
        str += std::to_string(_data[i]) + " ";
    str += "\n";
    return str;
}

// adds data to back of array
template <typename T>
void Array<T>::addBack(const T &data)
{
    T *temp = new T[_length + 1];

    for (size_t i = 0; i < _length; i++)
        temp[i] = _data[i];

    delete[] _data;
    temp[_length] = data;
    _data = temp;
    _length++;
}

// adds data to front of array
template <typename T>
void Array<T>::addFront(const T &data)
{
    T *temp = new T[_length + 1];

    for (size_t i = 0; i < _length; i++)
        temp[i + 1] = _data[i];

    delete[] _data;
    temp[0] = data;
    _data = temp;
    _length++;
}

// removes data from array at index
template <typename T>
void Array<T>::removeFromIndex(int index)
{
    if (index < 0 || index >= _length)
        return;

    T *temp = new T[_length - 1];

    for (size_t i = 0; i < index; i++)
        temp[i] = _data[i];

    for (size_t i = index + 1; i < _length; i++)
        temp[i - 1] = _data[i];

    delete[] _data;
    _data = temp;
    _length--;
}

// removes data from array
template <typename T>
void Array<T>::remove(const T &data)
{
    for (size_t i = 0; i < _length; i++)
    {
        if (_data[i] == data)
        {
            removeFromIndex(i);
            return;
        }
    }
}

template <typename T>
bool Array<T>::contains(const T &data)
{
    for (size_t i = 0; i < _length; i++)
    {
        if (_data[i] == data)
            return true;
    }
    return false;
}

template <typename T>
size_t Array<T>::getLength()
{
    return _length;
}
template <typename T>
T &Array<T>::operator[](int index)
{
    return _data[index];
}
#endif