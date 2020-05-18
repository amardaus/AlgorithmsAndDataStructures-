#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <climits>
#include <cstring>

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
};

template <typename T>
struct Edge{
    Vertex<T>* vertex;
    int weight;

    Edge(Vertex<T>* vertex, int weight): vertex(vertex), weight(weight) {}
};

template <typename T>
struct Graph {
    vector<Vertex<T> *> vertices;
    int count;

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

    void floydWarshall(const vector<pair<int,int>>& pairs){
        int n = vertices.size();
        int** D = new int*[n];
        for(int i = 0; i < n; i++){
            D[i] = new int[n];
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i != j){
                    D[i][j] = INT_MAX;
                }
            }
        }

        for(int i = 0; i < vertices.size(); i++){
            D[i][i] = 0;
            for(int j = 0; j < vertices.at(i)->adjacencies.size(); j++) {
                int ai = vertices.at(i)->vertexName-1;
                int bi = vertices.at(i)->adjacencies.at(j).vertex->vertexName-1;
                D[ai][bi] = vertices.at(i)->adjacencies.at(j).weight;
            }
        }

        for(int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if(D[i][k] != INT_MAX && D[k][j] != INT_MAX){
                        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                    }
                }
            }
        }

        for(int i = 0; i < pairs.size(); i++){
            int a = pairs.at(i).first;
            int b = pairs.at(i).second;
            cout << D[a-1][b-1] << " ";
        }
        cout << endl;
    }

};

int main(int argc, char* argv[]) {
    string filename;
    vector<pair<int,int>> pairs;

    if(argc < 3){
        cout << "Podano nieprawidlowa liczbe argumentow" << endl;
        exit(EXIT_FAILURE);
    }
    filename = argv[1];

    for(int i = 2; i < argc; i++){
        char* ab = strtok(argv[i], ",");
        int a = stoi(ab);
        ab = strtok(nullptr, ",");
        int b = stoi(ab);
        pairs.emplace_back(a,b);
    }

    //filename = "graphs/1000.csv";
    //pairs.emplace_back(20,780);
    //pairs.emplace_back(10,33);

    Graph<int> g = g.readGraph(filename);
    //g.printEdges();
    //g.exportDot("graph.dot");
    g.floydWarshall(pairs);

}