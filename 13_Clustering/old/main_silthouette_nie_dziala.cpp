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
#include <climits>

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

    map<int,vector<int>> getClusters(vector<int> roots){
        map<int,vector<int>> clusters;

        for(int i = 0; i < roots.size(); i++){
            int initial = roots.at(i);
            vector<int> vect = {};
            clusters.insert({initial, vect});
        }

        for(int j = 0; j < n; j++){
            clusters[findSet(parents[j])].push_back(j);
        }
        return clusters;
    }

    void printClusters(map<int,vector<int>> clusters){
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

    int* parents{};
    int* ranks{};

    void initializeArrays(){
        parents = new int[n];
        ranks = new int[n];
        for(int i = 0; i < n; i++){
            parents[i] = i;
            ranks[i] = 0;
        }
    }

    void MST(int K){
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
        auto clusters = getClusters(getRoots());
        cout << silthouette(clusters);
    }

    double euclideanDistance(int a, int b){
        return sqrt(pow(points[a].x-points[b].x,2) + pow(points[a].y-points[b].y,2));
    }

    double silthouette(map<int,vector<int>> clusters){
        int k = 0;
        int K = clusters.size();

        double ai[n];
        for(auto it = clusters.cbegin(); it != clusters.cend(); ++it)
        {
            double dsum = 0;
            int ccount = it->second.size();
            for(int a = 0; a < ccount; a++){
                dsum = 0;
                for(int b = 0; b < ccount; b++){
                    if(it->second[a] != it->second[b]) {
                        dsum += euclideanDistance(it->second[a], it->second[b]);
                    }
                }
                if(it->second.size() == 1)
                    ai[it->second[a]] = 0;
                else
                    ai[it->second[a]] = dsum/(ccount-1);
            }
            k++;
        }

        double bi[n];
        for(int i = 0; i < n; i++) bi[i] = INT_MAX;
        k = 0;
        for(auto currentCluster = clusters.cbegin(); currentCluster != clusters.cend(); ++currentCluster)
        {
            for(auto otherCluster = clusters.cbegin(); otherCluster != clusters.cend(); ++otherCluster){
                if(currentCluster != otherCluster){
                    double dsum = 0;
                    int ccountA = currentCluster->second.size();
                    int ccountB = otherCluster->second.size();
                    for(int a = 0; a < ccountA; a++){
                        dsum = 0;
                        for(int b = 0; b < ccountB; b++){
                            if(a != b) {
                                dsum += euclideanDistance(currentCluster->second[a], otherCluster->second[b]);
                            }
                        }
                        if(dsum/ccountB < bi[currentCluster->second[a]]) bi[currentCluster->second[a]] = dsum/ccountB;
                    }
                    k++;
                }
            }
        }

        double si[n];
        for(int i = 0; i < n; i++){
            if(ai[i] < bi[i]) si[i] = 1 - ai[i]/bi[i];
            else if(ai[i] == bi[i]) si[i] = 0;
            else si[i] = bi[i]/ai[i] - 1;
        }

        double s_mean = 0;
        for(int i = 0; i < n; i++){ s_mean += si[i]; }
        s_mean/=n;
        return s_mean;
    }

    void clusterize(){
        for(int K = 1; K < 6; K++){
            cout << "K = " << K << ": ";
            MST(K);
            cout << endl;
        }
        // COS JEST NIEPRAWIDLOWO LICZONE BO ZAWSZE DLA 1 I 2 WARTOSC JEST NAJWIEKSZA
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

    /*cout << "Podaj liczbe wierzcholkow: ";
    cin >> n;

    cout << "Podaj nazwe pliku: ";
    cin >> filename;*/

    filename = "data/data_4.csv";
    // POZBYC SIE SZUMOW - ROZMIAR KLASTRA NIE POWINIEN BYC 1, UWZGLEDNIC TO W SITHOULETTE SCOLE

    Graph g = readGraph(filename);
    g.clusterize();
    return 0;
}