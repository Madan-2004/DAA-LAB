#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Graph {
    int size;
    list<int>* arr;

    Graph(int v) {
        this->size = v;
        arr = new list<int>[v];
    }

    void addEdge(int u, int v){
        arr[u].push_back(v);
        // arr[v].push_back(u); // Assuming the graph is undirected
    }
};

bool DFS_Bridge(Graph& g, vector<bool>& visited, int src, vector<int>& tin, vector<int>& low, int parent = -1) {
    static int timer = 0;
    timer++;
    visited[src] = true;
    tin[src] = low[src] = timer;

    for(auto u : g.arr[src]){
        if(!visited[u]){
            if(DFS_Bridge(g, visited, u, tin, low, src)){
                return true;
            }
            low[src] = min(low[src], low[u]);
            if (low[u] > tin[src]){
                return true;
            }
        }
        else if(u != parent){
            low[src] = min(low[src], tin[u]);
        }
    }
    return false;
}

bool isBridge(Graph& g) {
    int n = g.size;
    vector<bool> visited(n, false);
    vector<int> tin(n), low(n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (DFS_Bridge(g, visited, i, tin, low)) {
                return true;
            }
        }
    }
    return false;
}

bool DFS_Articulation(Graph &g, vector <bool> &visited, int src, vector <int> &tin, vector <int> &low, int parent = -1){
    static int timer = 0;
    timer++;
    visited[src] = true;
    tin[src] = low[src] = timer;
    int child = 0;
    bool isArticulation = false;

    for(auto u:g.arr[src]){
        if(!visited[u]){
            child++;
            if(DFS_Articulation(g, visited, u, tin, low, src)){
                isArticulation = true;
            }
            low[src] = min(low[src], low[u]);
            if(parent != -1 && low[u] >= tin[src]){
                isArticulation = true;
            }
        }
        else if(u != parent){
            low[src] = min(low[src], tin[u]);
        }
    }
    if(parent == -1 && child > 1){
        isArticulation = true;
    }
    if(isArticulation){
        return true;
    }
    return false;
}

bool isArticulationPoint(Graph &g){
    int n = g.size;
    vector <bool> visited(n, false);
    vector <int> tin(n), low(n);

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            if(DFS_Articulation(g, visited, i, tin, low)){
                return true;
            }
        }
    }
    return false;
}

int main(){
    freopen("input_Q5.txt", "r", stdin);
    freopen("output_Q5.txt", "w", stdout);
    int t;
    cin>>t;

    while(t--){
        int n, edge;
        cin>>n>>edge;
        
        Graph g(n);
        int u, v;
        for(int i=0; i<edge; i++){
            cin>>u>>v;
            u--;
            v--;
            g.addEdge(u, v);
        }
        // Graph g(3);
        // g.addEdge(0, 1);
        // g.addEdge(1, 2);
        // g.addEdge(2, 0);
        
        auto start1 = high_resolution_clock::now(); // Start time
        if(isBridge(g)){
            cout<<"Bridge: YES!"<<endl;
        }
        else{
            cout<<"Bridge: NO!"<<endl;
        }
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration1 = duration_cast<microseconds>(stop1 - start1);

        cout<<"The time taken for Bridge detection is: "<<duration1.count()<<" microseconds."<<endl;   

        auto start2 = high_resolution_clock::now(); // Start time
        if(isArticulationPoint(g)){
            cout<<"Articulation point: YES!"<<endl;
        }
        else{
            cout<<"Articulation point: NO!"<<endl;
        }
        auto stop2 = high_resolution_clock::now(); // Stop time
        auto duration2 = duration_cast<microseconds>(stop2 - start2);

        cout<<"The time taken for Articulation point detection is: "<<duration2.count()<<" microseconds."<<endl;   
    }

    fclose(stdin);
    fclose(stdout);        
return 0;
}
