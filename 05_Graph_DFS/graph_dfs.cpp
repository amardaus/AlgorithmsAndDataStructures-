#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

template <typename T>
struct Edge;

enum Color { white, gray, black };

template <typename T>
struct Vertex{
public:
    T vertexName;
    vector<Edge<T>> adjacencies;
    Vertex() {}
    Vertex(T vertexName) : vertexName(vertexName) {}

    //DFS
    Color color;
    Vertex* parent;
    int startTime, endTime;

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
struct Graph{
    int n;
    Vertex<T>** vertices;
    int count;

    Graph(int n){
        this->n = n;
        vertices = new Vertex<T>*[n];
        count = 0;
    }

    void addEdge(T a, T b, int weight){
        bool foundA = false;
        bool foundB = false;

        int iA = 0, iB = 0;
        for(int i = 0; i < count; i++){
            if(vertices[i]->vertexName == a) {
                foundA = true;
                iA = i;
            }
            if(vertices[i]->vertexName == b) {
                foundB = true;
                iB = i;
            }
        }

        if(!foundA) {
            Vertex<T>* v1 = new Vertex(a);
            this->vertices[count] = v1;
            iA = count;
            count++;
        }

        Vertex<T>* v2;

        if(!foundB) {
            v2 = new Vertex(b);
            this->vertices[count] = v2;
            iB = count;
            count++;
        }
        else{
            v2 = this->vertices[iB];
        }
        vertices[iA]->adjacencies.emplace_back(Edge(v2, weight));
    }


    Graph<T> readGraph(const string& filename, int n){
        Graph<T> g = Graph<T>(n);

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
        for(int i = 0; i < n; i++){
            cout << vertices[i]->vertexName << ": ";
            if(!vertices[i]->adjacencies.empty()) {
                for(auto it = vertices[i]->adjacencies.begin(); it != vertices[i]->adjacencies.end(); it++){
                    cout << (*it).vertex->vertexName << ", ";
                }
            }
            cout << endl;
        }
    }
};

int xtime = 0;
template <typename T>
vector<Vertex<T>*> sorted;

template <typename T>
void DFS(Graph<T> g){
    xtime = 0;
    sorted<T>.clear();

    for(int i = 0; i < g.count; i++){
        g.vertices[i]->color = white;
        g.vertices[i]->parent = nullptr;
    }

    for(int i = 0; i < g.count; i++){
        if(g.vertices[i]->color == white){
            visitDFS(g, g.vertices[i]);
        }
    }
}

template <typename T>
void visitDFS(Graph<T> g, Vertex<T>* u){
    xtime++;
    u->startTime = xtime;
    u->color = gray;

    for(int j = 0; j < u->adjacencies.size(); j++){
        if(u->adjacencies[j].vertex->color == white){
            u->adjacencies[j].vertex->parent = u;
            visitDFS(g, u->adjacencies[j].vertex);
        }
    }
    u->color = black;
    xtime++;
    u->endTime = xtime;
    sorted<T>.push_back(u);
}

int main(int argc, char* argv[]) {
    int n;
    string filename;

    filename = "graph.csv";
    n = 6;
    Graph<char> g(6);
    g = g.readGraph(filename, n);
    DFS(g);
    for(int i = sorted<char>.size() - 1; i >= 0; i--){
        cout << sorted<char>.at(i)->vertexName << " ";
        /*if(sorted<char>.at(i)->parent){
            cout << " " << sorted<char>.at(i)->startTime << " ";
            cout << sorted<char>.at(i)->endTime << " " << sorted<char>.at(i)->parent->vertexName << endl;
        }else{
            cout << endl;
        }*/
    }
    //g.printEdges();
    return 0;
}
