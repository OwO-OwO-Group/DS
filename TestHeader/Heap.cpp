#include "Heap.h"

template <class T>
void HEAP<T>::print() {
    for (auto i : data)
        cout << i << endl;
}

template <class T>
void HEAP<T>::insert(T temp) {
    data.push_back(temp);
}

