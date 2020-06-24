#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <fstream>
#include <iomanip>
#include <chrono>

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
        vertices = vector<Vertex<T>*>(1000001,nullptr);
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
        for(int i = 0; i < vertices.size(); i++){
            if(vertices.at(i) != nullptr) makeSet(vertices.at(i));
        }

        sort(edges.begin(), edges.end(), [](Edge<T>* e1, Edge<T>* e2){
            return e1->weight < e2->weight;
        });

        vector<Edge<T>*> A;
        int sum = 0;

        auto start = chrono::steady_clock::now();

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
        cout << "Kruskal algorithm time: " << setprecision(6) << duration * 0.001 << "s" << endl;

        cout << "MST sum: " << sum << endl;
    }
};

int main(int argc, char* argv[]) {
    string filename;
    filename = "graphs/10000.csvo";

    Graph<int> g = g.readGraph(filename);
    g.kruskal();
}
