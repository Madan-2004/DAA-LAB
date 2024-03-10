# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Graph{
    int size;
    list <pair<int,int>>* arr;

    Graph(int v){
        this->size = v;
        arr = new list <pair<int,int>>[v];
    }

    void addEdge(int u, int v, int wt){
        arr[u].push_back({v, wt});
    }
};

vector <int> TopoSort(Graph& g){
    int n = g.size;
    vector <int> toposort, indegree(n, 0);

    for(int i=0; i<n; i++){
        for(auto it:g.arr[i]){
            indegree[it.first]++;
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
        toposort.push_back(u);
        for(auto it:g.arr[u]){
            indegree[it.first]--;
            if(indegree[it.first] == 0){
                q.push(it.first);
            }
        }
    }

    return toposort;
}

vector <int> Longest_Distance(Graph& g, vector <int>& topo_sort){
    int n = g.size;
    vector <int> dist(n, INT_MIN);

    vector <int> indegree(n, 0);

    for(int i=0; i<n; i++){
        for(auto it:g.arr[i]){
            indegree[it.first]++;
        }
    }

    for(int i=0; i<n; i++){
        if(indegree[i] == 0){
            dist[i] = 0;
        }
    }


    for(int i=0; i<n; i++){
        int u = topo_sort[i];
        for(auto it:g.arr[u]){
            if(dist[it.first] < it.second + dist[u]){
                dist[it.first] = it.second + dist[u];
            }
        }
    }

    return dist;
}

int main(){
    freopen("input_Q2.txt", "r", stdin);
    freopen("output_Q2.txt", "w", stdout);
    int t;
    cin>>t;
    while(t--){
        int n, edge;
        cin>>n>>edge;
        int u, v, wt;
        Graph g(n);
        wt = 1;

        for(int i=0; i<edge; i++){
            cin>>u>>v;
            u--;
            v--;
            g.addEdge(u, v, wt);
        }

        // Graph g(6); 
        // g.addEdge(0, 1, 5); 
        // g.addEdge(0, 2, 3); 
        // g.addEdge(1, 3, 6); 
        // g.addEdge(1, 2, 2); 
        // g.addEdge(2, 4, 4); 
        // g.addEdge(2, 5, 2); 
        // g.addEdge(2, 3, 7); 
        // g.addEdge(3, 5, 1); 
        // g.addEdge(3, 4, -1); 
        // g.addEdge(4, 5, -2); 
    
        // int src = 1; 

        auto start1 = high_resolution_clock::now(); // Start time
        vector <int> topo_sort = TopoSort(g);

        vector <int> long_dist = Longest_Distance(g, topo_sort);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);

        int long_distance = INT_MIN;

        for(int i=0; i<n; i++){
            long_distance = max(long_distance, long_dist[i]);
        }
        cout<<long_distance<<endl;

        cout<<"The time taken by the Longest Path Algorithm is: "<<duration.count()<<" microseconds."<<endl;
    }
            
    fclose(stdin);
    fclose(stdout);  
return 0;
}