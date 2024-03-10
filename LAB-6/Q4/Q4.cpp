# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Graph{
    int size;
    list <int>* arr;

    Graph(int v){
        this->size = v;
        arr = new list<int>[v];
    }

    void addEdge(int u, int v){
        arr[u].push_back(v);
    }
};

vector <int> TopoSort(Graph &g){        // Kahn's algorithm => O(V+E) time complexity.
    int n = g.size;
    vector <int> res;
    vector <int> indegree(n, 0);
    for(int i=0; i<n; i++){
        for(auto it:g.arr[i]){
            indegree[it]++;
        }
    }

    queue <int> q;
    for(int i=0; i<n; i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v:g.arr[u]){
            indegree[v]--;
            if(indegree[v] == 0){
                q.push(v);
            }
        }
        res.push_back(u);
    }  
    return res;
}

bool isLoopTopo(Graph &g){
    int n = g.size;
    vector <int> topo = TopoSort(g);
    return (topo.size() != n);
}

bool DFSRec(Graph &g, int src, vector <bool> &visited, vector <bool> &recSt){
    visited[src] = true;
    recSt[src] = true;

    for(auto u:g.arr[src]){
        if(!visited[u]){
            DFSRec(g, u, visited, recSt);
        }
        else if(recSt[u]){
            return true;
        }
    }
    recSt[src] = false;
    return false;
}

bool isLoopDFS(Graph &g){
    int n = g.size;
    vector <bool> visited(n, false);
    vector <bool> recSt(n, false);

    for(int i=0; i<n; i++){
        if(!visited[i]){
            if(DFSRec(g, i, visited, recSt)){
                return true;
            }
        }
    }
return false;
}

int main(){
    freopen("input_Q4.txt", "r", stdin);
    freopen("output_Q4.txt", "w", stdout);
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
        
        // Graph g(4);
        // g.addEdge(0, 1);
        // g.addEdge(0, 2);
        // g.addEdge(1, 2);
        // g.addEdge(2, 0);
        // g.addEdge(2, 3);
        // g.addEdge(3, 3);

        auto start1 = high_resolution_clock::now(); // Start time
        if(isLoopTopo(g)){
            cout<<"Loop exists."<<endl;
        }
        else{
            cout<<"Loop does not exist."<<endl;
        }
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration1 = duration_cast<microseconds>(stop1 - start1);

        auto start2 = high_resolution_clock::now(); // Start time
        bool iscycle = isLoopDFS(g);
        auto stop2 = high_resolution_clock::now(); // Stop time
        auto duration2 = duration_cast<microseconds>(stop2 - start2);

        cout<<"The time taken by Topo-Sort method is: "<<duration1.count()<<" microseconds."<<endl;      
        cout<<"The time taken by DFS method is: "<<duration2.count()<<" microseconds."<<endl;    
    }  

    fclose(stdin);
    fclose(stdout);  
return 0;
}