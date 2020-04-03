#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;

template<typename K, typename V>
class HashNode{
public:
    K key;
    V value;

    HashNode(): key(), value() { }
    HashNode(K key, V value): key(key), value(value){ }

    bool equals(const V& other){
        return this->value == other;
    }
};

template<typename K, typename V>
class HashTable{

public:
    int n;
    vector<HashNode<K,V>>* list;

    HashTable(int n) : n(n), list(new vector<HashNode<K,V>>[n]){ }

    int generateKey(V value){
        return abs(value) % n;    //n - array size
    }

    void insert(K key, V value){
        bool eq = false;
        HashNode<K,V> node = *new HashNode<K,V>(key, value);

        if(!list[key].empty()){
            for(auto &item: list[key]){
                if(item.equals(value)){
                    eq = true;
                    break;
                }
            }
        }
        if(!eq) {
            list[key].push_back(node);
        }
    }

    int findIndex(K key, V value){
        int i = 0;
        if(!list[key].empty()){
            for(auto &item: list[key]){
                if(item.equals(value)){
                    return i;
                }
                i++;
            }
        }
        return -1;
    }

    bool findElement(K key, V value){
        int i = findIndex(key, value);
        if(i >= 0){
            return true;
        }
        else{
            return false;
        }
    }

    void removeElement(K key, V value){
        int i = findIndex(key, value);
        if(i >= 0){
            list[key].erase(list[key].begin()+i);
        }
        else{
            cout << "Could not find element" << endl;
        }
    }

    void displayAll(){
        for(int i = 0; i < n; i++){
            if(!list[i].empty()){
                for(auto item : list[i]){
                    cout << item.value << " ";
                }
            }
        }
    }

    vector<HashNode<K,V>> getAllElements(){
        vector<HashNode<K,V>> v;

        for(int i = 0; i < n; i++){
            if(!list[i].empty()){
                for(auto item : list[i]){
                    v.push_back(item);
                }
            }
        }
        return v;
    }
};

template<typename K, typename V>
class Set{
    HashTable<K,V> tab;

public:

    Set(int n) : tab(*new HashTable<K,V>(n)){ }

    void insert(V value){
        int key = tab.generateKey(value);
        tab.insert(key, value);
    }

    void insert(K key, V value){
        tab.insert(key, value);
    }

    bool isMember(V value){
        int key = tab.generateKey(value);
        return tab.findElement(key, value);
    }

    void pop(V value){
        int key = tab.generateKey(value);
        tab.removeElement(key, value);
    }

    void display(){
        tab.displayAll();
    }

    Set<K,V> getUnion(Set<K,V> other){
        Set<K,V> set = *this;

        for(int i = 0; i < (*this).tab.n; i++){
            if(!(*this).tab.list[i].empty()){
                for(HashNode<K,V> &item: (*this).tab.list[i]){
                    set.insert(item.key, item.value);
                }
            }
        }

        for(int i = 0; i < other.tab.n; i++){
            if(!other.tab.list[i].empty()){
                for(HashNode<K,V> &item: other.tab.list[i]){
                    set.insert(item.key, item.value);
                }
            }
        }

        return set;
    }

    Set<K,V> getIntersection(Set<K,V> other){
        Set<K,V> set = *new Set<K,V>((*this).tab.n);

        for(int i = 0; i < (*this).tab.n; i++){
            if(!((*this).tab.list[i]).empty()){
                for(HashNode<K,V> &item: other.tab.list[i]){
                    for(HashNode<K,V> &item2: (*this).tab.list[i]){
                        if(item.equals(item2.value)){
                            set.insert(item.key, item.value);
                        }
                    }
                }
            }
        }

        return set;
    }

    Set<K,V> getDifference(Set<K,V> other) {
        Set<K,V> set = *new Set<K,V>((*this).tab.n);
        bool eq;

        for(int i = 0; i < (*this).tab.n; i++){
            if(!((*this).tab.list[i]).empty()){
                for(HashNode<K,V> &item: (*this).tab.list[i]){
                    eq = false;
                    for(HashNode<K,V> &item2: other.tab.list[i]){
                        if(item.equals(item2.value)){
                            eq = true;
                        }
                    }
                    if(!eq) set.insert(item.key, item.value);
                }
            }
        }
        return set;
    }

    Set<K,V> getSymmetricDifference(Set<K,V> other){
        Set<K,V> set = *new Set<K,V>((*this).tab.n);
        bool eq;

        for(int i = 0; i < (*this).tab.n; i++){
            if(!((*this).tab.list[i]).empty()){
                for(HashNode<K,V> &item: (*this).tab.list[i]){
                    eq = false;
                    for(HashNode<K,V> &item2: other.tab.list[i]){
                        if(item.equals(item2.value)){
                            eq = true;
                        }
                    }
                    if(!eq) set.insert(item.key, item.value);
                }
            }
        }

        for(int i = 0; i < other.tab.n; i++){
            if(!(other.tab.list[i]).empty()){
                for(HashNode<K,V> &item: other.tab.list[i]){
                    eq = false;
                    for(HashNode<K,V> &item2: (*this).tab.list[i]){
                        if(item.equals(item2.value)){
                            eq = true;
                        }
                    }
                    if(!eq) set.insert(item.key, item.value);
                }
            }
        }
        return set;
    }
};

int main(int argc, char* argv[]) {

    int count = 10000000;
    int* tmp_arr = new int[count];

    Set<int,int> s1 = *new Set<int, int>(count);
    Set<int,int> s2 = *new Set<int, int>(count);
    fstream myfile("./test_set.txt");
    int tmp;
    int i = 0;
    while(myfile >> tmp){
        tmp_arr[i] = tmp;
        i++;
    }

    auto start = std::chrono::steady_clock::now();
    for(i = 0; i < count; i++){
        s1.insert(tmp);
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "insertion time: " << std::setprecision(10) << duration/1000000.0 << "s" << endl;

    myfile.clear();
    myfile.seekg(0);
    while(myfile >> tmp){
        s2.insert(tmp);
    }

    start = std::chrono::steady_clock::now();
    cout << "isMember: " << s1.isMember(1000010) << endl;
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "isMember time: " << std::fixed << std::setprecision(10) << duration/1000000.0 << "s" << endl;

    start = std::chrono::steady_clock::now();
    s1.getUnion(s2);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "union time: " << std::setprecision(10) << duration/1000000.0 << "s" << endl;

    start = std::chrono::steady_clock::now();
    s1.getIntersection(s2);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "intersection time: " << std::setprecision(10) << duration/1000000.0 << "s" << endl;

    start = std::chrono::steady_clock::now();
    s1.getDifference(s2);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "difference time: " << std::setprecision(10) << duration/1000000.0 << "s" << endl;
    cout << endl;

    return 0;
}
