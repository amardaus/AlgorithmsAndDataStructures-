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

    void linkSets(int x, int y){
        if(ranks[x] > ranks[y]){
            parents[y] = x;
        }
        else{
            parents[x] = y;
            if(ranks[x] == ranks[y]){
                ranks[y]++;
            }
        }
    }

    vector<int> getRoots(){
        vector<int> roots;
        for(int i = 0; i < n; i++){
            if(parents[i] == i)
                roots.push_back(i);
        }
        return roots;
    }

    void verify(map<int,vector<int>> clusters){
        int cs = clusters.size();
        vector<int> verifClusters[cs];

        for(auto it = clusters.cbegin(); it != clusters.cend(); ++it){
            if(points[it->first].label >= cs){
                cout << "Incorrect label" << endl;
                exit(0);
            }
            verifClusters[points[it->first].label] = it->second;
        }

        for(int i = 0; i < points.size(); i++){
            int label = points.at(i).label;
            bool ok = false;
            for(int j = 0; j < verifClusters[label].size(); j++){
                if(verifClusters[label][j] == i) ok = true;
            }
            if(!ok) {
                cout << "Incorrect label for point " << "(" << points.at(i).x << "," <<  points.at(i).y << ")" << endl;
                break;
            }
        }
    }

    map<int,vector<int>> clusters;
    void getClusters(vector<int> roots){
        for(int i = 0; i < roots.size(); i++){
            int initial = roots.at(i);
            vector<int> vect = {};
            clusters.insert({initial, vect});
        }

        for(int j = 0; j < n; j++){
            clusters[findSet(parents[j])].push_back(j);
        }

        ofstream output;
        output.open ("clusters.dat");
        int k = 0;
        for(auto it = clusters.cbegin(); it != clusters.cend(); ++it)
        {
            for(auto j = it->second.begin(); j < it->second.end(); j++){
                output << points[*j].x << " " << points[*j].y << " ";
                output << k << endl;
            }
            k++;
        }
        output.close();
    }

    void unionSets(int x, int y){
        int ix = findSet(x);
        int iy = findSet(y);
        linkSets(ix,iy);
    }

    int* parents;
    int* ranks;

    void initializeArrays(){
        parents = new int[n];
        ranks = new int[n];
        for(int i = 0; i < n; i++){
            parents[i] = i;
            ranks[i] = 0;
        }
    }

        void clusterize(int K, bool _verify){
        double** adjacencyMatrix = buildGraph();
        vector<Edge> edges;
        initializeArrays();

        for(int i = 0; i < n; i++){
            for(int j = 0; j < i + 1; j++){
                if(i != j) edges.emplace_back(i,j,adjacencyMatrix[i][j]);
            }
        }

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
            return a.weight < b.weight;
        });

        vector<Edge> clusterized_Edges;
        for(int i = 0; i < edges.size(); i++){
            int set1 = findSet(edges.at(i).start);
            int set2 = findSet(edges.at(i).end);
            if(set1 != set2){
                clusterized_Edges.push_back(edges.at(i));
                unionSets(edges.at(i).start, edges.at(i).end);
            }
            if(clusterized_Edges.size() == n-K) break;
        }
        auto roots = getRoots();
        getClusters(roots);
        if(_verify) verify(clusters);
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
    string filename;
    int K;
    cout << "Podaj K: ";
    cin >> K;

    cout << "Podaj nazwe pliku: ";
    cin >> filename;

    /*K = 3;
    filename = "data/data_3.csv";*/

    Graph g = readGraph(filename);
    g.clusterize(K,false);

    return 0;
}
