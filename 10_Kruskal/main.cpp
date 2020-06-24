#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <fstream>
#include <iomanip>
#include "Set.cpp"

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
    Vertex<T>* start, *end;
    int weight;
    Edge(Vertex<T>* start, Vertex<T>* end, int weight): start(start), end(end), weight(weight) {}
};

template <typename T>
struct Graph {
    vector<Vertex<T>*> vertices;
    int count;
    vector<Edge<T>*> edges;

    Graph() {
        count = 0;
    }
    void addEdge(T a, T b, int weight) {
        bool foundA = false;
        bool foundB = false;
        Vertex<T> *vA, *vB;

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

        Edge<T>* eAB = new Edge<T>(vA,vB,weight);
        //Edge<T>* eBA = new Edge<T>(vB,vA,weight);
        edges.emplace_back(eAB);
        //edges.emplace_back(eBA);
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
            //  GRAF NIESKIEROWANY ZROBIC
        }
        input.close();
        return g;
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

    Vertex<T> *getVertex(T value) {
        for (int i = 0; i < count; i++) {
            if (vertices[i]->vertexName == value) return vertices[i];
        }
        return nullptr;
    }

    vector<Set<int,T>> sets;

    void makeSet(Vertex<T>* v){
        Set<int,T> s(count);
        s.insert(v->vertexName);
        sets.push_back(s);
    }

    int findSet(Vertex<T>* v){
        for(int i = 0; i < sets.size(); i++){
            if(sets.at(i).isMember(v->vertexName)) return i;
        }
        return -1;
    }

    Set<int,T> makeUnion(Set<int,T>* s1, Set<int,T>* s2){
        Set<int,T> s3 = s1->getUnion(s2);
        return s3;
    }

    void addVertex(Vertex<T>* v){
        vertices.emplace_back(v);
    }

    void addEdge(Edge<T>* e){
        edges.emplace_back(e);
    }

    void exportCSV(const string& filename){
        int sum = 0;

        ofstream output;
        output.open(filename);
        for(int i = 0; i < edges.size(); i++){
            output << edges[i]->start->vertexName << "," << edges[i]->end->vertexName << "," << setprecision(1) << fixed << 1.0*edges[i]->weight << endl;
            sum += edges[i]->weight;
        }
        cout << "Sum: " << sum << endl;
        output.close();
    }

    Graph<T> kruskal(const string& filename) {
        Graph<T> result;
        for (int i = 0; i < vertices.size(); i++) {
            makeSet(vertices.at(i));
            result.addVertex(vertices.at(i));
        }

        sort(edges.begin(), edges.end(), [](Edge<T> *e1, Edge<T> *e2) {
            return e1->weight < e2->weight;
        });

        for (int i = 0; i < edges.size(); i++) {
            int istart = findSet(edges.at(i)->start);
            int iend = findSet(edges.at(i)->end);
            if (istart < 0 || iend < 0) continue;
            auto s1 = sets.at(istart);
            auto s2 = sets.at(iend);

            if (istart != iend) {
                auto s12 = makeUnion(&s1, &s2);
                result.addEdge(edges.at(i));
                sets.erase(sets.begin() + istart);
                if (iend > istart) iend--;
                sets.erase(sets.begin() + iend);
                sets.push_back(s12);
            }
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    string filename;
    string output_filename;

    //filename = "graphs/100.csvo";
    //output_filename = "output.csv";

    if(argc != 3){
        cout << "Podano nieprawidlowa liczbe argumentow" << endl;
        exit(EXIT_FAILURE);
    }
    filename = argv[1];
    output_filename = argv[2];

    Graph<int> g = g.readGraph(filename);
    auto result = g.kruskal(output_filename);
    result.exportCSV(output_filename);
}