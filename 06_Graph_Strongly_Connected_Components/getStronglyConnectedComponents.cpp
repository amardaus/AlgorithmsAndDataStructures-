#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>

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

    bool operator<(const Vertex& v){
        return this->distance < v.distance;
    }
    bool operator>(const Vertex& v){
        return this->distance > v.distance;
    }
    bool operator==(const Vertex& v){
        return this->distance == v.distance;
    }

    //DFS
    Color color;
    Vertex* parent = nullptr;
    int startTime = 0, endTime = 0;
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
    vector<Vertex<T>*> sortedVertices;

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

    void printSorted(){
        for(int i = 0; i < sortedVertices.size(); i++){
            cout << sortedVertices[i]->vertexName << sortedVertices[i]->endTime << ": ";
            if(!sortedVertices[i]->adjacencies.empty()) {
                for(auto it = sortedVertices[i]->adjacencies.begin(); it != sortedVertices[i]->adjacencies.end(); it++){
                    cout << (*it).vertex->vertexName << ", ";
                }
            }
            cout << endl;
        }
    }

    Graph<T> transposeGraph(){
        int n = this->n;
        Graph<T> g2 = Graph<T>(n);
        for(int i = 0; i < count; i++){
            for(int iv = 0; iv < this->vertices[i]->adjacencies.size(); iv++){
                g2.addEdge(this->vertices[i]->adjacencies[iv].vertex->vertexName, this->vertices[i]->vertexName, 1);
            }
        }
        return g2;
    }
};

int xtime = 0;

template <typename T>
vector<Vertex<T>*> DFS(Graph<T> g, bool saveResult){
    xtime = 0;

    vector<Vertex<T>*> tmp = g.sortedVertices;
    g.sortedVertices.clear();

    for(int i = 0; i < g.count; i++){
        g.vertices[i]->color = white;
        g.vertices[i]->parent = nullptr;
    }

    vector<Vertex<T>*> connectedCompontents;
    for(int i = 0; i < tmp.size(); i++){
        if(tmp[i]->color == white){
            if(saveResult)
            {
                cout << "[" << tmp[i]->vertexName;
                connectedCompontents.push_back(tmp[i]);
                visitDFS(g, tmp[i], true);
            }
            else{
                visitDFS(g, tmp[i], false);
            }
            if(saveResult) { cout << "] "<< endl; }
        }
    }
    return connectedCompontents;
}

template <typename T>
void visitDFS(Graph<T> g, Vertex<T>* u, bool print){
    xtime++;
    u->startTime = xtime;
    u->color = gray;

    for(int j = 0; j < u->adjacencies.size(); j++){
        if(u->adjacencies[j].vertex->color == white){
            u->adjacencies[j].vertex->parent = u;
            if(print) cout << " " << u->adjacencies[j].vertex->vertexName;
            visitDFS(g, u->adjacencies[j].vertex, print);
        }
    }
    u->color = black;
    xtime++;
    u->endTime = xtime;
    g.sortedVertices.push_back(u);
}

template<typename T>
int getStronglyConnectedComponentsCount(Graph<T> g){
    for(int i = 0; i < g.count; i++){
        g.sortedVertices.push_back(g.vertices[i]);
    }
    DFS(g, false);
    std::sort(g.sortedVertices.begin(), g.sortedVertices.end(), [](Vertex<T>* v1, Vertex<T>* v2){
        return v1->endTime > v2->endTime;
    });

    Graph<T> gT = g.transposeGraph();
    for(int i = 0; i < g.count; i++){
        for(int j = 0; j < g.count; j++){
            if(gT.vertices[j]->vertexName == g.sortedVertices[i]->vertexName){
                gT.sortedVertices.push_back(gT.vertices[j]);
                break;
            }
        }
    }
    vector<Vertex<T>*> connectedComponents = DFS(gT, true);
    return connectedComponents.size();
}

template<typename T>
void getStronglyConnectedComponents(Graph<T> g){
    for(int i = 0; i < g.count; i++){
        g.sortedVertices.push_back(g.vertices[i]);
    }
    DFS(g,false);
    std::sort(g.sortedVertices.begin(), g.sortedVertices.end(), [](Vertex<T>* v1, Vertex<T>* v2){
        return v1->endTime > v2->endTime;
    });

    Graph<T> gT = g.transposeGraph();
    for(int i = 0; i < g.count; i++){
        for(int j = 0; j < g.count; j++){
            if(gT.vertices[j]->vertexName == g.sortedVertices[i]->vertexName){
                gT.sortedVertices.push_back(gT.vertices[j]);
                break;
            }
        }
    }
    vector<Vertex<T>*> connectedComponents = DFS(gT, true);
}

int main(int argc, char* argv[]) {
    int n;
    string filename;

    filename = "graph1.csv";
    n = 500;
    Graph<int> g(n);
    g = g.readGraph(filename, n);
    getStronglyConnectedComponents(g);

    return 0;
}
