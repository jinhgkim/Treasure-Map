/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque() : data(vector<T>()), n1(0), n2(0) {}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
     if((unsigned long)n2 == data.size())
        data.push_back(newItem);
    else
        data[n2] = newItem;
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T val = data[n1];
    n1++;

    int size = n2 - n1;
    if (n1 >= size) {
        // copy the array
        vector<T> newData;
        for (int i = n1; i < n2; i++){
            newData.push_back(data[i]);
        }
        // resize and assign the new array
        data.resize(size);
        data = newData;
        n1 = 0;
        n2 = size;
    }

    return val;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T val = data[n2-1];
    n2--;

    int size = n2 - n1;
    if (n1 >= size)
    {
        // copy the array
        vector<T> newData;
        for (int i = n1; i < n2; i++)
        {
            newData.push_back(data[i]);
        }
        // resize and assign the new array
        data.resize(size);
        data = newData;
        n1 = 0;
        n2 = size;
    }
    return val;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data[n1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data[n2-1];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return n1 == n2;
}