#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Graph{

private:
    int N;
    int** arr;

public:

    Graph(int N){
        N++;
        this->N = N;
        arr = new int*[N];
        for(int i = 0; i < N; i++){
            arr[i] = new int[N];
        }
    }

    void addEdge(int a, int b, int weight){
        arr[a][b] = weight;
    }

    void printEdges(){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(arr[i][j] != 0){
                    cout << i << " -> " << j << " [" << arr[i][j] << "]" << endl;
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
            for(int j = 0; j < N; j++){
                if(arr[i][j] != 0){
                    e[i]++;
                }
                if(arr[i][j] != 0){
                    e[j]++;
                }
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
            for(int j = 0; j < N; j++){
                if(arr[i][j] != 0){
                    output << "\t" << i << " -> " << j << "[label=\"" << arr[i][j] << "\"]" <<  ";" << endl;
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