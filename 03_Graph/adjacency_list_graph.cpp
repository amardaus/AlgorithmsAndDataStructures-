#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Graph{

private:
    int N;
    vector<pair<int,int>>* arr;

public:

    Graph(int N){
        N++;
        this->N = N;
        arr = new vector<pair<int,int>>[N];
    }

    void addEdge(int a, int b, int weight){
        arr[a].emplace_back(b, weight);
    }

    void printEdges(){
        for(int i = 0; i < N; i++){
            if(!arr[i].empty()){
                for(auto it = arr[i].begin(); it != arr[i].end(); it++){
                    cout << i << " -> " << (*it).first << " [" << (*it).second << "]" << endl;
                }
            }
        }
    }

    bool isRegular(int d){
        int* e = new int[N];
        for (int i = 0; i < N; i++) {
            e[i] = 0;
        }

        for(int i = 0; i < N; i++){
            for(auto it = arr[i].begin(); it != arr[i].end(); it++){
                e[i]++;
                e[(*it).first]++;
            }
        }

        for(int i = 1; i < N; i++){
            if(e[i] != d) return false;
        }
        return true;
    }

    void exportDot(const string& filename){
        ofstream output;
        output.open(filename);

        output << "digraph {\n";
        for(int i = 0; i < N; i++){
            if(!arr[i].empty()){
                for(auto it = arr[i].begin(); it != arr[i].end(); it++){
                    output << "\t" << i << " -> " << (*it).first << "[label=\"" << (*it).second << "\"]" <<  ";" << endl;
                }
            }
        }
        output << "}" << endl;
        output.close();
    }
};

Graph readGraph(const string& filename, int n){
    Graph* g = new Graph(n);

    ifstream input;
    input.open(filename);

    if(!input){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int abw[3];

    while(getline(input, line)){
        istringstream iss(line);

        for(int i = 0; i < 3; i++){
            string s;
            getline(iss, s, ',');
            abw[i] = stoi(s);
        }
        g->addEdge(abw[0], abw[1], abw[2]);
    }
    input.close();
    return *g;
}

int main() {
    int n;
    string filename;

    cout << "Podaj liczbe wierzcholkow: ";
    cin >> n;

    cout << "Podaj nazwe pliku: ";
    cin >> filename;

    Graph g = readGraph(filename, n);
    //g.printEdges();
    g.exportDot("graph.dot");
    cout << g.isRegular(9);

    return 0;
}