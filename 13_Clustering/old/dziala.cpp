#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <list>
#include <set>
#include <map>

using namespace std;

struct Point{
    double x;
    double y;
    int label;
    Point(double x, double y, int label): x(x), y(y), label(label){}
};

struct Graph{

private:
    vector<Point> points;
    int n;

public:

    Graph(){
        n = 0;
    }

    void addPoint(double x, double y, int label){
        points.emplace_back(x,y,label);
        n++;
    }

    void printPoints(){
        int n = points.size();
        for(int i = 0; i < n; i++){
            cout << points[i].x << endl;
        }
    }

    double** buildGraph(){
        double** adjacencyMatrix = new double*[n];
        for(int i = 0; i < n; i++){
            adjacencyMatrix[i] = new double[n];
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                adjacencyMatrix[i][j] = sqrt(pow(points[i].x-points[j].x,2) + pow(points[i].y-points[j].y,2));
            }
        }
        return adjacencyMatrix;
    }

    struct Edge{
        int start, end;
        double weight;
        Edge(int start, int end, double weight): start(start), end(end), weight(weight){}
    };

    int findSet(int x){
        if(x != parents[x])
            parents[x] = findSet(parents[x]);
        return parents[x];
    }

    bool isRoot(int x){
        return parents[x] == x;
    }

    int findRoot(int x){
        while(!isRoot(x)){
            x = parents[x];
        }
        return x;
    }

    void linkSets(int x, int y){
        /*if(sets.at(x).rank > sets.at(y).rank){
            sets.at(y).parent = x;
        }
        else{
            sets.at(x).parent = y;
            if(sets.at(x).rank == sets.at(y).rank){
                sets.at(y).rank++;
            }
        }*/

        parents[findRoot(x)] = findRoot(y);
    }

    vector<int> getRoots(){
        vector<int> roots;
        for(int i = 0; i < n; i++){
            if(parents[i] == i)
                roots.push_back(i);
        }
        return roots;
    }

    map<int,vector<int>> clusters;
    void clusterize(vector<int> roots){
        for(int i = 0; i < roots.size(); i++){
            int initial = roots.at(i);
            vector<int> vect = {};
            clusters.insert({initial, vect});
        }

        for(int j = 0; j < n; j++){
            clusters[findSet(parents[j])].push_back(j);
        }

        int k = 0;
        for(auto it = clusters.cbegin(); it != clusters.cend(); ++it)
        {
            for(auto j = it->second.begin(); j < it->second.end(); j++){
                std::cout << points[*j].x << " " << points[*j].y << " ";
                std::cout << k << endl;
            }
            cout << endl;
            k++;
        }
    }

    void unionSets(int x, int y){
        int ix = findSet(x);
        int iy = findSet(y);
        linkSets(ix,iy);
    }

    int* parents;
    /*
     *      PRZEROBIĆ NA IMPLEMENTACJĘ TABLICOWĄ TAK JAK OMÓWIONE NA STRONIE
     *
     *      https://flylib.com/books/en/2.300.1/disjoint_set_clusters.html
    */

    void MST(int K){
        double** adjacencyMatrix = buildGraph();
        vector<Edge> edges;

        parents = new int[n];
        for(int i = 0; i < n; i++){
            parents[i] = i;
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < i + 1; j++){
                if(i != j) edges.emplace_back(i,j,adjacencyMatrix[i][j]);
            }
        }

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
            return a.weight < b.weight;
        });

        vector<Edge> MST_Edges;
        for(int i = 0; i < edges.size(); i++){
            int set1 = findSet(edges.at(i).start);
            int set2 = findSet(edges.at(i).end);
            if(set1 != set2){
                MST_Edges.push_back(edges.at(i));
                unionSets(edges.at(i).start, edges.at(i).end);
            }
            if(MST_Edges.size() == n-K) break;
        }
        auto roots = getRoots();
        clusterize(roots);
    }
};

Graph readGraph(const string& filename){
    Graph g = Graph();

    ifstream input;
    input.open(filename);

    if(!input){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    double ab[2];
    int label;

    getline(input,line);

    while(getline(input, line)){
        istringstream iss(line);
        string s;
        getline(iss, s, ',');
        ab[0] = stod(s);
        getline(iss, s, ',');
        ab[1] = stod(s);
        getline(iss, s, ',');
        label = stoi(s);

        g.addPoint(ab[0], ab[1], label);
    }
    input.close();
    return g;
}

int main() {
    int N;
    string filename;

    /*cout << "Podaj liczbe wierzcholkow: ";
    cin >> n;

    cout << "Podaj nazwe pliku: ";
    cin >> filename;*/

    int K = 2;
    filename = "data/data_0.csv";

    Graph g = readGraph(filename);
    g.MST(K);
    return 0;
}