#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <climits>
#include <map>

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
    Vertex* parent;
};

template <typename T>
struct Edge{
    Vertex<T>* vertex;
    int weight;

    Edge(Vertex<T>* vertex, int weight): vertex(vertex), weight(weight) {}
};

template<typename T>
struct Result{
    bool pathFound;
    map<Vertex<T>*, int> distances;
    map<Vertex<T>*, Vertex<T>*> parents;

    void printResult(){
        if(!pathFound){
            cout << "FALSE\n";
            return;
        }

        else cout << "TRUE\n";

        for(auto it = distances.begin(); it != distances.end(); it++){
            cout << "(" << (*it).first->vertexName << "," << (*it).second << "),";
        }
        cout << endl;
        for(auto it = parents.begin(); it != parents.end(); it++){
            cout << "(" << (*it).first->vertexName << ",";
            if((*it).second){
                cout << (*it).second->vertexName << "),";
            }
            else{
                cout << "NULL" << ")";
            }
        }
    }

    void printPath(Vertex<T>* start, Vertex<T>* end){
        cout << "Path from " << start->vertexName << " to " << end->vertexName << ":\t";
        Vertex<T>* current = end;
        while(current != start){
            cout << current->vertexName << " <- ";
            current = parents[current];
        }
        cout << current->vertexName << " ";
        cout << "(distance: " << end->d << ")" << endl;
    }
};

template <typename T>
struct Graph{
    vector<Vertex<T>*> vertices;
    int count;
    vector<Edge<T>*> edges;

    Graph(){
        count = 0;
    }

    void addEdge(T a, T b, int weight){
        bool foundA = false;
        bool foundB = false;

        int iA = 0, iB = 0;
        for(int i = 0; i < count; i++){
            if(vertices.at(i)->vertexName == a) {
                foundA = true;
                iA = i;
            }
            if(vertices.at(i)->vertexName == b) {
                foundB = true;
                iB = i;
            }
        }

        if(!foundA) {
            Vertex<T>* v1 = new Vertex(a);
            vertices.push_back(v1);
            iA = count;
            count++;
        }

        Vertex<T>* v2;

        if(!foundB && a != b) {
            v2 = new Vertex(b);
            vertices.push_back(v2);
            iB = count;
            count++;
        }
        else{
            v2 = this->vertices[iB];
        }
        vertices[iA]->adjacencies.emplace_back(Edge(v2, weight));
    }


    Graph<T> readGraph(const string& filename){
        Graph<T> g = Graph<T>();

        ifstream input;
        input.open(filename);

        if(!input){
            cout << "Error opening file" << endl;
            exit(EXIT_FAILURE);
        }

        string line;
        T a, b;
        int w;
        string s;

        while(getline(input, line)){
            istringstream iss(line);

            getline(iss, s, ',');
            stringstream ca(s);
            ca >> a;
            getline(iss, s, ',');
            stringstream cb(s);
            cb >> b;
            getline(iss, s, ',');
            w = stoi(s);
            g.addEdge(a,b,w);
        }
        input.close();
        return g;
    }

    void printEdges(){
        for(int i = 0; i < count; i++){
            cout << vertices[i]->vertexName << ": ";
            if(!vertices[i]->adjacencies.empty()) {
                for(auto it = vertices[i]->adjacencies.begin(); it != vertices[i]->adjacencies.end(); it++){
                    cout << (*it).vertex->vertexName << ", ";
                }
            }
            cout << endl;
        }
    }

    void exportDot(const string& filename){
        ofstream output;
        output.open(filename);

        output << "digraph {\n";
        for(int i = 0; i < count; i++){
            if(!vertices[i]->adjacencies.empty()) {
                for (auto it = vertices[i]->adjacencies.begin(); it != vertices[i]->adjacencies.end(); it++) {
                    output << "\t" << vertices[i]->vertexName << " -> " << (*it).vertex->vertexName << "[label=\"" << (*it).weight << "\"]"
                           << ";" << endl;
                }
            }
        }
        output << "}" << endl;
        output.close();
    }

    Vertex<T>* getVertex(T value){
        for(int i = 0; i < count; i++){
            if(vertices[i]->vertexName == value) return vertices[i];
        }
        return nullptr;
    }

    void initializeSingleSource(Vertex<T>* v){
        for(int i = 0; i < count; i++){
            vertices[i]->d = INT_MAX;
            vertices[i]->parent = nullptr;
        }
        v->d = 0;
    }

    void relax(Vertex<T>* u, Vertex<T>* v, int w){
        if(u->d != INT_MAX && v->d > u->d + w){
            v->d = u->d + w;
            v->parent = u;
        }
    }

    Result<T> bellmanFord(Vertex<T>* s){
        initializeSingleSource(s);

        Vertex<T>* v;
        Vertex<T>* u;
        int w;

        for(int c = 0; c < count; c++){
            for(int i = 0 ; i < count; i++){
                for(int j = 0 ; j < vertices[i]->adjacencies.size(); j++){
                    u = vertices[i];
                    v = vertices[i]->adjacencies[j].vertex;
                    w = vertices[i]->adjacencies[j].weight;
                    relax(u, v, w);
                }
            }
        }

        Result<T> result;
        for(int i = 0 ; i < count; i++){
            result.distances.insert(pair<Vertex<T>*,int>(vertices[i],vertices[i]->d));
            result.parents.insert(pair<Vertex<T>*,Vertex<T>*>(vertices[i],vertices[i]->parent));
        }

        for(int i = 0 ; i < count; i++){
            for(int j = 0 ; j < vertices[i]->adjacencies.size(); j++){
                u = vertices[i];
                v = vertices[i]->adjacencies[j].vertex;
                w = vertices[i]->adjacencies[j].weight;

                if(u->d != INT_MAX && v->d > u->d + w){
                    result.pathFound = false;
                    return result;
                }
            }
        }
        result.pathFound = true;
        return result;
    }
};

int main(int argc, char* argv[]) {
    string filename;
    int startVertex;

    if(argc != 3){
        cout << "Podano nieprawidlowa liczbe argumentow" << endl;
        exit(EXIT_FAILURE);
    }
    filename = argv[1];
    startVertex = stoi(argv[2]);

    Graph<int> g = g.readGraph(filename);
    Vertex<int>* start  = g.getVertex(startVertex);

    Result res = g.bellmanFord(start);
    res.printResult();

    //cout << endl;
    //Vertex<int>* end  = g.getVertex(15);
    //res.printPath(start,end);
}