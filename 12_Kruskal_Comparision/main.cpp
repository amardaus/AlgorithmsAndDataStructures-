#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "Set.cpp"
#define MAX_SIZE 1000001

using namespace std;

template <typename T>
struct Edge;

template <typename T>
struct Vertex{
public:
    T vertexName;
    Vertex() {}
    Vertex(T vertexName) : vertexName(vertexName) {}

    bool operator<(const Vertex& v){
        return this->distance < v.distance;
    }
    bool operator>(const Vertex& v){
        return this->distance > v.distance;
    }
    bool operator==(const Vertex& v){
        return this->distance == v.distance;
    }

    Vertex<T>* p;
    int rank;
};

template <typename T>
struct Edge{
    int start, end;
    int weight;
    Edge(int start, int end, int weight): start(start), end(end), weight(weight) {}
};

template <typename T>
struct Graph {
    vector<Vertex<T>*> vertices;
    int count;
    vector<Edge<T>*> edges;

    Graph() {
        count = 0;
        vertices = vector<Vertex<T>*>(MAX_SIZE,nullptr);
    }

    void addEdge(int a, int b, int weight) {
        Vertex<T> *vA, *vB;

        if(vertices.at(a) == nullptr){
            vA = new Vertex<T>(a);
            vertices.at(a) = vA;
            count++;
        }

        if(vertices.at(b) == nullptr){
            vB = new Vertex<T>(b);
            vertices.at(b) = vB;
            count++;
        }

        edges.emplace_back(new Edge<T>(a,b,weight));
    }


    Graph<T> readGraph(const string &filename) {
        Graph<T> g = Graph<T>();

        ifstream input;
        input.open(filename);

        if (!input) {
            cout << "Error opening file" << endl;
            exit(EXIT_FAILURE);
        }

        string line;
        T a, b;
        int w;
        string s;

        while (getline(input, line)) {
            istringstream iss(line);

            getline(iss, s, ',');
            stringstream ca(s);
            ca >> a;
            getline(iss, s, ',');
            stringstream cb(s);
            cb >> b;
            getline(iss, s, ',');
            w = stoi(s);
            g.addEdge(a, b, w);
        }
        input.close();
        return g;
    }
    // -----------------------------------------------------


    vector<Set<int,T>> sets;

    void orgMakeSet(Vertex<T>* v){
        Set<int,T> s(count);
        s.insert(v->vertexName);
        sets.push_back(s);
    }

    int orgFindSet(Vertex<T>* v){
        for(int i = 0; i < sets.size(); i++){
            if(sets.at(i).isMember(v->vertexName)) return i;
        }
        return -1;
    }

    Set<int,T> orgMakeUnion(Set<int,T>* s1, Set<int,T>* s2){
        Set<int,T> s3 = s1->getUnion(s2);
        return s3;
    }

    void orgKruskal() {
        auto start = chrono::steady_clock::now();

        for (int i = 0; i < vertices.size(); i++) {
            if(vertices.at(i) != nullptr){
                orgMakeSet(vertices.at(i));
            }
        }

        sort(edges.begin(), edges.end(), [](Edge<T> *e1, Edge<T> *e2) {
            return e1->weight < e2->weight;
        });

        int sum = 0;

        for (int i = 0; i < edges.size(); i++) {
            int istart = orgFindSet(vertices.at(edges.at(i)->start));
            int iend = orgFindSet(vertices.at(edges.at(i)->end));
            if (istart < 0 || iend < 0) continue;
            auto s1 = sets.at(istart);
            auto s2 = sets.at(iend);

            if (istart != iend) {
                auto s12 = orgMakeUnion(&s1, &s2);
                sum += edges.at(i)->weight;
                sets.erase(sets.begin() + istart);
                if (iend > istart) iend--;
                sets.erase(sets.begin() + iend);
                sets.push_back(s12);
            }
        }

        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "ORIGINAL: " << setprecision(6) << duration * 0.001 << "s";

        cout << ",\t WEIGHT: " << sum << endl;
    }


    // -----------------------------------------------------

    void makeSet(Vertex<T>* x){
        x->p = x;
        x->rank = 0;
    }

    void link(Vertex<T>* x, Vertex<T>* y){
        if(x->rank > y->rank){
            y->p = x;
        }
        else{
            x->p = y;
            if(x->rank == y->rank){
                y->rank = y->rank + 1;
            }
        }
    }

    Vertex<T>* findSet(Vertex<T>* x){
        if(x != x->p){
            x->p = findSet(x->p);
        }
        return x->p;
    }

    void unionSets(Vertex<T>* x, Vertex<T>* y){
        link(findSet(x), findSet(y));
    }

    void kruskal(){
        auto start = chrono::steady_clock::now();

        for(int i = 0; i < vertices.size(); i++){
            if(vertices.at(i) != nullptr) makeSet(vertices.at(i));
        }

        sort(edges.begin(), edges.end(), [](Edge<T>* e1, Edge<T>* e2){
            return e1->weight < e2->weight;
        });

        vector<Edge<T>*> A;
        int sum = 0;

        for(int i = 0; i < edges.size(); i++){
            Vertex<T>* u = vertices.at(edges.at(i)->start);
            Vertex<T>* v = vertices.at(edges.at(i)->end);
            if(findSet(u) != findSet(v)){
                unionSets(u,v);
                A.emplace_back(edges.at(i));
                sum += edges.at(i)->weight;
            }
        }

        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << "FOREST: " << setprecision(6) << duration * 0.001 << "s";
        cout << ",\t\t WEIGHT: " << sum << endl;
    }
};

int main(int argc, char* argv[]) {
    string filename;
    filename = "graphs/100.csvo";

    /*if(argc != 2){
        cout << "Podano nieprawidlowa liczbe argumentow" << endl;
        exit(EXIT_FAILURE);
    }
    filename = argv[1];*/

    Graph<int> g = g.readGraph(filename);
    g.kruskal();
    g.orgKruskal();
}
