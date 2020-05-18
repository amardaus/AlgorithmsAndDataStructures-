#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <fstream>
#include <sstream>
#include "PriorityQueue.h"

using namespace std;

template <typename T>
struct Edge;

enum Color { WHITE, BLACK };

template <typename T>
struct Vertex{
public:
    T vertexName;
    vector<pair<Vertex<T>*,int>> adjacencies;
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

    Color color;
    int key;
    Vertex<T>* parent;
};

template <typename T>
struct Edge{
    Vertex<T>* start, *end;
    int weight;
    Edge(Vertex<T>* start, Vertex<T>* end, int weight): start(start), end(end), weight(weight) {}
};

template <typename T>
struct Graph {
    vector<Vertex<T>*> vertices;
    vector<Edge<T>*> edges;
    int count;

    Graph() {
        count = 0;
    }
    void addEdge(T a, T b, int weight) {
        bool foundA = false;
        bool foundB = false;
        Vertex<T> *vA = nullptr;
        Vertex<T> *vB = nullptr;

        for (int i = 0; i < count; i++) {
            if (vertices.at(i)->vertexName == a) {
                foundA = true;
                vA = vertices.at(i);
            }
            if (vertices.at(i)->vertexName == b) {
                foundB = true;
                vB = vertices.at(i);
            }
        }

        if (!foundA) {
            vA = new Vertex<T>(a);
            vertices.push_back(vA);
            count++;
        }


        if (!foundB && a != b) {
            vB = new Vertex<T>(b);
            vertices.push_back(vB);
            count++;
        }

        auto* eAB = new Edge<T>(vA,vB,weight);
        edges.emplace_back(eAB);
        vA->adjacencies.emplace_back(vB, weight);
        vB->adjacencies.emplace_back(vA, weight);
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
                    cout << (*it)->vertexName << ", ";
                }
            }
            cout << endl;
        }
    }

    void exportDot(const string &filename) {
        ofstream output;
        output.open(filename);

        output << "graph {\n";
        for(int i = 0; i < edges.size(); i++){
            output << "\t" << edges[i]->start->vertexName << " -- " << edges[i]->end->vertexName << "[label=\""
                   << edges[i]->weight << "\"]"
                   << ";" << endl;
        }
        output << "}" << endl;
        output.close();
    }

    void exportCSV(const string& filename){
        ofstream output;
        output.open(filename);
        for(int i = 0; i < edges.size(); i++){
            output << edges[i]->start->vertexName << "," << edges[i]->end->vertexName << "," << edges[i]->weight << endl;
        }
        output.close();
    }

    Vertex<T> *getVertex(T value) {
        for (int i = 0; i < count; i++) {
            if (vertices[i]->vertexName == value) return vertices[i];
        }
        return nullptr;
    }

    void prim(Vertex<T>* startV){
        PriorityQueue<Vertex<T>*> queue(count);
        for(int i = 0; i < vertices.size(); i++){
            vertices.at(i)->key = INT_MAX;
            vertices.at(i)->parent = nullptr;
        }
        startV->key = 0;

        for(int i = 0; i < vertices.size(); i++){
            queue.minHeapInsert(vertices.at(i), &vertices.at(i)->key);
        }

        int weight = 0;
        while(!queue.isEmpty()){
            Vertex<T>* u = queue.extractMin().value;
            weight += u->key;
            for(int i = 0; i < u->adjacencies.size(); i++){
                Vertex<T>* v = u->adjacencies.at(i).first;
                int w = u->adjacencies.at(i).second;
                if(v->color == WHITE && v->key > w){
                    v->key = w;
                }
            }
            u->color = BLACK;
        }
        cout << weight;     //POWINNO BYC 38 a nie 41, cos jest zleee
    }
};

int main(int argc, char* argv[]) {
    string filename;

    /*if(argc < 3){
        cout << "Podano nieprawidlowa liczbe argumentow" << endl;
        exit(EXIT_FAILURE);
    }
    filename = argv[1];
    startV = stoi(argv[2]);*/

    filename = "10.csvo";
    Graph<char> g = g.readGraph(filename);
    Vertex<char>* start = g.getVertex('a');
    g.prim(start);
    //g.printEdges();
    //g.exportCSV("out.csv");
}