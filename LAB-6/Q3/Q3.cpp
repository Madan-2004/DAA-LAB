# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Graph{
    int size;
    list <int>* arr;

    Graph(int v){
        this->size = v;
        arr = new list <int>[v];
    }

    void addEdge(int u, int v){
        arr[u].push_back(v);
    }
};

void DFS(Graph &g, stack <int> &s, int src, vector <bool> &visited){
    visited[src] = true;

    for(auto v:g.arr[src]){
        if(!visited[v]){
            DFS(g, s, v, visited);
        }
    }

    s.push(src);
}

Graph Transpose(Graph &g){
    Graph g_t(g.size);
    for(int i=0; i<g.size; i++){
        for(auto v:g.arr[i]){
            g_t.addEdge(v, i);
        }
    }
    return g_t;
}

void DFS_SCC(Graph &g_t, vector <bool> &visited_t, int src){
    visited_t[src] = true;
    cout<<src<<" ";

    for(auto v:g_t.arr[src]){
        if(!visited_t[v]){
            DFS_SCC(g_t, visited_t, v);
        }
    }
}

void SCC(Graph &g){
    Graph g_t = Transpose(g);

    vector<bool> visited(g.size, false), visited_t(g_t.size, false);
    stack<int> s;

    for(int i = 0; i < g.size; i++){
        if(!visited[i]){
            DFS(g, s, i, visited);
        }
    }

    cout << "The Strongly Connected Components are: " << endl;
    while(!s.empty()){
        int u = s.top();
        s.pop();
        if(!visited_t[u]){ // Use visited_t array for checking visited vertices in g_t
            DFS_SCC(g_t, visited_t, u);
            cout << endl;
        }
    }
}


int main(){
    freopen("input_Q3.txt", "r", stdin);
    freopen("output_Q3.txt", "w", stdout);
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
            g.addEdge(u,v);
        }

        // Graph g(5);
        // g.addEdge(0, 2);
        // g.addEdge(0, 3);
        // g.addEdge(1, 0);
        // g.addEdge(2, 1);
        // g.addEdge(3, 4);

        auto start1 = high_resolution_clock::now(); // Start time
        SCC(g);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);

        cout<<"The time taken by this program is: "<<duration.count()<<" microseconds."<<endl; 
    }

    fclose(stdin);
    fclose(stdout);       
return 0;
}