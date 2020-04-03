#include <iostream>
#include <utility>
#include <sstream>

using namespace std;

constexpr int MAX_SIZE = 100;

template<typename V>
struct Element{
    pair<V, int> element;         //V - value, int - priority
    Element() { }
    Element(pair<V,int> element): element(element) { }

    bool operator>(const Element& e2){
        return this->element.second > e2.element.second;
    }

    bool operator<(const Element& e2){
        return this->element.second < e2.element.second;
    }

    bool operator==(const Element& e2){
        return this->element.second == e2.element.second;
    }
};

template<typename V>
struct Heap{
    Element<V>* arr;
    int curr_size = 0;

    Heap(){
        arr = new Element<V>[MAX_SIZE]();
    }

    int left_child(int i){
        return i*2;
    }

    int right_child(int i){
        return i*2+1;
    }

    int parent(int i){
        return i/2;
    }

    void buildMaxHeap(){
        for(int i = curr_size/2; i >= 0; i--){
            heapify(i);
        }
    }

    void insert(Element<V> element){
        arr[curr_size] = element;
        curr_size++;
        buildMaxHeap();
    }

    void heapify(int i){
        int l = left_child(i);
        int r = right_child(i);
        int largest = i;

        if(arr[l] > arr[i] && l < curr_size){
            largest = l;
        }
        if(arr[r] > arr[i] && r < curr_size){
            largest = r;
        }

        if(largest != i){
            swap(arr[largest], arr[i]);
            heapify(largest);
        }
    }

    int findIndex(V value){
        int i = 0;

        while(i < curr_size){
            if(arr[i].element.first == value){
                return i;
            }
            i++;
        }
        cout << "Nie znaleziono elementu" << endl;
        return -1;
    }

    void printAll(){
        for(int i = 0; i < curr_size; i++){
            cout << i << ":(" << arr[i].element.first << "," << arr[i].element.second << ")\t";
        }
    }
};

template<typename V>
struct PriorityQueue{
    Heap<V> heap;

    void InsertElement(Element<V> E){
        heap.insert(E);
    }

    int getMaxPriority(){
        return heap.arr[0].element.second;
    }

    Element<V> pop(){
        Element<V> e = heap.arr[0];
        heap.arr[0] = heap.arr[heap.curr_size-1];
        heap.curr_size--;
        heap.heapify(0);
        return e;
    }

    void IncreasePriority(Element<V> e){
        int i = heap.findIndex(e.element.first);
        if(e.element.second <= heap.arr[i].element.second){
            cout << "New key is smaller than current key" << endl;
            return;
        }

        heap.arr[i] = e;
        Element<V> tmp;

        while(i > 0 && heap.arr[heap.parent(i)] < e){
            tmp = heap.arr[i];
            heap.arr[i] = heap.arr[heap.parent(i)];
            heap.arr[heap.parent(i)] = tmp;
            i = heap.parent(i);
        }
    }
};

int main(int argc, char* argv[]) {
    PriorityQueue<string> queue;
    int key;
    string value;
    string p;

    for(int i = 1; i < argc; i++){
        p = argv[i];
        int start = p.find_first_of('(');
        int end = p.find_last_of(')');
        int mid = p.find_first_of(',');

        value = p.substr(start+1, mid-1);
        key = stoi(p.substr(mid+1, end-mid-1));
        Element<string> p(*new pair<string,int>(value, key));
        queue.InsertElement(p);
    }

    cout << endl;
    for(int i = 0; i < argc - 1; i++){
        cout << queue.pop().element.first << " ";
    }
    cout << endl;

    return 0;
}