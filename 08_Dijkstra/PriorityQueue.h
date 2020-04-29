//
// Created by olcia on 23.04.2020.
//

#ifndef INC_08_DIJKSTRA_PRIORITYQUEUE_H
#define INC_08_DIJKSTRA_PRIORITYQUEUE_H

#include <climits>

constexpr int MAX_SIZE = 1024;
using namespace std;

template<typename T>
struct Element{
    int* priority;
    T value;
    Element();
    Element(T value, int* priority);

    bool operator>(const Element& other);
    bool operator<(const Element& other);
    bool operator==(const Element& other);
};

template<typename T>
Element<T>::Element() : value(0), priority(0) {

}

template<typename T>
Element<T>::Element(T value, int* priority): value(value), priority(priority) {

}

template<typename T>
bool Element<T>::operator>(const Element &other) {
    return this->priority > other.priority;
}

template<typename T>
bool Element<T>::operator<(const Element &other) {
    return *this->priority < *other.priority;
}

template<typename T>
bool Element<T>::operator==(const Element &other) {
    return *this->priority == *other.priority;
}

template<typename T>
struct Heap{
    Element<T>* elements;
    int heapSize;

    Heap();
    ~Heap();

    int left(int i);
    int right(int i);
    int parent(int i);
    void heapify(int i);

public:
    void buildMinHeap();
};

template<typename T>
Heap<T>::Heap() {
    heapSize = 0;
    elements = new Element<T>[MAX_SIZE];
}

template<typename T>
Heap<T>::~Heap() {
    delete[] elements;
}

template<typename T>
void Heap<T>::buildMinHeap() {
    for(int i = heapSize/2; i >= 0; i--){
        heapify(i);
    }
}

template<typename T>
void Heap<T>::heapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if(l < heapSize && *elements[l].priority < *elements[i].priority){
        smallest = l;
    }
    if(r < heapSize && *elements[r].priority < *elements[i].priority){
        smallest = r;
    }

    if(smallest != i){
        Element<T> tmp = elements[i];
        elements[i] = elements[smallest];
        elements[smallest] = tmp;
        heapify(smallest);
    }
}

template<typename T>
int Heap<T>::left(int i) {
    return i*2+1;
}

template<typename T>
int Heap<T>::right(int i) {
    return i*2+2;
}

template<typename T>
int Heap<T>::parent(int i) {
    return (i-1)/2;
}

template<typename T>
struct PriorityQueue{
    Heap<T> heap;
    PriorityQueue();
    ~PriorityQueue();

    void minHeapInsert(T value, int* priority);
    int getMinPriority();
    Element<T> extractMin();
    void printHeap();
    bool isEmpty();
};

template<typename T>
int PriorityQueue<T>::getMinPriority() {
    return heap.elements[0].priority;
}

template<typename T>
Element<T> PriorityQueue<T>::extractMin() {
    Element<T> e = heap.elements[0];
    heap.elements[0] = heap.elements[heap.heapSize-1];
    heap.heapSize--;
    heap.buildMinHeap();
    return e;
}

template<typename T>
PriorityQueue<T>::PriorityQueue() {

}

template<typename T>
PriorityQueue<T>::~PriorityQueue() {

}

template<typename T>
void PriorityQueue<T>::printHeap() {
    for(int i = 0; i < heap.heapSize; i++){
        cout << heap.elements[i].value << "(" << heap.elements[i].priority << ") ";
    }
}

template<typename T>
void PriorityQueue<T>::minHeapInsert(T value, int* priority) {
    heap.elements[heap.heapSize].value = value;
    //heap.elements[heap.heapSize].priority = INT_MAX;
    heap.heapSize++;
    int i = heap.heapSize-1;
    heap.elements[i].priority = priority;
    while(i > 0 && heap.elements[heap.parent(i)] > heap.elements[i]){
        Element<T> tmp = heap.elements[i];
        heap.elements[i] = heap.elements[heap.parent(i)];
        heap.elements[heap.parent(i)] = tmp;
        i = heap.parent(i);
    }
    heap.buildMinHeap();
}

template<typename T>
bool PriorityQueue<T>::isEmpty() {
    return heap.heapSize == 0;
}

#endif //INC_08_DIJKSTRA_PRIORITYQUEUE_H
