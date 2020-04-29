#include <iostream>

template <typename T>
class Visitor{
public:
    virtual void visit(T& element) = 0;
};

template <typename T>
class AddingVisitor : public Visitor<T>{
private:
    int sum;
    void visit(T& element){
        sum += element;
    }

public:
    AddingVisitor(): sum(0) {}
    int getSum() const{
        return sum;
    }
};

template <typename T>
struct Container{
    Container(){}
    ~Container() {};
    virtual int getCount() const = 0;
    virtual bool isEmpty(){ return getCount() == 0; }
    virtual bool isFull() = 0;
    virtual void makeNull() = 0;
    virtual void accept(Visitor<T>& visitor) = 0;

};

template <typename T>
class Set : public virtual Container<T>{
protected:
    int count;
    int universeSize;

public:
    Set(int n): universeSize(n) { }
    int getUniverseSize(){ return universeSize; }

};

template<typename T>
class SetAsArray: public Set<T>{
    bool* array;

public:
    void accept(Visitor<T>& visitor){
        for(int i = 0; i < Set<T>::universeSize; i++){
            if(array[i]) visitor.visit(i);
        }
    }
    void makeNull(){
        Set<T>::count = 0;
        for(int i = 0; i < Set<T>::universeSize; i++){
            array[i] = false;
        }
    }
    bool isFull(){
        return getCount() == Set<T>::getUniverseSize();
    }
    int getCount() const{
        return Set<T>::count;
    }
    SetAsArray(int n) : Set<T>(n) {
        array = new bool[n];
        Set<T>::count = 0;
        for(int i = 0; i < n; i++){
            array[i] = false;
        }
    }
    void insert(int element){
        if(!array[element]){
            array[element] = true;
            Set<T>::count++;
        }
    }
    bool isMember(int element) const{
        return array[element];
    }
    void remove(int element){
        if(array[element]){
            array[element] = false;
            Set<T>::count--;
        }
    }
    friend SetAsArray<T> operator+(const SetAsArray<T>& s1, const SetAsArray<T>& s2);
    friend SetAsArray<T> operator-(const SetAsArray<T>& s1, const SetAsArray<T>& s2);
    friend SetAsArray<T> operator*(const SetAsArray<T>& s1, const SetAsArray<T>& s2);
    friend bool operator==(const SetAsArray<T>& s1, const SetAsArray<T>& s2);
    friend bool operator<=(const SetAsArray<T>& s1, const SetAsArray<T>& s2);
};

template<typename T>
SetAsArray<T> operator+(const SetAsArray<T>& s1, const SetAsArray<T>& s2){
    if(s1.universeSize == s2->universeSize){
        int n = s1.universeSize;
        SetAsArray<T> s12(n);
        for(int i = 0; i < n; i++){
            if(s1.array[i] || s2.array[i]){
                s12[i] = true;
                s12.count++;
            }
        }
        return s12;
    }
}

template<typename T>
SetAsArray<T> operator-(const SetAsArray<T>& s1, const SetAsArray<T>& s2){
    if(s1.universeSize == s2.universeSize){
        int n = s1.universeSize;
        SetAsArray<T> s12(n);
        for(int i = 0; i < n; i++) {
            if (s1.array[i] && !s2.array[i]) {
                s12[i] = true;
                s12.count++;
            }
        }
        return s12;
    }
}

template<typename T>
SetAsArray<T> operator*(const SetAsArray<T> &s1, const SetAsArray<T> &s2) {
    if(s1.universeSize == s2.universeSize){
        int n = s1.universeSize;
        SetAsArray<T> s12(n);
        for(int i = 0; i < n; i++) {
            if (s1.array[i] && s2.array[i]) {
                s12[i] = true;
                s12.count++;
            }
        }
        return s12;
    }
}

template<typename T>
bool operator==(const SetAsArray<T> &s1, const SetAsArray<T> &s2) {
    if(s1.universeSize == s2.universeSize){
        int n = s1.universeSize;
        for(int i = 0; i < n; i++) {
            if(s1.array[i] != s2.array[i]) return false;
        }
        return true;
    } else return false;
}

template<typename T>
bool operator<=(const SetAsArray<T> &s1, const SetAsArray<T> &s2) {
    if(s1.universeSize == s2.universeSize){
        int n = s1.universeSize;
        for(int i = 0; i < n; i++) {
            if(s1.array[i] && !s2.array[i]) return false;
        }
        return true;
    } else return false;
}

int main() {
    SetAsArray<int> set(10);
    set.insert(1);
    set.insert(2);
    set.insert(4);
    set.insert(8);

    AddingVisitor<int> visitor;
    set.accept(visitor);
    std::cout << "Sum: " << visitor.getSum() << std::endl;

    return 0;
}