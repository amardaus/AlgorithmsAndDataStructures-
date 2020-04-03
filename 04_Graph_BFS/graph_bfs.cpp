#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <queue>

using namespace std;

struct Edge;

enum Color { white, gray, black };
struct Vertex{
public:
    char vertexName;
    vector<Edge> adjacencies;
    Vertex() {}
    Vertex(char vertexName) : vertexName(vertexName) {}

    //BFS
    Color color;
    int distance;
    Vertex* parent;
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

struct Edge{
    Vertex* vertex;
    int weight;

    Edge(Vertex* vertex, int weight): vertex(vertex), weight(weight) {}
};

struct Graph;
Graph BFS(Graph graph, char start);

struct Graph{
    int n;
    Vertex** vertices;
    int count;

    Graph(int n){
        this->n = n;
        vertices = new Vertex*[n];
        count = 0;
    }

    void setDistance(char name, int distance){
        for(int i = 0; i < count; i++){
            if(vertices[i]->vertexName == name) {
                vertices[i]->distance = distance;
            }
        }
    }

    void setParent(char name, Vertex* parent){
        for(int i = 0; i < count; i++){
            if(vertices[i]->vertexName == name) {
                vertices[i]->parent = parent;
            }
        }
    }

    void addEdge(char a, char b, int weight){
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
            Vertex* v1 = new Vertex(a);
            this->vertices[count] = v1;
            iA = count;
            count++;
        }

        Vertex* v2;

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

    void printBFS(){
        for(int i = 0; i < count; i++){
            cout << vertices[i]->vertexName << vertices[i]->distance << ": ";
            if(!vertices[i]->adjacencies.empty()) {
                for(auto it = vertices[i]->adjacencies.begin(); it != vertices[i]->adjacencies.end(); it++){
                    cout << (*it).vertex->vertexName << (*it).vertex->distance << ", ";
                }
            }
            cout << endl;
        }
    }

    void printParents(){
        for(int i = 0; i < count; i++) {
            cout << vertices[i]->vertexName << "| distance: " << vertices[i]->distance;
            if(vertices[i]->parent != nullptr){
                cout << "| parent: " << vertices[i]->parent->vertexName;
            }
            cout << endl;
        }
    }

    int findIndex(Graph g, char c){
        for(int i = 0; i < g.count; i++){
            if(c == g.vertices[i]->vertexName) return i;
        }
        return -1;
    }

    vector<char> getPath(char start, char end){
        Graph bfs = BFS(*this, start);

        Vertex* s = nullptr;
        Vertex* e = nullptr;
        for(int i = 0; i < bfs.n; i++){
            if(start == bfs.vertices[i]->vertexName) s =  bfs.vertices[i];
            if(end == bfs.vertices[i]->vertexName) e =  bfs.vertices[i];
        }


        vector<char> v;
        Vertex* tmp = e;
        v.push_back(tmp->vertexName);

        while(s->vertexName != tmp->vertexName){
            tmp = tmp->parent;
            v.push_back(tmp->vertexName);
        }

        return v;
    }

    int getHops(char start, char end){
        Graph bfs = BFS(*this, start);
        int i = findIndex(bfs, end);
        if(i < 0) return i;
        return bfs.vertices[i]->distance;
    }
};

Graph BFS(Graph graph, char start){
    int startindex = 0;

    for (int i = 0; i < graph.n; i++) {
        if (graph.vertices[i]->vertexName != start) {
            graph.vertices[i]->color = white;
            graph.vertices[i]->distance = INT_MAX;
            graph.vertices[i]->parent = nullptr;
        }
        else{
            startindex = i;
        }
    }

    queue<Vertex*> queue;
    queue.push(graph.vertices[startindex]);
    graph.vertices[startindex]->color = gray;
    graph.vertices[startindex]->distance = 0;
    graph.vertices[startindex]->parent = nullptr;

    Graph bfsGraph = Graph(graph.n);


    while (!queue.empty()) {
        Vertex* u = queue.front();
        queue.pop();

        for (int i = 0; i < u->adjacencies.size(); i++) {

            if(u->adjacencies[i].vertex->color == white){
                u->adjacencies[i].vertex->color = gray;
                u->adjacencies[i].vertex->distance = u->distance + 1;
                u->adjacencies[i].vertex->parent = u;
                bfsGraph.addEdge(u->vertexName, u->adjacencies[i].vertex->vertexName,1);
                bfsGraph.setDistance(u->adjacencies[i].vertex->vertexName, u->adjacencies[i].vertex->distance);
                bfsGraph.setParent(u->adjacencies[i].vertex->vertexName, u);
                queue.push(u->adjacencies[i].vertex);
            }
        }
        u->color = black;
    }
    return bfsGraph;
}

Graph readGraph(const string& filename, int n){
    Graph g = Graph(n);

    ifstream input;
    input.open(filename);

    if(!input){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    char a, b;
    int w;
    string s;

    while(getline(input, line)){
        istringstream iss(line);

        getline(iss, s, ',');
        a = s[0];
        getline(iss, s, ',');
        b = s[0];
        getline(iss, s, ',');
        w = stoi(s);
        g.addEdge(a,b,w);
    }
    input.close();
    return g;
}

int main(int argc, char* argv[]) {
    int n;
    string filename;

    if(argc < 4){
        cout << "Podano za malo argumentow" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Podaj liczbe wierzcholkow: ";
    cin >> n;

    filename = argv[1];
    Graph g = readGraph(filename, n);

    int a = argc-2;
    char start = argv[2][0];

    for(int i = 1; i < a; i++){
        cout << g.getHops(start, argv[i+2][0]) << " ";
        // nazwy wierzcholkow to pojedyncze znaki char
    }

    return 0;
}