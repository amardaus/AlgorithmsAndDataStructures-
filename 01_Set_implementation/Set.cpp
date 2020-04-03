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
private:
    int hashfunc(V value){
        ostringstream oss;
        oss << value;
        string str = oss.str();
        int hash = 0;
        char c;
        int i = 0;

        while(str[i] != '\0'){
            hash = str[i] + (i+1) * hash;
            i++;
        }
        return hash;
    }

public:
    int n;
    vector<HashNode<K,V>>* list;

    HashTable(int n) : n(n), list(new vector<HashNode<K,V>>[n]){ }

    int generateKey(V value){
        int key = hashfunc(value);
        return key % n;    //n - array size
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
        //cout << "inserting: " << value << "-" << key << endl;
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
                    set.insert(item.value);
                }
            }
        }

        for(int i = 0; i < other.tab.n; i++){
            if(!other.tab.list[i].empty()){
                for(HashNode<K,V> &item: other.tab.list[i]){
                    set.insert(item.value);
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
                            set.insert(item.value);
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
                    if(!eq) set.insert(item.value);
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
                    if(!eq) set.insert(item.value);
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
                    if(!eq) set.insert(item.value);
                }
            }
        }
        return set;
    }
};

int main(int argc, char* argv[]) {

    int count = argc;
    Set<int,string> s1 = *new Set<int, string>(count);

    for(int i = 1; i < count; i++){
        s1.insert(argv[i]);
    }

    s1.display();
    cout << endl;


    /*int count = 5;
    Set<int,string> s1 = *new Set<int, int>(count);

    s1.insert(8);
    s1.insert(102);
    s1.insert(100);
    s1.insert(203);
    s1.insert(203);
    s1.insert(204);

    Set<int,int> s2 = *new Set<int, int>(count);
    s2.insert(1);
    s2.insert(2);
    s2.insert(3);
    s2.insert(4);
    s2.insert(8);

    Set<int,int> s3 = s1.getIntersection(s2);
    Set<int,int> s4 = s1.getDifference(s2);
    Set<int,int> s5 = s1.getUnion(s2);

    s3.display();
    cout << endl;
    s4.display();
    cout << endl;
    s5.display();
    cout << endl;*/

    return 0;
}
