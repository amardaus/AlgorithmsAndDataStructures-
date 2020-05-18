#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <chrono>
#include "PriorityQueue.h"

using namespace std;

template <typename T>
struct Edge;

template <typename T>
struct Vertex{
public:
    T vertexName;
    vector<Edge<T>> adjacencies;
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

    int d;
    Vertex<T>* parent;
};

template <typename T>
struct Edge{
    Vertex<T>* vertex;
    int weight;

    Edge(Vertex<T>* vertex, int weight): vertex(vertex), weight(weight) {}
};

template<typename T>
struct Result{
    vector<int> distances;
    float timeInMilliseconds;

    Result(){}

    void setDistance(int d){
        distances.push_back(d);
    }

    void setTime(float time){
        this->timeInMilliseconds = time;
    }
};

template <typename T>
struct Graph {
    vector<Vertex<T> *> vertices;
    int count;
    vector<Edge<T> *> edges;

    Graph() {
        count = 0;
    }
    void addEdge(T a, T b, int weight) {
        bool foundA = false;
        bool foundB = false;

        int iA = 0, iB = 0;
        for (int i = 0; i < count; i++) {
            if (vertices.at(i)->vertexName == a) {
                foundA = true;
                iA = i;
            }
            if (vertices.at(i)->vertexName == b) {
                foundB = true;
                iB = i;
            }
        }

        if (!foundA) {
            Vertex<T> *v1 = new Vertex<T>(a);
            vertices.push_back(v1);
            iA = count;
            count++;
        }

        Vertex<T> *v2;

        if (!foundB && a != b) {
            v2 = new Vertex<T>(b);
            vertices.push_back(v2);
            iB = count;
            count++;
        } else {
            v2 = this->vertices[iB];
        }
        vertices[iA]->adjacencies.emplace_back(Edge<T>(v2, weight));
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

    void printEdges() {
        for (int i = 0; i < count; i++) {
            cout << vertices[i]->vertexName << ": ";
            if (!vertices[i]->adjacencies.empty()) {
                for (auto it = vertices[i]->adjacencies.begin(); it != vertices[i]->adjacencies.end(); it++) {
                    cout << (*it).vertex->vertexName << ", ";
                }
            }
            cout << endl;
        }
    }

    void exportDot(const string &filename) {
        ofstream output;
        output.open(filename);

        output << "digraph {\n";
        for (int i = 0; i < count; i++) {
            if (!vertices[i]->adjacencies.empty()) {
                for (auto it = vertices[i]->adjacencies.begin(); it != vertices[i]->adjacencies.end(); it++) {
                    output << "\t" << vertices[i]->vertexName << " -> " << (*it).vertex->vertexName << "[label=\""
                           << (*it).weight << "\"]"
                           << ";" << endl;
                }
            }
        }
        output << "}" << endl;
        output.close();
    }

    Vertex<T> *getVertex(T value) {
        for (int i = 0; i < count; i++) {
            if (vertices[i]->vertexName == value) return vertices[i];
        }
        return nullptr;
    }

    void initialize(Vertex<T>* s){
        for(int i = 0; i < vertices.size(); i++){
            vertices.at(i)->parent = nullptr;
            vertices.at(i)->d = INT_MAX;
        }
        s->d = 0;
    }

    void relax(Vertex<T>* u, Vertex<T>* v, int w){
        if(u->d != INT_MAX && v->d > u->d + w){
            v->d = u->d + w;
            v->parent = u;
        }
    }

    Result<T> dijkstra(Vertex<T>* startVertex, vector<Vertex<T>*> endVertices){
        Result<T> result;
        auto start = chrono::steady_clock::now();

        initialize(startVertex);
        vector<Vertex<T>*> S;
        PriorityQueue<Vertex<T>*> pq(vertices.size());
        for(int i = 0; i < vertices.size(); i++){
            pq.minHeapInsert(vertices.at(i), &vertices.at(i)->d);
        }

        while(!pq.isEmpty()){
            Vertex<T>* e = pq.extractMin().value;
            S.push_back(e);
            for(int i = 0; i < e->adjacencies.size(); i++){
                relax(e, e->adjacencies.at(i).vertex, e->adjacencies.at(i).weight);
                pq.heap.buildMinHeap();
            }
        }

        auto end = std::chrono::steady_clock::now();
        float duration = std::chrono::duration_cast<chrono::microseconds>(end - start).count();
        result.setTime(duration/1000.0);

        for(int i = 0; i < endVertices.size(); i++){
            result.setDistance(endVertices.at(i)->d);
        }

        return result;
    }
};

int main(int argc, char* argv[]) {
    string filename;
    int startV;

    if(argc < 3){
        cout << "Podano nieprawidlowa liczbe argumentow" << endl;
        exit(EXIT_FAILURE);
    }
    filename = argv[1];
    startV = stoi(argv[2]);

    Graph<int> g = g.readGraph(filename);
    Vertex<int>* startVertex  = g.getVertex(startV);
    vector<Vertex<int>*> endVertices;

    for(int i = 3; i < argc; i++){
        int v = stoi(argv[i]);
        Vertex<int>* e  = g.getVertex(v);
        endVertices.emplace_back(e);
    }

    Result<int> result = g.dijkstra(startVertex, endVertices);

    for(int i = 0; i < result.distances.size(); i++) {
        cout << result.distances.at(i) << " ";
    }
    cout << endl;
    cout << result.timeInMilliseconds << " ms" << endl;

    //g.exportDot("test.dot");
}